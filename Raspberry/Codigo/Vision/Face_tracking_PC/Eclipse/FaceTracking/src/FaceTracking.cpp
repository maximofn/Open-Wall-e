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
#include "Defines.h"



int main( int argc, char** argv )
{
	// Declaration of variables
	int nPictureById[MAX_PEOPLE]; 				// Id of each person of the model of face recognition
	int im_width, im_height;					// heigh, witdh of 1st images of the model of face recognition
	string people[MAX_PEOPLE];					// Each person of the model of face recognition
	CascadeClassifier face_cascade;				// Cascade Classifier
	Mat captureFrame, grayscaleFrame;			// Captured and converted to gray Frames
	double x_face_pos, y_face_pos, area_face;	// Coordinates of the detected face
	int PREDICTION_SEUIL;						// Prediction limit
#ifdef RASPBERRY
	Eigenfaces model;							// Model of face recognition
	RaspiCamCvCapture * captureDevice;			// Video input

#else
	Ptr<FaceRecognizer> model;					// Model of face recognition
	CvCapture * captureDevice;					// Video input
#endif

	// Prediction limit depending on the device
#ifdef EIGENFACES
	PREDICTION_SEUIL = 10;
#else
	PREDICTION_SEUIL = 1000;
#endif

	// Video input depending on the device
#ifdef RASPBERRY
	captureDevice = raspiCamCvCreateCameraCapture(0); // Index doesn't really matter
#endif
#ifdef UBUNTU
	captureDevice = cvCreateCameraCapture(0);
#endif
#ifdef MAQUINA_VIRTUAL
	captureDevice = cvCaptureFromFile("/home/maximo/Escritorio/Face_tracking/Face_tracking/Debug/Matias_Prats.avi");
#endif

	// Model of face recognition depending on the device
#ifdef EIGENFACES
	model = createEigenFaceRecognizer();
#else
	model = createFisherFaceRecognizer();
#endif

	// Training Model of face recognition
	train_model_recognition(nPictureById, people, model, im_width, im_height);

	// Load of Haar Cascade
	if (!load_haar_cascade(face_cascade)) {	return -1;}

	// Create new window
#ifdef SHOW
	SHOW cvNamedWindow("Face tracking", 1);
#endif

	do {
		//IplImage* image = raspiCamCvQueryFrame(captureDevice);	// Get images from the video input
		IplImage* image = cvQueryFrame(captureDevice);	// Get images from the video input
		captureFrame = cvarrToMat(image);			// Convert images to Mat
		cvtColor(captureFrame, grayscaleFrame, CV_RGB2GRAY);	// Convert the image to gray scale

		// Detection and Face Recognition
		face_recognition(people, face_cascade, grayscaleFrame, captureFrame, im_width, im_height, model, PREDICTION_SEUIL, x_face_pos, y_face_pos, area_face);

		// Display results
#ifdef SHOW
		imshow("Face tracking", captureFrame);
#endif
	} while(cvWaitKey(10) < 0);

	// Destroy window
#ifdef SHOW
	cvDestroyWindow("Face tracking");
#endif

#ifdef RASPBERRY
	raspiCamCvReleaseCapture(&captureDevice);
#endif
#ifdef UBUNTU
	cvReleaseCapture(&captureDevice);
#endif
#ifdef MAQUINA_VIRTUAL
	cvReleaseCapture(&captureDevice);
#endif

	return 0;
}

