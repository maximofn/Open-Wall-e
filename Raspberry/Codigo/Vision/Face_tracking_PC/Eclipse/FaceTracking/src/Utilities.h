/*
 * Utilities.h
 *
 *  Created on: 04/06/2016
 *      Author: maximofn
 */

#ifndef SRC_UTILITIES_H_
#define SRC_UTILITIES_H_

/******************************************************************************/
/*                            ARCHIVOS IMPORTADOS                             */
/******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include "time.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
using namespace std;

/******************************************************************************/
/*                           DEFINICIONES Y MACROS                            */
/******************************************************************************/

/******************************************************************************/
/*                        ESTRUCTURAS Y TIPOS DEFINIDOS                       */
/******************************************************************************/

/******************************************************************************/
/*                             VARIABLES GLOBALES                             */
/******************************************************************************/

/******************************************************************************/
/*                                 FUNCIONES                                  */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* NOMBRE: trace                                                              */
/* ARGUMENTOS ENTRADA:                                                        */
/*    ARGUMENTO0: (string) s: Mensaje para imprimir                           */
/* ARGUMENTOS SALIDA: N/A                                                     */
/* VALOR DEVUELTO: N/A                                                        */
/* DESCRIPCION: Funcion que imprime por pantalla un mensaje                   */
/*----------------------------------------------------------------------------*/
inline void trace(string s)
{
	//printf (" TRACE: %s", s);
	cout << s ;
}

/*----------------------------------------------------------------------------*/
/* NOMBRE: trace                                                              */
/* ARGUMENTOS ENTRADA:                                                        */
/*    ARGUMENTO0: (char) c: Mensaje para imprimir                             */
/* ARGUMENTOS SALIDA: N/A                                                     */
/* VALOR DEVUELTO: N/A                                                        */
/* DESCRIPCION: Funcion que imprime por pantalla un mensaje                   */
/*----------------------------------------------------------------------------*/
inline void trace(char* c[])
{
	//printf (" %s", c);
	cout << c ;
}



/*----------------------------------------------------------------------------*/
/* NOMBRE: debug                                                              */
/* ARGUMENTOS ENTRADA:                                                        */
/*    ARGUMENTO0: (string) s: Mensaje para imprimir                           */
/* ARGUMENTOS SALIDA: N/A                                                     */
/* VALOR DEVUELTO: N/A                                                        */
/* DESCRIPCION: Funcion que imprime por pantalla un mensaje                   */
/*----------------------------------------------------------------------------*/
inline void debug(string s)
{
	cout << "DEBUG: " << s;
}

/*----------------------------------------------------------------------------*/
/* NOMBRE: trace                                                              */
/* ARGUMENTOS ENTRADA:                                                        */
/*    ARGUMENTO0: (char) c: Mensaje para imprimir                             */
/* ARGUMENTOS SALIDA: N/A                                                     */
/* VALOR DEVUELTO: N/A                                                        */
/* DESCRIPCION: Funcion que imprime por pantalla un mensaje                   */
/*----------------------------------------------------------------------------*/
inline void debug(char* c)
{
	printf (" %s", c);
}



/*----------------------------------------------------------------------------*/
/* NOMBRE: get_ProgramDirectory                                               */
/* ARGUMENTOS ENTRADA: N/A                                                    */
/* ARGUMENTOS SALIDA: N/A                                                     */
/* VALOR DEVUELTO:                                                            */
/*    string: directorio donde se ejecuta el programa                         */
/* DESCRIPCION: Funcion que devuleve el directorio del programa               */
/*----------------------------------------------------------------------------*/
string get_ProgramDirectory();


#endif /* SRC_UTILITIES_H_ */
