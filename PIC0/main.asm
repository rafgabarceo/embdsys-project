
_main:

;main.c,55 :: 		void main() {
;main.c,57 :: 		TRISB = 0x00; // Set the entire PORTB as outputs.
	CLRF       TRISB+0
;main.c,58 :: 		UART1_Init(9600); // Initialize UART communication
	MOVLW      51
	MOVWF      SPBRG+0
	BSF        TXSTA+0, 2
	CALL       _UART1_Init+0
;main.c,59 :: 		while(1)
L_main0:
;main.c,61 :: 		if(UART1_Data_Ready() == 1)
	CALL       _UART1_Data_Ready+0
	MOVF       R0+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_main2
;main.c,63 :: 		static uint8_t state = UART1_Read();
	CALL       _UART1_Read+0
	MOVF       R0+0, 0
	MOVWF      main_state_L2+0
;main.c,64 :: 		switchRoutine(&state);
	MOVLW      main_state_L2+0
	MOVWF      FARG_switchRoutine_state+0
	CALL       _switchRoutine+0
;main.c,65 :: 		}
L_main2:
;main.c,66 :: 		}
	GOTO       L_main0
;main.c,67 :: 		}
L_end_main:
	GOTO       $+0
; end of _main

_switchRoutine:

;main.c,69 :: 		void switchRoutine(uint8_t* state)
;main.c,71 :: 		switch(*state)
	GOTO       L_switchRoutine3
;main.c,73 :: 		case 0x00:
L_switchRoutine5:
;main.c,74 :: 		PORTB = 0x35; // 0011 0101
	MOVLW      53
	MOVWF      PORTB+0
;main.c,75 :: 		break;
	GOTO       L_switchRoutine4
;main.c,76 :: 		case 0x02:
L_switchRoutine6:
;main.c,77 :: 		PORTB = 0x15; // 0001 0101
	MOVLW      21
	MOVWF      PORTB+0
;main.c,78 :: 		break;
	GOTO       L_switchRoutine4
;main.c,79 :: 		case 0x04:
L_switchRoutine7:
;main.c,80 :: 		PORTB = 0x25; // 0010 0101
	MOVLW      37
	MOVWF      PORTB+0
;main.c,81 :: 		break;
	GOTO       L_switchRoutine4
;main.c,82 :: 		default:
L_switchRoutine8:
;main.c,83 :: 		PORTB = 0xC5; // 1100 0101
	MOVLW      197
	MOVWF      PORTB+0
;main.c,84 :: 		}
	GOTO       L_switchRoutine4
L_switchRoutine3:
	MOVF       FARG_switchRoutine_state+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      0
	BTFSC      STATUS+0, 2
	GOTO       L_switchRoutine5
	MOVF       FARG_switchRoutine_state+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      2
	BTFSC      STATUS+0, 2
	GOTO       L_switchRoutine6
	MOVF       FARG_switchRoutine_state+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      4
	BTFSC      STATUS+0, 2
	GOTO       L_switchRoutine7
	GOTO       L_switchRoutine8
L_switchRoutine4:
;main.c,85 :: 		}
L_end_switchRoutine:
	RETURN
; end of _switchRoutine
