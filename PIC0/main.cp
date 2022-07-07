#line 1 "C:/Users/arceo/Documents/EMBDSYS Final project/PIC0/main.c"
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
#line 53 "C:/Users/arceo/Documents/EMBDSYS Final project/PIC0/main.c"
void switchRoutine(uint8_t* state);

void main() {

 TRISB = 0x00;
 UART1_Init(9600);
 while(1)
 {
 if(UART1_Data_Ready() == 1)
 {
 static uint8_t state = UART1_Read();
 switchRoutine(&state);
 }
 }
}

void switchRoutine(uint8_t* state)
{
 switch(*state)
 {
 case 0x00:
 PORTB = 0x35;
 break;
 case 0x02:
 PORTB = 0x15;
 break;
 case 0x04:
 PORTB = 0x25;
 break;
 default:
 PORTB = 0xC5;
 }
}
