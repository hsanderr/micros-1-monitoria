/*
 * Henrique Sander Lourenco
 * Pratica: Usar teclado matricial para tocar 8 notas da escala de d? maior
 * no buzzer, conectado a porta RC2 ou RE1.
 * Tecla     Nota        Freq (Hz)  Periodo timer (1/(2*Frequencia)) (ms)
 * 1         DO          2073       241
 * 2         RE          2349       213
 * 3         MI          2637       190
 * 4         FA          2794       179
 * 5         SOL         3136       159
 * 6         LA          3520       142
 * 7         SI          3951       127
 * 8         DO          4146       121
 *
 */
 
 #define DO1_HIGH_BYTE 0xfe
 #define DO1_LOW_BYTE 0x41
 #define RE_HIGH_BYTE 0xfe
 #define RE_LOW_BYTE 0x81
 #define MI_HIGH_BYTE 0xfe
 #define MI_LOW_BYTE 0xb7
 #define FA_HIGH_BYTE 0xfe
 #define FA_LOW_BYTE 0xd3
 #define SOL_HIGH_BYTE 0xfe
 #define SOL_LOW_BYTE 0xe8
 #define LA_HIGH_BYTE 0xff
 #define LA_LOW_BYTE 0x11
 #define SI_HIGH_BYTE 0xff
 #define SI_LOW_BYTE 0x39
 #define DO2_HIGH_BYTE 0xff
 #define DO2_LOW_BYTE 0x4c
 
typedef enum
{
  NENHUMA,
  DO1,
  RE,
  MI,
  FA,
  SOL,
  LA,
  SI,
  DO2,
} nota_t;

nota_t nota = NENHUMA;
nota_t nota_anterior;

typedef enum
{
  UM,
  DOIS,
  TRES,
  QUATRO,
  CINCO,
  SEIS,
  SETE,
  OITO,
} teclas_t;

teclas_t teclas;

int inverter_saida_buzzer = 0;
int saida_buzzer = 0;

// valores para carregar TMR0H e TMR0L
static const unsigned int tmr0_load_values[8][2] =    {{DO1_HIGH_BYTE,
                                                     DO1_LOW_BYTE},
                                                     {RE_HIGH_BYTE,
                                                     RE_LOW_BYTE},
                                                     {MI_HIGH_BYTE,
                                                     MI_LOW_BYTE},
                                                     {FA_HIGH_BYTE,
                                                     FA_LOW_BYTE},
                                                     {SOL_HIGH_BYTE,
                                                     SOL_LOW_BYTE},
                                                     {LA_HIGH_BYTE,
                                                     LA_LOW_BYTE},
                                                     {SI_HIGH_BYTE,
                                                     SI_LOW_BYTE},
                                                     {DO2_HIGH_BYTE,
                                                     DO2_LOW_BYTE}};
                                                     
// carrega TMR0H e TMR0L de acordo com modo de contagem
void load_tmr0(nota_t a_nota)
{
  TMR0H = tmr0_load_values[a_nota - 1][0];
  TMR0L = tmr0_load_values[a_nota - 1][1];
}

// rotina de interrupcao do timer 0 (alta prioridade)
void Timer0_Interrupt() iv 0x000008 ics ICS_AUTO {
//  counter++; // incrementa contador
//  if (counter == 10)
//  {
//    counter = 0; // se contador chegar a 10, volta para 0
//  }
//  LATD = PORTD & 0b10000000; // limpa display, com excecao do ponto
//  LATD = display_mode[counter]; // mostra valor do contador no display
//
//   troca nivel logico do LED
//  if (led_current_mode == LED_ON)
//  {
//    led_current_mode = LED_OFF;
//  }
//  else
//  {
//    led_current_mode = LED_ON;
//  }
//  LATC0_bit = led_current_mode;
//
//   limpa flags e reativa interupcoes
  TMR0IF_bit = 0;
  GIEH_bit = 1;
  GIEL_bit = 1;
  TMR0IE_bit = 1;
  inverter_saida_buzzer = 1;
}

//char keypadPort at PORTB;

void toca_nota (nota_t nota)
{

}

