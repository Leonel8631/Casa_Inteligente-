
// =========================================================================================
//  Módulo: INFOII-07TX.C			                                  
//  Propósito: funciones de transmision y recepcion	del puerto serie
//  Fecha: 26-06-09
//  Autor: Ing. Gustavo Fresno
//=========================================================================================
#include "INFOII.h"
#include <string.h>
#define PUERTO_0		0

unsigned char		Buffer_UART[50];
unsigned char 		Tamanio_Paquete_UART = 0;
unsigned char 		Puntero_UART;
unsigned char	    Puerto_Serie = 0;
extern bit ESTADO_LED_1;
extern bit ESTADO_LED_2;
extern bit ESTADO_LED_3;
extern bit ESTADO_LED_4;

//=========================================================================================
// Configuro la UART
//=========================================================================================
void UART_Init(void)
{
//	char SFRPAGE_SAVE = SFRPAGE;		// Save Current SFR page
//	SFRPAGE = UART0_PAGE;
//   	SCON0 = 0x50; 
//	PCON = 0x80;                    	// SCON0: mode 1, 8-bit UART, enable RX
//	SSTA0 = 0x10; 						// BR / 1, T1 genera BR
//   	TI0    = 0;                         // Indicate TX0 ready
//	ES0 = 1; 
//	EIE2 = 0;

//	SFRPAGE = SFRPAGE_SAVE;				// Restore SFR page
	TCON = 0x00|(TCON&0x33);			// Timer 1 y 0 apagados
	TMOD = (TMOD&0x0f)|0x20;			// Timer 1 control por TR1, timer auto reload
	CKCON = (CKCON&0xF0)|0x10;			// T1CLK = SYSCLK

 	TH1 = -(SYSCLK/BAUDRATE/32);		// set Timer1 reload value for baudrate

   	TR1 = 1;                        	// Arranco el Timer1

   	SCON0 = 0x50;                     	// SCON0: mode 1, 8-bit UART, enable RX
   //ver que puerto serie utilizamos es SCON0 port 0 o SCON1
 	PCON = 0x80;

   	TI0    = 1;                         // Indicate TX0 ready
	ES0=1;

}

//=========================================================================================
// Interrupcion de la UART 0
//=========================================================================================
void Interrupcion_Serie0 (void) interrupt 4 
{
	unsigned char 	dato;

	if(SCON0 & 0x01) // RI0						// Chequeo RI1 en el registro SCON1, si llego una interupcion por recepcion
	{	
	//LED_3_ON;										// Verifico si ha Interrumpido por Recepción
	    SCON0 &= ~0x01;							// Reseteo Flag de Recepción

		dato = SBUF0;							// Vacío el buffer
	}
	else
	{
	
		if(SCON0 & 0x02)  	// TI0
		{										// Verifico si ha Interrumpido por Transmisión
		    SCON0 &= ~0x02;						// Reseteo Flag de transmision
			if(Tamanio_Paquete_UART)			// Si tengo datos para transmitir...
			{
				SBUF0 = Buffer_UART[Puntero_UART];
				
				Puntero_UART++;
				if(Puntero_UART == Tamanio_Paquete_UART)
				{
					Tamanio_Paquete_UART = 0;
					Puntero_UART = 0;
				}
			}
		}
	}
	return;
}


//=========================================================================================
// Para enviar un paquete a la UART 1
//=========================================================================================
void Enviar_Paquete_UART(unsigned char *Paquete, unsigned char Tamanio)
{
	unsigned char i;

	if(!Tamanio_Paquete_UART)
	{
		for(i = 0 ; i < Tamanio ; i++)
			Buffer_UART[i] = Paquete[i];  	// Copio todo al buffer de comunicaciones
	   
		Tamanio_Paquete_UART = Tamanio;
	    SCON0 &= ~0x02;						// Reseteo Flag de transmision
		SBUF0 = Buffer_UART[0];		   		// Disparo la nueva transmision
		Puntero_UART = 1;
	}
}	 
/*
//=========================================================================================
// Para enviar un valor a la UART 1
//=========================================================================================
void Enviar_Valor_UART ( int val , unsigned char Tamanio)
{
	unsigned char i;

	if(!Tamanio_Paquete_UART)
	{							 
		for (i = (Tamanio -1) ; i ; i-- )
		{
			Buffer_UART[i] = (val % 10) + '0';
			val /= 10;
		}
		  

		Tamanio_Paquete_UART = Tamanio - 1;
	    SCON0 &= ~0x02;						// Reseteo Flag de transmision
		SBUF0 = (val % 10) + '0';
		Puntero_UART = 1;
	}

}
 */	


 void Envio_Zonas(void)
 {	//El valor de la temperatura,el error si es que se genero, el estado
/*
	PROTOCOLO:	ENVIO   	<-DISP-ESTADO-T1-T2-.-T3-T4->-XSUM				
*/
	unsigned char i=0;
	unsigned char XSUM=0;
	unsigned char aux[6+1];

	aux[0]='<';					//Le paso el inicio
	aux[1]=1+'0';			//Temperatura 4 digitos
	aux[2]=ESTADO_LED_2;			//  |     
	aux[3]=ESTADO_LED_3;				//Punto que separa las unidades de las decimas
	aux[4]=ESTADO_LED_4;			//  |		//  --
	aux[5]='>';				//Fin de paquete
	

	for(i=0;i<6;i++)
		XSUM+=aux[i];		//genero el cheksum
	aux[6]=XSUM;			//cheksum de validacion
	Enviar_Paquete_UART(aux, 7);
	

}