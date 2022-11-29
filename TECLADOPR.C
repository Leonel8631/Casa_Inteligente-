#include "INFOII.H"

void Board(void)
{
	unsigned char CodigoActual ;
	
	CodigoActual = BoardHW( );									// Se Compromete con el HW
	//key = CodigoActual;
	BoardSW( CodigoActual );										//  No se compromete con el HW
}