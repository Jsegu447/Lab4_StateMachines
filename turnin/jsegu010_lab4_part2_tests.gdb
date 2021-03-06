# Test file for "Lab4_StateMachines"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
test "PINA: 0x00,0x01,0x00 => RELEASEONb0 to RELEASEONb1"
# Set inputs
set State SM1_START
setPINA 0x00
# Continue for several ticks
continue 4
expectPORTB 0x01
# Set expect values
setPINA 0x01
setPINA 0x00
expectPORTB 0x02
expect State SM1_RELEASEONB1
# Check pass/fail
checkResult

# Add tests below

 test "PINA: 0x00 => START STATE SET, WAIT"
 # Set inputs
 set State SM2_START
 setPINA 0x00
 expectPORTC 0x07
 # Continue for several ticks
 continue 4
 expectPORTC 0x07
 # Set expect value
expect State SM2_WAIT
 # Check pass/fail
 checkResult

 test "PINA: 0x00,0x01, 0x00 => WAIT TO INCREMENT TO WAIT"
 set State SM2_START
 setPINA 0x00
 continue 4
 setPINA 0x01
 continue 1
 setPINA 0x00
 continue 4
 expectPORTC 0x08
 expect State SM2_WAIT
 checkResult

 test "PINA: 0x00,0x03,0x00=> RESET"
 set State SM2_START
 setPINA 0x00
 continue 4
 setPINA 0x03
 continue 4
 setPINA 0x00
 continue 4
 expectPORTC 0x00
 expect State SM2_WAIT
 checkResult

test "PINA: 0x00,0x03,0x33=> STAY RESET"
 set State SM2_START
 setPINA 0x00
 continue 4
 setPINA 0x03
 continue 4
 setPINA 0x03
 continue 4
 expectPORTC 0x00
 expect State SM2_RESET
 checkResult

#on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
