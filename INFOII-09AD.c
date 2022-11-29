// =========================================================================================
//  Módulo: INFOII-09AD.C			                                  
//  Propósito: funciones de inicializacion y configuracion del conversor AD del F020                                 
//  Módulo componente de: INFOII-09
//  Fecha: 16-06-09
//  Autor: Ing. Gustavo Fresno
//  Tema : Conversores AD
// =========================================================================================

#include <INFOII.h>

#define				CANAL_LDR_COCINA				0
#define				CANAL_LDR_COMEDOR				4
#define 			CANAL_SENS_TEMP_COCINA			5

code unsigned char	Canal_ADC[] = {CANAL_LDR_COCINA,CANAL_LDR_COMEDOR,CANAL_SENS_TEMP_COCINA};					// Variable que indica el conversor que se esta utilizando

unsigned char		Puntero_Canal_ADC = 0;
unsigned int 		Medicion_ADC[3];						// Variables donde guardo lo leido por cada canal

//----------------------------------------------------------------------------------------------------
//			Funcion donde inicializo el ADC
//			Se inicializa de manera de configurar el ADC0 para funcionar por interrupcion
//----------------------------------------------------------------------------------------------------
void Inic_ADC(void)
{
	REF0CN = 0x03;

	EIE2 |= 0x02;
	AMX0CF = 0;	
								// Configuro los canales individuales y no diferenciales
	AMX0SL = Canal_ADC[Puntero_Canal_ADC];						// Elijo el canal 
	ADC0CF = 0x38;							// Divido la velocidad de muestreo a la minima velocidad de conversion	

	ADC0CN = 0xD0;							// Disparo la 1° conversion
}

//----------------------------------------------------------------------------------------------------
//	Interrupcion del conversor analogico-digital
//----------------------------------------------------------------------------------------------------
void Int_ADC0(void)	interrupt 15
{
	ADC0CN = 0;												// Paro la conversion

	Medicion_ADC[Puntero_Canal_ADC] = (unsigned int)ADC0H;	// Leo la lectura del canal y lo guardo en la respectiva variable
	Medicion_ADC[Puntero_Canal_ADC] *= 256;
	Medicion_ADC[Puntero_Canal_ADC] += (unsigned int)ADC0L;
	 
	AMX0CF = 0;												// Configuro los canales individuales y no diferenciales

	Puntero_Canal_ADC++;
							   			// Incremento el puntero

	if(Puntero_Canal_ADC==2)
	ADC0CF=0x3A;
	else
	ADC0CF=0x38;
									// Verifico que no sea mayor a 3 (x q tengo 3 conversores)
	if(Puntero_Canal_ADC==3)
	Puntero_Canal_ADC=0;
	
	AMX0SL = Canal_ADC[Puntero_Canal_ADC];					// Asigno y disparo el canal que deseo muestrear


	//Display(Medicion_ADC[Puntero_Canal_ADC]);										// Disparo la conversion de nuevo (quedo en un ciclo de conversion)
}	 