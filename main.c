#include <INFOII.h>
#define PROGRAMACION 3
#define ALARMADA 4
#define SIRENA_ON LED_1_ON
#define SIRENA_OFF LED_1_OFF
#define SENSOR TECLA_4
#define ERROR 2
#define INGRESO_CLAVE 5
#define INGRESO_CLAVE_DESACTIVAR 6
#define CAMBIAR_CLAVE 7
#define ACTIVAR_ZONAS 8



unsigned char i;
long int Clave;
long int ClaveM;
long int Clave_Maestra;
unsigned char Flag_Clave;
unsigned char Flag_Sensores;
unsigned char TECLA;
unsigned char ESTADO=OFF;
unsigned char Flag_Fin_T0;
unsigned char Flag_Fin_T1;
unsigned char Flag_Fin_T2;
unsigned char Flag_Cambio_Clave;
bit ESTADO_LED_1;
bit ESTADO_LED_2;
bit ESTADO_LED_3;
bit ESTADO_LED_4;


unsigned int RefLuz = 2000;	 // REFERENCIA DE LUZ
unsigned int RefMINTemp=600;	 // REFERENCIA DE TEMP MINIMA ADMISIBLE
unsigned int RefMAXTemp=1600;	 // REFERENCIA DE TEMP MAXIMA ADMISIBLE

extern unsigned int 		Medicion_ADC[3]; // VECTOR DONDE GUARDO MEDICIONES DE ADC

void main (void)
{
	Inicializacion();
	TECLA=0;
	Clave=0;
	Clave_Maestra=1234;
	i=0;
	Flag_Clave=0;
	Flag_Sensores=0;
	Flag_Cambio_Clave=0;
	Flag_Fin_T0=0;
	Flag_Fin_T1=0;
	Flag_Fin_T2=0;
	UART_Init();
	Inic_LCD();
	Inic_ADC();
	DISPLAYLCD("BIENVENIDOS", 11, 0,0);
	DISPLAYLCD("AL SISTEMA", 10, 1,0);
	TIMERS_Encender(0,4);
	Enviar_Paquete_UART("ALARMA CONECTADA", 16);
	Display(0);
	
	while(1)
	{
		TIMERS_Verificar_Fin();
		if(Flag_Fin_T0==ON)
		{
	 		Flag_Fin_T0=OFF;
			Inic_LCD();
			DISPLAYLCD("F1: ACTIVAR", 11, 0,0);
			DISPLAYLCD("F2: Programacion", 16, 1,0);
		}
		if(Flag_Fin_T1==ON)
		{
	 		Flag_Fin_T1=OFF;
			Inic_LCD();
			DISPLAYLCD("ALARMA ACTIVADA", 15, 0,0);
			DISPLAYLCD("F3: DESACTIVAR", 14, 1,0);
		}

		if(Flag_Fin_T2==ON)
		{
	 		Flag_Fin_T2=OFF;
			Inic_LCD();
			DISPLAYLCD("INGRESE CLAVE", 13, 0,0);
		}

		TECLA=Get_Key();
		/*if(TECLA!=NO_KEY)
		//Display(TECLA);*/	 
		Aplicacion();
		Estado_Sensores();
			Chequear_Luz();
		Chequear_Temperatura();
		
			

	}

}