void para_de_tocar (void)
{
  TMR0ON_bit = 0;
  TMR0IE_bit = 0;
  LATC.b2 = 0;
}

long frequencias[] = {2073, 2349, 2637, 2794, 3136, 3520, 3951, 4146};

void main()
{
  ANSELB = 0; // Configura PORTB como digital
  ANSELC = 0; // Configura PORTC como digital

  /*
   * trisb<7:4> => linhas<3:0>
   * trisb<3:0> => colunas<3:0>
   */
  TRISB = 0x0f; // TRISB<7:4> => saida, TRISB<3:0> => entrada
  LATB.b7 = 0;
  LATB.b6 = 0;
  LATB.b5 = 0;
  LATB.b4 = 0;

  TRISC.b2 = 0; // Configura RC2 como saida
  LATC.b2 = 0; // Coloca nivel logico baixo no pino RC2

  // habilita pull-up interno dos pinos RB<3:0>
  WPUB0_bit = 1;
  WPUB1_bit = 1;
  WPUB2_bit = 1;
  WPUB3_bit = 1;
  RBPU_bit = 0;

  T0CON = 0x08; // timer 0 no modo 16 bits e sem presclaer
  IPEN_bit = 1;  // habilita niveis de prioridade
  GIEH_bit = 1; // habilita interrupcoes de alta prioridade
  GIEL_bit = 1; // habilita interrupcoes de baixa prioridade
  TMR0IE_bit = 1; // habilita interrupcao do timer 0
  TMR0IP_bit = 1; // timer 0: alta prioridade
  
  saida_buzzer = 0;

  while (1)
  {
    nota_anterior = nota;
    if (PORTB.b2 == 0)
    {
        LATB.b6 = 0;
        LATB.b5 = 1;
        LATB.b4 = 0;
        if (PORTB.b2 == 1)
        {
          nota = LA;
        }
        LATB.b6 = 0;
        LATB.b5 = 0;
        LATB.b4 = 1;
        if (PORTB.b2 == 1)
        {
          nota = MI;
        }
        LATB.b6 = 0;
        LATB.b5 = 0;
        LATB.b4 = 0;
    }
    else if (PORTB.b1 == 0)
    {
        LATB.b6 = 1;
        LATB.b5 = 0;
        LATB.b4 = 0;
        if (PORTB.b1 == 1)
        {
          nota = RE;
        }
        LATB.b6 = 0;
        LATB.b5 = 1;
        LATB.b4 = 0;
        if (PORTB.b1 == 1)
        {
          nota = SOL;
        }
        LATB.b6 = 0;
        LATB.b5 = 0;
        LATB.b4 = 1;
        if (PORTB.b1 == 1)
        {
          nota = DO2;
        }
        LATB.b6 = 0;
        LATB.b5 = 0;
        LATB.b4 = 0;
    }
    else if (PORTB.b0 == 0)
    {
        LATB.b6 = 1;
        LATB.b5 = 0;
        LATB.b4 = 0;
        if (PORTB.b0 == 1)
        {
          nota = DO1;
        }
        LATB.b6 = 0;
        LATB.b5 = 1;
        LATB.b4 = 0;
        if (PORTB.b0 == 1)
        {
          nota = FA;
        }
        LATB.b6 = 0;
        LATB.b5 = 0;
        LATB.b4 = 1;
        if (PORTB.b0 == 1)
        {
          nota = LA;
        }
        LATB.b6 = 0;
        LATB.b5 = 0;
        LATB.b4 = 0;
    }
    else
    {
      nota = NENHUMA;
    }
    if (nota_anterior != nota)
    {
      if (nota == NENHUMA)
      {
        TMR0ON_bit = 0;
        LATC.b2 = 0;
        saida_buzzer = 0;
      }
      else
      {
        load_tmr0(nota);
        TMR0ON_bit = 1;
      }
    }
    if (inverter_saida_buzzer)
    {
      if (saida_buzzer == 1)
      {
        LATC.b2 = 0;
        saida_buzzer = 0;
        inverter_saida_buzzer = 0;
      }
      else
      {
        LATC.b2 = 1;
        saida_buzzer = 1;
        inverter_saida_buzzer = 0;
      }
      load_tmr0(nota);
    }
  }
}