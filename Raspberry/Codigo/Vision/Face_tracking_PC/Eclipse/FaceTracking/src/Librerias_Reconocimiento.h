/*
 * Librerias_Reconocimiento.h
 *
 *  Created on: 21/03/2014
 *      Author: Máximo Fernández Núñez
 */

#ifndef LIBRERIAS_RECONOCIMIENTO_H_
#define LIBRERIAS_RECONOCIMIENTO_H_

/******************************************************************************/
/*                            ARCHIVOS IMPORTADOS                             */
/******************************************************************************/

#include "../Resources/Defines.h"
#include "../Resources/Resources.h"

#ifdef RECOGNITION
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

// some constants to manage nb of people to learn+ id of people
#define MAX_PEOPLE 					15
#define P_MAXIMO					0
#define P_ANGELINA_JOLIE			1
#define P_ARNOLD_SCHWARZENEGGER		2
#define P_BRAD_PITT					3
#define P_EMMA_WATSON				4
#define P_GEROGE_CLOONEY			5
#define P_JENNIFER_LOPEZ			6
#define P_JOHNNY_DEPP				7
#define P_JUSTIN_TIMBERLAKE			8
#define P_KATY_PERRY				9
#define P_KEANU_REEVES				10
#define P_NAOMI_WATTS				11
#define P_PATRICK_STEWART			12
#define P_MATIAS_PRATS				13
#define P_DESCONOCIDO				14
// #define P_NEWPERSON		X

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
/* NOMBRE: read_csv                                                           */
/* ARGUMENTOS ENTRADA: N/A                                                    */
/*    ARGUMENTO0: (string) people: Nombres de las personas para entrenar      */
/*    ARGUMENTO1: (string) filename: directorio del archivo csv               */
/* ARGUMENTOS SALIDA:                                                         */
/*    ARGUMENTO0: (int) nPictureById: Numero de fotos por cada persona        */
/*    ARGUMENTO1: (vector<Mat>) images: Imagenes de la coleccion              */
/*    ARGUMENTO2: (vector<int>) labels: labels de la coleccion                */
/* VALOR DEVUELTO: N/A                                                        */
/* DESCRIPCION: Funcion que lee el archivo csv                                */
/*----------------------------------------------------------------------------*/
void read_csv(int nPictureById[MAX_PEOPLE], string people[MAX_PEOPLE], const string& filename,
		vector<Mat>& images, vector<int>& labels, char separator = ';');



#ifdef RASPBERRY
	/*----------------------------------------------------------------------------*/
	/* NOMBRE: train_model_recognition                                            */
	/* ARGUMENTOS ENTRADA: N/A                                                    */
	/*    ARGUMENTO0: (int) nPictureById: Numero de fotos por cada persona        */
	/*    ARGUMENTO1: (string) people: Nombres de las personas para entrenar      */
	/*    ARGUMENTO2: (Eigenfaces) model: Modelo de reconocimiento                */
	/* ARGUMENTOS SALIDA:                                                         */
	/*    ARGUMENTO0: (int) im_width: Ancho de las imagenes                       */
	/*    ARGUMENTO1: (int) im_height: Alto de las imagenes                       */
	/* VALOR DEVUELTO: N/A                                                        */
	/* DESCRIPCION: Entrenamiento del modelo de reconocimiento                    */
	/*----------------------------------------------------------------------------*/
	void train_model_recognition(int nPictureById[MAX_PEOPLE], string people[MAX_PEOPLE], Eigenfaces& model,
			int& im_width, int& im_height);



	/*----------------------------------------------------------------------------*/
	/* NOMBRE: face_recognition                                                   */
	/* ARGUMENTOS ENTRADA: N/A                                                    */
	/*    ARGUMENTO0: (string) people: Nombres de las personas para entrenar      */
	/*    ARGUMENTO1: (Mat) gray: Imagen en blanco y negro                        */
	/*    ARGUMENTO2: (Mat) captureFrame: Imagen en color                         */
	/*    ARGUMENTO3: (vector< Rect_<int> >) faces: vector con caras detectadas   */
	/*    ARGUMENTO4: (int) im_width: Ancho de las imagenes                       */
	/*    ARGUMENTO5: (int) im_height: Alto de las imagenes                       */
	/*    ARGUMENTO6: (Eigenfaces) model: Modelo de reconocimiento                */
	/*    ARGUMENTO7: (int) prediction_seuil: Prediccion                          */
	/* ARGUMENTOS SALIDA:                                                         */
	/*    ARGUMENTO0: (double) x_face_pos: Posicion x de la cara                  */
	/*    ARGUMENTO1: (double) y_face_pos: Posicion y de la cara                  */
	/* VALOR DEVUELTO: N/A                                                        */
	/* DESCRIPCION: Reconocimiento de la persona detectada                        */
	/*----------------------------------------------------------------------------*/
	void face_recognition(string people[MAX_PEOPLE], Mat& gray, Mat& captureFrame, vector< Rect_<int> > *faces,
			int im_width, int im_height, Eigenfaces model,
			int prediction_seuil, double& x_face_pos, double& y_face_pos, double& area_face);
