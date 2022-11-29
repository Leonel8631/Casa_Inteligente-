// =========================================================================================
//  Propósito: Tunciones de temporizadores                                 
//  Módulo componente de: INFOII-2010
//  Fecha: 14-05-2010
//  Autor: Ing. Gustavo Fresno
// =========================================================================================
#include "INFOII.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Declaracion de variables
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Variables globales 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Variables para los temporizadores
STRUCT_TIMER	Timers;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Variables globales externas
extern unsigned char Flag_Fin_T0;
extern unsigned char Flag_Fin_T1;
extern unsigned char Flag_Fin_T2;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Funciones
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//******************************************************************************************
//	Proposito: Lanzamientos de Timers.                 		  		
//	Parametros:      						  							  			
//                  Nro_Timer : Numero de Timer                                  	
//                  Tiempo : valor de Timer.                                  		
//	Retorna: void.							  						      			
//******************************************************************************************
void TIMERS_Encender(unsigned char Nro_Timer, TIEMPOS Tiempo)
{
	ET0 = 0;	  												// Dehabilito la interrupcion del timer 0

	Timers.Cuenta[Nro_Timer] = Tiempo;			   				// Cargo el temporizador
	Timers.F_Final &= (~( (FLAGS_TIMERS) 0x01 << Nro_Timer) ); 	// Apago el flag del temporizador

	ET0 = 1;													// Habilito la interrupcion del timer 0
}

//******************************************************************************************
//	Proposito: Lanzamientos de Timers. (Condicion tiempo 0 activo el evento)                		  		
//	Parametros:      						  							  			
//                  Nro_Timer : Numero de Timer                                  	
//                  Tiempo : valor de Timer.                                  		
//	Retorna: void.							  						      			
//******************************************************************************************
//void TIMERS_Encender(unsigned char Nro_Timer, TIEMPOS Tiempo)
//{
//	if(Tiempo)
//	{
//		ET0 = 0;	  												// Dehabilito la interrupcion del timer 0
//		Timers.Cuenta[Nro_Timer] = Tiempo;			   				// Cargo el temporizador
//  	Timers.F_Final &= (~( (FLAGS_TIMERS) 0x01 << Nro_Timer) ); 	// Apago el flag del temporizador
//		ET0 = 1;													// Habilito la interrupcion del timer 0
//	}
//	else
//	{
//		ET0 = 0;	  												// Dehabilito la interrupcion del timer 0
//		Timers.Cuenta[Nro_Timer]=0;
//		Timers.F_Final |= ( (FLAGS_TIMERS) 0x01 << Nro_Timer);		
//		ET0 = 1;													// Habilito la interrupcion del timer 0
//	}
//}

//******************************************************************************************
//	Proposito: Apaga todo los timers
//	Parametros: void
//	Retorna: void.							  						      			
//******************************************************************************************
void TIMERS_Apagar_Todos(void)
{
	unsigned char i;
	
	ET0 = 0;						  			// Dehabilito la interrupcion del timer 0
											 		
	for (i = CANTIDAD_DE_TIMERS ; i ;  i--)
  		Timers.Cuenta[i] = 0;
  	Timers.Cuenta[0] = 0;						// Reseteo todos los temporizadores
  	
	Timers.F_Final = 0;							// Apago todos los flags de los timers

	ET0 = 1;			   						// Habilito la interrupcion del timer 0
}
 /*
//*******************************************************************************************
//	Proposito: Apaga un timer en particular
//	Parametros:      						  							  			
//                  Nro_Timer : Numero de Timer                                  	
//	Retorna: void.							  						      			
//*******************************************************************************************
void TIMERS_Detener(unsigned char Nro_Timer)
{
	ET0 = 0;							  					// Dehabilito la interrupcion del timer 0

  	Timers.Cuenta[Nro_Timer] = 0;							// Reseteo el temporizador
  	Timers.F_Final &= (~((FLAGS_TIMERS) 0x01 << Nro_Timer));	// Reseteo el flag del temporizador

	ET0 = 1;						 						// Habilito la interrupcion del timer 0
}	*/ 

