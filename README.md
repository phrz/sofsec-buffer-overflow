# SMU 2018 Software Security Buffer Overflow PoC
by Paul Herz
---

## Running

To run, you need 32-bit Debian (aka Kali), GCC, and Make (included on Kali).

Type `make` into the terminal while in the same folder as this README.
This will ask you if it can disable ASLR temporarily, then compile and run the program.


## Editing

If you intend to modify the source code in the process of understanding this program, you need to run `make clean` after each change and before running `make` again, otherwise make will skip the compilation step.


## Scenario

This imaginary bank has users who have transactions under their name. A user logging in normally can see only their transactions. An administrator can see ALL transactions for debugging purposes. We really don't want our normal users to be able to do that!


## Conditions for Success

A successful exploit uses buffer overflows to escalate the privilege of any normal user to admin level, such that logging in lists ALL transactions, including for users other than the one you logged in as. This program uses a pseudo-database of users and transactions found at the bottom of the file, so you start off knowing at least how to log in as a normal-privilege user.
