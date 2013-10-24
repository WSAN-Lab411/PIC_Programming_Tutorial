#include "define.h"
void UART2Init(void)
{
    U2MODE = 0x0000;//enable UART2
                    //U2TX and U2RX pins are enabled and used
                    //Standard Speed mode (16 BRG clock cycles per bit)
                    //8-bit data, no parity
                    //One Stop bit

    U2STAbits.URXISEL = 0b00;
    U2BRG  = (CLOCK_FREQ/2/16)/BAUD_RATE-1;
    IEC1bits.U2RXIE = 1;
    U2MODEbits.UARTEN = 1;
    U2STAbits.UTXEN = 1;

    IFS1bits.U2RXIF = 0;         /*clear interrupt flag*/
}

void Printf(const char* string)
{
    unsigned char c;

    while( (c = *string++) != 0 )
    UART2Put(c);
}

void UART2Put(unsigned char c)
{
    while(U2STAbits.TRMT == 0);
    U2TXREG = c;
}
