PCLINT Configuration
====================

PCLINT configuration.

## Prerequisites

- Linux (I use something ubuntu-like)
- System GCC
- The executable `pclint` somewhere in search path
    - I use a shell wrapper around lint-nt.exe running with wine

## Process

- `make install` will find the various toolchain includes and cache the locations
- `make all` will produce report.txt and print the following:
    - `make mandatory` print a count and summary of all MISRA *mandatory* deviations
    - `make required` print a count and summary of all MISRA *required* deviations
    - `make advisory` print a count and summary of all MISRA *advisory* deviations

## Rules

- The rules are defined in the makefile
- Order is important
    
## Issues

- It's a mystery as to how to suppress toolchain warnings (-wlib(0) does nothing)
- I'm not sure the correct order between `au-misra3.lnt` and `co-gcc.lnt`
    - I am using the order that produces fewer warnings about the toolchain





