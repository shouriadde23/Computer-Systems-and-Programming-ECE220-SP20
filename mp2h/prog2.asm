;


; This is a program for a 5 function calculator - addition, subtraction, multiplication, division and 
; exponent. It accepts single digit none negative inputs and does division and exponent of positive 
; numbers only. The charcharters are accepted form the keyboard and echoed back to the screen. Then
; the input is checked for validity. If it is an invalid input the program halts and prints 
; "Invalid Expression". If the input is a number its pushed into the stack and if the input is an 
; operator two numbers are poped from the stack and the result calculated is pished into the stack
; If there is an underflow the program halts and prints "Invalid Expression". When '=' is 
; entered the result is poped out if the expression is valid. 

; R0 - stores input
; R1 - used to check input validity and as a temporary registers in subroutines
; R2 - used as a temporary register
; R3 - stored first operand
; R4 - stored second operand
; R5 - temporary register
; R6 - temporary register
; R7 - used to store PC value to return to subroutine call

.ORIG x3000

AND R0, R0, #0
AND R1, R1, #0
AND R2, R2, #0
AND R3, R3, #0
AND R4, R4, #0
AND R5, R5, #0
AND R6, R6, #0
AND R7, R7, #0                                                          ; initializing registers 

READ_NEXT_CHAR								; read the next character entered
	GETC							        ; get character for keyboard
	OUT								; display character to screen
	LD R1, EQUAL							; load into R1 the 2s comp ASCII value of '='
	ADD R1, R1, R0							; add R1 and R0
	BRz CHECK_STACK_SIZE						; if char entered is '=' branch
	LD R1, SPACE							; load into r1 the 2s comp ASCII value of ' '
	ADD R1, R1, R0							; add R1 and R0
	BRz READ_NEXT_CHAR						; if char entered is ' ' branch
	AND R2, R2, #0							; initialize R2
	ADD R2, R2, #15							; add 15 to R2
	LEA R1, MULTIPLY						; point R1 to the memory location MULTIPLY
VALIDITY_CHECK_LOOP							; check the validity of the input
	ST R1, SAVE_INPUT						; save the value in R1
	LDR R1, R1, #0							; load the value stored in R1
	ADD R1, R1, R0							; add R1 ad R0
	BRz VALID							; if char is valid branch
	LD R1, SAVE_INPUT						; load back the value of R1
	ADD R1, R1, #1							; increment pointer R1
	ADD R2, R2, #-1							; decrement counter R2
	BRp VALIDITY_CHECK_LOOP						; branch back to check validity
	BRnzp INVALID							; if not branch to invalid

VALID									; if the input is valid check operand
	AND R2, R2, #0							; initialize R2 to zero
	ADD R2, R2, #10							; add 10 to R2
	LEA R1, NUMBERS							; point R1 to the memory location NUMBERS
OPERAND_CHECK								; check operand
	ST R1, SAVE_INPUT						; store the value of R1
	LDR R1, R1, #0							; load the value of R1 in R1
	ADD R1, R1, R0							; add R1 and R0
	BRz IT_IS_A_NUMBER					        ; branch if char is a number
	LD R1, SAVE_INPUT						; load the value back to R1
	ADD R1, R1, #1							; increment pointer R1
	ADD R2, R2, #-1							; decrement counter R2
	BRp OPERAND_CHECK						; branch to operand check
	BRnzp IT_IS_A_OPERATOR			                        ; if not branch to operator

IT_IS_A_NUMBER								; if char is a number
	LD R1, INVERSE_30						; load into R1 -30
	ADD R0, R0, R1							; offset R0 to decimal number
	JSR PUSH							; go to subroutine push
	AND R5, R5, #0							; initialize R5 to zero
	BRnzp READ_NEXT_CHAR						; branch to read next char