//*******************************************************************************************
//	Proposito: Analiza flags de timers.              	  			
//	Parametros: void.						  							  			
//	Retorna: void.							  										
//*******************************************************************************************
void TIMERS_Verificar_Fin(void)
{
	FLAGS_TIMERS j;

    for( j = 1 ; j ; j <<= 1)
    {
        switch( Timers.F_Final &  j )
        {
			case T0 :

				//----------------------------------------------------------------------------
				// Aca escribimos las rutinas que se van a ejecutar cuando se vence el Timer 0
				Flag_Fin_T0=ON;
				//----------------------------------------------------------------------------
				//----------------------------------------------------------------------------
	           	Timers.F_Final = Timers.F_Final & ~T0;
   	         	break;
   	         		
            case T1 :
				//----------------------------------------------------------------------------
				// Aca escribimos las rutinas que se van a ejecutar cuando se vence el Timer 1
				Flag_Fin_T1=ON;
				//----------------------------------------------------------------------------
				//----------------------------------------------------------------------------
				Timers.F_Final = Timers.F_Final & ~T1;
               	break;
               		
            case T2 :
				//----------------------------------------------------------------------------
				// Aca escribimos las rutinas que se van a ejecutar cuando se vence el Timer 2
				Flag_Fin_T2=ON;
				//----------------------------------------------------------------------------
				//----------------------------------------------------------------------------
				Timers.F_Final = Timers.F_Final & ~T2;            	
               	break;  
               		              
            case T3 :
				//----------------------------------------------------------------------------
				// Aca escribimos las rutinas que se van a ejecutar cuando se vence el Timer 3
				//----------------------------------------------------------------------------
				//----------------------------------------------------------------------------
				Timers.F_Final = Timers.F_Final & ~T3;
               	break;
               		
            case T4 :
				//----------------------------------------------------------------------------
				// Aca escribimos las rutinas que se van a ejecutar cuando se vence el Timer 4
				//----------------------------------------------------------------------------
				//----------------------------------------------------------------------------
				Timers.F_Final = Timers.F_Final & ~T4;
               	break; 
               	
            case T5 :
				//----------------------------------------------------------------------------
				// Aca escribimos las rutinas que se van a ejecutar cuando se vence el Timer 5
				//----------------------------------------------------------------------------

				//----------------------------------------------------------------------------
				Timers.F_Final = Timers.F_Final & ~T5;
               	break; 
 
            case T6 :
				//----------------------------------------------------------------------------
				// Aca escribimos las rutinas que se van a ejecutar cuando se vence el Timer 6
				//----------------------------------------------------------------------------
				//----------------------------------------------------------------------------
				Timers.F_Final = Timers.F_Final & ~T6;
               	break; 

            case T7 :
				//----------------------------------------------------------------------------
				// Aca escribimos las rutinas que se van a ejecutar cuando se vence el Timer 7
				//----------------------------------------------------------------------------
				//----------------------------------------------------------------------------
				Timers.F_Final = Timers.F_Final & ~T7;
               	break; 

            default:
               	break; 
	  	}                       
    }
}

//******************************************************************************************
//	Proposito: Descuento de Timers.                 		  		
//	Parametros:      						  							  			
//                  Nro_Timer : Numero de Timer                                  	               		
//	Retorna: void.							  						      			
//******************************************************************************************
void TIMERS_Descuento(unsigned char Nro_Timer)
{
	//LED_4_ON;
	if (Timers.Cuenta[ Nro_Timer ])
   	{
   		Timers.Cuenta[ Nro_Timer ] --;
	   	if( !Timers.Cuenta[ Nro_Timer ] )
	   		Timers.F_Final |= ( (FLAGS_TIMERS) 0x01 << Nro_Timer );
	}
}

//******************************************************************************************
//	Proposito: Inicializar de Timers.                 		  		
//	Parametros:      						  							  			
//	Retorna: void.							  						      			
//******************************************************************************************
void TIMERS_Inicializar(void)
{
	TIMERS_Apagar_Todos();

}
				











