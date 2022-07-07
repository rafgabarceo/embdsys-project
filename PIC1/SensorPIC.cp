#line 1 "C:/Users/arceo/Documents/EMBDSYS Final project/PIC1/SensorPIC.c"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for pic/include/stdint.h"




typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;



typedef signed char int_fast8_t;
typedef signed int int_fast16_t;
typedef signed long int int_fast32_t;


typedef unsigned char uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned long int uint_fast32_t;


typedef signed int intptr_t;
typedef unsigned int uintptr_t;


typedef signed long int intmax_t;
typedef unsigned long int uintmax_t;
#line 9 "C:/Users/arceo/Documents/EMBDSYS Final project/PIC1/SensorPIC.c"
sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D7 at RB6_bit;
sbit LCD_D6 at RB1_bit;
sbit LCD_D5 at RB2_bit;
sbit LCD_D4 at RB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D7_Direction at TRISB6_bit;
sbit LCD_D6_Direction at TRISB1_bit;
sbit LCD_D5_Direction at TRISB2_bit;
sbit LCD_D4_Direction at TRISB3_bit;
#line 35 "C:/Users/arceo/Documents/EMBDSYS Final project/PIC1/SensorPIC.c"
uint8_t pathDetection(uint8_t* control_signals);
uint8_t objectDetection(uint8_t* control_signals);
void initADC();

void main() {

 Lcd_Init();
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Out(1, 1, "LawnBot :)");


 TRISD |= (1 <<  TRISD2 ) |
 (1 <<  TRISD3 ) |
 (1 <<  TRISD1 );

 TRISD &= ~(1 <<  TRISD0 );

 PORTD &= ~(1 <<  TRISD0 );


 INTCON |= (1 << GIE) | (1 << PEIE) | (1 << INTE);


 T1CON = 0x10;

 UART1_Init(9600);
 ADC_Init();


 while(1)
 {
 static uint8_t slaveControlSignals[] = {
 0x00,
 0x02,
 0x04,
 0x12
 };

 pathDetection(slaveControlSignals);
 objectDetection(slaveControlSignals);


 }
}
#line 84 "C:/Users/arceo/Documents/EMBDSYS Final project/PIC1/SensorPIC.c"
uint8_t pathDetection(uint8_t* control_signals)
{

 if((PORTD & (1 <<  RD3 )) && (PORTD & (1 <<  RD2 )))
 {
 UART1_Write(*(control_signals + 3));
 }
 else if((PORTD & (1 <<  RD3 )))
 {
 UART1_Write(*(control_signals + 2));
 }
 else if((PORTD & (1 <<  RD2 )))
 {
 UART1_Write(*(control_signals + 1));
 } else
 {
 UART1_Write(*(control_signals));
 }
}
#line 107 "C:/Users/arceo/Documents/EMBDSYS Final project/PIC1/SensorPIC.c"
uint8_t objectDetection(uint8_t* control_signals)
{
 char output[3];
 static int sample = ADC_Read(0);
 LCD_Cmd(_LCD_CLEAR);

 if(sample > 160)
 {

 UART1_Write(*(control_signals + 3));
 LCD_Out(2,1, "Object infront");
 } else
 {

 UART1_Write(*(control_signals));
 LCD_Out(2,1, "Mowing...");
 }

}