IT_IS_A_OPERATOR							; if char is an operator
	ST R0, SAVE_R0							; store the char entered in a memory loacation
	JSR POP								; go to subroutine pop
	AND R3, R3, #0							; initialize R3 to zero
	ADD R3, R3, R0							; store R0 in R3
	JSR POP							        ; go to the subroutine pop
	AND R4, R4, #0							; initialize R4 to zero
	ADD R4, R4, R0							; store R0 in R4
	ADD R5, R5, #-1							; decrement R5
	BRz INVALID							; if underflow branch to invalid
	LD R0, SAVE_R0							; load back R0
	LD R1, PLUS							; load 2s comp of plus
	ADD R1, R1, R0							; add R1 and R0
	BRz OPERATOR_ADDITION						; branch to addition
	LD R1, MINUS							; load 2s comp of minus
	ADD R1, R1, R0							; add R1 and R0
	BRz OPERATOR_SUBTRACTION					; branch to subtracion
	LD R1, MULTIPLY							; load 2s comp of multiply
	ADD R1, R1, R0							; add R1 and R0
	BRz OPERATOR_MULT						; branch to multiply
	LD R1, DIVISION							; load 2s comp of division
	ADD R1, R1, R0							; add R1 and R0
	BRz OPERATOR_DIVISION						; branch to division
	LD R1, EXP							; load 2s comp of exponent
	ADD R1, R1, R0							; add R1 and R0
	BRz OPERATOR_EXPONENT						; branch to exponent

OPERATOR_ADDITION							; if char is '+'
	AND R0, R0, #0							; initialize R0
	JSR ADDITION							; go to subroutine addition
	JSR PUSH							; go to subroutine push
	BRnzp READ_NEXT_CHAR						; read next character

OPERATOR_SUBTRACTION							; if char is '-'
	AND R0, R0, #0							; initialize R0
	JSR MIN								; go to subroutine minus
	JSR PUSH							; go to subroutine push
	BRnzp READ_NEXT_CHAR						; read next character

OPERATOR_MULT								; if char is '*'
	AND R0, R0, #0							; initialize R0 to zero
	AND R5, R5, #0							; initialize R5 to zero
	ST R3, SAVE_THE_REG3						; store R3
	ST R4, SAVE_THE_REG4						; store R4
	ADD R3, R3, #0							; set cc
	BRzp #2								; branch 3 memory locations
	NOT R3, R3							; invert R3
	ADD R3, R3, #1							; increment R3
	ADD R4, R4, #0							; set cc
	BRzp #2								; branch 3 memory locations
	NOT R4, R4							; invert R4
	ADD R4, R4, #1							; increment R4
	ADD R5, R3, R5							; set R5 to R3
	AND R3, R3, #0							; initialize R3 to zero
	JSR MUL								; go to subroutine multiplication
	LD R3, SAVE_THE_REG3						; load R3
	LD R4, SAVE_THE_REG4						; load R4
	ADD R3, R3, #0							; set cc
	BRn THERE_1							; branch if R3 is negative
	BRp THERE_4							; branch if R3 is positive
	THERE_1								; if R3 is negative
	ADD R4, R4, #0							; set cc
	BRn THERE_2							; branch if R4 is negative
	BRp THERE_3							; branch if R4 is positive
	THERE_4								; if R3 is positive
	ADD R4, R4, #0							; set cc
	BRn THERE_3							; branch if R4 is negative
	BRp THERE_2							; branch if R4 is positive
	THERE_3 							; if R4 is negative
	NOT R0, R0							; invert R0
	ADD R0, R0, #1							; increment R0
	THERE_2								; if R4 is positive
	JSR PUSH							; go to subroutine
	BRnzp READ_NEXT_CHAR						; read next character

OPERATOR_DIVISION							; if char is '/'
	AND R0, R0, #0							; initialize R0 to zero
	AND R5, R5, #0							; initialize R5 to zero
	ADD R3, R3, #0							; set cc
	BRz INVALID							; if the denominator is zero inout is invalid
	JSR DIV								; go to subroutine division
	AND R0, R0, #0							; initialize R0 to zero
	ADD R0, R5, R0							; set R0 to R5
	JSR PUSH							; go to subroutine oush
	AND R5, R5, #0							; initialize R5 to zero
	BRnzp READ_NEXT_CHAR						; read new character

