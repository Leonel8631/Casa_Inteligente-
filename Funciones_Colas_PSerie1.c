//-----------------------------------------------------------------------------
//-	Archivo:				Funciones_Colas_PSerie.C											-
//-----------------------------------------------------------------------------
//-	Comentario:				Manejo de Comunicacion Serie con colas y 		-
//-							por interrupcion.								-
//-							Adaptado para usarlo con varias colas.			-
//-							Encapsulado para driver generico				-
//-																			-
//-	Autor Original: Ing. Juan Cruz
//- Modificacion: Ing. Fresno Gustavo
//-	Version:				002												-
//-	Fecha inicio:			09/2006											-
//-	Ultima Modificacion:	10/2006											-
//-----------------------------------------------------------------------------
//
//-----------------------------
//-	Inclusion de Archivos	-
//------------------------------
#include <C8051F020.H>
#include "Funciones_Colas_PSerie.h"

STRUCT_COLA	UART1; 	// Estructura principal
/* ------------------
   -	Programa	-
   ------------------ */


//---------------------------------------------------------------------------------
//-	Funcion:		void InicializarSerie (void);		       					-
//---------------------------------------------------------------------------------
//-	Accion:			Inicializa la Cola de Recepcion,							-
//-					Inicializa la Cola de Transmision,							-
//-					Inicializa variables de Control de Comunicacion Serie.		-
//--------------------------------------------------------------------------------- */
void InicializarSerie1 (void)
{
	InicializarColaRecepcion1();					// Inicializo la Cola de Recepcion
	InicializarColaTransmision1();					// Inicializo la Cola de Transmision
	UART1.TX.TxEnCurso = 0;							// Señalizo Transmision En Curso NO
}

//---------------------------------------------------------------------------------
//-	Funcion:		void InicializarColaRecepcion (void);						-
//---------------------------------------------------------------------------------
//-	Accion:			Inicializa el Contador de Datos Almacenados en la Cola,		-
//-					Inicializa el Puntero para la Entrada de Datos a la Cola,	-
//-					Inicializa el Puntero para la Salida de Datos de la Cola.	-
//---------------------------------------------------------------------------------
void InicializarColaRecepcion1(void)
{
	uint32_t i;

	UART1.RX.CantidadCola = 0;		// Inicializo Contador de Datos Almacenados
	UART1.RX.EntradaCola = 0;		// Inicializo el Puntero para la Entrada de Datos
	UART1.RX.SalidaCola = 0;		// Inicializo el Puntero para la Salida de Datos

	for( i = 0 ; i < LONG_COLA_RX1 ; i++)
		UART1.RX.Cola[i] = 0;
}
//---------------------------------------------------------------------------------
//-	Funcion:		uint8_t CantidadEnColaRecepcion (void);				-
//---------------------------------------------------------------------------------
//-	Devuelve:		la cantidad de datos almacenados en la Cola de RX.			-
//---------------------------------------------------------------------------------
uint32_t CantidadEnColaRecepcion1(void)
{
    return (UART1.RX.CantidadCola);				// Retorno Contador de Datos Almacenados en la Cola
}

//---------------------------------------------------------------------------------
//-	Funci�n:	uint8_t AgregarDatoColaRecepcion (uint8_t dato) 	-
//---------------------------------------------------------------------------------
//-	Acci�n:		Almacena el dato recibido en la cola de RX						-
//-				Incrementa el contador de datos almacenados en la cola,			-
//-				actualiza el puntero de ingreso de datos a la cola.				-
//-	Recibe:		Dato a almacenar												-
//-	Devuelve:	OK			Si no hubo problemas								-
//-				ERROR		Si la cola estaba llena								-
//--------------------------------------------------------------------------------- */
uint8_t AgregarDatoColaRecepcion1(uint8_t dato)
{
	// Verifico si la Cola esta llena
	if(UART1.RX.CantidadCola >= LONG_COLA_RX1)
	{
		return (ERROR_COLA_RX_LLENA);
	}

	// Almaceno el Dato en la Cola
	UART1.RX.Cola[UART1.RX.EntradaCola] = dato;
	// Incremento el puntero de entrada de la cola de datos
	UART1.RX.EntradaCola++;

	// Verifico si llegue al fin de la Cola
	if (UART1.RX.EntradaCola >= LONG_COLA_RX1)
		UART1.RX.EntradaCola = 0;						// Inicializo Puntero para la Entrada de Datos a la Cola

	// Incremento el contador de datos recibidos
	UART1.RX.CantidadCola++;

	return (OK);								
}

//---------------------------------------------------------------------------------
//-	Funcion:	unsigned char RetirarDatoColaRecepcion (void)			-
//---------------------------------------------------------------------------------
//-	Accion:		Recupera un dato de la cola de RX.								-
//-				Decrementa el contador de datos almacenados en la cola,			-
//-				actualiza el puntero de egreso de datos de la cola.				-
//-	Recibe:		void.								-
//-	Devuelve:	OK			Si no hubo problemas								-
//-				ERROR		Si la cola estaba vacia								-
//--------------------------------------------------------------------------------- */
uint8_t RetirarDatoColaRecepcion1(void)
{
	uint8_t dato;

	// Verifico si la Cola esta Vacia
	if(UART1.RX.CantidadCola == 0)
	{
		return (ERROR_COLA_RX_VACIA);
	}

	// Retiro el dato de la cola de datos
	dato = UART1.RX.Cola[UART1.RX.SalidaCola];
	// Incremento el puntero de salida de la cola de datos
	UART1.RX.SalidaCola++;

	// Verifico si llegue al fin de la Cola
	if (UART1.RX.SalidaCola >= LONG_COLA_RX1)
		UART1.RX.SalidaCola = 0;

	// Decremento el contador de datos recibidos
	UART1.RX.CantidadCola--;

	return dato;
}

