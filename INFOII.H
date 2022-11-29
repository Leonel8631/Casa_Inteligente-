// =========================================================================================
//  Módulo: INFOII.H			                                                                   
//  Fecha: 16-03-09
//  Autor: Ing. Marcelo Trujillo - Ing. Juan Manuel Cruz
//  Tema : Macros
//=========================================================================================
// Cabeceras  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef F120
	#include "c8051f120.h"
#else
	#include "c8051f020.h"
#endif
	
#include <stdio.h>
#include <intrins.h>

// Nuevos Tipos  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef			unsigned char							FLAGS_TIMERS;
typedef			unsigned int							TIEMPOS;

// Tamaños // ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define			MAXIMO									10
#define			CANTIDAD_DIGITOS_DISPLAY				6
#define			CANT_ENT								8
#define			MAX_CONT_ANTIRREBOTES					100

// Cantidades  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define			DECIMAS									40
#define			SEGUNDOS								10
#define			MINUTOS									60
#define			HORAS									60

#define			CANTIDAD_DE_REBOTES						200
#define			TICKSdErEPETICION						200
#define			EntTICKSdErEPETICION					1000
#define			NO_KEY									((unsigned char ) 0xff)
 
// De Propósito general  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define			OFF										0
#define			ON										1
#define			BAJO									0
#define			ALTO									1
#define			ENTRADA									0
#define			SALIDA									1

#define			t_2500Hz_H								0xfd
#define			t_2500Hz_L								0x1f

// Para el puerto serie

#define			SYSCLK									(11059200 * 2)
#define			BAUDRATE								57600 

#define  		Cuentas_9600_bps_H						0xff
#define  		Cuentas_9600_bps_L						0xB8

// Temporizadores /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define			CANTIDAD_DE_TIMERS						8

typedef struct
{
	FLAGS_TIMERS	F_Final;
	TIEMPOS			Cuenta[CANTIDAD_DE_TIMERS];
}STRUCT_TIMER;

#define		  	ET_ENCENDER_1							0
#define		  	ET_ENCENDER_2							1
#define		  	ET_ENCENDER_3							2
#define		  	ET_ENCENDER_4							3

#define			T_LED_1									40
#define			T_LED_2									10
#define			T_LED_3									20
#define			T_LED_4									30

// --- Eventos 
#define			T0										0x01
#define			T1										0x02
#define			T2										0x04
#define			T3										0x08
#define			T4										0x10
#define			T5										0x20
#define			T6										0x40
#define			T7										0x80


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Definiciones de los puertos 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Declaraciones de Hardware  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ---- Salidas 
#define			Leds								P5
//#define			Entrada									P5
#define			Salidas								P7

//Maqueta
sbit sensor_puerta=				P2^6; //
sbit sensor_ventana_comedor=	P2^1; //
sbit sensor_mov_comedor=		P2^0;//BIEN
sbit sensor_ventana_hab=		P2^3;//
sbit sensor_ventana_banio=		P2^5;
sbit sensor_ventana_cocina=		P2^7;
sbit sensor_mov_cocina=			P2^2; //
sbit boton_panico=				P2^4;

// Display
#ifdef F120
sbit			DIGITO_0 =							P4^0;
sbit			DIGITO_1 =							P4^1;
sbit			DIGITO_2 =							P4^2;
sbit			DIGITO_3 =							P4^3;
sbit			DIGITO_4 =							P4^4;
sbit			DIGITO_5 =							P4^5;
#endif

sbit			PUERTO_DISPLAY_DP =					P3^0;
sbit			PUERTO_DISPLAY_G =					P3^1;
sbit			PUERTO_DISPLAY_F =					P3^2;
sbit			PUERTO_DISPLAY_E =					P3^3;
sbit			PUERTO_DISPLAY_D =					P3^4;
sbit			PUERTO_DISPLAY_C =					P3^5;
sbit			PUERTO_DISPLAY_B =					P3^6;
sbit			PUERTO_DISPLAY_A =					P3^7;

