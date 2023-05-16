/*
 * Henrique Sander Lourenco
 * Pratica: Usar teclado matricial para tocar 8 notas da escala de dó maior
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

typedef enum
{
  DO1,
  RE,
  MI,
  FA,
  SOL,
  LA,
  SI,
  DO2,
} nota_t;

nota_t nota;

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

int recaregar_timer = 0; // indica se o timer 0 deve ser recarregado

// rotina de interrupcao do timer 0 (baixa prioridade)
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
  recaregar_timer = 1; // seta flag para recarregar timer 0
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

  int nota = 0;

  T0CON = 0x08; // timer 0 no modo 16 bits e sem presclaer
  IPEN_bit = 1;  // habilita niveis de prioridade
  GIEH_bit = 1; // habilita interrupcoes de alta prioridade
  GIEL_bit = 1; // habilita interrupcoes de baixa prioridade
  INT0IE_bit = 1; // habilita interrupcao externa 0 (RB0)
  INT1IE_bit = 1; // habilita interrupcao externa 1 (RB1)
  TMR0IE_bit = 1; // habilita interrupcao do timer 0
  
  while (1)
  {
    if (PORTB.b3 == 0)
    {
      // botao na coluna 3 pressionado
      // desenhar esquemático para entender
        LATB.b7 = 0;
        LATB.b6 = 0;
        LATB.b5 = 0;
        LATB.b4 = 0;
    }
//    nota = Keypad_Key_Press();
//    if(nota)
//    {
//      while(1)
//      {
//        nota = Keypad_Key_Press();
//        if (!nota)
//        {
//          break;
//        }
//      }
//    }
//    else
//    {
//
//    }
//  }
//  Keypad_Key_Press();
}