OPERATOR_EXPONENT							; if char is '^'
	AND R0, R0, #0							; initialize R0 to zero
	AND R5, R5, #0							; initialize R5 to zero
	ADD R3, R3, #0							; set cc
	BRz GO								; branch if R3 is zero
	ADD R4, R4, #0							; set cc
	BRz GOO								; branch if R4 is zero
	ADD R5, R4, R5							; copy R4 into R5
	AND R2, R2, #0							; initialize R2 to zero
	ADD R2, R2, R3							; copy R3 into R2
	AND R6, R6, #0							; initialize R6 to zero
	AND R3, R3, #0							; initialize R3 to zero
	ST R5, SAVE_R5							; store the value of R5
	JSR POWER							; go to subroutine power
	GOO ADD R0, R0, #-1						; decrement 1 from R0
	GO ADD R0, R0, #1						; add 1 to R0
	JSR PUSH							; go to subroutine push
	BRnzp READ_NEXT_CHAR						; read new character

INVALID									; if input is invalid
	LEA R0, INVALID_TEXT						; point to the memory location of the string
	PUTS								; print the string on the screen
	BRnzp DONE							; branch to done

CHECK_STACK_SIZE							; if char is '='
	LD R1, STACK_TOP						; load into R1 the top pointer
	LD R2, STACK_START						; load into R2 the start of the stack
	ADD R1, R1, #1							; increment R1
	NOT R2, R2							; invert R2
	ADD R2, R2, #1							; add 1 to R2
	ADD R2, R1, R2							; add R2 abd R1
	BRnp INVALID							; if its negative branch to invalid
	JSR POP								; else go to subroutine pop
	AND R5, R5, #0							; initialize R5 to zero
	ADD R5, R5, R0							; copy R0 to R5
	JSR PRINT_HEX							; go to subroutine to print in hex
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;IN:R5                        ;
;OUT:R0                       ;
PRINT_HEX								; subroutine to print in hex
	AND R0, R0, #0							; initialize R0 to zero
	AND R6, R6, #0							; initialize R6 to zero
  ADD R6, R6, #4							; add 4 to R6
OUTTER									; outer loop
	AND R3, R3, #0							; initialize R3 to zero
	ADD R3, R3, #4							; add 4 to R3
INNER									; innner loop
	ADD R0, R0, R0							; left shift R0
	ADD R5, R5, #0							; add zero to R5 to set cc
	BRzp #1		      						; branch if R5 is zero or positive
	ADD R0, R0, #1							; add 1 to R0
	ADD R5, R5, R5							; left shift R5
	ADD R3, R3, #-1							; decrement R3
	BRp INNER		      					; branch to INNER
	LEA R3, HEX		   					; load memory address of HEX into R3
	ADD R3, R3, R0							; add the R0 to the value of R3
	LDR R0, R3, #0							; load the contents of the address R3 into R0
  OUT		         					  	; display the contents R0
	AND R0, R0, #0							; initialize R0 to zero
  ADD R6, R6, #-1							; decrement R6
	BRp OUTTER		    					; branch back to to OUTTER if R6 is positive
	BRnzp DONE							; when done branch to done
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;IN:R3,R4                     ;
;OUT:R0                       ;
ADDITION						         	; subroutine to add
	ADD R0, R3, R4							; add R3 and R4 and store in R0
	RET								; return to subroutine call
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;IN:R3,R4                     ;
;OUT:R0                       ;
MIN									; subroutine to subtract
	NOT R1, R3							; take 2s comp of R3
	ADD R1, R1, #1							; and store in R1
	ADD R0, R1, R4							; store the difference of R3 and R4 in R0
	AND R1, R1, #0							; initialize R1 to zero
	RET								; return to subroutine call
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;IN:R3,R4                     ;
;OUT:R0                       ;
MUL									; subroutine to multiply
	ST R7, SAVE_R7							; store the value of R7 (PC)
	AND R1, R1, #0							; initialize R1 to zero
