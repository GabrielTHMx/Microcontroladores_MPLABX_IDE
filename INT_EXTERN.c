/*
 * File:   Cnfiguracion inicial de PIC18F4550
 * Author: Gabriel Santana Martinez
 *
 * Created on 4 de abril de 2022, 03:34 PM
 */
// CONFIG1L
#pragma config PLLDIV = 2       // PLL Prescaler Selection bits (Divide by 2 (8 MHz oscillator input))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 2       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes from the 96 MHz PLL divided by 2)

// CONFIG1H
#pragma config FOSC = HSPLL_HS  // Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

#define _XTAL_FREQ 48000000
#include <xc.h>
#include <pic18f4550.h>

void main(void) {
    
    //CONFIGURACION DE GPIOs
    ADCON1bits.PCFG = 0x0f;
    TRISC = 0x00    ;
    LATC = 0x00;
    
    /*//CONFIGURACION DE INTERRUPCION EXTERNA INT0
    TRISBbits.RB0 = 1;                          //RB0 - INT0 como entrada
    INTCONbits.INT0E = 1;                       //INT0 habilitada   
    INTCONbits.INT0F = 0;                       //Flag de INT0 en 0 = interrupcion aun no ha ocurrido  
    INTCON2bits.INTEDG0 = 1;                    //Rising edge*/
    
    //CONFIGURACION DE INTERRUPCION EXTERNA INT1 CON PRIORIDAD
    TRISBbits.RB1 = 1;                          //RB1 - INT1 como entrada
    INTCON3bits.INT1E = 1;                      //INT1 hailitada
    INTCON3bits.INT1IP = 1;                     //INT1 como ALTA PRIORIDAD
    INTCON3bits.INT1F = 0;                      //Flag de INT1 en 0, INT1 no ha ocurrido
    INTCON2bits.INTEDG1 = 1;                    //Rising edge
    
    //CONFIGURACION DE INTERRUPCION EXTERNA INT2 CON BAJA PRIORIDAD
    TRISBbits.RB2 = 1;                          //RB2 - INT2 como entrada
    INTCON3bits.INT2E = 1;                      //INT2 habilitada
    INTCON3bits.INT2IP = 0;                     //INT2 como BAJA PRIORIDAD
    INTCON3bits.INT2F = 0;                      //Flag de INT2 en 0, INT2 no ha ocurrido
    INTCON2bits.INTEDG2 = 1;                    //Rising edge
    
    RCONbits.IPEN = 1;                          //Habilitacion de niveles de PRIORIDAD
    INTCONbits.GIEH = 1;                        //Habilitacion de ALTA PRIORIDAD en interrupciones
    INTCONbits.GIEL = 1;                        //Habilitacion de BAJA PRIORIDAD en interrupciones
    //INTCONbits.PEIE = 1;                         //Habilitacion de interrupciones globales
    //INTCONbits.GIE = 1;                         //Habilitacion de interrupciones globales
    
    int i = 0;
    while (1) 
    {
        for( i = 1; i <= 64; i *= 2)
        {
            LATC = i;
            __delay_ms(500);
        }
    }
}

/*void __interrupt() Int_Ext_0()
{
    if(INTCONbits.INT0F == 1)               //Verifica si la interrupcion ha ocurrido
    {   
        //ACCIONES A EJECUTAR
        for(int i = 0; i <= 2; i ++)
        {
            LATC = 255;
            __delay_ms(500);
            LATC = !LATC;
            __delay_ms(500);
        }
        
        INTCONbits.INT0F = 0;               //Limpia flag de INT0
    }
}*/

void __interrupt(high_priority) Int_Ext_1()
{
    if(INTCON3bits.INT1F == 1)
    {
        //ACCIONES A EJECUTAR
        for(int i = 0; i <= 3; i ++)
        {
            LATC = 7;
            __delay_ms(500);
            LATC = !LATC;
            __delay_ms(500);
        }
        
        INTCON3bits.INT1F = 0;              //Limpia flag de INT1
    }
}

void __interrupt(low_priority) Int_Ext_2()
{
    if(INTCON3bits.INT2F == 1)
    {
        //ACCIONES A EJECUTAR
        for(int i = 0; i <= 4; i ++)
        {
            LATC = 112;
            __delay_ms(500);
            LATC = !LATC;
            __delay_ms(500);
        }
        
        INTCON3bits.INT2F = 0;              //Limpia flag de INT1
    }
}
