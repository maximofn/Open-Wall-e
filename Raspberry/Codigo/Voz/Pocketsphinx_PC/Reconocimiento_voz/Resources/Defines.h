/*
 * Defines.h
 *
 *  Created on: 16/10/2016
 *      Author: maximofn
 */

#ifndef DEFINES_H_
#define DEFINES_H_


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

/******************************* Device mode **********************************/
//#define RASPBERRY
#ifndef RASPBERRY
	#define UBUNTU
#endif

/*************************** Trace and debug mode *****************************/
#define TRACE
#define DEBUG

/******************* Ventana e información en la ventana **********************/

/***************************** Haar cascade mode ******************************/

/****************************** Recognition mode ******************************/

/******************************************************************************/
/*                        ESTRUCTURAS Y TIPOS DEFINIDOS                       */
/******************************************************************************/

/******************************************************************************/
/*                             VARIABLES GLOBALES                             */
/******************************************************************************/

/******************************************************************************/
/*                                 FUNCIONES                                  */
/******************************************************************************/



#endif /* DEFINES_H_ */