#line 1 "C:/Users/henri/Documents/2023_1/Ap_Micros_1_Monitoria/Prat_1/MikroC/main.c"
#line 19 "C:/Users/henri/Documents/2023_1/Ap_Micros_1_Monitoria/Prat_1/MikroC/main.c"
typedef enum {
 SLOW_CNT,
 FAST_CNT,
} count_mode_t;

typedef enum {
 LED_OFF,
 LED_ON,
} led_mode_t;

count_mode_t current_mode = FAST_CNT;

led_mode_t led_current_mode = LED_OFF;

static const unsigned int tmr0_load_values[2][2] = {{ 0xc2 ,
  0xf7 },
 { 0xf0 ,
  0xbe }};

void Int0_Interrupt() iv 0x00008 ics ICS_AUTO {
 if (current_mode == FAST_CNT)
 {
 current_mode = SLOW_CNT;
 }
 else
 {
 current_mode = FAST_CNT;
 }
 INT0IF_bit = 0;
 GIEH_bit = 1;
 GIEL_bit = 1;
 INT0IE_bit = 1;
 TMR0H = tmr0_load_values[current_mode][0];
 TMR0L = tmr0_load_values[current_mode][1];
}

void Timer0_Interrupt() iv 0x000018 ics ICS_AUTO {
 if (led_current_mode == LED_ON)
 {
 led_current_mode = LED_OFF;
 }
 else
 {
 led_current_mode = LED_ON;
 }
 LATC0_bit = led_current_mode;
 TMR0IF_bit = 0;
 GIEH_bit = 1;
 GIEL_bit = 1;
 TMR0IE_bit = 1;
 TMR0H = tmr0_load_values[current_mode][0];
 TMR0L = tmr0_load_values[current_mode][1];
}

void load_tmr0(count_mode_t mode)
{
 TMR0H = tmr0_load_values[mode][0];
 TMR0L = tmr0_load_values[mode][1];
}

void main() {
 ANSELB = 0;
 ANSELC = 0;
 RC0_bit = 0;
 LATC0_bit = 0;
 RB0_bit = 1;
 RB1_bit = 1;
 load_tmr0(current_mode);
 T0CON = 0x86;
 IPEN_bit = 1;
 GIEH_bit = 1;
 GIEL_bit = 1;
 INT0IE_bit = 1;
 TMR0IE_bit = 1;
 RBPU_bit = 0;
 TMR0IP_bit = 0;
 INT1IP_bit = 1;
 while (1) {}
}
