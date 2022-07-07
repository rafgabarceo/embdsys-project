
_main:

;SensorPIC.c,39 :: 		void main() {
;SensorPIC.c,41 :: 		Lcd_Init();
	CALL       _Lcd_Init+0
;SensorPIC.c,42 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;SensorPIC.c,43 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);
	MOVLW      12
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;SensorPIC.c,44 :: 		Lcd_Out(1, 1, "LawnBot :)");
	MOVLW      1
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr1_SensorPIC+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;SensorPIC.c,49 :: 		(1 << SONIC_ECHO_DIRECTION);
	MOVLW      14
	IORWF      TRISD+0, 1
;SensorPIC.c,51 :: 		TRISD &= ~(1 << SONIC_TRIGGER_DIRECTION);
	BCF        TRISD+0, 0
;SensorPIC.c,53 :: 		PORTD &= ~(1 << SONIC_TRIGGER_DIRECTION);
	BCF        PORTD+0, 0
;SensorPIC.c,56 :: 		INTCON |= (1 << GIE) | (1 << PEIE) | (1 << INTE);
	MOVLW      208
	IORWF      INTCON+0, 1
;SensorPIC.c,59 :: 		T1CON = 0x10;
	MOVLW      16
	MOVWF      T1CON+0
;SensorPIC.c,61 :: 		UART1_Init(9600); // Initialize the UART
	MOVLW      51
	MOVWF      SPBRG+0
	BSF        TXSTA+0, 2
	CALL       _UART1_Init+0
;SensorPIC.c,62 :: 		ADC_Init();
	CALL       _ADC_Init+0
;SensorPIC.c,65 :: 		while(1)
L_main0:
;SensorPIC.c,74 :: 		pathDetection(slaveControlSignals);
	MOVLW      main_slaveControlSignals_L1+0
	MOVWF      FARG_pathDetection_control_signals+0
	CALL       _pathDetection+0
;SensorPIC.c,75 :: 		objectDetection(slaveControlSignals);
	MOVLW      main_slaveControlSignals_L1+0
	MOVWF      FARG_objectDetection_control_signals+0
	CALL       _objectDetection+0
;SensorPIC.c,78 :: 		}
	GOTO       L_main0
;SensorPIC.c,79 :: 		}
L_end_main:
	GOTO       $+0
; end of _main

_pathDetection:

;SensorPIC.c,84 :: 		uint8_t pathDetection(uint8_t* control_signals)
;SensorPIC.c,87 :: 		if((PORTD & (1 << RIGHT_SENSOR_DETECT)) && (PORTD & (1 << LEFT_SENSOR_DETECT)))
	BTFSS      PORTD+0, 3
	GOTO       L_pathDetection4
	BTFSS      PORTD+0, 2
	GOTO       L_pathDetection4
L__pathDetection12:
;SensorPIC.c,89 :: 		UART1_Write(*(control_signals + 3));
	MOVLW      3
	ADDWF      FARG_pathDetection_control_signals+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;SensorPIC.c,90 :: 		}
	GOTO       L_pathDetection5
L_pathDetection4:
;SensorPIC.c,91 :: 		else if((PORTD & (1 << RIGHT_SENSOR_DETECT)))
	BTFSS      PORTD+0, 3
	GOTO       L_pathDetection6
;SensorPIC.c,93 :: 		UART1_Write(*(control_signals + 2));
	MOVLW      2
	ADDWF      FARG_pathDetection_control_signals+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;SensorPIC.c,94 :: 		}
	GOTO       L_pathDetection7
L_pathDetection6:
;SensorPIC.c,95 :: 		else if((PORTD & (1 << LEFT_SENSOR_DETECT)))
	BTFSS      PORTD+0, 2
	GOTO       L_pathDetection8
;SensorPIC.c,97 :: 		UART1_Write(*(control_signals + 1));
	INCF       FARG_pathDetection_control_signals+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;SensorPIC.c,98 :: 		} else
	GOTO       L_pathDetection9
L_pathDetection8:
;SensorPIC.c,100 :: 		UART1_Write(*(control_signals));
	MOVF       FARG_pathDetection_control_signals+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;SensorPIC.c,101 :: 		}
L_pathDetection9:
L_pathDetection7:
L_pathDetection5:
;SensorPIC.c,102 :: 		}
L_end_pathDetection:
	RETURN
; end of _pathDetection

_objectDetection:

;SensorPIC.c,107 :: 		uint8_t objectDetection(uint8_t* control_signals)
;SensorPIC.c,110 :: 		static int sample = ADC_Read(0);
	CLRF       FARG_ADC_Read_channel+0
	CALL       _ADC_Read+0
	MOVF       R0+0, 0
	MOVWF      objectDetection_sample_L0+0
	MOVF       R0+1, 0
	MOVWF      objectDetection_sample_L0+1
;SensorPIC.c,111 :: 		LCD_Cmd(_LCD_CLEAR);
	MOVLW      1
	MOVWF      FARG_Lcd_Cmd_out_char+0
	CALL       _Lcd_Cmd+0
;SensorPIC.c,113 :: 		if(sample > 160)
	MOVLW      128
	MOVWF      R0+0
	MOVLW      128
	XORWF      objectDetection_sample_L0+1, 0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__objectDetection16
	MOVF       objectDetection_sample_L0+0, 0
	SUBLW      160
L__objectDetection16:
	BTFSC      STATUS+0, 0
	GOTO       L_objectDetection10
;SensorPIC.c,116 :: 		UART1_Write(*(control_signals + 3));
	MOVLW      3
	ADDWF      FARG_objectDetection_control_signals+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;SensorPIC.c,117 :: 		LCD_Out(2,1, "Object infront");
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr2_SensorPIC+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;SensorPIC.c,118 :: 		} else
	GOTO       L_objectDetection11
L_objectDetection10:
;SensorPIC.c,121 :: 		UART1_Write(*(control_signals));
	MOVF       FARG_objectDetection_control_signals+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;SensorPIC.c,122 :: 		LCD_Out(2,1, "Mowing...");
	MOVLW      2
	MOVWF      FARG_Lcd_Out_row+0
	MOVLW      1
	MOVWF      FARG_Lcd_Out_column+0
	MOVLW      ?lstr3_SensorPIC+0
	MOVWF      FARG_Lcd_Out_text+0
	CALL       _Lcd_Out+0
;SensorPIC.c,123 :: 		}
L_objectDetection11:
;SensorPIC.c,125 :: 		}
L_end_objectDetection:
	RETURN
; end of _objectDetection
