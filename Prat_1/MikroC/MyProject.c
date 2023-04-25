/*
 * Henrique Sander Lourenco
 * Pratica: Fazer um display de 7 segmentos contar de 0 a 9 quando um bot?o
 * for pressionado.
 * Botao na porta RB0 => per?odo de 1s
 * Botao na porta RB1 => per?odo de 0,25s
 * Utilizar TMR0 com interrupcao para gerar as bases de tempo do contador
 * Frequencia do clock = 8MHz
 * Escolha do display feita a partir do multiplex conectado na porta A
 * Ciclos de maquina = fosc/4
 *
 */

#define SLOW_CNT_HIGH_BYTE 0xc2
#define SLOW_CNT_LOW_BYTE 0xf7
#define FAST_CNT_HIGH_BYTE 0xf0
#define FAST_CNT_LOW_BYTE 0xbe

typedef enum {
  SLOW_CNT,
  FAST_CNT,
} count_mode_t;

typedef enum {
  LED_OFF,
  LED_ON,
} led_mode_t;

//typedef enum {
//  ZERO,
//  ONE,
//  TWO,
//  THREE,
//  FOUR,
//  FIVE,
//  SIX,
//  SEVEN,
//  EIGHT
//} display_num_t;

unsigned char display_mode[10] = {0b00111111,
                                  0b10000110,
                                  0b01011011,
                                  0b11001111,
                                  0b01100110,
                                  0b11101101,
                                  0b01111101,
                                  0b10000111,
                                  0b01111111,
                                  0b11101111};

count_mode_t current_mode = FAST_CNT;

led_mode_t led_current_mode = LED_OFF;

int counter = 0;

static const unsigned int tmr0_load_values[2][2] = {{SLOW_CNT_HIGH_BYTE,
                                                     SLOW_CNT_LOW_BYTE},
                                                    {FAST_CNT_HIGH_BYTE,
                                                     FAST_CNT_LOW_BYTE}};

void IntExt_Interrupt() iv 0x00008 ics ICS_AUTO {
  if (INT0IF_bit == 1)
  {
    current_mode = SLOW_CNT;
  }
  else if (INT1IF_bit == 1)
  {
    current_mode = FAST_CNT;
  }
  INT0IF_bit = 0;
  INT1IF_bit = 0;
  GIEH_bit = 1;
  GIEL_bit = 1;
  INT0IE_bit = 1;
  INT1IE_bit = 1;
  TMR0H = tmr0_load_values[current_mode][0];
  TMR0L = tmr0_load_values[current_mode][1];
}

void Timer0_Interrupt() iv 0x000018 ics ICS_AUTO {
  counter++;
  if (counter == 10)
  {
    counter = 0;
  }
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
  TMR0IF_bit = 0; // clear TMR0IF
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
  ANSELA = 0; // Configure PORTA pins as digital
  ANSELB = 0; // Configure PORTB pins as digital
  ANSELC = 0; // Configure PORTC pins as digital
  ANSELD = 0; // Configure PORTD pins as digital

  TRISA = 0; // Configure PORTA pins as outputs
  TRISD = 0; // Configure PORTD pins as outputs
  TRISC = 0; // Configure PORTC pins as outputs
  TRISB = 0xff;

  // Display selection
  LATA.b0 = 1;
  LATA.b1 = 0;
  LATA.b2 = 0;
  LATA.b3 = 0;

  load_tmr0(current_mode);
  T0CON = 0x86; // Set Timer0 to 16-bit mode and prescaler to 128
  IPEN_bit = 1;
  GIEH_bit = 1;
  GIEL_bit = 1;
  INT0IE_bit = 1;
  INT1IE_bit = 1;
  TMR0IE_bit = 1;
  WPUB0_bit = 1;
  WPUB1_bit = 1;
  RBPU_bit = 0;
  TMR0IP_bit = 0;
  INT1IP_bit = 1;
  LATD = display_mode[counter];
  while (1) {}
}