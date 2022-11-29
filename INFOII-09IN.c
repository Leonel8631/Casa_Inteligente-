// =========================================================================================
//  Módulo: INFOII-09IN.C			                                  
//  Propósito: funciones de inicializacion o configuracion del F020                                 
//  Módulo componente de: INFOII-09
//  Fecha: 01-05-09
//  Autor: Ing. Gustavo Fresno
//  Tema : Inicializacion
// =========================================================================================

#include <INFOII.h>

//------------------------------------------------------------------------------------
// PORT_Init
//------------------------------------------------------------------------------------
void PORT_Init(void)
{
#ifdef F120
	char SFRPAGE_SAVE = SFRPAGE;	// Save Current SFR page
	SFRPAGE = CONFIG_PAGE;			// Switch to configuration page
#endif
									//										76543210
	XBR0 = 0x04;					// Enable UART0 y el  					00000110
	XBR1 = 0x14;					// Enable /INT0 E /INT1	   				00010100
	XBR2 = 0xC4;					// Enable crossbar, UART1				01000100
									// and weak pull-ups globally enable
	
////  Port Output Mode Register (Open Drain or Push Pull)
	P0MDOUT = 0x00;      			  
	P1MDOUT = 0x0f;      
	P2MDOUT = 0x00;      
	P3MDOUT = 0x00;
//	P5MDOUT = 0XF0;     
	P74OUT = 0xcb;					// Configuro el puerto 5 como push-pull	el 
									// nibble alto y open-drain el nibble bajo
//	XBR0 = 0x04;					// Habilito UART0	  					00000100
//	XBR1 = 0x00;					// Todo dehabilitado	   				00000000
//	XBR2 = 0x44;					// Habilito crossbar y UART1			01000100
//								   	// Habilito pull-up
//
////  Port Output Mode Register (Open Drain or Push Pull)
////	P74OUT = 0x08;					// Configuro el puerto 5 como push-pull	el 
////									// nibble alto y open-drain el nibble bajo
////
//	P1MDOUT = 0x5f;    				// Configuro los pines del display como push-pull
//	P2MDOUT = 0xff; 
//
//	P5 = 0x0f;
}

#ifdef F120
void SYSCLK_Crystal_Init(void)
{
	unsigned int xdata i;				// delay counter

	char SFRPAGE_SAVE = SFRPAGE;		// Save Current SFR page

	SFRPAGE = CONFIG_PAGE;				// Set SFR Page
	
	OSCXCN = 0x67;						// start external oscillator with
										// 11.0592MHz crystal (XFCN = 7)
	for (i = 0 ; i < 256 ; i++);		// XTLVLD blanking interval (>1ms)
	
	while (!(OSCXCN & 0x80));			// Wait for crystal osc. to settle
	
	SFRPAGE = LEGACY_PAGE;
	RSTSRC = 0x06;						// enable missing clock detector, y el supervisor de tencion
	SFRPAGE = CONFIG_PAGE;
	CLKSEL = 0x01;						// select external oscillator as SYSCLK
										// source
	OSCICN = 0x00;						// disable internal oscillator
	
	SFRPAGE = SFRPAGE_SAVE;				// Restore SFR page
}
#else
void SYSCLK_Crystal_Init(void)
{
	unsigned int i;						// Variable local
	
	OSCXCN = 0x67;						// Configuro el registro de control del oscilador 
										// 01100111
										// Habilito el oscilador para funcionar con cristal (22.1184MHz)
										// Configuro el rango de trabajo del oscilador
	
	for (i=0; i < 256; i++);			// Demora "Cuidado esta demora (bloqueante) se puede hacer porque 
										// estoy en la inicializacion y no bloqueo ningun otro proceso!!!!
										// Hay que hacer esta demora para que se estabilice el oscilador

	while (!(OSCXCN & 0x80));			// Espero hasta que se estabilice (Cuidado es bloqueante!!)

	OSCICN = 0x88;						// Configuro el oscilador interno
										// 10001000
										// Configuro el micro para utilizar el oscilador externo

	while (!(OSCXCN & 0x80));			// Espero hasta que se estabilice (Cuidado es bloqueante!!)

	OSCICN = 0x08;						// Configuro el oscilador interno
										// 00001000
										// Configuro el micro para utilizar el oscilador externo
}
#endif
//-----------------------------------------------------------------------------
// SYSPLL_Init
//-----------------------------------------------------------------------------
// This routine initializes the system PLL to use an 11.0592 MHz crystal
// as its clock source. Pasamos del Clock externo al PLL
// ----------------------------------------------------------------------------
#ifdef F120
void Init_PLL(void)
{
	char xdata i;                   // delay counter
	char SFRPAGE_SAVE = SFRPAGE;    // Save Current SFR page

// Estos pasos son asi, estan explicados en las HD

	SFRPAGE = CONFIG_PAGE;			// Set SFR Page
	PLL0CN = 0x04;					// 2- PLLSRC   (Page = F )
	SFRPAGE = LEGACY_PAGE;
	FLSCL = 0x20;					// 3- FLRT     (Page = 0 )
	SFRPAGE = CONFIG_PAGE;
	PLL0CN = 0x05;					// 4- PLLPWR   (Page = F )

	PLL0DIV = 0x01;
	PLL0FLT = 0x37;
	PLL0MUL = 0x01;
	
	for (i = 0 ; i < 5 ; i++);		// blanking interval (>5us)

	while (!(PLL0CN && 0x10));		// PLLCK Wait for PLL. to settle
	
	PLL0CN = PLL0CN | 0x02;			// 2- PLLEN (Page = F )
	CLKSEL = 0x32;					// select PLL as SYSCLK source (Page =  F)
	SFRPAGE = SFRPAGE_SAVE;			// Restore SFR page
}
#endif

