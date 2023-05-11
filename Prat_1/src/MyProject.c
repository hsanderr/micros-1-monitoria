/*
 * Henrique Sander Lourenco
 * Pratica: Fazer um display de 7 segmentos contar de 0 a 9 quando um botao
 * for pressionado.
 * Botao na porta RB0 => periodo de 1s
 * Botao na porta RB1 => periodo de 0,25s
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

// modos de contagem
typedef enum {
  SLOW_CNT, // período de 1s
  FAST_CNT, // periodo de 0,25s
} count_mode_t;

// modos do LED
typedef enum {
  LED_OFF, // LED desligado
  LED_ON, // LED ligado
} led_mode_t;

unsigned char display_mode[10] = {0b00111111, // mostra zero no display
                                  0b10000110, // mostra um no display
                                  0b01011011, // mostra dois no display
                                  0b11001111, // mostra três no display
                                  0b01100110, // mostra quatro no display
                                  0b11101101, // mostra cinco no display
                                  0b01111101, // mostra seis no display
                                  0b10000111, // mostra sete no display
                                  0b01111111, // mostra oito no display
                                  0b11101111}; // mostra nove no display

count_mode_t current_mode = FAST_CNT; // modo de contagem
led_mode_t led_current_mode = LED_OFF; // modo do LED
int counter = 0; // contador
int reload_timer = 0; // indica se o timer 0 deve ser recarregadi

// valores para carregar TMR0H e TMR0L
static const unsigned int tmr0_load_values[2][2] = {{SLOW_CNT_HIGH_BYTE,
                                                     SLOW_CNT_LOW_BYTE},
                                                    {FAST_CNT_HIGH_BYTE,
                                                     FAST_CNT_LOW_BYTE}};

// rotina de interrupcao para interrupcao externa (alta prioridade)
void IntExt_Interrupt() iv 0x00008 ics ICS_AUTO {
  if (INT0IF_bit == 1)
  {
    // fonte de interrupcao: RB0
    if (current_mode != SLOW_CNT)
    {
      reload_timer = 1;
      current_mode = SLOW_CNT;
    }

  }
  else if (INT1IF_bit == 1)
  {
    // fonte de interrupcao: RB1
    if (current_mode != FAST_CNT)
    {
      reload_timer = 1;
      current_mode = FAST_CNT;
    }
  }
  
  // limpa flags e reativa interrupcoes
  INT0IF_bit = 0;
  INT1IF_bit = 0;
  GIEH_bit = 1;
  GIEL_bit = 1;
  INT0IE_bit = 1;
  INT1IE_bit = 1;
}

// rotina de interrupcao do timer 0 (baixa prioridade)
void Timer0_Interrupt() iv 0x000018 ics ICS_AUTO {
  counter++; // incrementa contador
  if (counter == 10)
  {
    counter = 0; // se contador chegar a 10, volta para 0
  }
  LATD = PORTD & 0b10000000; // limpa display, com excecao do ponto
  LATD = display_mode[counter]; // mostra valor do contador no display
  
  // troca nivel logico do LED
  if (led_current_mode == LED_ON)
  {
    led_current_mode = LED_OFF;
  }
  else
  {
    led_current_mode = LED_ON;
  }
  LATC0_bit = led_current_mode;
  
  // limpa flags e reativa interupcoes
  TMR0IF_bit = 0;
  GIEH_bit = 1;
  GIEL_bit = 1;
  TMR0IE_bit = 1;
  
  reload_timer = 1; // seta flag para recarregar timer 0
}

// carrega TMR0H e TMR0L de acordo com modo de contagem
void load_tmr0(count_mode_t mode)
{
  TMR0H = tmr0_load_values[mode][0];
  TMR0L = tmr0_load_values[mode][1];
}

void main() {
  ANSELA = 0; // Configura PORTA como digital
  ANSELB = 0; // Configura PORTB como digital
  ANSELC = 0; // Configura PORTC como digital
  ANSELD = 0; // Configura PORTD como digital

  TRISA = 0; // Configura PORTA como saida
  TRISB = 0xff; // Configura PORTB como entrada
  TRISC = 0; // Configura PORTC como saida
  TRISD = 0; // Configura PORTD como saida

  // Selecao do display
  LATA.b0 = 1; //
  LATA.b1 = 0;
  LATA.b2 = 0;
  LATA.b3 = 0;

  load_tmr0(current_mode); // inicializa TMR0H e TMR0L
  
  T0CON = 0x86; // timer 0 no modo  bits e presclaer 1:128
  IPEN_bit = 1;  // habilita niveis de prioridade
  GIEH_bit = 1; // habilita interrupcoes de alta prioridade
  GIEL_bit = 1; // habilita interrupcoes de baixa prioridade
  INT0IE_bit = 1; // habilita interrupcao externa 0 (RB0)
  INT1IE_bit = 1; // habilita interrupcao externa 1 (RB1)
  TMR0IE_bit = 1; // habilita interrupcao do timer 0
  
  // habilita pull-up interno dos pinos RB0 e RB1
  WPUB0_bit = 1;
  WPUB1_bit = 1;
  RBPU_bit = 0;
  
  TMR0IP_bit = 0; // timer 0: baixa prioridade
  INT1IP_bit = 1; // interrupcao externa: alta prioridade
  LATD = 0; // apaga display
  LATD = display_mode[counter]; // mostra valor do contador no display
  
  while (1) 
  {
    if (reload_timer)
    {
      // recarrega timer 0 se necessario
      load_tmr0(current_mode);
    }
  }
}