MHERE									; loop
	ADD R5, R5, #0							; initialize R5 to zero
	BRz LEAVE							; branch if R5 is zero
	JSR ADDITION							; go to subroutine addition
	ADD R1, R0, R1							; add R0 to R1
	ADD R5, R5, #-1							; decrement R5
	BRp MHERE							; branch back to loop if R5 is positive
	LD R7, SAVE_R7							; load the value of R7 from memory
LEAVE 									; leave label
	AND R0, R0, #0							; initialize R0 to zero
	ADD R0, R0, R1							; store the value of R1 into R0
	RET								; return to subroutine call
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;IN:R3,R4                     ;
;OUT:R0                       ;
POWER									; subroutine for exponent
	ST R7, SAVE_REG7						; store the value of R7 (PC)
EHERE									; loop
	JSR MUL								; go to subroutine multiply
	ADD R6, R0, #0							; store the value of R0 in R6
	AND R4, R4, #0							; initialize R4 to zero
	ADD R4, R4, R6							; add the value of R6 to R4
	LD R5, SAVE_R5							; load the value of R5 from memory
	ADD R2, R2, #-2							; decrement R2 by 2
	BRp EHERE							; if r2 is positive branch to loop
	LD R7, SAVE_REG7						; load the value of R7 from memory
	RET								; return to subroutine call
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;IN:R3,R4                     ;
;OUT:R0                       ;
DIV									; subroutine to divide
	ST R7, SAVE_R7							; store the value of R7 (PC)
DHERE									; loop
	JSR MIN						 		; go to subroutine minus
	ADD R5, R5, #1							; increment R5
	AND R4, R4, #0							; initialize R4 to zero
	ADD R4, R0, R4							; add R0 to R4
	NOT R1, R4							; take the 2s comp of R4
	ADD R1, R1, #1							; and store in R1
	ADD R1, R1, R3							; add R1 and R4
	BRnz DHERE							; branch back to loop if R1 is >= R3
	ADD R4, R4, #0							; initialize R4 to zero
	BRzp #1								; branch to next memory space if R4 is not negative
	ADD R5, R5, #-1							; decrement R5
	LD R7, SAVE_R7							; load the value of R7 from memory
	RET								; return to subroutine call
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;IN:R0                        ;
;OUT:R5(0-success,1-fail)     ;
PUSH									; subroutine to push obj into stack
	ST R3, PUSH_SaveR3						; save R3
	ST R4, PUSH_SaveR4						; save R4
	AND R5, R5, #0							; initialize R5 to zero
	LD R3, STACK_END						; load into R3 the end of the stack
	LD R4, STACk_TOP						; load into R4 the top pointer
	ADD R3, R3, #-1							; decrement R3 by one
	NOT R3, R3							; take the 2s comp of R3
	ADD R3, R3, #1							; and store it in R3
	ADD R3, R3, R4							; add R3 to R4
	BRz OVERFLOW						        ; if zero stack is full
	STR R0, R4, #0							; no overflow, store value in the stack
	ADD R4, R4, #-1							; move top of the stack
	ST R4, STACK_TOP						; store top of stack pointer
	BRnzp DONE_PUSH							; branch to done push
OVERFLOW								; if overflow
	ADD R5, R5, #1							; increment R5 by 1
DONE_PUSH								; if not overflow
	LD R3, PUSH_SaveR3						; load back the value of R3 from memory
	LD R4, PUSH_SaveR4						; load back the value of R4 from memory
	RET								; return to subroutine call
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;OUT:R0,R5(0-success,1-fail)  ;
POP							  		; subroutine to
	ST R3, POP_SaveR3						; save R3
	ST R4, POP_SaveR4						; save R3
	AND R5, R5, #0							; clear R5
	LD R3, STACK_START						; load into R3 the start of the stack
	LD R4, STACK_TOP						; load into R4 the top pointer
	NOT R3, R3							; take the 2s comp of R3
	ADD R3, R3, #1							; and store it in R3
	ADD R3, R3, R4							; add R3 and R4
	BRz UNDERFLOW							; branch to underflow if zero
	ADD R4, R4, #1							; increment R4
	LDR R0, R4, #0							; load into R0 what value in R4 memory
	ST R4, STACK_TOP						; store the value of R4 into top pointer
	BRnzp DONE_POP							; branch to done pop
