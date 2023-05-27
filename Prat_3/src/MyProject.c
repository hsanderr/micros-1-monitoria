/*

  Parte 1: 
        utilizar libs ADC e LCD
        ler tensão na entrada RA (0, 1, 2, 3 ou 5)
        AN2 e AN3 são para Vref externos
        mostrar valor lido na linha 1 do LCD na forma AN5 = x.xx V
        
  Parte 2:
        medir entrada do LM35 (RE1 ou RE2)
        ajustar Vref para faixa de tensão medida (usar a função FVR do PIC)
        curva teórica: 10mV / ºC
        mostrar valor lido na linha 2 do LCD na forma xx.x ºC
        
  Value                    Description
  _ADC_INTERNAL_REF        Both voltage references set to internal VDD and VSS.
  _ADC_EXTERNAL_REF        Both voltage references set to external Vref+ and Vref- pins.
  _ADC_EXTERNAL_VREFL      Low voltage reference set to Vref- pin.
  _ADC_EXTERNAL_VREFH      High voltage reference set to Vref+ pin.
  _ADC_INTERNAL_VREFL      Low voltage reference set to internal VSS.
  _ADC_INTERNAL_VREFH      High voltage reference set to internal VDD.
  _ADC_INTERNAL_FVRH1      High voltage reference set to 1.024V.
  _ADC_INTERNAL_FVRH2      High voltage reference set to 2.048V.
  _ADC_INTERNAL_FVRH4      High voltage reference set to 4.096V.
  _ADC_INTERNAL_FVR        Both voltage references set to internal 4.096V and 2.048V, respectively.
  _ADC_INTERNAL_FVRL2      Low voltage reference set to internal 2.048V
  _ADC_INTERNAL_FVRH3      High voltage reference set to internal 3.072V

  Van = Vb * Vrefp / (2^n - 1)
  Vb = Van * (2^n - 1) / Vrefp

*/

#define ADC_VCHANNEL 0
#define ADC_TCHANNEL 6
#define START_DELAY_MS 3000
#define LOOP_DELAY_MS 3000
#define VREFP 4.096
#define TWO_POWER_TEN 1024

unsigned int ad_voltage;
unsigned int ad_temp;
float ad_voltage_an;
float ad_temp_an;
int use_get_sample = 1;

// Lcd pinout settings
sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D7 at RB3_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D4 at RB0_bit;

// Pin direction
sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D7_Direction at TRISB3_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D4_Direction at TRISB0_bit;

char voltage_txt[17] = {0};
char temp_txt[17] = {0};

void main() {
  ANSELA = 0x01;             // Configure RA0 pin as analog
  ANSELE = 0x02;
  ANSELB = 0x00;             // Configure RB pins as digital
  TRISA = 0x01;              // Configure RA0 pin as output
  TRISE = 0x02;
  TRISB = 0x00;              // Configure RB pins as output
//  ADFM_bit = 1;              // Right justified
  ADC_Init_Advanced(_ADC_INTERNAL_VREFL | _ADC_INTERNAL_FVRH4);
  LCD_Init();
  // Clear Lcd display:
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
  LCD_Out(1,1,"Prática 3...");
  
  delay_ms(START_DELAY_MS);
  while(1)
  {
    if (use_get_sample)
    {
      Lcd_Cmd(_LCD_CURSOR_OFF);
      LCD_Out(1,1,"ADC_Get_Sample");
      ad_voltage = ADC_Get_Sample(ADC_VCHANNEL);
      ad_voltage_an = ad_voltage * TWO_POWER_TEN / VREFP;
      ad_temp = ADC_Get_Sample(ADC_TCHANNEL);
      use_get_sample = 0;
    }
    else
    {
      Lcd_Cmd(_LCD_CURSOR_OFF);
      LCD_Out(1,1,"ADC_Read");
      ad_voltage = ADC_Read(ADC_VCHANNEL);
      ad_temp = ADC_Read(ADC_TCHANNEL);
      use_get_sample = 1;
    }
    delay_ms(1000);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    sprintf(voltage_txt, "AN0=%.2f", ad_voltage_an);
    LCD_Out(1,1,voltage_txt);
    delay_ms(LOOP_DELAY_MS);
  }
}