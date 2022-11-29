#include <INFOII.h>

// 	Digitos del display
unsigned char Digito_Display[CANTIDAD_DIGITOS_DISPLAY];

// 	Tabla de conversion bcd a 7 segmentos
//	Codigo bcd		a	b	c	d	e	f	g   dp
//	0				1	1	1	1	1	1	0   0
//	1				0	1	1	0	0	0	0
// 	2				1	1	0	1	1	0	1
// 	3				1	1	1	1	0	0	1
// 	4				0	1	1	0	0	1	1
//	5				1	0	1	1	0	1	1
//	6				1	0	1	1	1	1	1
//	7				1	1	1	0	0	0	0
// 	8				1	1	1	1	1	1	1
//	9				1	1	1	1	0	1	1	

unsigned char code Tabla_Digitos_BCD_7seg[] = { 0x3f, 0x06, 0x5B, 0x4f, 0x66, 0x6D, 0x7D, 0x07, 0x7f, 0x6f};
//*********************************************************************************************
//	Proposito: Display de 7 Segmentos.                  		  
//	Parametros: 							  
//		int Valor : valor a presentar
//	Retorna: void.							  
//*********************************************************************************************
void Display(long Valor)
{
	unsigned char i;

	for( i = (CANTIDAD_DIGITOS_DISPLAY - 1) ; i ; i-- )
	{
		Digito_Display[i] = Tabla_Digitos_BCD_7seg[Valor % 10];
		Valor /= 10; 
	}
	Digito_Display[0] = Tabla_Digitos_BCD_7seg[Valor % 10];
}