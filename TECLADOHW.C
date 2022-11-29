#include "INFOII.H"

unsigned char BoardHW (void)
{
	TECLADO_FILA_1 = 0;
	TECLADO_FILA_2 = 1;
	TECLADO_FILA_3 = 1;
	TECLADO_FILA_4 = 1;
	if (TECLADO_COLUMNA_1 == 0)
		return TECLA_9;//
	if (TECLADO_COLUMNA_2 == 0)
		return TECLA_NUMERAL;//
	if (TECLADO_COLUMNA_3 == 0)
		return TECLA_3;
	if (TECLADO_COLUMNA_4 == 0)
		return TECLA_6;//
	TECLADO_FILA_1 = 1;
	TECLADO_FILA_2 = 0;
	TECLADO_FILA_3 = 1;
	TECLADO_FILA_4 = 1;
	if (TECLADO_COLUMNA_1 == 0)
		return TECLA_F3;//
	if (TECLADO_COLUMNA_2 == 0)
		return TECLA_F4;//
	if (TECLADO_COLUMNA_3 == 0)
		return TECLA_F1;//
	if (TECLADO_COLUMNA_4 == 0)
		return TECLA_F2; //
	TECLADO_FILA_1 = 1;
	TECLADO_FILA_2 = 1;
	TECLADO_FILA_3 = 0;
	TECLADO_FILA_4 = 1;
	if (TECLADO_COLUMNA_1 == 0)
		return TECLA_7;	//
	if (TECLADO_COLUMNA_2 == 0)
		return TECLA_ASTERISCO;	//
	if (TECLADO_COLUMNA_3 == 0)
		return TECLA_1;//
	if (TECLADO_COLUMNA_4 == 0)
		return TECLA_4;//
	TECLADO_FILA_1 = 1;
	TECLADO_FILA_2 = 1;
	TECLADO_FILA_3 = 1;
	TECLADO_FILA_4 = 0;
	if (TECLADO_COLUMNA_1 == 0)
		return TECLA_8;//
	if (TECLADO_COLUMNA_2 == 0)
		return TECLA_0;
	if (TECLADO_COLUMNA_3 == 0)
		return TECLA_2;
	if (TECLADO_COLUMNA_4 == 0)
		return TECLA_5; 
	return NO_KEY;
}