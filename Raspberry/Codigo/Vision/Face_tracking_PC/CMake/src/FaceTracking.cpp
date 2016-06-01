/*
 * FaceTracking.cpp
 *
 *  Created on: 28/05/2016
 *      Author: maximofn
 */

// OPENCV
#include <iostream>
#include <fstream>
#include <sstream>
#include "time.h"

#include <cv.h>
#include <highgui.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/core/core.hpp"
//#include "opencv2/contrib/contrib.hpp"
#include "opencv2/objdetect/objdetect.hpp"

using namespace std;
using namespace cv;

// some constants to manage nb of people to learn+ id of people
#define MAX_PEOPLE 		1
#define P_MAXIMO		0
// #define P_NEWPERSON		1

int main( int argc, char** argv )
{
	CvCapture * captureDevice = cvCreateCameraCapture(0);

	//int nPictureById[MAX_PEOPLE];
	//string  people[MAX_PEOPLE];

	Mat captureFrame, grayscaleFrame;

	cvNamedWindow("Face tracking", 1);

	do {
		IplImage* image = cvQueryFrame(captureDevice);

		cvShowImage("Face tracking", image);
	} while(cvWaitKey(10) < 0);

	cvDestroyWindow("Face tracking");
	cvReleaseCapture(&captureDevice);

	printf( "\nPrograma" );
	waitKey(0);

  return 0;
}
