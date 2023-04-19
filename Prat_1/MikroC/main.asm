
_Int0_Interrupt:

;main.c,38 :: 		void Int0_Interrupt() iv 0x00008 ics ICS_AUTO {
;main.c,39 :: 		if (current_mode == FAST_CNT)
	MOVF        _current_mode+0, 0 
	XORLW       1
	BTFSS       STATUS+0, 2 
	GOTO        L_Int0_Interrupt0
;main.c,41 :: 		current_mode = SLOW_CNT;
	CLRF        _current_mode+0 
;main.c,42 :: 		}
	GOTO        L_Int0_Interrupt1
L_Int0_Interrupt0:
;main.c,45 :: 		current_mode = FAST_CNT;
	MOVLW       1
	MOVWF       _current_mode+0 
;main.c,46 :: 		}
L_Int0_Interrupt1:
;main.c,47 :: 		INT0IF_bit = 0;
	BCF         INT0IF_bit+0, BitPos(INT0IF_bit+0) 
;main.c,48 :: 		GIEH_bit = 1;
	BSF         GIEH_bit+0, BitPos(GIEH_bit+0) 
;main.c,49 :: 		GIEL_bit = 1;
	BSF         GIEL_bit+0, BitPos(GIEL_bit+0) 
;main.c,50 :: 		INT0IE_bit = 1;
	BSF         INT0IE_bit+0, BitPos(INT0IE_bit+0) 
;main.c,51 :: 		TMR0H = tmr0_load_values[current_mode][0];
	MOVF        _current_mode+0, 0 
	MOVWF       R0 
	MOVLW       0
	MOVWF       R1 
	MOVWF       R2 
	MOVWF       R3 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	RLCF        R2, 1 
	RLCF        R3, 1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	RLCF        R2, 1 
	RLCF        R3, 1 
	MOVLW       main_tmr0_load_values+0
	ADDWF       R0, 1 
	MOVLW       hi_addr(main_tmr0_load_values+0)
	ADDWFC      R1, 1 
	MOVLW       higher_addr(main_tmr0_load_values+0)
	ADDWFC      R2, 1 
	MOVF        R0, 0 
	MOVWF       TBLPTRL+0 
	MOVF        R1, 0 
	MOVWF       TBLPTRH+0 
	MOVF        R2, 0 
	MOVWF       TBLPTRU+0 
	TBLRD*+
	MOVFF       TABLAT+0, TMR0H+0
;main.c,52 :: 		TMR0L = tmr0_load_values[current_mode][1];
	MOVLW       2
	ADDWF       R0, 0 
	MOVWF       TBLPTR+0 
	MOVLW       0
	ADDWFC      R1, 0 
	MOVWF       TBLPTR+1 
	MOVLW       0
	ADDWFC      R2, 0 
	MOVWF       TBLPTR+2 
	TBLRD*+
	MOVFF       TABLAT+0, TMR0L+0
;main.c,53 :: 		}
L_end_Int0_Interrupt:
L__Int0_Interrupt7:
	RETFIE      1
; end of _Int0_Interrupt

_Timer0_Interrupt:
	MOVWF       ___Low_saveWREG+0 
	MOVF        STATUS+0, 0 
	MOVWF       ___Low_saveSTATUS+0 
	MOVF        BSR+0, 0 
	MOVWF       ___Low_saveBSR+0 

;main.c,55 :: 		void Timer0_Interrupt() iv 0x000018 ics ICS_AUTO {
;main.c,56 :: 		if (led_current_mode == LED_ON)
	MOVF        _led_current_mode+0, 0 
	XORLW       1
	BTFSS       STATUS+0, 2 
	GOTO        L_Timer0_Interrupt2
;main.c,58 :: 		led_current_mode = LED_OFF;
	CLRF        _led_current_mode+0 
;main.c,59 :: 		}
	GOTO        L_Timer0_Interrupt3
L_Timer0_Interrupt2:
;main.c,62 :: 		led_current_mode = LED_ON;
	MOVLW       1
	MOVWF       _led_current_mode+0 
;main.c,63 :: 		}
L_Timer0_Interrupt3:
;main.c,64 :: 		LATC0_bit = led_current_mode;
	BTFSC       _led_current_mode+0, 0 
	GOTO        L__Timer0_Interrupt10
	BCF         LATC0_bit+0, BitPos(LATC0_bit+0) 
	GOTO        L__Timer0_Interrupt11
L__Timer0_Interrupt10:
	BSF         LATC0_bit+0, BitPos(LATC0_bit+0) 
L__Timer0_Interrupt11:
;main.c,65 :: 		TMR0IF_bit = 0; // clear TMR0IF
	BCF         TMR0IF_bit+0, BitPos(TMR0IF_bit+0) 
;main.c,66 :: 		GIEH_bit = 1;
	BSF         GIEH_bit+0, BitPos(GIEH_bit+0) 
;main.c,67 :: 		GIEL_bit = 1;
	BSF         GIEL_bit+0, BitPos(GIEL_bit+0) 
;main.c,68 :: 		TMR0IE_bit = 1;
	BSF         TMR0IE_bit+0, BitPos(TMR0IE_bit+0) 
