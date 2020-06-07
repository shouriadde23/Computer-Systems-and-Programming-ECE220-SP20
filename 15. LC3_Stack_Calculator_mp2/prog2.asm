;net id: shouria2
;group members: hb10

; Introduction: In this MP, the objective was to create a calculator using the stack PUSH and POP subroutines.
; In order to start this MP, the first step was to check if the inputted character's ASCII value matched any 
; of the arithmetic operations (addition, subtraction, multiplication, divison, exponential) or digit operands
; falling in the range of 0-9. To make the checking process easier, I loaded the 2's complement ASCII values 
; into R6 which would help in checking if a character matched. If all of these checks failed, then I branched
; to the invalid expression. After the checks for the ASCII characters was completed, the next steps were to 
; have individual operation helpers which would pop the 2 desired values, check for underflow, and call the
; appropriate subroutine if there was no underflow. After this step was completed, the next step was to write the 
; individual subroutines which consisted of PRINT_HEX, EVALUATE, ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION, 
; and EXPONENT. The hardest of the these subroutines was the EXPONENT. Overall, this lab took a good amount of time
; but also gave me experience using STACK and subroutines.

;R0 - used to print/output/input
;R1 - used rarely, but used in PRINT_HEX and EVALUATE as temporary registers
;R2 - used it in calculator functions just as a temporary value storage register
;R3 - used as first inputs in the calculator functions
;R4 - used as second inputs in the calculator functions
;R5 - temporary variable used to help check what kind of input R0 is 
;R6 - used to load hex values of the ascii values to compare R0 to in order to figure out the input type

.ORIG x3000

	AND R1, R1, #0 ; clearing registers
	AND R2, R2, #0 ; 
	AND R3, R3, #0 ; 
	AND R4, R4, #0 ;
	AND R5, R5, #0 ;
	AND R6, R6, #0 ;

	IN_LOOP	
		GETC		; Reading the next character input
		OUT			; Outputting that next input to screen

	; Begin valid checking of the input character; checks happen based off of incrementing ASCII values		

		; Check if the inputted character is a space and branch to appropriate execution section
		LD R6, SPACE_OFF
		ADD R5, R0, R6
		BRz IN_LOOP
		
		; Check if input char is multiplication operator and branch to appropriate execution section
		LD R6, MULT_OFF
		ADD R5, R0, R6
		BRz MULT_OP
		
		; Check if the input char is an addition operator and branch to appropriate execution section
		LD R6, PLUS_OFF
		ADD R5, R0, R6
		BRz ADD_OP
		
		; Check if input char is subtraction operator and branch to appropriate execution section
		LD R6, SUB_OFF
		ADD R5, R0, R6
		BRz SUB_OP
	
		; Check if input char is divison operator and branch to appropriate execution section
		LD R6, DIV_OFF
		ADD R5, R0, R6
		BRz DIV_OP		
		
		; Check if input char falls in the 0-9 number range and branch to appropriate execution section
		LD R6, NINE_OFF
		ADD R5, R0, R6
		BRnz NUM_OP
		
		; Check to see if value is the equals operator; if it is then branch to EVALUATE
		LD R6, EQUAL_OFF
		ADD R5, R0, R6
		BRz EVALUATE
		
		; Check if input char is an exponent and branch to appropriate execution section
		LD R6, EXP_OFF
		ADD R5, R0, R6
		BRz EXP_OP

		; All checks have failed if we reached this point, and we can conclude input char is invalid
		BRnzp INVALID
		
	; Begin the execution of operations based off what the input char entered was
	
	MULT_OP		
		JSR POP
		ADD R3, R0, #0	; Have the 1st popped value stored into R3
		JSR POP
		ADD R4, R0, #0	; Have the 2nd popped value stored into R4
		ADD R5, R5, #0	
		BRp INVALID		; Checking for underflow condition
		JSR MUL		; Jump to the multiplication subroutine
		JSR PUSH
		BRnzp IN_LOOP	; Branch back to the beginning of the input char checking loop
	
	ADD_OP
		JSR POP
		ADD R3, R0, #0	; Have the 1st popped value stored into R3
		JSR POP
		ADD R4, R0, #0	; Have the 2nd popped value stored into R4
		ADD R5, R5, #0	
		BRp INVALID		; Checking for underflow condition
		JSR PLUS		; Jump to the addition subroutine
		JSR PUSH
		BRnzp IN_LOOP	; Branch back to the beginning of the input char checking loop

	SUB_OP
		JSR POP
		ADD R4, R0, #0	; Have the 1st popped value stored into R4
		JSR POP
		ADD R3, R0, #0	; Have the 2nd popped value stored into R3
		ADD R5, R5, #0	
		BRp INVALID		; Checking for underflow condition
		JSR MIN			; Jump to the subtraction subroutine
		JSR PUSH
		BRnzp IN_LOOP	; Branch back to the beginning of the input char checking loop

	DIV_OP
		JSR POP
		ADD R4, R0, #0	; Have the 1st popped value stored into R4
		JSR POP
		ADD R3, R0, #0	; Have the 2nd popped value stored into R3
		ADD R5, R5, #0	
		BRp INVALID		; Checking for underflow condition
		JSR DIV			; Jump to the division subroutine
		JSR PUSH
		BRnzp IN_LOOP	; Branch back to the beginning of the input char checking loop

	EXP_OP
		JSR POP
		ADD R4, R0, #0	; Have the 1st popped value stored into R4
		JSR POP
		ADD R3, R0, #0	; Have the 2nd popped value stored into R3
		ADD R5, R5, #0	
		BRp INVALID		; Checking for underflow condition
		JSR EXP			; Jump to the exponent subroutine
		JSR PUSH
		BRnzp IN_LOOP	; Branch back to the beginning of the input char checking loop
	
	NUM_OP
		LD R6, ZERO_OFF	; Load the 2's complement offset value of ASCII character '0' into R1
		ADD R5, R0, R6	; Add the offset to value stored in R5
		BRn INVALID		; If the value doesn't fall in the range greater than or equal to 0-9 then it's invalid
		ADD R0, R0, #-10 ; Subtract 48 from R0 to account for the offset
		ADD R0, R0, #-10
		ADD R0, R0, #-10
		ADD R0, R0, #-10
		ADD R0, R0, #-8
		JSR PUSH
		BRnzp IN_LOOP	; Branch back to the beginning of the input char checking loop

	INVALID
		LEA R0, INVAL_EXP ; Load the string "Invalid Expression" into R0
		PUTS			; Print the entire string to the console
		HALT			; Halt program execution
		
		



