RSCODE version 1.3-bsail-0.1
===============

[![Build Status](https://img.shields.io/travis/bsail/rscode/master.svg)](https://travis-ci.org/bsail/rscode)
[![Coverage Status](https://img.shields.io/coveralls/github/bsail/rscode/master.svg)](https://coveralls.io/github/bsail/rscode?branch=master)

Library to encode and decode messages using Reed-Solomon codes.
Licensed under GNU General Public License Version 3.

Fork of original library by [Henry Minsky](https://github.com/hqm/rscode).
Several Galois functions were written by [James S. Plank](http://web.eecs.utk.edu/~plank/plank/papers/CS-07-593/)
This version differs from original version: we significantly reduced the memory consumption.

[Latest version of the library](https://github.com/bsail/rscode)

Library Setup
---------------

User must create additional header file "rscode-config.h" and put it somewhere in the include search path outside of this library.
This header file should include several declarations that control the behavior of the library.
The example header file may by found in `test/support` directory.

```C
/* Print debugging info */
/* #define DEBUG 1 */

/* Disable erasures functions */
/* #define RSCODE_DISABLE_ERASURES_FUNCTIONS 1 */

/* Number of parity bytes */
#define NPAR 16
```

Tests are always built with maximum included functions.

Development
---------------

For developers looking to extend, bug fix, build, and test this library with dependencies and test infrastructure included in the source tree.


Setup Environment - Ubuntu 16.04/18.04
---------------------------------

```bash
sudo apt install build-essential git ruby
sudo gem install ceedling
```

Get Code
-----------------

```bash
mkdir lepton
git clone https://github.com/bsail/rscode lepton
cd lepton
```

Tests
---------------

Build & Run Unit Tests

```bash
ceedling test:all
```

You may use and create additional tasks for Ceedling build system. Please refer to the documentation in the `vendor/ceedling/docs`.
