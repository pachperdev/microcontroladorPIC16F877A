// Mauricio Andres Pacheco Perez - 200088930
// Laura Vanessa Bermúdez vega - 200128427
// Tasa de transmisión(Baudios por segundo) = 9600
// Frecuencia del oscilador = 10Mhz

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 10000000
#include <xc.h>

void UART_Init(long baudRate){
    
    TRISC=0b10000000; //Configura Rx como entrada y Tx como salida
    
    SPBRG = (10000000UL/(long)(16UL*baudRate))-1;  //Paso 1: establecer la taza de baudios
    TXSTA = 0b00100100; //Paso 2/4/5: Modo asincrono, datos de 8 bits y habilitar trasmision
    RCSTA = 0b10010000; //Paso 4/5 (Rx) habilitar recepcion y datos de 8 bits
    
}

void UART_TxChar(char ch){
        
    while(TXIF==0);         //Esperar a que el registro de trasmision este vacio
    TXIF=0;                 //Limpiar bandera de trasmision
    TXREG = ch;             //Paso 7: cargar el dato a trasmitir en TxReg
}

char UART_RxChar(){
    
    while(RCIF==0);         //Esperar a que el dato sea recibido
    RCIF=0;                 //Limpiar bandera de recepcion
    return(RCREG);          //Retornar el dato recibido
}

int main() {
    char i,a[]={"Ingrese datos para realizar un eco\n"};
    char ch;
    
    UART_Init(9600);        //Inicia el modulo de UART con tasa de 9600
    __delay_ms(1000);       //Delay de un segundo
    for (i=0;a[i]!=0;i++){
        
        UART_TxChar(a[i]);  //Trasmitir el Cadena predefinida
        
    }
    
    while(1){
        
        ch = UART_RxChar(); //Recibe caracterl del puero serial
        UART_TxChar(ch);    //Trasmite por el puerto serial el caracter recibido
    }
}
