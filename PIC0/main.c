/*

MOTORPIC will control the motors.
These are the following states that the motor pic will have:

Truth table for the wheel motors

L   R   D   WL  WR  B
0   0   0   1   1   1
0   0   1   0   0   0
0   1   0   1   0   1
0   1   1   0   0   0
1   0   0   0   1   1
1   0   1   0   0   0
1   1   0   0   0   0
1   1   1   0   0   0

The only states that matters are:

0x00    :   0x07
0x02    :   0x05
0x04    :   0x03

Rest are 0

Because the L and R are from the sensor pic, the only values
that will matter to the MOTORPIC are WR and WL.

The D is either there is an object in front of the robot or not.
If there is an object at a certain distance (can be adjusted in simulation),
the motor blades will stop and the wheels will stop moving.

Because PORTB is eightbit, then it can be thought of as a byte.
The upper nibble of the PORTB is counted as the control signals.
These control signals are responsible for controlling the enable pins.

The lower nibble of PORTB is counted as the output signals for the motors.
This can be held at a constant 0101 as the enable pins will be responsible
for turning motors off.

*/

#include <stdint.h>

#define RIGHTWHEEL0 RB0
#define RIGHTHWEEL1 RB1
#define LEFTWHEEL0 RB2
#define LEFTHWEEL1 RB3
#define RIGHTHWEELENABLE RB4
#define LEFTWHEELENABLE RB5
#define BLADEMOTOR RB6

void switchRoutine(uint8_t* state);

void main() {

    TRISB = 0x00; // Set the entire PORTB as outputs.
    UART1_Init(9600); // Initialize UART communication
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
            PORTB = 0x35; // 0011 0101
            break;
        case 0x02:
            PORTB = 0x15; // 0001 0101
            break;
        case 0x04:
            PORTB = 0x25; // 0010 0101
            break;
        default:
            PORTB = 0xC5; // 1100 0101
    }
}