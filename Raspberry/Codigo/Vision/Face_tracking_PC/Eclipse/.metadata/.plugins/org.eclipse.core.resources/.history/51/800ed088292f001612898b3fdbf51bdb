/*
 * Defines.h
 *
 *  Created on: 31/05/2016
 *      Author: maximofn
 */

#ifndef SRC_DEFINES_H_
#define SRC_DEFINES_H_

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
#define SHOW
#ifdef SHOW
	#define INFORMATION
#endif

/***************************** Haar cascade mode ******************************/
#define LBP_CASCADE_FRONTALFACE
//#define HAAR_CASCADE_FRONTALFACE_ALT
//#define HAAR_CASCADE_FRONTALFACE_ALT2
//#define HAAR_CASCADE_FRONTALFACE_ALT_TREE
//#define HAAR_CASCADE_FRONTALFACE_ALT_DEFAULT

/****************************** Recognition mode ******************************/
#define RECOGNITION
#ifdef RECOGNITION
	#define EIGENFACES
	#ifndef EIGENFACES
		#define FISHERFACES
	#endif
#endif

/******************************************************************************/
/*                        ESTRUCTURAS Y TIPOS DEFINIDOS                       */
/******************************************************************************/

/******************************************************************************/
/*                             VARIABLES GLOBALES                             */
/******************************************************************************/

/******************************************************************************/
/*                                 FUNCIONES                                  */
/******************************************************************************/


#endif /* SRC_DEFINES_H_ */
