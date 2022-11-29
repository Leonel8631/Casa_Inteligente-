#include "INFOII.h"

/*
COMANDO									RS	RW	D7	D6	D5	D4	D3	D2	D1	D0	TIEMPO DE EJECUCIÓN
Borrar el visualizador					0	0	0	0	0	0	0	0	0	1	1.64mS
Poner el cursor al inicio				0	0	0	0	0	0	0	0	1	x	1.64mS
Modo de entrada							0	0	0	0	0	0	0	1	I/D	S	40uS
Activar/desactivar el visualizador		0	0	0	0	0	0	1	D	U	B	40uS
Desplazar el cursor/visualizador		0	0	0	0	0	1	D/C	R/L	x	x	40uS
Modo de funcionamiento					0	0	0	0	1	DL	N	F	x	x	40uS
Establecer la dirección CGRAM			0	0	0	1	Dirección CGRAM	40uS
Establecer la dirección DDRAM			0	0	1	Dirección CGRAM	40uS
Leer la bandera "BUSY"(ocupado) (BF)	0	1	BF	Dirección CGRAM	-
Escribir en la CGRAM o en la DDRAM		1	0	D7	D6	D5	D4	D3	D2	D1	D0	40uS
Leer la CGRAM o la DDRAM				1	1	D7	D6	D5	D4	D3	D2	D1	D0	40uS
I/D 1 = Incremento (por 1)                           R/L 1 = Desplazamiento a la derecha
    0 = Decremento (por 1)                               0 = Desplazamiento a la izquierda
    
S 1 = Desplazamiento del visualizador activado        DL 1 = Bus de datos de 8 bits
  0 = Desplazamiento del visualizador desactivado        0 = Bus de datos de 4 bits
  
D 1 = Visualizador encendido                           N 1 = Visualizador de dos líneas
  0 = Visualizador apagado                               0 = Visualizador en una línea
  
U 1 = Cursor activado                                  F 1 = Carácter de 5x10 puntos
  0 = Cursor desactivado                                 0 = Carácter de 5x7 puntos

B 1 = Parpadeo del cursor encendido                  D/C 1 = Desplazamiento del visualizador
  0 = Parpadeo del cursor apagado                        0 = Desplazamiento del cursor

*/
 
//--------------------------------------------------------------------------//
//---PRIMITIVAS-------------------------------------------------------------//
void DISPLAYLCD(unsigned char *texto, unsigned char cantidad, bit reglon,unsigned char posicion)
{   

	unsigned char i;

	//Inic_LCD();
	if(reglon==0)
		Escribir8(COMANDO,0x80+posicion);
	else
		Escribir8(COMANDO,0x80+0x40+posicion);//posicion inicial + segunda linea + posicion
    for(i=0;i<cantidad;i++)
    {
        Escribir8(DATO,texto[i]);
    }

}

/*void DISPLAYLCD_NUMERO(unsigned int numero, unsigned char cifras,bit reglon,unsigned char posicion)
{   unsigned char d;
    unsigned char temp[5];
    if(reglon==0)
		Escribir8(COMANDO,0x80+posicion);
	else
		Escribir8(COMANDO,0x80+0x40+posicion);//posicion inicial + segunda linea + posicion

	for(d=0;d<cifras;d++)
    {
		if(d==2)
			temp[2]='.';
		else
        {	temp[d]=numero%10 + '0';
        	numero/=10;
		}
    }
    for(d=cifras;d>0;d--)
    {
        Escribir8(DATO,temp[d-1]);
    }
}*/	 
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Nombre de la función: void ini_LCD(void)
//      Proposito:inicializa el display 
//	Parametros:void 					                                        
//	Retorna: void.							       
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
void IniC_LCD (void)
        
{		
	unsigned char i,j;

	for(i=0;i<3;i++)
	{
		E_OFF;	
     	P6=0X3C;// LCD_INIC;
			delay();//rutina de retardo fija de 30 mseg
     	RS_OFF; //instruccion
     	E_ON;
	 	for(j=3;j;j--);
     	E_OFF;
  }

  //control_LCD(LCD_DATO);//veo el BF
  Escribir8(COMANDO,0x3F);// 
  Escribir8(COMANDO,0X01);//HAGO UN clrscr().Se podría haber usado la macro que creamos
                    //llamada clrscr()
  Escribir8(COMANDO,0x08);//display OFF
  Escribir8(COMANDO,0X01);// clear display
  Escribir8(COMANDO,0x0C);//display ON,sin cursor y blinking OFF del cursor                     
  Escribir8(COMANDO,0X06);//programo el LCD para mis necesidades

}
                      

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//	Nombre de la función: void delay(void)
//      Proposito:retardo fijo de 30 mseg 
//	Parametros:void 					                                        
//	Retorna: void.							       
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void delay(void)
{
 	 unsigned int i;
 	 for (i=0;i<35000;i++);
}
void delay2(void)
{
 	 unsigned int i;
 	 for (i=0;i<5000;i++);
}  

//--------------------------------------------------------------------------//
//--------------------------------------------------------------------------//

//---DRIVER-----------------------------------------------------------------//	
//--------------------------------------------------------------------------//
void Escribir8(bit opcion,unsigned char dato)//Comunicacion 8 bits
{

    if(opcion==COMANDO)
	{	RS_OFF;	//CONFLCD=(CONFLCD&(0x3f));	//RS=0 Registro de Control
    	//RW=0;//Escritura
    	E_ON;	//CONFLCD=(CONFLCD&(0x3f))|(0x40);	//Modulo conectado E=1
		P_DATOS=dato;
		delay2();
    	E_OFF;	//CONFLCD=(CONFLCD&(0x3f));//Modulo desconectado E=0
	}
	else
	{	RS_ON;	//CONFLCD=(CONFLCD&(0x3f))|(0x80);	//RS=1 Registro de Datos
    	//RW=0;//Escritura
    	E_ON;	//CONFLCD=(CONFLCD&(0x3f))|(0x40);	//Modulo conectado E=1
		P_DATOS=dato;
		delay2();
    	E_OFF;	//CONFLCD=(CONFLCD&(0x3f));	//Modulo desconectado E=0
	}

}  
//--------------------------------------------------------------------------//
//--------------------------------------------------------------------------//