void Aplicacion(void)
{
	
	switch(ESTADO)
	{
		case OFF: 

			if(TECLA == TECLA_F1)
			{							

				SIRENA_OFF;
				ESTADO=INGRESO_CLAVE; 
				Inic_LCD();
				DISPLAYLCD("INGRESE CLAVE", 13, 0,0);
				
			}
			if(TECLA==TECLA_F2)
			{
				SIRENA_OFF;
				ESTADO=PROGRAMACION;
				Inic_LCD();
				DISPLAYLCD("ESTADO PROGRAMAC", 16, 0,0);
				DISPLAYLCD("F3: ESTADO OFF", 14, 1,0);
			}
			break;

		case PROGRAMACION:		  // agregar menu para ver que hace el usuario
			
			if(TECLA == TECLA_F1)
			{
				Inic_LCD();
				DISPLAYLCD("ACTIVAR ZONAS",13, 0,0);
				SIRENA_OFF;
				ESTADO=ACTIVAR_ZONAS;
			} 
			if(TECLA == TECLA_F2)
			{
				Inic_LCD();
				DISPLAYLCD("CAMBIAR CLAVE",13, 0,0);
				SIRENA_OFF;
				ESTADO=CAMBIAR_CLAVE;
			} 
			if(TECLA == TECLA_F3)
			{
				Inic_LCD();
				DISPLAYLCD("ESTADO OFF",10, 0,0);
				TIMERS_Encender(0,4);
				SIRENA_OFF;
				ESTADO=OFF;
			}  
			
			break;

		case ACTIVAR_ZONAS:
			LED_3_ON;
			ESTADO=PROGRAMACION;
			
			break;

		case CAMBIAR_CLAVE:
			Flag_Cambio_Clave=Cambio_Clave();
			if (Flag_Cambio_Clave==ON)
			{
				Flag_Cambio_Clave=OFF;
				ESTADO=PROGRAMACION;							 
				Inic_LCD();
				DISPLAYLCD("CAMBIO DE CLAVE", 15, 0,0);
				DISPLAYLCD("CORRECTO", 8, 1,0);
			}

			if (Flag_Cambio_Clave==ERROR)
			{
				Flag_Cambio_Clave=OFF;
				ESTADO=PROGRAMACION;
				Inic_LCD();
				DISPLAYLCD("CAMBIO DE CLAVE", 15, 0,0);
				DISPLAYLCD("INCORRECTO", 10, 1,0);
			} 	
			
			break;

		case INGRESO_CLAVE:
			Flag_Clave=Ingreso_Clave();
			if(Flag_Clave==ON)
			{
				Flag_Clave=OFF;
				Flag_Sensores=OFF;
				SIRENA_OFF;
				RELE_1_OFF;
				RELE_2_OFF;
				RELE_3_OFF;
				ESTADO=ON;
				Inic_LCD();
				DISPLAYLCD("INGRESO DE CLAVE", 16, 0,0);
				DISPLAYLCD("CORRECTO", 8, 1,0);
				TIMERS_Encender(1,4);


			}

			if (Flag_Clave==ERROR)
			{
				Flag_Clave=OFF;
				Flag_Sensores=OFF;
				SIRENA_OFF;
				RELE_1_OFF;
				RELE_2_OFF;
				RELE_3_OFF;
				ESTADO=OFF;
				Inic_LCD();
				DISPLAYLCD("INGRESO DE CLAVE", 16, 0,0);
				DISPLAYLCD("INCORRECTO", 10, 1,0);
				TIMERS_Encender(0,4);
			}
				
			
			break;

		case INGRESO_CLAVE_DESACTIVAR:
			Flag_Clave=Ingreso_Clave();
			if(Flag_Clave==ON)
			{
				Flag_Clave=OFF;
				Flag_Sensores=OFF;
				SIRENA_OFF;
				RELE_1_OFF;
				RELE_2_OFF;
				RELE_3_OFF;
				ESTADO=OFF;
				Inic_LCD();
				DISPLAYLCD("INGRESO DE CLAVE", 16, 0,0);
				DISPLAYLCD("CORRECTO", 8, 1,0);
				TIMERS_Encender(0,4);
			}

			else if(Flag_Clave==ERROR)
			{
				Flag_Clave=OFF;
				Flag_Sensores=OFF;
				Inic_LCD();
				DISPLAYLCD("INGRESO DE CLAVE", 16, 0,0);
				DISPLAYLCD("INCORRECTO", 10, 1,0);		   
				TIMERS_Encender(2,4);
			}	 

			break;

		case ON:
			
	
			if(TECLA == TECLA_F3)
			{
				SIRENA_OFF;
				ESTADO=INGRESO_CLAVE_DESACTIVAR;
				Inic_LCD();
				DISPLAYLCD("INGRESE CLAVE", 13, 0,0);
			}
			if(Flag_Sensores==ON)
			{
				BUZZER_ON;
				ESTADO=ALARMADA;
				Inic_LCD();
				DISPLAYLCD("ESTADO ALARMADA", 15, 0,0);
				DISPLAYLCD("INGRESE CLAVE", 13, 1,0);
				RELE_1_ON;
				RELE_2_ON;
				RELE_3_ON;
			}
			
			break;

		case ALARMADA:
			Flag_Clave=Ingreso_Clave();
			if(Flag_Clave==ON)
			{
				Flag_Clave=OFF;
				Flag_Sensores=OFF;
				SIRENA_OFF;
				RELE_1_OFF;
				RELE_2_OFF;
				RELE_3_OFF;
				ESTADO=OFF;
				Inic_LCD();
				DISPLAYLCD("INGRESO DE CLAVE", 16, 0,0);
				DISPLAYLCD("CORRECTO", 8, 1,0);
				TIMERS_Encender(0,4);

			}
			
			if (Flag_Clave==ERROR)
			{
				Flag_Clave=OFF;
				Inic_LCD();
				DISPLAYLCD("INGRESO DE CLAVE", 16, 0,0);
				DISPLAYLCD("INCORRECTO", 10, 1,0);
				TIMERS_Encender(2,4);
			} 	
			break;

		default:
			break;
	}
		
}
 
