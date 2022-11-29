//==============================================================================================
//		-		Proposito: Funcion que se encarga de barrer el display
//		-		Parametros: void
//		-		Retorna: void
//==============================================================================================

#include <INFOII.h>

extern unsigned char Digito_Display[];

void Barrido_Display(void)
{
	unsigned char			Auxiliar;
	static	unsigned char 	Indice_Display = 0;

#ifdef F120
	char SFRPAGE_SAVE = SFRPAGE;    // Save Current SFR page
	SFRPAGE = CONFIG_PAGE;			// Set SFR Page
#endif

	// Apago todos los digitos
#ifdef F120
	DIGITO_0 = 0;
	DIGITO_1 = 0;
	DIGITO_2 = 0;
	DIGITO_3 = 0;
	DIGITO_4 = 0;
	DIGITO_5 = 0;
#else
	P4 &= 0xc0;	
#endif
	// Escribo en el puerto de datos
	Auxiliar = Digito_Display[Indice_Display];		// Se utiliza esta variable auxiliar para ahorrar codigo
	
	PUERTO_DISPLAY_A = Auxiliar & 0x01;				// Comienzo a barrer los pines del micro
	PUERTO_DISPLAY_B = (Auxiliar >> 1 ) & 0x01;
	PUERTO_DISPLAY_C = (Auxiliar >> 2 ) & 0x01;
	PUERTO_DISPLAY_D = (Auxiliar >> 3 ) & 0x01;
	PUERTO_DISPLAY_E = (Auxiliar >> 4 ) & 0x01;
	PUERTO_DISPLAY_F = (Auxiliar >> 5 ) & 0x01;
	PUERTO_DISPLAY_G = (Auxiliar >> 6 ) & 0x01;
	PUERTO_DISPLAY_DP = (Auxiliar >> 7 ) & 0x01;

	// Activo el display que corresponde
	switch(Indice_Display)
	{
		case 0:
			#ifdef F120
				DIGITO_0 = 1;
			#else
				P4 |= 0x01;	
			#endif
			break;
			
		case 1:
			#ifdef F120
				DIGITO_1 = 1;
			#else
				P4 |= 0x02;	
			#endif
			break;

		case 2:
			#ifdef F120
				DIGITO_2 = 1;
			#else
				P4 |= 0x04;	
			#endif
			break;

		case 3:
			#ifdef F120
				DIGITO_3 = 1;
			#else
				P4 |= 0x08;	
			#endif
			break;

		case 4:
			#ifdef F120
				DIGITO_4 = 1;
			#else
				P4 |= 0x10;	
			#endif
			break;

		case 5:
			#ifdef F120
				DIGITO_5 = 1;
			#else
				P4 |= 0x20;	
			#endif
			break;

		default:
			#ifdef F120
				DIGITO_0 = 0;
				DIGITO_1 = 0;
				DIGITO_2 = 0;
				DIGITO_3 = 0;
				DIGITO_4 = 0;
				DIGITO_5 = 0;
			#else
				P4 &= 0xc0;	
			#endif
			break;
	}

	// Incremento el indice del display
	Indice_Display++;
	Indice_Display %= 6;

#ifdef F120
	SFRPAGE = SFRPAGE_SAVE;			// Set SFR Page
#endif
}