//------------------------------------------------------------------------------------
// Esta funcion resetea el microcontrolador
//------------------------------------------------------------------------------------
/*void Resetear(void)
{
	RSTSRC |= 0x01;						// HW Reset
}
  */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*	Propósito: Inicialización de Hardware en el arranque del programa
//*	Parámetros: void
//*	Retorna: void
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Inicializacion(void)
{
	WDTCN = 0xDE;                       // Deshabilito el watchdog timer
	WDTCN = 0xAD;
	 
	SYSCLK_Crystal_Init();             	// Configuro el Oscilador
#ifdef F120
	Init_PLL();							// Cambio el PLL 
#endif
	P7=0X10;

	PORT_Init();						// Configuro los puertos

	Inicializacion_Timer();				// Configuro los timers
	TIMERS_Inicializar();
}

//------------------------------------------------------------------------------------
// Esta funcion configura el temporizador 0 para utilizarse como base de tiempo
//------------------------------------------------------------------------------------
void Inicializacion_Timer(void)
{
#ifdef F120
	char SFRPAGE_SAVE = SFRPAGE;    // Save Current SFR page
	SFRPAGE = TIMER01_PAGE;
#endif

	EA = 0;								// Deshabilito todo por las dudas

//------------------ TIMER 0 -----------------------------------
// Timer 0:	
//						  SYSCLK
//			Cuenta =    ___________
//			     		(65536-Tn)
//
//			Cuenta = tiempo que quiero contar. ej 2500 Hz
//
//			SYSCLK = Xtal
//--------------------------------------------------------------


	TH0 = t_2500Hz_H;				// 2500Hz
	TL0 = t_2500Hz_L;				// Xtal 22MHz
	TMOD = 0x01;					// Configuro el modo 1 de funcionamiento para el timer 0
	CKCON = 0;				   	// Configuro el divisor del clock
	
	TR0 = 1;
	ET0=1;						// Es un bit de TCON, Habilito el timer 0 para muestrar en tiempo
	TF0 = 0;
//--------------------------------------------------------------

//------------------ TIMER 1 -----------------------------------
   	TH1 = -(SYSCLK/BAUDRATE/16);	// set Timer1 reload value for baudrate
   	TR1 = 1;                        // start Timer1
	ET1 = 0;						// Deshabilito la interrupcion timer 1
	TF1 = 0;
//--------------------------------------------------------------

	EA = 1;							// Habilito todas las interrupciones

#ifdef F120
	SFRPAGE = SFRPAGE_SAVE;
#endif
}