//---------------------------------------------------------------------------------
//-	Funcion:		void InicializarColaTransmision (void);						-
//---------------------------------------------------------------------------------
//-	Accion:			Inicializa el Contador de Datos Almacenados en la Cola,		-
//-					Inicializa el Puntero para la Entrada de Datos a la Cola,	-
//-					Inicializa el Puntero para la Salida de Datos de la Cola.	-
//--------------------------------------------------------------------------------- */
void InicializarColaTransmision1(void)
{
	uint32_t i;

	UART1.TX.CantidadCola = 0;		// Inicializo Contador de Datos Almacenados
	UART1.TX.EntradaCola = 0;		// Inicializo el Puntero para la Entrada de Datos
	UART1.TX.SalidaCola = 0;		// Inicializo el Puntero para la Salida de Datos

	for( i = 0 ; i < LONG_COLA_TX1 ; i++)
		UART1.TX.Cola[i] = 0;
}

//---------------------------------------------------------------------------------
//-	Funci�n:	unsigned char CantidadEnColaTransmision (void);		  		   	-
//---------------------------------------------------------------------------------
//-	Devuelve:	la cantidad de datos almacenados en la cola de TX.				-
//--------------------------------------------------------------------------------- */
uint8_t CantidadEnColaTransmision1(void)
{
    return (UART1.TX.CantidadCola);			// Retorno Contador de Datos Almacenados en la Cola
}
//---------------------------------------------------------------------------------
//-	Funcion:	unsigned char AgregarDatoColaTransmision (uchar dato)			-
//---------------------------------------------------------------------------------
//-	Accion:		Almacena el Dato recibido en la cola de TX.						-
//-				Incrementa el Contador de Datos Almacenados en la Cola,			-
//-				actualiza el Puntero de Ingreso de Datos a la Cola.				-
//-	Recibe:		Dato a almacenar												-
//-	Devuelve:	OK			Si no hubo problemas									-
//-				ERROR		Si la cola estaba llena								-
//--------------------------------------------------------------------------------- */
uint8_t AgregarDatoColaTransmision1(uint8_t dato)
{	
	if(UART1.TX.CantidadCola >= LONG_COLA_TX0)			// Verifico si la Cola No esta Llena
	{
		return (ERROR_COLA_TX_LLENA);
	}
		
		UART1.TX.Cola[UART1.TX.EntradaCola] = dato;			// Almaceno el Dato en la Cola
		UART1.TX.EntradaCola++;
	
		UART1.TX.CantidadCola ++;							// Incremento Contador de Datos Almacenados en la Cola

		if (UART1.TX.EntradaCola >= LONG_COLA_TX1)
			UART1.TX.EntradaCola = 0;
		
		if (UART1.TX.TxEnCurso == 0)						// Verifico si NO Hay Transmision en Curso
		{
	        RI0 = 0;
	        SBUF1 = RetirarDatoColaTransmision1();
			UART1.TX.TxEnCurso = 1;
		}
		
		return (OK);										// Retorno Exito
	
}

//---------------------------------------------------------------------------------
//-	Funcion:	uint8_t RetirarDatoColaTransmision (void)	 			-
//---------------------------------------------------------------------------------
//-	Accion:		Recupera un dato de la cola de TX.								-
//-				Decrementa el Contador de Datos Almacenados en la Cola,			-
//-				actualiza el puntero de egreso de datos de la cola.				-
//-	Recibe:		void.								-
//-	Devuelve:	OK			Si no hubo problemas								-
//-				ERROR		Si la cola estaba vacia								-
//--------------------------------------------------------------------------------- */
uint8_t RetirarDatoColaTransmision1 (void)
{
	uint8_t dato;

	if(UART1.TX.CantidadCola == 0)				// Verifico si la Cola esta Vacia
	{
		return (ERROR_COLA_TX_VACIA);
	}
		dato = UART1.TX.Cola[UART1.TX.SalidaCola];	// Recupero el Dato de la Cola
		UART1.TX.SalidaCola++;

		UART1.TX.CantidadCola --;					// Decremento Contador de Datos Almacenados en la Cola

		if (UART1.TX.SalidaCola >= LONG_COLA_TX1)
			UART1.TX.SalidaCola = 0;
	
		return dato;	
	
}

//---------------------------------------------------------------------------------
//-	Funcion:	void UART_Handler (void)	 			-
//---------------------------------------------------------------------------------
//-	Accion:		Funcion interrupcion de la UART				-
//-	Recibe:		void							-
//-	Devuelve:	void							-
//--------------------------------------------------------------------------------- */
void UART_Handler(void) interrupt 20
{
    if(SCON1 & 0x01)
    {
        SCON1 &= ~0x01;

        AgregarDatoColaRecepcion1(SBUF1);
    }
    else
    {
        if(SCON1 & 0x02)
        {	SCON1 &= ~0x02;
            

            if(CantidadEnColaTransmision1()!=0)
                SBUF1 = RetirarDatoColaTransmision1();
			
        }
    }
}

