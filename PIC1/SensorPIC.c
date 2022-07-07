/*

SensorPIC can be counted as the master interface. It will be sending
control signals to the MotorPIC.

*/
#include <stdint.h>

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

#define LEFT_SENSOR_DETECT RD2
#define RIGHT_SENSOR_DETECT RD3
#define LEFT_SENSOR_DETECT_DIRECTION TRISD2
#define RIGHT_SENSOR_DETECT_DIRECTION TRISD3

#define SONIC_TRIGGER RD0
#define SONIC_ECHO RD1
#define SONIC_TRIGGER_DIRECTION TRISD0
#define SONIC_ECHO_DIRECTION TRISD1

#define TIMER_WAIT_US 80

uint8_t pathDetection(uint8_t* control_signals);
uint8_t objectDetection(uint8_t* control_signals);
void initADC();

void main() {
    // Initialize LCD
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    Lcd_Out(1, 1, "LawnBot :)");
    
    // initialize the sensors
    TRISD |= (1 << LEFT_SENSOR_DETECT_DIRECTION) | 
    (1 << RIGHT_SENSOR_DETECT_DIRECTION) |
    (1 << SONIC_ECHO_DIRECTION);
    
    TRISD &= ~(1 << SONIC_TRIGGER_DIRECTION);
    
    PORTD &= ~(1 << SONIC_TRIGGER_DIRECTION);

    // Enable interrupts
    INTCON |= (1 << GIE) | (1 << PEIE) | (1 << INTE);
    
    // initialize the timer module
    T1CON = 0x10;
    
    UART1_Init(9600); // Initialize the UART
    ADC_Init();

    
    while(1)
    {
        static uint8_t slaveControlSignals[] = {
            0x00, // Normal forward operation
            0x02, // Only enable left motor wheel
            0x04, // Only enable right motor wheel
            0x12 // Stop operation
        };

        pathDetection(slaveControlSignals);
        objectDetection(slaveControlSignals);
        
        // TODO: Output LCD
    }
}

/*
    Returns the current state of the wheel motors based on the outputted signal.
*/
uint8_t pathDetection(uint8_t* control_signals)
{
        // Check if there is any collision on any of the sensors steering sensors
        if((PORTD & (1 << RIGHT_SENSOR_DETECT)) && (PORTD & (1 << LEFT_SENSOR_DETECT)))
        {
            UART1_Write(*(control_signals + 3));
        }
        else if((PORTD & (1 << RIGHT_SENSOR_DETECT)))
        {
            UART1_Write(*(control_signals + 2));
        }
        else if((PORTD & (1 << LEFT_SENSOR_DETECT)))
        {
            UART1_Write(*(control_signals + 1));
        } else
        {
            UART1_Write(*(control_signals));
        }
}

/*
    Returns the current state of the robot based on the outputted signal.
*/
uint8_t objectDetection(uint8_t* control_signals)
{
    char output[3];
    static int sample = ADC_Read(0);
    LCD_Cmd(_LCD_CLEAR);
    // Approximately 40 cm
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