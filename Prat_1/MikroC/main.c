/* 
 * Henrique Sander Lourenço
 * Prática: Fazer um display de 7 segmentos contar de 0 a 9 quando um botão
 * for pressionado.
 * Botão na porta RB0 => período de 1s
 * Botão na porta RB1 => período de 0,25s
 * Utilizar TMR0 com interrupção para gerar as bases de tempo do contador
 * Frequência do clock = 8MHz
 * Escolha do display feita a partir do multiplex conectado na porta A
 * Ciclos de máquina = fosc/4
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

count_mode_t current_mode;
 
void interrupt() {
  if (TMR0IF_bit) {
    TMR0IF_bit = 0; // clear TMR0IF
    GIE_bit = 1;
    TMR0IE_bit = 1;
    TMR0L = 0xb2;
    TMR0H = 0xf0;
  }
}

static const unsigned int tmr0_load_values[2][2] = {{SLOW_CNT_HIGH_BYTE, 
                                                     SLOW_CNT_LOW_BYTE},
                                                    {FAST_CNT_HIGH_BYTE, 
                                                     FAST_CNT_LOW_BYTE}};

void load_tmr0(count_mode_t mode) 
{
  TMR0H = tmr0_load_values[mode][0];
  TMR0L = tmr0_load_values[mode][1];
}

void main() {
  ANSELB = 0; // Configure PORTB pins as digital
  RB0_bit = 1; // Configure RB0 as input
  RB1_bit = 1; // Configure RB1 as input
  TMR0L = 0xf0;
  TMR0H = 0xb2;
  T0CON = 0x86; // Set Timer0 to 16-bit mode and prescaler to 128
  GIE_bit = 1;
  TMR0IE_bit = 1;
  while (1) {}
}