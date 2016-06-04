/*
 * Librerias_Reconocimiento.h
 *
 *  Created on: 21/03/2014
 *      Author: Máximo Fernández Núñez
 */

#ifndef LIBRERIAS_RECONOCIMIENTO_H_
#define LIBRERIAS_RECONOCIMIENTO_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include "time.h"

// OPENCV
#include <cv.h>
#include <highgui.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/contrib/contrib.hpp"
#ifdef RASPBERRY
#include "/home/pi/wall-e/libfacerec-0.04/include/facerec.hpp"
#include "RaspiCamCV.h"
#endif
using namespace std;
using namespace cv;


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

// for Cascade mode
#define LBP_CASCADE_FRONTALFACE
//#define HAAR_CASCADE_FRONTALFACE_ALT
//#define HAAR_CASCADE_FRONTALFACE_ALT2
//#define HAAR_CASCADE_FRONTALFACE_ALT_TREE
//#define HAAR_CASCADE_FRONTALFACE_ALT_DEFAULT


	void read_csv(int nPictureById[MAX_PEOPLE], string people[MAX_PEOPLE], const string& filename,
			vector<Mat>& images, vector<int>& labels, char separator = ';');
#ifdef RASPBERRY
	void train_model_recognition(int nPictureById[MAX_PEOPLE], string people[MAX_PEOPLE], Eigenfaces& model,
			int& im_width, int& im_height);
	void face_recognition(string people[MAX_PEOPLE], CascadeClassifier& face_cascade, Mat& gray, Mat& captureFrame,
			int im_width, int im_height, Eigenfaces model,
			int PREDICTION_SEUIL, double& x_face_pos, double& y_face_pos, double& area_face);
#else
	void train_model_recognition(int nPictureById[MAX_PEOPLE], string people[MAX_PEOPLE], Ptr<FaceRecognizer> model,
			int& im_width, int& im_height);
	void face_recognition(string people[MAX_PEOPLE], CascadeClassifier& face_cascade, Mat& gray, Mat& captureFrame,
			int im_width, int im_height, Ptr<FaceRecognizer> model,
			int PREDICTION_SEUIL, double& x_face_pos, double& y_face_pos, double& area_face);
#endif
	bool load_haar_cascade(CascadeClassifier& face_cascade);


#endif /* LIBRERIAS_RECONOCIMIENTO_H_ */