;main.c,69 :: 		TMR0H = tmr0_load_values[current_mode][0];
	MOVF        _current_mode+0, 0 
	MOVWF       R0 
	MOVLW       0
	MOVWF       R1 
	MOVWF       R2 
	MOVWF       R3 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	RLCF        R2, 1 
	RLCF        R3, 1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	RLCF        R2, 1 
	RLCF        R3, 1 
	MOVLW       main_tmr0_load_values+0
	ADDWF       R0, 1 
	MOVLW       hi_addr(main_tmr0_load_values+0)
	ADDWFC      R1, 1 
	MOVLW       higher_addr(main_tmr0_load_values+0)
	ADDWFC      R2, 1 
	MOVF        R0, 0 
	MOVWF       TBLPTRL+0 
	MOVF        R1, 0 
	MOVWF       TBLPTRH+0 
	MOVF        R2, 0 
	MOVWF       TBLPTRU+0 
	TBLRD*+
	MOVFF       TABLAT+0, TMR0H+0
;main.c,70 :: 		TMR0L = tmr0_load_values[current_mode][1];
	MOVLW       2
	ADDWF       R0, 0 
	MOVWF       TBLPTR+0 
	MOVLW       0
	ADDWFC      R1, 0 
	MOVWF       TBLPTR+1 
	MOVLW       0
	ADDWFC      R2, 0 
	MOVWF       TBLPTR+2 
	TBLRD*+
	MOVFF       TABLAT+0, TMR0L+0
;main.c,71 :: 		}
L_end_Timer0_Interrupt:
L__Timer0_Interrupt9:
	MOVF        ___Low_saveBSR+0, 0 
	MOVWF       BSR+0 
	MOVF        ___Low_saveSTATUS+0, 0 
	MOVWF       STATUS+0 
	SWAPF       ___Low_saveWREG+0, 1 
	SWAPF       ___Low_saveWREG+0, 0 
	RETFIE      0
; end of _Timer0_Interrupt

_load_tmr0:

;main.c,73 :: 		void load_tmr0(count_mode_t mode)
;main.c,75 :: 		TMR0H = tmr0_load_values[mode][0];
	MOVF        FARG_load_tmr0_mode+0, 0 
	MOVWF       R0 
	MOVLW       0
	MOVWF       R1 
	MOVWF       R2 
	MOVWF       R3 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	RLCF        R2, 1 
	RLCF        R3, 1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	RLCF        R2, 1 
	RLCF        R3, 1 
	MOVLW       main_tmr0_load_values+0
	ADDWF       R0, 1 
	MOVLW       hi_addr(main_tmr0_load_values+0)
	ADDWFC      R1, 1 
	MOVLW       higher_addr(main_tmr0_load_values+0)
	ADDWFC      R2, 1 
	MOVF        R0, 0 
	MOVWF       TBLPTRL+0 
	MOVF        R1, 0 
	MOVWF       TBLPTRH+0 
	MOVF        R2, 0 
	MOVWF       TBLPTRU+0 
	TBLRD*+
	MOVFF       TABLAT+0, TMR0H+0
;main.c,76 :: 		TMR0L = tmr0_load_values[mode][1];
	MOVLW       2
	ADDWF       R0, 0 
	MOVWF       TBLPTR+0 
	MOVLW       0
	ADDWFC      R1, 0 
	MOVWF       TBLPTR+1 
	MOVLW       0
	ADDWFC      R2, 0 
	MOVWF       TBLPTR+2 
	TBLRD*+
	MOVFF       TABLAT+0, TMR0L+0
;main.c,77 :: 		}
L_end_load_tmr0:
	RETURN      0
; end of _load_tmr0

_main:

;main.c,79 :: 		void main() {
;main.c,80 :: 		ANSELB = 0; // Configure PORTB pins as digital
	CLRF        ANSELB+0 
;main.c,81 :: 		ANSELC = 0;
	CLRF        ANSELC+0 
;main.c,82 :: 		RC0_bit = 0; //
	BCF         RC0_bit+0, BitPos(RC0_bit+0) 
;main.c,83 :: 		LATC0_bit = 0; //
	BCF         LATC0_bit+0, BitPos(LATC0_bit+0) 
;main.c,84 :: 		RB0_bit = 1; // Configure RB0 as input
	BSF         RB0_bit+0, BitPos(RB0_bit+0) 
;main.c,85 :: 		RB1_bit = 1; // Configure RB1 as input
	BSF         RB1_bit+0, BitPos(RB1_bit+0) 
;main.c,86 :: 		load_tmr0(current_mode);
	MOVF        _current_mode+0, 0 
	MOVWF       FARG_load_tmr0_mode+0 
	CALL        _load_tmr0+0, 0
;main.c,87 :: 		T0CON = 0x86; // Set Timer0 to 16-bit mode and prescaler to 128
	MOVLW       134
	MOVWF       T0CON+0 
;main.c,88 :: 		IPEN_bit = 1;
	BSF         IPEN_bit+0, BitPos(IPEN_bit+0) 
;main.c,89 :: 		GIEH_bit = 1;
	BSF         GIEH_bit+0, BitPos(GIEH_bit+0) 
;main.c,90 :: 		GIEL_bit = 1;
	BSF         GIEL_bit+0, BitPos(GIEL_bit+0) 
;main.c,91 :: 		INT0IE_bit = 1;
	BSF         INT0IE_bit+0, BitPos(INT0IE_bit+0) 
;main.c,92 :: 		TMR0IE_bit = 1;
	BSF         TMR0IE_bit+0, BitPos(TMR0IE_bit+0) 
;main.c,93 :: 		RBPU_bit = 0;
	BCF         RBPU_bit+0, BitPos(RBPU_bit+0) 
;main.c,94 :: 		TMR0IP_bit = 0;
	BCF         TMR0IP_bit+0, BitPos(TMR0IP_bit+0) 
;main.c,95 :: 		INT1IP_bit = 1;
	BSF         INT1IP_bit+0, BitPos(INT1IP_bit+0) 
;main.c,96 :: 		while (1) {}
L_main4:
	GOTO        L_main4
;main.c,97 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
