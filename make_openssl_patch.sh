#!/bin/bash

if [ ! -d "$1" ]; then
	echo "Use: ${0} <OpenSSL project directory>"
	echo " where <dir> is the clean OpenSSL project directory, as it is in"
	echo " the repository (without the objets from compilation, etc)"
	exit 1
fi

THIS_SCRIPT="$(basename ${BASH_SOURCE})"
THIS_DIR="$(cd $(dirname ${BASH_SOURCE}) && pwd)"

TEMP_DIR="$(mktemp -d)"
ENGINE_PATH="${THIS_DIR}/engine_atecc"
GIT_REVISION="$(cd ${THIS_DIR}; git rev-parse --verify --short=7 HEAD 2>/dev/null)"
PATCH_COMMIT_MESSAGE="import ateccx08 engine

Patch auto generated from cryptauth-openssl-engine repository.
Git revision: ${GIT_REVISION}"

# Create a new repository and copy the OpenSSL working directory.
(cd "${TEMP_DIR}" && git init) > /dev/null 2>&1
cp -a "${1}/." "${TEMP_DIR}"
(cd "${TEMP_DIR}" && git add . && git commit -sam "Initial commit") > /dev/null 2>&1

# 1) Add the CryptoAuth OpenSSL Engine
mkdir -p "${TEMP_DIR}/engines/ateccx08"
cp -a "${ENGINE_PATH}/." "${TEMP_DIR}/engines/ateccx08"

# Skip binary files (use the .gitignore from the project)
cp "${THIS_DIR}/.gitignore" "${TEMP_DIR}"

# Skip .pdf files (they are binary but not in the gitignore)
find "${TEMP_DIR}" -name "*.pdf" -exec rm {} \;

# 2) Remove 'cryptoauthlib' dir. (should use the one in the SDK)
rm -rf "${TEMP_DIR}/engines/ateccx08/cryptoauthlib"

# 3) Modify Makefile to include the new engine
sed -i -e 's/ENGDIRS= ccgost/ENGDIRS= ccgost ateccx08/g' "${TEMP_DIR}/Makefile.org"

# Create a commit to get the patch
(
	cd "${TEMP_DIR}";
	git add .;
	git commit -sam "${PATCH_COMMIT_MESSAGE}";
	git format-patch -1 -o "${THIS_DIR}";
) > /dev/null 2>&1

# Remove first line from the patch
TMP_FILE="$(mktemp patch.XXXXXXXX)"
PATCH_FILE="$(find ${THIS_DIR} -name 0001-*.patch)"
sed '1d' "${PATCH_FILE}" > "${TMP_FILE}"
mv "${TMP_FILE}" "${PATCH_FILE}"

