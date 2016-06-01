/*
 * Librerias_Reconocimiento.h
 *
 *  Created on: 28/05/2016
 *      Author: maximofn
 */

#ifndef SRC_LIBRERIAS_RECONOCIMIENTO_H_
#define SRC_LIBRERIAS_RECONOCIMIENTO_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include "time.h"
using namespace std;

//OpenCV
#include <cv.h>
#include <highgui.h>
#include <opencv2/objdetect/objdetect.hpp>
#include "opencv2/core.hpp"
#include "/usr/local/include/opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace cv;
using namespace cv::face;
using namespace std;
//#include "opencv2/contrib/contrib.hpp"
//#include "/home/pi/wall-e/libfacerec-0.04/include/facerec.hpp"
using namespace cv;

// some constants to manage number of people to learn + id of people
#define MAX_PEOPLE 				15
#define P_MAXIMO				0
#define P_ANGELINA_JOLIE		1
#define P_ARNOLD_SCHWARZENEGGER	2
#define P_BRAD_PITT				3
#define P_EMMA_WATSON			4
#define P_GEROGE_CLOONEY		5
#define P_JENNIFER_LOPEZ		6
#define P_JOHNNY_DEPP			7
#define P_JUSTIN_TIMBERLAKE		8
#define P_KATY_PERRY			9
#define P_KEANU_REEVES			10
#define P_NAOMI_WATTS			11
#define P_PATRICK_STEWART		12
#define P_MATIAS_PRATS			13
#define P_DESCONOCIDO			14
// #define P_NEWPERSON			X

// for Cascade mode
#define LBP_CASCADE_FRONTALFACE					1
#define HAAR_CASCADE_FRONTALFACE_ALT			2
#define HAAR_CASCADE_FRONTALFACE_ALT2			3
#define HAAR_CASCADE_FRONTALFACE_ALT_TREE		4
#define HAAR_CASCADE_FRONTALFACE_ALT_DEFAULT	5
#define CASCADE_MODE 							LBP_CASCADE_FRONTALFACE



void read_csv(int nPictureById[MAX_PEOPLE], string people[MAX_PEOPLE], const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';');

//void train_model_recognition(int nPictureById[MAX_PEOPLE], string people[MAX_PEOPLE], Eigenfaces& model, int& im_width, int& im_height);
//void train_model_recognition(int nPictureById[MAX_PEOPLE], string people[MAX_PEOPLE], Ptr<FaceRecognizer> model, int& im_width, int& im_height);

bool load_haar_cascade(CascadeClassifier& face_cascade);

void face_recognition(string people[MAX_PEOPLE], CascadeClassifier& face_cascade, Mat& gray, Mat& captureFrame, int im_width, int im_height, Ptr<FaceRecognizer> model, int PREDICTION_SEUIL, double& x_face_pos, double& y_face_pos, double& area_face);
//void face_recognition(string people[MAX_PEOPLE], CascadeClassifier& face_cascade, Mat& gray, Mat& captureFrame, int im_width, int im_height, Eigenfaces model, int PREDICTION_SEUIL, double& x_face_pos, double& y_face_pos, double& area_face);


#endif /* SRC_LIBRERIAS_RECONOCIMIENTO_H_ */
