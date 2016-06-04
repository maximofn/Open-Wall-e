//============================================================================
// Name        : Face_tracking.cpp
// Author      : Máximo Fernandezn Nuñez
// Version     : 1.0
// Copyright   :
// Description : Face tracking: software made ​​from the work of Emil Valkov,
// which was based on the work of Pierre Raufast
//============================================================================

// Librerias
#include "Librerias_Reconocimiento.h"

// OPENCV
#include <iostream>
#include <fstream>
#include <sstream>
#include "time.h"

#include <cv.h>
#include <highgui.h>

#include <opencv2/core/core.hpp>
#include "opencv2/contrib/contrib.hpp"
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/objdetect/objdetect.hpp>

//#include "/home/pi/wall-e/libfacerec-0.04/include/facerec.hpp"

//#include "RaspiCamCV.h"

using namespace std;
using namespace cv;

// for show mode
extern bool SHOW_MODE;
#define SHOW if (SHOW_MODE==1)

// for device mode
#define RASPBERRY 			1
#define UBUNTU 				2
#define MAQUINA_VIRTUAL			3
int DEVICE_MODE				= UBUNTU;
#define RASPBERRY_MODE 			if (DEVICE_MODE==1)
#define UBUNTU_MODE 			if (DEVICE_MODE==2)
#define MAQUINA_VIRTUAL_MODE		if (DEVICE_MODE==3)

// for face recognition mode
#define EIGENFACES 				1
#define FISHERFACES 				2
#define FACE_RECOGNICER_MODE 	EIGENFACES
#define EIGENFACES_MODE 	if (FACE_RECOGNICER_MODE==1)
#define FISHERFACES_MODE 	if (FACE_RECOGNICER_MODE==2)

// some constants to manage number of people to learn + id of people
#define MAX_PEOPLE 			15
#define P_MAXIMO			0
#define P_ANGELINA_JOLIE		1
#define P_ARNOLD_SCHWARZENEGGER		2
#define P_BRAD_PITT			3
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



int main( int argc, char** argv )
{
	// Declaration of variables
	int nPictureById[MAX_PEOPLE]; 			// Id of each person of the model of face recognition
	int im_width, im_height;			// heigh, witdh of 1st images of the model of face recognition
	string people[MAX_PEOPLE];			// Each person of the model of face recognition
	//Eigenfaces model;				// Model of face recognition
	Ptr<FaceRecognizer> model;			// Model of face recognition
	CascadeClassifier face_cascade;			// Cascade Classifier
	Mat captureFrame, grayscaleFrame;		// Captured and converted to gray Frames
	double x_face_pos, y_face_pos, area_face;	// Coordinates of the detected face
	//RaspiCamCvCapture * captureDevice;		// Video input
	CvCapture * captureDevice;			// Video input
	int PREDICTION_SEUIL;				// Prediction limit

	// Prediction limit depending on the device
	EIGENFACES_MODE 	PREDICTION_SEUIL = 5000;
	FISHERFACES_MODE 	PREDICTION_SEUIL = 1000;

	// Video input depending on the device
	//RASPBERRY_MODE 		captureDevice = raspiCamCvCreateCameraCapture(0); // Index doesn't really matter
	UBUNTU_MODE 		captureDevice = cvCreateCameraCapture(0);
	MAQUINA_VIRTUAL_MODE 	captureDevice = cvCaptureFromFile("/home/maximo/Escritorio/Face_tracking/Face_tracking/Debug/Matias_Prats.avi");

	// Model of face recognition depending on the device
	EIGENFACES_MODE	model = createEigenFaceRecognizer();
	FISHERFACES_MODE	model = createFisherFaceRecognizer();

	// Training Model of face recognition
	//train_model_recognition(nPictureById, people, model, im_width, im_height);

	// Load of Haar Cascade
	//if (!load_haar_cascade(face_cascade)) {	return -1;}

	// Create new window
	SHOW cvNamedWindow("Face tracking", 1);

	do {
		//IplImage* image = raspiCamCvQueryFrame(captureDevice);	// Get images from the video input
		IplImage* image = cvQueryFrame(captureDevice);	// Get images from the video input
		captureFrame = cvarrToMat(image);			// Convert images to Mat
		cvtColor(captureFrame, grayscaleFrame, CV_RGB2GRAY);	// Convert the image to gray scale

		// Detection and Face Recognition
		face_recognition(people, face_cascade, grayscaleFrame, captureFrame, im_width, im_height, model, PREDICTION_SEUIL, x_face_pos, y_face_pos, area_face);

		// Display results
		//SHOW cvShowImage("Face tracking", image);
		SHOW imshow("Face tracking", captureFrame);
	} while(cvWaitKey(10) < 0);

	// Destroy window
	SHOW cvDestroyWindow("Face tracking");
	//RASPBERRY_MODE		raspiCamCvReleaseCapture(&captureDevice);
	UBUNTU_MODE		cvReleaseCapture(&captureDevice);
	MAQUINA_VIRTUAL_MODE	cvReleaseCapture(&captureDevice);

	return 0;
}


