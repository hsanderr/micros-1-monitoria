#line 1 "C:/Users/Henrique/usp/Monitoria_Ap_Micros_1/micros-1-monitoria/Prat_1/MikroC/main.c"
#line 19 "C:/Users/Henrique/usp/Monitoria_Ap_Micros_1/micros-1-monitoria/Prat_1/MikroC/main.c"
typedef enum {
 SLOW_CNT,
 FAST_CNT,
} count_mode_t;

typedef enum {
 LED_OFF,
 LED_ON,
} led_mode_t;
#line 41 "C:/Users/Henrique/usp/Monitoria_Ap_Micros_1/micros-1-monitoria/Prat_1/MikroC/main.c"
unsigned char display_mode[10] = {0b11111100,
 0b01100001,
 0b11011010,
 0b11110011,
 0b01100110,
 0b10110111,
 0b10111110,
 0b11100001,
 0b11111110,
 0b11110111};

count_mode_t current_mode = FAST_CNT;

led_mode_t led_current_mode = LED_OFF;

int counter = 0;

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
 counter++;
 LATD = display_mode[counter];
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
 ANSELA = 0;
 ANSELB = 0;
 ANSELC = 0;
 ANSELD = 0;



 TRISA = 0;
 TRISD = 0;
 TRISC = 0;
 TRISB.b0 = 1;
 TRISB.b1 = 1;


 LATA.b0 = 1;
 LATA.b1 = 0;
 LATA.b2 = 0;
 LATA.b3 = 0;

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
 LATD = display_mode[counter];
 while (1) {}
}
