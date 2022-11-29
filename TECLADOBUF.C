#include <INFOII.h>

// 	Buffer de Teclado
extern unsigned char key;

//	Proposito: Lectura y borrado del buffer de teclado.		  	
//	Parametros: void.						  										
//	Retorna: void							  										
//*********************************************************************************************
unsigned char Get_Key(void)
{
	unsigned char Keys;
     
   	Keys = key;

   	key = NO_KEY;
 
   	return Keys;
}