#else
	/*----------------------------------------------------------------------------*/
	/* NOMBRE: train_model_recognition                                            */
	/* ARGUMENTOS ENTRADA: N/A                                                    */
	/*    ARGUMENTO0: (int) nPictureById: Numero de fotos por cada persona        */
	/*    ARGUMENTO1: (string) people: Nombres de las personas para entrenar      */
	/*    ARGUMENTO2: (Ptr<FaceRecognizer>) model: Modelo de reconocimiento       */
	/* ARGUMENTOS SALIDA:                                                         */
	/*    ARGUMENTO0: (int) im_width: Ancho de las imagenes                       */
	/*    ARGUMENTO1: (int) im_height: Alto de las imagenes                       */
	/* VALOR DEVUELTO: N/A                                                        */
	/* DESCRIPCION: Entrenamiento del modelo de reconocimiento                    */
	/*----------------------------------------------------------------------------*/
	void train_model_recognition(int nPictureById[MAX_PEOPLE], string people[MAX_PEOPLE], Ptr<FaceRecognizer> model,
			int& im_width, int& im_height);



	/*----------------------------------------------------------------------------*/
	/* NOMBRE: face_recognition                                                   */
	/* ARGUMENTOS ENTRADA: N/A                                                    */
	/*    ARGUMENTO0: (string) people: Nombres de las personas para entrenar      */
	/*    ARGUMENTO1: (Mat) gray: Imagen en blanco y negro                        */
	/*    ARGUMENTO2: (Mat) captureFrame: Imagen en color                         */
	/*    ARGUMENTO3: (vector< Rect_<int> >) faces: vector con caras detectadas   */
	/*    ARGUMENTO4: (int) im_width: Ancho de las imagenes                       */
	/*    ARGUMENTO5: (int) im_height: Alto de las imagenes                       */
	/*    ARGUMENTO6: (Ptr<FaceRecognizer>) model: Modelo de reconocimiento       */
	/*    ARGUMENTO7: (int) prediction_seuil: Prediccion                          */
	/* ARGUMENTOS SALIDA:                                                         */
	/*    ARGUMENTO0: (double) x_face_pos: Posicion x de la cara                  */
	/*    ARGUMENTO1: (double) y_face_pos: Posicion y de la cara                  */
	/* VALOR DEVUELTO: N/A                                                        */
	/* DESCRIPCION: Reconocimiento de la persona detectada                        */
	/*----------------------------------------------------------------------------*/
	void face_recognition(string people[MAX_PEOPLE], Mat& gray, Mat& captureFrame, vector< Rect_<int> > *faces,
			int im_width, int im_height, Ptr<FaceRecognizer> model,
			int prediction_seuil, double& x_face_pos, double& y_face_pos, double& area_face);
#endif

#endif


#endif /* LIBRERIAS_RECONOCIMIENTO_H_ */
