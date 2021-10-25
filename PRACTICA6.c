// Mauricio Andres Pacheco Perez
// Laura Vanessa Bermúdez vega

//| Delay	|	prescaler |
//| 0,007	|	4	  |


#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h> 
// Esta libreria hace que MPLABX y CX8 carguen automaticamente las definiciones del microcontrolador que se usa en el proyecto

char value = 0;

void interrupt my_isr()
{
    if (TMR1IF==1)
    {
        value =~value;
        TMR1H = 0xDD;
        TMR1L = 0xD2;
        TMR1IF=0;
    }
}   
void main() 
{
    TRISB = 0x00;
    T1CON = 0b00100000;
    TMR1H = 0xDD;
    TMR1L = 0xD2;
    TMR1IE=1;
    GIE=1;
    PEIE=1;
    TMR1ON = 1;
    while(1)
    {
        PORTB = value;
    }
    
}