//int main( int argc, char** argv )
//{
//	// Declaration of variables
//	int nPictureById[MAX_PEOPLE]; 				// Id of each person of the model of face recognition
//	int im_width, im_height;					// heigh, witdh of 1st images of the model of face recognition
//	string people[MAX_PEOPLE];					// Each person of the model of face recognition
//	//Eigenfaces model;							// Model of face recognition
//	Ptr<FaceRecognizer> model;				// Model of face recognition
//	CascadeClassifier face_cascade;			// Cascade Classifier
//	Mat captureFrame, grayscaleFrame;			// Captured and converted to gray Frames
//	double x_face_pos, y_face_pos, area_face;	// Coordinates of the detected face
//	//RaspiCamCvCapture * captureDevice;		// Video input
//	CvCapture * captureDevice;					// Video input
//	int PREDICTION_SEUIL;						// Prediction limit
//
//	// Prediction limit depending on the device
//#ifdef EIGENFACES
//	PREDICTION_SEUIL = 5000;
//#endif
//#ifdef FISHERFACES
//	PREDICTION_SEUIL = 1000;
//#endif
//
//	// Video input depending on the device
//#ifdef RASPBERRY
//	captureDevice = raspiCamCvCreateCameraCapture(0); // Index doesn't really matter
//#endif
//#ifdef UBUNTU
//	captureDevice = cvCreateCameraCapture(0);
//#endif
//#ifdef MAQUINA_VIRTUAL
//	captureDevice = cvCaptureFromFile("/home/maximo/Escritorio/Face_tracking/Face_tracking/Debug/Matias_Prats.avi");
//#endif
//
//	// Model of face recognition depending on the device
//	//EIGENFACES_MODE	model = createEigenFaceRecognizer();
//	//FISHERFACES_MODE	model = createFisherFaceRecognizer();
//
//	// Training Model of face recognition
//	//train_model_recognition(nPictureById, people, model, im_width, im_height);
//
//	// Load of Haar Cascade
//	//if (!load_haar_cascade(face_cascade)) {	return -1;}
//
//	// Create new window
//	SHOW cvNamedWindow("Face tracking", 1);
//
//	do {
//		//IplImage* image = raspiCamCvQueryFrame(captureDevice);	// Get images from the video input
//		IplImage* image = cvQueryFrame(captureDevice);	// Get images from the video input
//		captureFrame = cvarrToMat(image);			// Convert images to Mat
//		cvtColor(captureFrame, grayscaleFrame, CV_RGB2GRAY);	// Convert the image to gray scale
//
//		// Detection and Face Recognition
//		//face_recognition(people, face_cascade, grayscaleFrame, captureFrame, im_width, im_height, model, PREDICTION_SEUIL, x_face_pos, y_face_pos, area_face);
//
//		// Display results
//		//SHOW cvShowImage("Face tracking", image);
//		SHOW imshow("Face tracking", captureFrame);
//	} while(cvWaitKey(10) < 0);
//
//	// Destroy window
//	SHOW cvDestroyWindow("Face tracking");
//#ifdef	RASPBERRY
//	raspiCamCvReleaseCapture(&captureDevice);
//#endif
//#ifdef	UBUNTU
//	cvReleaseCapture(&captureDevice);
//#endif
//#ifdef	MAQUINA_VIRTUAL
//	cvReleaseCapture(&captureDevice);
//#endif
//
//	return 0;
//}
