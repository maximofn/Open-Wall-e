/*
 * FaceTracking_LoadModel.cpp
 *
 *  Created on: 12/06/2016
 *      Author: maximofn
 */

// Librerias
#include "Libreria_SaveLoadModel.h"
#include "../Resources/Defines.h"
#include "../Resources/Resources.h"
#include "Utilities.h"
#include "libreria_Detection.h"
#include "Librerias_Reconocimiento.h"
#ifdef RASPBERRY
	#include "../Resources/raspicam/RaspiCamCV.h"
#endif

int main( int argc, char** argv )
{
	// Medida de tiempo inicial
	clock_t t0, t_load, t_loop, t_loop0;
	double dtime;
	t0 = clock();

	// Declaration of variables
	CascadeClassifier face_cascade;				// Cascade Classifier
	Mat captureFrame, grayscaleFrame;			// Captured and converted to gray Frames
	double x_face_pos, y_face_pos, area_face;	// Coordinates of the detected face
	vector< Rect_<int> > faces;					// Vector of faces
	#ifdef RASPBERRY
		RaspiCamCvCapture * captureDevice;		// Video input
	#else
		CvCapture * captureDevice;				// Video input
	#endif
	char sTmp[255];

#ifdef TRACE
	sprintf(sTmp,"\n Directorio de ejecucion del programa: ");
	trace (sTmp);
	cout << get_ProgramDirectory();
#endif

#ifdef RECOGNITION
	// Declaration of variables Face recognition
	string people[MAX_PEOPLE];					// Each person of the model of face recognition
	int im_width, im_height;					// heigh, witdh of 1st images of the model of face recognition
	int prediction_seuil;						// Prediction limit
	Ptr<FaceRecognizer> model;					// Model of face recognitio

	// Prediction limit depending on the device
	#ifdef EIGENFACES
		prediction_seuil = 10;
	#else
		prediction_seuil = 1000;
	#endif

	// Model of face recognition
	#ifdef EIGENFACES
		model = createEigenFaceRecognizer();
	#else
		model = createFisherFaceRecognizer();
	#endif

	// Read measures file
	read_measures_file(im_width, im_height, '=');

	// Read people file
	read_people_file(people, '(', ')', '=');

	// Load model
	load_model_recognition(model);
	t_load = clock();

	#ifdef DEBUG
		dtime = difftime(t_load,t0);
		sprintf(sTmp,"\n (Face Tracking) tiempo de carga del modelo = ");
		debug(sTmp);
		cout << print_time(dtime);
	#endif

#endif

	// Video input depending on the device
	#ifdef RASPBERRY
		captureDevice = raspiCamCvCreateCameraCapture(0); // Index doesn't really matter
	#else
		captureDevice = cvCreateCameraCapture(0);
	#endif

	// Load of Haar Cascade
	if (!load_haar_cascade(face_cascade)) {	return -1;}

	// Create new window
	SHOW cvNamedWindow("Face tracking", 1);

	do {
		t_loop0 = clock();

		#ifdef RASPBERRY
				IplImage* image = raspiCamCvQueryFrame(captureDevice);	// Get images from the video input
		#else
				IplImage* image = cvQueryFrame(captureDevice);			// Get images from the video input
		#endif
		captureFrame = cvarrToMat(image);			// Convert images to Mat
		cvtColor(captureFrame, grayscaleFrame, CV_RGB2GRAY);	// Convert the image to gray scale

		// Detection and Face Recognition
		face_detection(face_cascade, grayscaleFrame, captureFrame, &faces, x_face_pos, y_face_pos, area_face);

		#ifdef RECOGNITION
				// Detection and Face Recognition
				face_recognition(people, grayscaleFrame, captureFrame, &faces, im_width, im_height, model,
								prediction_seuil, x_face_pos, y_face_pos, area_face);
		#endif

		// Display results
		#ifdef SHOW
				imshow("Face tracking", captureFrame);
		#endif

		t_loop = clock();
		#ifdef DEBUG
			dtime = difftime(t_loop,t_loop0);
			sprintf(sTmp,"\n (Face Tracking) tiempo del bucle del reconocimiento de cara = ");
			debug(sTmp);
			cout << print_time(dtime);
		#endif
	} while(cvWaitKey(10) < 0);

	// Destroy window
	#ifdef SHOW
		cvDestroyWindow("Face tracking");
	#endif

	#ifdef TRACE
		trace ("\n");
	#endif

	#ifdef RASPBERRY
		raspiCamCvReleaseCapture(&captureDevice);
	#else
		cvReleaseCapture(&captureDevice);
	#endif

	return 0;
}