// Teclado
sbit			TECLADO_COLUMNA_1 = 				P1^4;
sbit			TECLADO_COLUMNA_2 = 				P1^5;
sbit 			TECLADO_COLUMNA_3 =					P1^6;
sbit 			TECLADO_COLUMNA_4 =					P1^7;

sbit			TECLADO_FILA_1 = 					P1^0;
sbit			TECLADO_FILA_2 = 					P1^1;
sbit			TECLADO_FILA_3 = 					P1^2;
sbit			TECLADO_FILA_4 = 					P1^3;

sbit			TECLADO_1 = 						P0^4;
sbit			TECLADO_2 = 						P0^5;
sbit			TECLADO_3 = 						P0^6;
sbit			TECLADO_4 = 						P0^7;

/*
sbit			LED_1 = 							P5^4;
sbit			LED_2 = 							P5^5;
sbit			LED_3 = 							P5^6;
sbit			LED_4 = 							P5^7;

sbit			BUZZER = 							P7^4;

sbit			RELE_0 = 							P7^0;
sbit			RELE_1 = 							P7^1;
sbit			RELE_2 = 							P7^2;
sbit			RELE_3 = 							P7^3;  
*/
#define			RELE_1_ON							(P7 |= 0x01)
#define			RELE_1_OFF							(P7 &= ~0x01)

#define			RELE_2_ON							(P7 |= 0x02)
#define			RELE_2_OFF							(P7 &= ~0x02)

#define			RELE_3_ON							(P7 |= 0x04)
#define			RELE_3_OFF							(P7 &= ~0x04)

#define			RELE_4_ON							(P7 |= 0x08)
#define			RELE_4_OFF							(P7 &= ~0x08)

// ---- Entradas 

// ---- Teclado 

// Acondicionamiento de las macros para la APLICACION //////////////////////////////////////////////////////////////////////////////////////////////////////////                	
// --- Salidas 
/*#define			SALIDA_1							(Salidas & 0x01)
#define			SALIDA_2							(Salidas & 0x02)
#define			SALIDA_3							(Salidas & 0x04)
#define			SALIDA_4							(Salidas & 0x08)

#define			SALIDA_1_ON							(Salidas |= 0x01)
#define			SALIDA_2_ON							(Salidas |= 0x02)
#define			SALIDA_3_ON							(Salidas |= 0x04)
#define			SALIDA_4_ON							(Salidas |= 0x08)

#define			SALIDA_1_OFF						(Salidas &= ~0x01)
#define			SALIDA_2_OFF						(Salidas &= ~0x02)
#define			SALIDA_3_OFF						(Salidas &= ~0x04)
#define			SALIDA_4_OFF						(Salidas &= ~0x08)*/	 

// --- Leds
/*#define			LED_1								(Leds & 0x20)
#define			LED_2								(Leds & 0x10)
#define			LED_3								(Leds & 0x40)
#define			LED_4								(Leds & 0x80) */

// Todos los leds probados.
#define			LED_1_ON							(Leds |= 0x20)
#define			LED_2_ON							(Leds |= 0x10)
#define			LED_3_ON							(Leds |= 0x40)
#define			LED_4_ON							(Leds |= 0x80)

#define			LED_1_OFF							(Leds &= ~0x20)
#define			LED_2_OFF							(Leds &= ~0x10)
#define			LED_3_OFF							(Leds &= ~0x40)
#define			LED_4_OFF							(Leds &= ~0x80)	
// --- Salidas

#define			BUZZER_OFF							(Salidas &= ~0x10)
#define			BUZZER_ON							(Salidas |= 0x10)




// --- Teclado
// Codigo de teclas
#define			TECLA_1										1
#define			TECLA_2	                                    2
#define			TECLA_3	                                    3
#define			TECLA_4	                                    4
#define			TECLA_5										5
#define			TECLA_6	                                    6
#define			TECLA_7	                                    7
#define			TECLA_8	                                    8
#define			TECLA_9										9
#define			TECLA_NUMERAL                               11
#define			TECLA_0                                     0
#define			TECLA_ASTERISCO	                            10