; These are the two's complement offset values of each ASCII char used to determine what the inputted char is

EQUAL_OFF	.FILL xFFC3	; The two's complement offset of '=' ASCII character
SPACE_OFF	.FILL xFFE0 ; The two's complement offset of ' ' ASCII character
SUB_OFF		.FILL xFFD3	; The two's complement offset of '-' ASCII character
PLUS_OFF	.FILL xFFD5	; The two's complement offset of '+' ASCII character
MULT_OFF	.FILL xFFD6	; The two's complement offset of '*' ASCII character
DIV_OFF		.FILL xFFD1	; The two's complement offset of '/' ASCII character
EXP_OFF 	.FILL xFFA2	; The two's complement offset of '^' ASCII character
ZERO_OFF	.FILL xFFD0	; The two's complement offset of '0' ASCII character
NINE_OFF	.FILL xFFC7	; The two's complement offset of '9' ASCII character
INVAL_EXP	.STRINGZ "Invalid Expression"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX
	START_LAB
		AND R1, R1, #0 				; clearing R1
		ADD R1, R1, #4 				; R1 = digit counter = 4
	
	START_LABTWO
		AND R0, R0, #0 				; clearing R0
		AND R2, R2, #0				; clearing R2
		ADD	R2, R2, #4				; bit counter
		

	LOOP_ONE
		ADD R3, R3, #0 				; having a reference to R3
		BRzp POSITIVE 				; move to positive label if positive, checking for 0 
		ADD R0, R0, #1 				; adding one if negative
		BRnzp NEXT_ONE 				; move down 

	POSITIVE
		ADD R0, R0, #0				; adding zero if positive
	
	NEXT_ONE
		ADD R3, R3, R3 				; left shift of R3
		ADD R2, R2, #-1 			; decrement bit counter
		BRz NEXT_TWO 				; 
		ADD R0, R0, R0 				; left shift of R0 
		BRnzp LOOP_ONE 				; go back up 

	NEXT_TWO
		ADD R7, R0, #-9				; checking if its a number or alphabet
		BRp PRINT_ALPH 				; if its negative after subtracting nine its an alphabet
		ADD R0, R0, #10				; adding appropriate value for ascii printing
		ADD R0, R0, #10				;
		ADD R0, R0, #10				;
		ADD R0, R0, #10				;
		ADD R0, R0, #8				;
		OUT							;
		BRnzp NEXT_DIGIT			;
	
	PRINT_ALPH
		ADD R0, R0, #10				; adding appropriate value for ascii printing #55
		ADD R0, R0, #10				;
		ADD R0, R0, #10				;
		ADD R0, R0, #10				;
		ADD R0, R0, #10				;
		ADD R0, R0, #5				;
		OUT;

	NEXT_DIGIT
		ADD R1, R1, #-1				; decrementing digit counter
		BRp START_LABTWO			; 
		HALT						;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

;your code goes here
		; Check if stack has only 1 value
		; Load R1 with the label STACK_TOP
		; Load R2 with the label STACK_START

		LD R1, STACK_START
		LD R2, STACK_TOP
		ADD R2, R2, #1
		NOT R2, R2
		ADD R2, R2, #1
		ADD R1, R1, R2
		BRnp INVALID
		JSR POP	
		ADD R3, R0, #0
		ADD R5, R0, #0
		BRnzp PRINT_HEX

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

PLUS	
		ADD R0, R3, R4
		RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

MIN	
		NOT R4, R4
		ADD R4, R4, #1
		ADD R0, R3, R4
		RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

MUL		
		
		AND R0, R0, #0
		ST R2, SAVE_R2
		ADD R2, R0, #-1
		BRz FIN_MULT
		BEG_MULT	
			ADD R0, R0, R3
			ADD R4, R4, #-1
			BRp BEG_MULT
		FIN_MULT
			LD R2, SAVE_R2
			RET

SAVE_R2			.BLKW #1; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV						
		AND R0, R0, #0		
		NOT R4, R4
		ADD R4, R4, #1
START
		ADD R3, R3, R4
		BRn END
		ADD R0, R0, #1
		BRnzp START
	END 
		RET	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
; the first popped element is stored in R4 and is the exponent value
; the second popped element is stored in R3 and is the base value
EXP
		AND R0, R0, #0
		ST R2, ORIG_R2
		ADD R4, R4, #-1
		ADD R2, R3, #0
		ADD R2, R2, #-1
		ADD R0, R3, R0
		ST R2, MODIF_R2
		LOOP_OUTEXP
			LD R2, MODIF_R2
			LOOP_INEXP
				ADD R0, R3, R0
				ADD R2, R2, #-1
				BRp LOOP_INEXP
			ADD R3, R0, #0
			ADD R4, R4, #-1
		 	BRp LOOP_OUTEXP
		LD R2, ORIG_R2
		RET
		
ORIG_R2			.BLKW #1
MODIF_R2		.BLKW #1
	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
