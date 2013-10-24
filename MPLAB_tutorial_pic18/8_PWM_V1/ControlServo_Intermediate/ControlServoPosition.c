/* ***************************************************************************
**  File Name    	: ControlServoPosition.c
**  Version			: 1.0
**  Description		: rotate automatically servo motor from -90 to +90 degree
**  Author			: NguyenTienDat
**	Class			: KSTN - DTVT - K54
**  Microcontroller	: PIC18F46K20
**  Compiler     	: Microchip C18 v3.34 C Compiler
**  IDE          	: Microchip MPLAB IDE v8.70
**  Programmer   	: Microchip PICKit2 Programmer
**  Last Updated 	: 7 Feb 2012
**	Describe     	: In this my program, I completely use available functions
**					  which it built in MCC18. So, the program become very short
**					  Base on the program, you can develope more than, so, let using
**					  your creative thinking and produce your program. Hope you enjoy it!
** ***************************************************************************/
#include <p18f46k20.h>
#include <timers.h>
#include <pwm.h>

#pragma config FOSC = INTIO67
#pragma config WDTEN = OFF, LVP = OFF

char k=0;
unsigned char duty_cycle[] = {63,65,70,75,80,85,90,95,100,105,110,115,120,124};

void main(void)
{	
	char period = 249;
	
	//----------------------open TMR2 before Open PWM2--------------------------------------------
	OpenTimer2(TIMER_INT_OFF&T2_PS_1_16&T2_POST_1_1);
	
	//-------------------------Configure pwm -----------------------------------------------------
	OpenPWM2(period);			//Configure PWM module and initialize PWM period
	
	//---------------------set duty cycle---------------------------------------------------------
	SetDCPWM2(duty_cycle[k]);		//set the duty cycle
	
	//-----------------------use TMR0 to change position of servo----------------------------------
	OpenTimer0( TIMER_INT_OFF & T0_16BIT & T0_SOURCE_INT & T0_PS_1_4 );
	
	while(1)
	{
		while(!INTCONbits.TMR0IF);//waiting for the flag is set
		INTCONbits.TMR0IF = 0;//clear flag for next times overflow
		k=k+1;
		SetDCPWM2(duty_cycle[k]);//new duty cycle
		if(k==13) k=-1;
	}
}
