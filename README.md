CryptoAuthentication OpenSSL Engine
=====================================
Overview
----------
This is an OpenSSL Engine implementation using ATECC508A for ECC key storage, ECDSA sign/verify, ECDH, and FIPS Random Number Generator

The implementation integrates the [Atmel ATECC508A](http://www.atmel.com/devices/atecc508a.aspx) into the [OpenSSL ENGINE API](http://openssl.org/docs/manmaster/crypto/engine.html) to provide secure hardware key storage, [CAVP certified random numbers](http://csrc.nist.gov/groups/STM/cavp/documents/aes/aesval.html), P256 ECDSA & ECDH, and secure storage for data.

This project will integrate the key creation and import capabilities of the ATECC508A into the OpenSSL key creation and certificate creation process. 

Also, secure key storage for RSA keys are implemented using the encrypted read/write feature of the ATECC508A.

This repository provides two pieces of software:
* CryptoAuthLib: a C library to interact with the Atmel ATECC508A Cryptochip.
* ATECCX08 engine: a OpenSSL Engine that uses Cryptoauthlib to implement several OpenSSL operations using the cryptochip.

Note: The ATECCX08 engine is not supported in this release.

Supported Cipher Suites
------------------------
Many ECDH(E)-ECDSA and ECDHE-RSA cipher suites are supported with the OpenSSL Engine for ATECC508A implementation.  

Details for cipher suites can be found [here](https://github.com/AtmelCSO/cryptoauth-openssl-engine/wiki/Supported-Ciphers)

Download and Make 
------------------
This repository is compiled and integrated by Digi Embedded Yocto.

The **CryptoAuthLib** (included in *engine_atecc/cryptoauthlib*) can be compiled using
a Digi Embedded Yocto based toolchian.

The **ATECCX08 engine** (included in *engine_atecc/engine_meth*) requires to be compiled
within the OpenSSL project. This engine is not supported in the current release.

More information about [Digi Embedded Yocto](https://github.com/digi-embedded/meta-digi).

Platform Integration
--------------------
Follow the platform integration instructions found [here](https://github.com/AtmelCSO/cryptoauth-openssl-engine/wiki/Integrate-ATECC508A-onto-Your-Platform)

Unit Tests
-------------
Unit testing is provided for both integration of the ATECC508A device and OpenSSL Examples.  
For details see:
[Platform Integration Tests](https://github.com/AtmelCSO/cryptoauth-openssl-engine/wiki/ATECC508A-Integration-Tests)
[OpenSSL Engine Tests & Examples](https://github.com/AtmelCSO/cryptoauth-openssl-engine/wiki/Tests-And-Examples)

Source-Level Documentation
Full Doxygen source-level documentation is provided.
See: /docs/doxygen/html/index.html

Web Server Setup
-----------------
The OpenSSL Engine for ATECC508A can also be configured. 
See Details [here](https://github.com/AtmelCSO/cryptoauth-openssl-engine/wiki/Web-Server-For-The-Web-Browser).

Wiki Topics:
------------
- [Linux Development Setup](https://github.com/AtmelCSO/cryptoauth-openssl-engine/wiki/Linux:-Development-Setup)
- [Compiling on Linux](https://github.com/AtmelCSO/cryptoauth-openssl-engine/wiki/Linux:-Compile-OpenSSL-Engine-for-ATECC508A)
- [Debugging on Linux](https://github.com/AtmelCSO/cryptoauth-openssl-engine/wiki/Linux:-Debugging)
- [ATECC508A Integration](https://github.com/AtmelCSO/cryptoauth-openssl-engine/wiki/ATECC508A:-Platform-Integration)
- [ATECC508A Certificate Provisioning](http://www.atmel.com/tools/at88ckeccroot-signer.aspx)
- [Tests and Examples](https://github.com/AtmelCSO/cryptoauth-openssl-engine/wiki/Tests:-OpenSSL-Tests-and-Examples)


License
---------

Copyright (c) 2015 Atmel Corporation. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

 3. The name of Atmel may not be used to endorse or promote products derived
    from this software without specific prior written permission.

 4. This software may only be redistributed and used in connection with an
    Atmel integrated circuit.

THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
XPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.


Copyright (C) 2017 Digi International Inc, All Rights Reserved.

This software is provided as instructional material without charge
by Digi International for use by its employees and customers
subject to the following terms.

PERMISSION
Permission is hereby granted, free of charge, to any person obtaining
a copy of this software, to deal with it without restriction,
including without limitation the rights to use, copy,  modify, merge,
publish, distribute, sublicense, and/or sell copies of it, and to permit
persons to whom it is furnished to do so, provided the above copyright
notice and this permission notice are included in all derived works
and the use of this software is restricted to Digi products.

WARRANTY
THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, OR NONINFRINGEMENT.

LIABILITY
IN NO EVENT SHALL DIGI INTERNATIONAL BE LIABLE FOR ANY CLAIM, DAMAGES,
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT, OR OTHERWISE,
ARISING FROM, OUT OF, OR IN CONNECTION WITH THE SOFTWARE, OR THE USE
OR OTHER DEALINGS WITH THE SOFTWARE.