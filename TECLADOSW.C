#include "INFOII.H"

unsigned char key;

void BoardSW( unsigned char CodigoActual )
{
	// Se definen estaticas para encapsular el codigo
	static unsigned char CodigoAnterior = NO_KEY;
	static unsigned char EstadosEstables;


	if( CodigoActual == NO_KEY )								// No hay tecla presionada o hubo un rebote
	{
		CodigoAnterior = NO_KEY;
		EstadosEstables = 0;
		return;
	}

	if( EstadosEstables == 0  )										// Se detecto una tecla por primera vez
	{
		CodigoAnterior = CodigoActual;
		EstadosEstables = 1;
		return;
	}

	if( CodigoActual != CodigoAnterior )						// Pregunto si la tecla sigue pulsada
	{
		CodigoAnterior = NO_KEY;
		EstadosEstables = 0;
		return;
	}

	if( EstadosEstables == CANTIDAD_DE_REBOTES )
	{
		key = CodigoActual;											// Acepto la nueva tecla
		EstadosEstables = 0; 				
														
		return;
	}

	EstadosEstables ++;
	return;
}