UNDERFLOW								; if underflow
	ADD R5, R5, #1					 		; increment R5 by 1
DONE_POP								; if not underflow
	LD R3, POP_SaveR3				  		; load back the value of R3 from memory
	LD R4, POP_SaveR4			    			; load back the value of R4 from memory
	RET								; return to subroutine call
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
STACK_END		  .FILL x3FF0					; end of stack
STACK_START		  .FILL x4000					; start of stack
STACK_TOP		  .FILL x4000					; top pointer of stack
PUSH_SaveR3		  .BLKW #1					; save R3
PUSH_SaveR4	          .BLKW #1					; save R4
POP_SaveR3		  .BLKW #1	 				; save R3
POP_SaveR4	          .BLKW #1					; save R4
SAVE_R7  		  .BLKW #1					; save R7
SAVE_REG		  .BLKW #1					; save register
SAVE_INPUT                .BLKW #1					; save input
SAVE_R0                   .BLKW #1					; save R0
SAVE_THE_REG3 	          .BLKW #1					; save R3
SAVE_THE_REG4 	          .BLKW #1					; save R4
SAVE_R5   		  .BLKW #1					; save R5
SAVE_REG7 	          .BLKW #1					; save R7
INVERSE_30		  .FILL xFFD0					; 2s comp of 30
EQUAL			  .FILL xFFC3       			        ; 2s comp of ASCII '='
SPACE			  .FILL xFFE0					; 2s comp of ASCII ' '
MULTIPLY    		  .FILL xFFD6					; 2s comp of ASCII '*'
MINUS			  .FILL xFFD3					; 2s comp of ASCII '-'
DIVISION 	          .FILL xFFD1					; 2s comp of ASCII '/'
PLUS		          .FILL xFFD5					; 2s comp of ASCII '+'
EXP			  .FILL xFFA2					; 2s comp of ASCII '^'
NUMBERS			  .FILL xFFD0					; 2s comp of ASCII '0'
			  .FILL xFFCF					; 2s comp of ASCII '1'
			  .FILL xFFCE					; 2s comp of ASCII '2'
			  .FILL xFFCD					; 2s comp of ASCII '3'
			  .FILL xFFCC					; 2s comp of ASCII '4'
			  .FILL xFFCB					; 2s comp of ASCII '5'
			  .FILL xFFCA					; 2s comp of ASCII '6'
			  .FILL xFFC9					; 2s comp of ASCII '7'
			  .FILL xFFC8					; 2s comp of ASCII '8'
			  .FILL xFFC7					; 2s comp of ASCII '9'
HEX		          .FILL x0030          				; ASCII '0'
			  .FILL x0031  					; ASCII '1'
			  .FILL x0032   				; ASCII '2'
			  .FILL x0033   				; ASCII '3'
			  .FILL x0034   				; ASCII '4
			  .FILL x0035   				; ASCII '5'
			  .FILL x0036   				; ASCII '6'
			  .FILL x0037   				; ASCII '7'
			  .FILL x0038   				; ASCII '8'
			  .FILL x0039   				; ASCII '9'
			  .FILL x0041   				; ASCII 'A'
			  .FILL x0042   				; ASCII 'B'
			  .FILL x0043   				; ASCII 'C'
			  .FILL x0044   				; ASCII 'D'
			  .FILL x0045  				 	; ASCII 'E'
			  .FILL x0046   				; ASCII 'F'

INVALID_TEXT 		  .STRINGZ "Invalid Expression"
DONE 			  HALT

.END