unsigned char Ingreso_Clave(void)
{
 	unsigned char b;
	if (i<4)
	{
		if((TECLA!=NO_KEY)&(TECLA<10))
		{
			Clave*=10;
			Clave+=TECLA;
			i++;
			Display(Clave);
		  	if (i==4)
			{
				if(Clave==Clave_Maestra)
				{
					Clave=0;
					i=0;
					return b=1;
				}
				else
				{
				i=0;
				Clave=0;
				return b=2;
				}
			}	
		}
	}
	
	return (b=0);
} 


void Estado_Sensores(void)
{
	if (ESTADO==ON)
	{

	if((sensor_puerta==1)||(sensor_ventana_comedor==1)||(sensor_mov_comedor==1))		 	
	{
		Flag_Sensores=ON;
		LED_1_ON;
		ESTADO_LED_1=ON;
	}
	else
	{
		LED_1_OFF;
		ESTADO_LED_1=OFF;
	}
	if((sensor_ventana_cocina==1)||(sensor_mov_cocina==1))
	{
		Flag_Sensores=ON;		 	
		LED_2_ON;
		ESTADO_LED_2=ON;
	}
	else
	{
		LED_2_OFF;
		ESTADO_LED_2=OFF;
	}
	if((sensor_ventana_hab==1))	
	{
		Flag_Sensores=ON;	 	
		LED_3_ON;
		ESTADO_LED_3=ON;
	}
	else
	{
		LED_3_OFF;
		ESTADO_LED_3=OFF;
	}				  
	if((sensor_ventana_banio==1))
	{
		Flag_Sensores=ON;		 	
		LED_4_ON;
		ESTADO_LED_4=ON;
	}
	else
	{
		LED_4_OFF;
		ESTADO_LED_4=OFF;
	}	 
	if(boton_panico==1)
		BUZZER_ON;
	else
		BUZZER_OFF;
	} 
}


unsigned char Cambio_Clave(void)
{
	unsigned char b;
		if (i<4)
		{
			if((TECLA!=NO_KEY)&(TECLA<10))
			{
				ClaveM*=10;
				ClaveM+=TECLA;
				i++;
				Display(ClaveM);
				if (i==4)
				{
					Clave_Maestra=ClaveM;
					ClaveM=0;
					i=0;
					return b=1;
				}

			}
		}
		
	return (b=0);

}

	 void Chequear_Luz(void)
{
	if(Medicion_ADC[0]<RefLuz)
	{ 
		RELE_1_ON;
	}
	else
	{
		RELE_1_OFF;
	}
	 if(Medicion_ADC[1]<RefLuz)
	{ 
		RELE_2_ON;
	}
	else
	{
		RELE_2_OFF;
	}
}

void 	Chequear_Temperatura(void){

if(Medicion_ADC[2]>RefMAXTemp)
	{ 
		RELE_3_ON;	//ENCIENDO VENTILADOR
	}
	else
	{
		if(Medicion_ADC[2]<(RefMAXTemp-150))
		{RELE_3_OFF;}
	}
if(Medicion_ADC[2]<RefMINTemp)
	{ 
		RELE_4_ON;	//ENCIENDO CALEFACTOR
	}
	else
	{
		if(Medicion_ADC[2]>(RefMINTemp+150))
		{RELE_4_OFF;}
	}
} 



