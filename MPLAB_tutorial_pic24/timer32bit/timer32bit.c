#include <p24fj128ga306.h>

// Configure by dat_a3cbq91
    _CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & LPCFG_OFF & ICS_PGx1 & WINDIS_OFF & FWDTEN_WDT_SW &  FWPSA_PR128 & WDTPS_PS512);
    _CONFIG2(IESO_ON & FNOSC_FRC & FCKSM_CSECME & OSCIOFCN_OFF & IOL1WAY_OFF & POSCMD_HS);
    _CONFIG3(BOREN_ON);
// End by dat_a3cbq91


#define CLOCK_DIVIDER_SETTING 0x0020
#define ONE_SECOND 62500

unsigned long period = ONE_SECOND;

void InitTimer32Bit(void);
int main()
{
	/*******************************create by lab411****************************/
    OSCCON = 0x2001;//current osc HS, new osc FRC

    CLKDIV = 0x0000;//Fcy = Fosc/2
    
	InitTimer32Bit();
	TRISFbits.TRISF3 = 0;
	LATFbits.LATF3 = 1;
	while(1);
	return 0;
}

void InitTimer32Bit(void)
{
	//T2CON = 0;
	T2CON = 0b0000000000001000 | CLOCK_DIVIDER_SETTING;//configure Timer2/3 for 32-bit operation, prescale 1:64
	T3CON = 0;
	
	TMR3 = 0;
	TMR2 = 0;
	
	PR3 = period >> 16;
	PR2 = period & 0xFFFF;
	
	IPC2bits.T3IP = 0x01;
	IFS0bits.T3IF  = 0;
	IEC0bits.T3IE = 1;
	//T2CONbits.T32 = 1;
	T2CONbits.TON = 1;
}

void _ISR __attribute__((interrupt, auto_psv)) _T3Interrupt(void)
{
	IFS0bits.T3IF = 0;
	LATFbits.LATF3 = ~LATFbits.LATF3;
}
