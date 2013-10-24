#include "define.h"

// Configure by dat_a3cbq91
    _CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & LPCFG_OFF & ICS_PGx1 & WINDIS_OFF & FWDTEN_WDT_SW &  FWPSA_PR128 & WDTPS_PS512);
    _CONFIG2(IESO_ON & FNOSC_FRC & FCKSM_CSECME & OSCIOFCN_OFF & IOL1WAY_OFF & POSCMD_HS);
    _CONFIG3(BOREN_ON);
// End by dat_a3cbq91
    
unsigned char UART2_data, ReceiveFlag = 0;

int main(void)
{
    OSCCON = 0x2001;//current osc HS, new osc FRC
	
    CLKDIV = 0x0000;//Fcy = Fosc/2

    /************Maping Pins************/
    //unlock registers
    asm volatile ("mov #OSCCONL, w1  \n"
        "mov #0x46, w2     \n"
        "mov #0x57, w3     \n"
        "mov.b w2, [w1]    \n"
        "mov.b w3, [w1]    \n"
        "bclr OSCCON, #6");

    /*------UART2-----*/
    // RX2 >> RP24
    RPINR19bits.U2RXR = 24;
    // TX2 >> RP23
    RPOR11bits.RP23R  = 5;

    //lock register
    asm volatile ("mov #OSCCONL, w1  \n"
        "mov #0x46, w2     \n"
        "mov #0x57, w3     \n"
        "mov.b w2, [w1]    \n"
        "mov.b w3, [w1]    \n"
        "bset OSCCON, #6");
    /*********************************end by lab411*****************************/

	ANSD = 0x0000;
    TRISFbits.TRISF3 = 0;
    UART2Init();
//    OpenUART2(UART_EN & UART_IDLE_STOP & UART_DIS_WAKE & UART_DIS_LOOPBACK & UART_NO_PAR_8BIT &
//              UART_1STOPBIT & UART_MODE_FLOW & UART_UEN_00 & UART_UXRX_IDLE_ONE& UART_BRGH_SIXTEEN,
//              UART_TX_ENABLE & UART_INT_RX_CHAR,
//              UART2BRG);
    //ConfigIntUART2(UART_RX_INT_EN & UART_TX_INT_DIS);
    Printf((const char *) "System is ready\r\n");
    LATFbits.LATF3 = 1;

    while(1)
    {
        if(ReceiveFlag)
        {
            switch(UART2_data)
            {
                case '1':
                    Printf((const char *)"My name is Nguyen Tien Dat\r\n");
                    break;

                case '2':
                    Printf((const char *)"I am studying in CTES\r\n");
                    break;

                case '3':
                    Printf((const char *)"My major is electronic and Telecommunication\r\n");
                    break;

                case '4':
                    Printf((const char *)"Nice to meet you\r\n");
                    break;

                default:
                    break;
            }
            ReceiveFlag = 0;
        }
    }
    return 0;
}

void _ISR __attribute__((interrupt, auto_psv)) _U2RXInterrupt(void)
{
    IFS1bits.U2RXIF = 0;
    UART2_data = U2RXREG;
    ReceiveFlag = 1;
    
    LATFbits.LATF3 = ~LATFbits.LATF3;
}
