//***************************************************************************************************************************
//	Proposito: Timer_Tick, funcion que se llama por interrupcion de timer cada 
//	Parametros: void
//	Retorna: void.							  						      			
//***************************************************************************************************************************

#include <INFOII.h>


unsigned char 	decimas = DECIMAS;
unsigned char 	segundos = SEGUNDOS;
unsigned char 	minutos = MINUTOS;
unsigned char 	horas = HORAS;
unsigned char cont=0;

void Timer_Tick(void) interrupt 1	
{
	
    TR0 = 0;
    TH0 = t_2500Hz_H;						// 2500Hz
    TL0 = t_2500Hz_L + TL0;				   	// Xtal 22MHz
    TR0 = 1;

	//---------------------------------------------------------------------------------
	// Aca tengo que poner todas las funciones que quiero que funcionen a 2,5 milisegundos
	//---------------------------------------------------------------------------------

	Barrido_Display();				  		// Realizo el barrido del display
	Board();
	//---------------------------------------------------------------------------------

	decimas--;
	if(!decimas)							// Base de tiempo de CENTESIMAS
	{
		decimas = DECIMAS;

		//---------------------------------------------------------------------------------
		// Aca tengo que poner todas las funciones que quiero que funcionen a 1 centesima
		//---------------------------------------------------------------------------------


		//---------------------------------------------------------------------------------

		segundos--;
		if(!segundos)	// Base de tiempo de SEGUNDOS
		{
			segundos = SEGUNDOS;
			TIMERS_Descuento(0);
			TIMERS_Descuento(1);
			TIMERS_Descuento(2);
			Envio_Zonas();
			
			
			//---------------------------------------------------------------------------------
			// Aca tengo que poner todas las funciones que quiero que funcionen a 1 segundos
			//---------------------------------------------------------------------------------


			//---------------------------------------------------------------------------------

			minutos--;
			
			if(!minutos)							// Base de tiempo de MINUTOS
			{
				minutos = MINUTOS;
	
			
				//---------------------------------------------------------------------------------
				// Aca tengo que poner todas las funciones que quiero que funcionen a 1 centesima
				//---------------------------------------------------------------------------------


				//---------------------------------------------------------------------------------

				horas--;

				if(!horas)				 			// Base de tiempo de HORAS
				{
					horas = HORAS;

					//---------------------------------------------------------------------------------
					// Aca tengo que poner todas las funciones que quiero que funcionen a 1 centesima
					//---------------------------------------------------------------------------------


					//---------------------------------------------------------------------------------
				}
			}
		}
	}
}