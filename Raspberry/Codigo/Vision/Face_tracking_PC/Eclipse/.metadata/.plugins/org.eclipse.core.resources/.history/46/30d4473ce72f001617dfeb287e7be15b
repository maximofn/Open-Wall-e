/*
 * libreria_Detection.h
 *
 *  Created on: 07/06/2016
 *      Author: maximofn
 */

#ifndef SRC_LIBRERIA_DETECTION_H_
#define SRC_LIBRERIA_DETECTION_H_

/******************************************************************************/
/*                            ARCHIVOS IMPORTADOS                             */
/******************************************************************************/

#include "../Resources/Defines.h"
#include "../Resources/Resources.h"
#include "Utilities.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "time.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

// OPENCV
#include <cv.h>
#include <highgui.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#ifdef RASPBERRY
	#include "../libfacerec-0.04/include/facerec.hpp"
	#include "../Resources/raspicam/RaspiCamCV.h"
#else
	#include <opencv2/contrib/contrib.hpp>
#endif

using namespace std;
using namespace cv;

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
/* NOMBRE: load_haar_cascade                                                  */
/* ARGUMENTOS ENTRADA: N/A                                                    */
/* ARGUMENTOS SALIDA:                                                         */
/*    ARGUMENTO0: (CascadeClassifier) face_cascade: clasificador de cara      */
/* VALOR DEVUELTO:                                                            */
/*    true: Clasificador cargado con exito                                    */
/*    false: Clasificador no cargado con exito                                */
/* DESCRIPCION: Funcion que carga el clasificador de caras                    */
/*----------------------------------------------------------------------------*/
bool load_haar_cascade(CascadeClassifier& face_cascade);



/*----------------------------------------------------------------------------*/
/* NOMBRE: face_detection                                                     */
/* ARGUMENTOS ENTRADA:                                                        */
/*    ARGUMENTO0: (CascadeClassifier) face_cascade: clasificador de cara      */
/*    ARGUMENTO1: (Mat) grayscaleFrame: Frame convertido a escala de grises   */
/* ARGUMENTOS SALIDA:                                                         */
/*    ARGUMENTO0: (Mat) captureFrame: Frame a color con recuedro en caras     */
/*    ARGUMENTO1: (vector< Rect_<int> >) faces: vector con caras detectadas   */
/*    ARGUMENTO2: (double) x_face_pos: Posición x de la cara                  */
/*    ARGUMENTO3: (double) y_face_pos: Posición y de la cara                  */
/*    ARGUMENTO4: (double) area_face: Area de la cara                         */
/* VALOR DEVUELTO: N/A                                                        */
/* DESCRIPCION: Funcion que detecta caras                                     */
/*----------------------------------------------------------------------------*/
void face_detection(CascadeClassifier& face_cascade, Mat& grayscaleFrame, Mat& captureFrame, vector< Rect_<int> > *faces,
		double& x_face_pos, double& y_face_pos, double& area_face);



#endif /* SRC_LIBRERIA_DETECTION_H_ */
