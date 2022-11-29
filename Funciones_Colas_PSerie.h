/*
 * Funciones_Colas_PSerie.h
 *
 *  Created on: 20/06/2011
 *      Author: Gustavo Fresno
 */

#ifndef FUNCIONES_COLAS_PSERIE_H_
#define FUNCIONES_COLAS_PSERIE_H_

typedef unsigned char       uint8_t;
typedef unsigned int        uint16_t;
typedef unsigned long       uint32_t;

#define LONG_COLA_RX0		100
#define LONG_COLA_TX0		100
#define LONG_COLA_RX1		100
#define LONG_COLA_TX1		100

#define	OK					0
#define ERROR_COLA_RX_LLENA	2
#define ERROR_COLA_RX_VACIA	3
#define	ERROR_COLA_TX_LLENA	4
#define ERROR_COLA_TX_VACIA 5

typedef struct
{
	struct
	{
				uint8_t     Cola[LONG_COLA_RX0];	// Cola en la que se Almacenan los Datos
                uint8_t     CantidadCola;			// Contador de Datos Almacenados en la Cola
                uint8_t 	EntradaCola;			// Puntero para la Entrada de Datos a la Cola
                uint8_t 	SalidaCola;				// Puntero para la Salida de Datos de la Cola
	}RX;

	struct
	{
		uint8_t     Cola[LONG_COLA_TX0];	// Cola en la que se Almacenan los Datos
		uint8_t     CantidadCola;			// Contador de Datos Almacenados en la Cola
		uint8_t 	EntradaCola;			// Puntero para la Entrada de Datos a la Cola
		uint8_t 	SalidaCola;				// Puntero para la Salida de Datos de la Cola
		uint8_t 	TxEnCurso;				// Flag que indica si hay transmision en curso
	}TX;
}STRUCT_COLA;

/*void InicializarSerie0 (void);
void InicializarColaRecepcion0(void);
uint32_t CantidadEnColaRecepcion0(void);
uint8_t AgregarDatoColaRecepcion0(uint8_t dato);
uint8_t RetirarDatoColaRecepcion0(void);
void InicializarColaTransmision0(void);
uint8_t CantidadEnColaTransmision0(void);
uint8_t AgregarDatoColaTransmision0(uint8_t dato);
uint8_t RetirarDatoColaTransmision0 (void);
//TODAS SON PARA EL PUERTO SERIAL		*/
void InicializarSerie1 (void);
void InicializarColaRecepcion1 (void);
uint32_t CantidadEnColaRecepcion1(void);
uint8_t AgregarDatoColaRecepcion1(uint8_t dato);
uint8_t RetirarDatoColaRecepcion1(void);
void InicializarColaTransmision1(void);
uint8_t CantidadEnColaTransmision1(void);
uint8_t AgregarDatoColaTransmision1(uint8_t dato);
uint8_t RetirarDatoColaTransmision1 (void);
//PARA EL PUERTO USB				  
#endif /* FUNCIONES_COLAS_PSERIE_H_ */