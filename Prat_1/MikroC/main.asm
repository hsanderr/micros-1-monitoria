
_interrupt:

;main.c,26 :: 		void interrupt(void) {
;main.c,27 :: 		if (TMR0IF_bit) {
	BTFSS       TMR0IF_bit+0, BitPos(TMR0IF_bit+0) 
	GOTO        L_interrupt0
;main.c,28 :: 		TMR0IF_bit = 0; // clear TMR0IF
	BCF         TMR0IF_bit+0, BitPos(TMR0IF_bit+0) 
;main.c,29 :: 		GIEH_bit = 1;
	BSF         GIEH_bit+0, BitPos(GIEH_bit+0) 
;main.c,30 :: 		TMR0IE_bit = 1;
	BSF         TMR0IE_bit+0, BitPos(TMR0IE_bit+0) 
;main.c,31 :: 		TMR0L = 0xb2;
	MOVLW       178
	MOVWF       TMR0L+0 
;main.c,32 :: 		TMR0H = 0xf0;
	MOVLW       240
	MOVWF       TMR0H+0 
;main.c,33 :: 		}
L_interrupt0:
;main.c,34 :: 		}
L_end_interrupt:
L__interrupt4:
	RETFIE      1
; end of _interrupt

_load_tmr0:

;main.c,41 :: 		void load_tmr0(count_mode_t mode)
;main.c,43 :: 		TMR0H = tmr0_load_values[mode][0];
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
;main.c,44 :: 		TMR0L = tmr0_load_values[mode][1];
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
;main.c,45 :: 		}
L_end_load_tmr0:
	RETURN      0
; end of _load_tmr0

_main:

;main.c,47 :: 		void main() {
;main.c,48 :: 		ANSELB = 0; // Configure PORTB pins as digital
	CLRF        ANSELB+0 
;main.c,49 :: 		RB0_bit = 1;
	BSF         RB0_bit+0, BitPos(RB0_bit+0) 
;main.c,50 :: 		RB1_bit = 1;
	BSF         RB1_bit+0, BitPos(RB1_bit+0) 
;main.c,51 :: 		TMR0L = 0xf0;
	MOVLW       240
	MOVWF       TMR0L+0 
;main.c,52 :: 		TMR0H = 0xb2;
	MOVLW       178
	MOVWF       TMR0H+0 
;main.c,53 :: 		T0CON = 0x86; // Set Timer0 to 16-bit mode and prescaler to 128
	MOVLW       134
	MOVWF       T0CON+0 
;main.c,54 :: 		IPEN_bit = 1;
	BSF         IPEN_bit+0, BitPos(IPEN_bit+0) 
;main.c,55 :: 		GIEH_bit = 1;
	BSF         GIEH_bit+0, BitPos(GIEH_bit+0) 
;main.c,56 :: 		GIEL_bit = 1;
	BSF         GIEL_bit+0, BitPos(GIEL_bit+0) 
;main.c,57 :: 		TMR0IE_bit = 1;
	BSF         TMR0IE_bit+0, BitPos(TMR0IE_bit+0) 
;main.c,58 :: 		while (1) {}
L_main1:
	GOTO        L_main1
;main.c,59 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
