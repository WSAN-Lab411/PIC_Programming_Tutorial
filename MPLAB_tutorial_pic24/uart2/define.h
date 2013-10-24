/* 
 * File:   define.h
 * Author: TienDat
 *
 * Created on July 26, 2013, 3:24 PM
 */

#ifndef DEFINE_H
#define	DEFINE_H

#include <p24FJ128GA306.h>

#define USE_FUNCTION_AVAILABLE

#ifdef USE_FUNCTION_AVAILABLE
    #include <uart.h>
#endif

#define CLOCK_FREQ  8000000
#define BAUD_RATE   19200
#define UART2BRG   (CLOCK_FREQ/2/16)/BAUD_RATE-1

void UART2Init(void);
void Printf(const char* string);
void UART2Put(unsigned char c);

#endif	/* DEFINE_H */