#define			TECLA_F1                                    12
#define			TECLA_F2                                    13
#define			TECLA_F3                                 	14
#define			TECLA_F4                                    15


// Filas


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Pototipos //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Aplicacion
void Aplicacion(void);
unsigned char Ingreso_Clave(void);
void Estado_Sensores(void);
unsigned char Cambio_Clave(void);
void Chequear_Luz(void);
void Chequear_Temperatura(void);



// *FW.c
void Inicializar ( void ) ;
void Board(void) ;
void BoardSW( unsigned char ) ;
unsigned char BoardHW(void) ;
void Barrido_Leds(void);
void Barrido_Display(void);
void Barrido_Salidas(void);

// Modulo: *TM.c
void TIMERS_Encender(unsigned char Nro_Timer, TIEMPOS Tiempo);
void TIMERS_Apagar_Todos(void);
void TIMERS_Detener(unsigned char Nro_Timer);
void TIMERS_Verificar_Fin(void);
void TIMERS_Descuento(unsigned char Nro_Timer);
void TIMERS_Inicializar(void);

// Modulo: *IO.c
unsigned char Get_Key(void);
void Display(long );

// Modulo: *IN.c
void SYSCLK_Crystal_Init(void);
void Init_PLL(void);
void PORT_Init(void);
void UART_Init(void);
void Resetear(void);
void Inicializacion(void);
void Inicializacion_Timer(void);

// Modulo: *TX.c
void Envio_Zonas(void);
void UART_Init(void);
void Interrupcion_Serie0 (void);
void Enviar_Paquete_UART(unsigned char *, unsigned char );
void Enviar_Valor_UART ( int  , unsigned char );
void Enviar_Paquete_UART_POOLING(unsigned char *, unsigned char );
void Sacar_Caracter_x_Puerto_Serie(unsigned char Puerto, unsigned char Caracter);
void Sacar_Cadena_x_Puerto_Serie(unsigned char Puerto, unsigned char *Buffer);



#define 		COMANDO										1

#define 		PUERTO_NUM7SEG 							0x84 //PUERTO 4	LCD y 7 SEG
#define 		PUERTO_LCD     							0x86 //PUERTO 6

//Display LCD
sfr     		P_DATOS	  =					PUERTO_LCD;//Defino el puerto de envio de datos del LCD
sfr				CONFLCD	  =					PUERTO_NUM7SEG;//Configuracion de e rs


//Mascaras de Configuracion LCD
#define			RS_ON						(CONFLCD |= 0x80)   // Bit 7 del P4 ON
#define			RS_OFF						(CONFLCD &= ~ 0x80) // Bit 7 del P4 OFF
#define			E_ON						(CONFLCD |= 0x40)   // Bit 6 del P4 ON
#define			E_OFF						(CONFLCD &= ~ 0x40) // Bit 6 del P4 OFF

//CODIGO LCD
#define 		COMANDO										1
#define			DATO										0
#define 		LCD_INIC									0x37


//Modulo: LCD
void Escribir4(bit opcion,unsigned char DATA); 					//escribir dato en modo 4 bits------PRIMITIVA del LCD------
void Escribir8(bit opcion,unsigned char COMANDOS);				//escribir comando en modo 4 bits ------PRIMITIVA del LCD------
void DISPLAYLCD(unsigned char *texto, unsigned char cantidad, bit reglon,unsigned char posicion);//Envio caracteres al display -----Driver del LCD-----
void DISPLAYLCD_NUMERO(unsigned int numero, unsigned char cifras,bit reglon,unsigned char posicion);	//Envio un numero al display ------Driver del LCD-----
void Inic_LCD(void);											//Inicializa el display LCD
void delay(void);								//Demora de un valor tiempo
void delay2(void);

//void Int_ADC0(void);
void Inic_ADC(void);



