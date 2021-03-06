/*
 * libreria_Detection.cpp
 *
 *  Created on: 07/06/2016
 *      Author: maximofn
 */

#include "libreria_Detection.h"


bool load_haar_cascade(CascadeClassifier& face_cascade)
{
	// set path for haar cascade
	// change fn_harr to be quicker LBP (see article)
	string fn_haar;
	char sTmp[1000];

	fn_haar = get_fn_haarFileDirectory();

#ifdef TRACE
	sprintf(sTmp,"\n (init load haar cascade) haar = ");
	trace(sTmp);
	cout << fn_haar;
#endif

	// load face model
	if (!face_cascade.load(fn_haar))
   	{
		cout <<"\n (Error load haar cascade) face cascade model not loaded :" + fn_haar;
		return false;
	}
#ifdef TRACE
	trace("\n (init load haar cascade) Load modele : ok");
#endif

	return true;
}



void face_detection(CascadeClassifier& face_cascade, Mat& grayscaleFrame, Mat& captureFrame, vector< Rect_<int> > *faces,
		double& x_face_pos, double& y_face_pos, double& area_face)
{
	// Declaration of variables
	Mat face,face_resized;			// Face converted to gray scale and face resized
	//vector< Rect_<int> > faces;		// Vector of faces
	double scaleFactor = 1.1;		// Parameter specifying how much the image size is reduced at each image scale
	int minNeighbors = 3; 			// Parameter specifying how many neighbors each candidate rectangle should have to retain it
	int minSize = 8;				// Minimum possible object size. Objects smaller than that are ignored.
	int maxSize = 80;				// Maximum possible object size. Objects larger than that are ignored.
	char sTmp[150];

	// Detect faces
	face_cascade.detectMultiScale(grayscaleFrame, *faces, scaleFactor, minNeighbors, CV_HAAR_SCALE_IMAGE, Size(minSize,maxSize));

	// For each faces founded
	for(unsigned int i = 0; i < (*faces).size(); i++)
	{
		// crop face (pretty easy with opencv, don't you think ?
		Rect face_i = (*faces)[i];

		// get face area and position
		x_face_pos = face_i.x + face_i.width/2;
		y_face_pos = face_i.y + face_i.height/2;
		area_face = face_i.width * face_i.height;

#ifdef TRACE
	    sprintf(sTmp,"\n Cara detectada, x = %i, y = %i, area = %i", (int)x_face_pos, (int)y_face_pos, (int)area_face);
	    trace(sTmp);
#endif

		// create a rectangle around the face
#ifdef INFORMATION
		rectangle(captureFrame, face_i, CV_RGB(0, 255 ,0), 1);
#endif
	} // end for
}
