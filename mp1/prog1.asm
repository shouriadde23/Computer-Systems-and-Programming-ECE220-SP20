;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; In this lab, I used 3 main loops to print out the histogram. The inner-most loop included a loop 
; for counting the bits and another loop to print the appropriate digits for each letter frequency
; in the given string. After the appropriate loops were placed for printing the histogram frequencies
; for each letter, I had an outermost loop which loaded the histogram starting address into a registerar
; and kept updating it as the outermost loop executed. The outermost loop repeated 27 times- once for
; the '@' symbol and once for each character. The characters were printed and were followed by a space 
; and a new-line ASCII command. 
; Lab Partners' Net IDs: arangan3, mahuja3

; R0 is holding the histogram frequency (digit) count
; R1 is the register holding the digit counter
; R2 is the register that holds each character ASCII value
; R3 is holding the bit counter value
; R4 is a temporary register which stores either ZERO_VAL or A_VAL
; R5 is register which updates the character address of the histogram 
; R6 is a pointer for the starting address of the histogram 

		AND R6, R6, #0		; Clearing the contents of the register holding histogram starting address
		LD R6, HIST_ADDR	; Load the histogram start address into R6
		LD R5, CHAR_AT		; Load the starting @ character into R5
		AND R0, R0, 0		; Clearing the contents of R0
		; Outermost loop begins here
BEGIN	ADD R0, R0, R5		; Adding the contents of R5 into R0
		OUT					; Print the contents of R0 to the screen
		LD R0, SPACE		; Load the space character into R0
		OUT					; Output the space character to the screen
		AND R0, R0, 0		; Clear the contents of R0
		
		LDR R2, R6, #0		; Load the starting address of the histogram into R2  

		; Inner loop begins here

		AND R4, R4, #0		; Clearing the contents of the temporary register R4
		AND R1, R1, 0		; Clearing the contents of R1 as the register holding the digit counter value
		ADD R1, R1, #4		; Initializing R1 with a digit counter value of 4

		; Digit loop begins here
NEXTDIGIT
		AND R0, R0, 0		; Clear the register holding the histogram frequency (digit) value
		AND R3, R3, 0		; Clearing the contents of the bit counter value
		ADD R3, R3, #4		; Initialize R1 with a value of 4

		; Bit loop begins here
NEXTBIT 
		ADD R0, R0, R0		; Left shift R0 to pick up the next bit value
		ADD R2, R2, #0 		; Make R2 the most recently used register in order for the branch to work
		BRn ONEVAL			; If negative, branch to the ONEVAL label
		ADD R0, R0, #0		; Add 0 to digit value
		BRnzp SKIP			; Branch to the SKIP label
ONEVAL	ADD R0, R0, #1		; Add 1 to the digit count value
SKIP	ADD R2, R2, R2		; Left shift the character ASCII value
		ADD R3, R3, #-1		; Decrementing the bit counter value by 1
		BRp NEXTBIT			; Branch back to read the next bit
		ADD R0, R0, #-9		; Add -9 to digit value	
		BRnz ADDZERO		; If negative or zero branch to the ADDZERO label
		LD R4, A_VAL		; Load R4 with the label A_VAL
		ADD R0, R0, R4		; Add contents of R4 into R0
		ADD R0, R0, #-10	; Subtract the decimal value of 10 from R0
		BRnzp FINISH		; Branch to the FINISH Label
ADDZERO	LD R4, ZERO_VAL		; Load R4 with the label ZERO_VAL	
		ADD R0, R0, R4		; Add contents of R4 into R0
FINISH	PRINT 	OUT			; Output  contents of R0 to the screen
		AND R4, R4, #0		; Clear the contents of R4
		ADD R1, R1, #-1		; Decrement the digit counter value by 1
		BRp NEXTDIGIT 		; Branch back to the beginning of the digit loop
					
		; End of the inner loop

		ADD R6, R6, #1 		; Increment the starting address of the histogram by 1
		LD R0, NEW_LINE		; Load the filled new line value into R0
		OUT					; Output the new line
		AND R0, R0, #0		; Clearing the contents of R0
		ADD R5, R5, #-15	; Combining the register holding ASCII value as a counter
		ADD R5, R5, #-15	; Counting down by a decimal value of 90 because this represents ASCII value of 'Z' 
		ADD R5, R5, #-15	; Counting down by a decimal value of 90 because this represents ASCII value of 'Z'
		ADD R5, R5, #-15	; Counting down by a decimal value of 90 because this represents ASCII value of 'Z'
		ADD R5, R5, #-15	; Counting down by a decimal value of 90 because this represents ASCII value of 'Z'
		ADD R5, R5, #-15	; Counting down by a decimal value of 90 because this represents ASCII value of 'Z'
		BRz DONE			; Branch to the HALT statement
		ADD R5, R5, #15		; Restoring the current ASCII character value by counting up by 91
		ADD R5, R5, #15		; Restoring the current ASCII character value by counting up by 91
		ADD R5, R5, #15		; Restoring the current ASCII character value by counting up by 91
		ADD R5, R5, #15		; Restoring the current ASCII character value by counting up by 91
		ADD R5, R5, #15		; Restoring the current ASCII character value by counting up by 91
		ADD R5, R5, #15		; Restoring the current ASCII character value by counting up by 91
		ADD R5, R5, #1		; Restoring the current ASCII character value by counting up by 91
		BRnp BEGIN			; Branch back to the beginning of the outermost loop					
							
DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00 ; histogram starting address
STR_START	.FILL x4000	; string starting address
ZERO_VAL	.FILL x0039	; ASCII value representing '0' + 9
A_VAL		.FILL x004A	; ASCII value representing 'A' + 9
CHAR_AT		.FILL x0040	; ASCII value representing '@'
SPACE		.FILL x0020	; ASCII value representing ' '
NEW_LINE	.FILL x000A	; ASCII value representing new line

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
