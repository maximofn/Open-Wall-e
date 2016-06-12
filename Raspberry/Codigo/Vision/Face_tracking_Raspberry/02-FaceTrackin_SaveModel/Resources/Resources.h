/*
 * Resources.h
 *
 *  Created on: 09/06/2016
 *      Author: maximofn
 */

#ifndef RESOURCES_RESOURCES_H_
#define RESOURCES_RESOURCES_H_

/******************************************************************************/
/*                            ARCHIVOS IMPORTADOS                             */
/******************************************************************************/

#include "../Resources/Defines.h"

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
/* NOMBRE: get_csvFileDirectory                                               */
/* ARGUMENTOS ENTRADA: N/A                                                    */
/* ARGUMENTOS SALIDA: N/A                                                     */
/* VALOR DEVUELTO:                                                            */
/*    string: directorio del archivo csv                                      */
/* DESCRIPCION: Funcion que devuelve el directorio del archivo csv            */
/*----------------------------------------------------------------------------*/
string get_csvFileDirectory();



/*----------------------------------------------------------------------------*/
/* NOMBRE: get_fn_haarFileDirectory                                           */
/* ARGUMENTOS ENTRADA: N/A                                                    */
/* ARGUMENTOS SALIDA: N/A                                                     */
/* VALOR DEVUELTO:                                                            */
/*    string: directorio del archivo haar                                     */
/* DESCRIPCION: Funcion que devuelve el directorio del archivo haar           */
/*----------------------------------------------------------------------------*/
string get_fn_haarFileDirectory();



/*----------------------------------------------------------------------------*/
/* NOMBRE: get_measureFileDirectory                                           */
/* ARGUMENTOS ENTRADA: N/A                                                    */
/* ARGUMENTOS SALIDA: N/A                                                     */
/* VALOR DEVUELTO:                                                            */
/*    string: directorio del archivo de medidas                               */
/* DESCRIPCION: Funcion que devuelve el directorio del archivo de medidas     */
/*----------------------------------------------------------------------------*/
string get_measureFileDirectory();



/*----------------------------------------------------------------------------*/
/* NOMBRE: get_peopleFileDirectory                                            */
/* ARGUMENTOS ENTRADA: N/A                                                    */
/* ARGUMENTOS SALIDA: N/A                                                     */
/* VALOR DEVUELTO:                                                            */
/*    string: directorio del archivo de gente                                 */
/* DESCRIPCION: Funcion que devuelve el directorio del archivo de gente       */
/*----------------------------------------------------------------------------*/
string get_peopleFileDirectory();



/*----------------------------------------------------------------------------*/
/* NOMBRE: get_modelFileDirectory                                             */
/* ARGUMENTOS ENTRADA: N/A                                                    */
/* ARGUMENTOS SALIDA: N/A                                                     */
/* VALOR DEVUELTO:                                                            */
/*    string: directorio del archivo de modelo                                */
/* DESCRIPCION: Funcion que devuelve el directorio del archivo de modelo      */
/*----------------------------------------------------------------------------*/
string get_modelFileDirectory();




#endif /* RESOURCES_RESOURCES_H_ */
