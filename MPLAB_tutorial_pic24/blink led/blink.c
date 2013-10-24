#include <p24FJ128GA306.h>

// Configure by dat_a3cbq91
    _CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & LPCFG_OFF & ICS_PGx1 & WINDIS_OFF & FWDTEN_WDT_SW &  FWPSA_PR128 & WDTPS_PS512);
    _CONFIG2(IESO_ON & FNOSC_FRC & FCKSM_CSECME & OSCIOFCN_OFF & IOL1WAY_OFF & POSCMD_HS);
    _CONFIG3(BOREN_ON);

int main(void)
{
    unsigned int i,k;
    TRISFbits.TRISF3 = 0;//output
    LATFbits.LATF3 = 1;//high level
    while(1)
    {
	    for(i=0; i<20; i++)
	    {
	        for(k=0;k<40000;k++)
	        {
	            
	        }
	    }
    	LATFbits.LATF3 = ~LATFbits.LATF3;
    }
    
    return 0;
}
