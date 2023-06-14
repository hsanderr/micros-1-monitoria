/*
 * Pratica 4
 * Pt. 1: utilizar 5 botões para controlar a velocidade da ventoinha.
 *     - velocidades: 0%, 25%, 50%, 75%, 100%
 *     - mostrar duty cycle no display LCD
 * Pt. 2: utilizar o sensor infravermelho para calcular a velocidade de giro
 * da ventoinha em RPM.
 *     - mostrar o valor lido no display LCD
 * Sensor: RC0
 * Ventoinha: RC2  (CCP1)
 */
 
#define PWM_FREQ_HZ 8000
#define PWM_DUTY_CYCLE_0 0
#define PWM_DUTY_CYCLE_25 64
#define PWM_DUTY_CYCLE_50 128
#define PWM_DUTY_CYCLE_75 191
#define PWM_DUTY_CYCLE_100 255

// Lcd pinout settings
sbit LCD_RS at RE2_bit;
sbit LCD_EN at RE1_bit;
sbit LCD_D7 at RD7_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D3 at RD3_bit;
sbit LCD_D2 at RD2_bit;
sbit LCD_D1 at RD1_bit;
sbit LCD_D0 at RD0_bit;

// Pin direction
sbit LCD_RS_Direction at TRISE2_bit;
sbit LCD_EN_Direction at TRISE1_bit;
sbit LCD_D7_Direction at TRISD7_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D3_Direction at TRISD3_bit;
sbit LCD_D2_Direction at TRISD2_bit;
sbit LCD_D1_Direction at TRISD1_bit;
sbit LCD_D0_Direction at TRISD0_bit;


void main() {
//  TRISC.f0 = 1; // RC0 input
//  TRISC.f2 = 1; // disable output driver
  
  // use 8-bit timer Timer2
//  C1TSEL1_bit = 0;
//  C1TSEL0_bit = 0;

  ANSELC.f2 = 0;
  ANSELB = 0;
  ANSELD = 0;
  ANSELE = 0;
  
  TRISB = 0xff; // RB input
  TRISD = 0;
  TRISE = 0;
  
  // habilita pull-up interno dos pinos RB<3:0>
  WPUB0_bit = 1;
  WPUB1_bit = 1;
  WPUB2_bit = 1;
  WPUB3_bit = 1;
  RBPU_bit = 0;

  TRISC.f2 = 0; // RC2 output
  LATC.f2 = 0; // load 0 to RC2

  PWM1_Init(PWM_FREQ_HZ);
  PWM1_Start();
  PWM1_Set_Duty(PWM_DUTY_CYCLE_0);
  
  LCD_Init();
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);
  LCD_Out(1,1,"Duty cycle = 0");

  while(1)
  {

    if (RB0_bit) {                    // button on RB0 pressed
      PWM1_Set_Duty(PWM_DUTY_CYCLE_0);
      Lcd_Cmd(_LCD_CLEAR);
      LCD_Out(1,1,"Duty cycle = 0%%");
    }

    if (RB1_bit) {                    // button on RB1 pressed
      PWM1_Set_Duty(PWM_DUTY_CYCLE_25);
      Lcd_Cmd(_LCD_CLEAR);
      LCD_Out(1,1,"Duty cycle = 25%%");
    }

    if (RB2_bit) {                    // button on RB2 pressed
      PWM2_Set_Duty(PWM_DUTY_CYCLE_50);
      Lcd_Cmd(_LCD_CLEAR);
      LCD_Out(1,1,"Duty cycle = 50%%");
    }

    if (RB3_bit) {                    // button on RB3 pressed
      PWM2_Set_Duty(PWM_DUTY_CYCLE_75);
      Lcd_Cmd(_LCD_CLEAR);
      LCD_Out(1,1,"Duty cycle = 75%%");
    }
    
    if (RB4_bit) {                    // button on RB4 pressed
      PWM2_Set_Duty(PWM_DUTY_CYCLE_100);
      Lcd_Cmd(_LCD_CLEAR);
      LCD_Out(1,1,"Duty cycle = 100%%");
    }

  }
}
