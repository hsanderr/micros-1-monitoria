#line 1 "C:/Users/henri/Documents/2023_1/Ap_Micros_1_Monitoria/Prat_1/MikroC/main.c"
#line 19 "C:/Users/henri/Documents/2023_1/Ap_Micros_1_Monitoria/Prat_1/MikroC/main.c"
typedef enum {
 SLOW_CNT,
 FAST_CNT,
} count_mode_t;

count_mode_t current_mode;

void interrupt(void) {
 if (TMR0IF_bit) {
 TMR0IF_bit = 0;
 GIEH_bit = 1;
 TMR0IE_bit = 1;
 TMR0L = 0xb2;
 TMR0H = 0xf0;
 }
}

static const unsigned int tmr0_load_values[2][2] = {{ 0xc2 ,
  0xf7 },
 { 0xf0 ,
  0xbe }};

void load_tmr0(count_mode_t mode)
{
 TMR0H = tmr0_load_values[mode][0];
 TMR0L = tmr0_load_values[mode][1];
}

void main() {
 ANSELB = 0;
 RB0_bit = 1;
 RB1_bit = 1;
 TMR0L = 0xf0;
 TMR0H = 0xb2;
 T0CON = 0x86;
 IPEN_bit = 1;
 GIEH_bit = 1;
 GIEL_bit = 1;
 TMR0IE_bit = 1;
 while (1) {}
}
