/*
 * Librerias_Reconocimiento.cpp
 *
 *  Created on: 21/03/2014
 *      Author: Máximo Fernández Núñez
 */


#include "Librerias_Reconocimiento.h"


// some constants to manage nb of people to learn+ id of people
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

// for debug and trace
#define TRACE 1
#define DEBUG_MODE 0
#define DEBUG if (DEBUG_MODE==1)

// for show and information
bool SHOW_MODE = 1;
#define SHOW if (SHOW_MODE==1)
bool INFORMATION_MODE = 1;
#define INFORMATION if (INFORMATION_MODE==1 && SHOW_MODE==1)

// for device mode
#define RASPBERRY 		1
#define UBUNTU 			2
#define MAQUINA_VIRTUAL		3
extern int DEVICE_MODE;
#define RASPBERRY_MODE 			if (DEVICE_MODE==1)
#define UBUNTU_MODE 			if (DEVICE_MODE==2)
#define MAQUINA_VIRTUAL_MODE		if (DEVICE_MODE==3)

// for Cascade mode
#define LBP_CASCADE_FRONTALFACE			1
#define HAAR_CASCADE_FRONTALFACE_ALT		2
#define HAAR_CASCADE_FRONTALFACE_ALT2		3
#define HAAR_CASCADE_FRONTALFACE_ALT_TREE	4
#define HAAR_CASCADE_FRONTALFACE_ALT_DEFAULT	5
#define CASCADE_MODE 				LBP_CASCADE_FRONTALFACE








/////////////////////////////////////////////////
// trace if TRACE==1
/////////////////////////////////////////////////
void trace(string s)
{
	if (TRACE==1)
	{
		cout<<s<<"\n";
	}
}










/////////////////////////////////////////////////
//
// read csv files.
// Fully copied from Philipp Wagner works
// http://docs.opencv.org/trunk/modules/contrib/doc/facerec/tutorial/facerec_video_recognition.html
//
//	[int nPictureById[MAX_PEOPLE], string  people[MAX_PEOPLE]] =
// 		= read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';')
//
////////////////////////////////////////////////
void read_csv(int nPictureById[MAX_PEOPLE], string people[MAX_PEOPLE], const string& filename, vector<Mat>& images, vector<int>& labels, char separator) {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "(E) No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    int nLine=0;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty())
        {
        	// read the file and build the picture collection
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
            nPictureById[atoi(classlabel.c_str())]++;
        	nLine++;
        }
    }

    // write number of picture by people
    // did you notice? I'm not familiar with string classe :-)
    // I prefer my old good char* ...
    // (what a pity)
	char sTmp[128];
    sprintf(sTmp,"(init) %d pictures read to train",nLine);
    trace((string)(sTmp));
	for (int j=0;j<MAX_PEOPLE;j++)
	{
		sprintf(sTmp,"(init) %d pictures of %s (%d) read to train",nPictureById[j],people[j].c_str(),j);
   	 	trace((string)(sTmp));
	}
}










/**
 *  train model recognition
 *
 * @param no param
 *
 * [int nPictureById[MAX_PEOPLE], string people[MAX_PEOPLE], Ptr<FaceRecognizer> model, int& im_width, int& im_height] =
 * 		= train_model_recognition(int nPictureById[MAX_PEOPLE], string people[MAX_PEOPLE], Ptr<FaceRecognizer> model, int& im_width, int& im_height)
 *
 * or
 *
 * [int nPictureById[MAX_PEOPLE], string people[MAX_PEOPLE], Eigenfaces& model, int& im_width, int& im_height] =
 * 		= train_model_recognition(int nPictureById[MAX_PEOPLE], string people[MAX_PEOPLE], Eigenfaces& model, int& im_width, int& im_height)
 */
//void train_model_recognition(int nPictureById[MAX_PEOPLE], string people[MAX_PEOPLE], Eigenfaces& model, int& im_width, int& im_height)
void train_model_recognition(int nPictureById[MAX_PEOPLE], string people[MAX_PEOPLE], Ptr<FaceRecognizer> model, int& im_width, int& im_height)//, Fisherfaces model)
{
	vector<Mat> images;
	vector<int> labels;

	// init people, should be do in a config file, but I don't have time, I need to go to swimming pool with my daughters and they prefer to swimm
	// than to see their father do a config file, life is hard "Pierre (http://thinkrpi.wordpress.com/)"
	people[P_MAXIMO] 			= "Maximo";
	people[P_ANGELINA_JOLIE] 		= "Angelina Jolie";
	people[P_ARNOLD_SCHWARZENEGGER] 	= "Arnold Schwarzenegger";
	people[P_BRAD_PITT] 			= "Brad Pitt";
	people[P_EMMA_WATSON] 			= "Emma Watson";
	people[P_GEROGE_CLOONEY] 		= "George Clooney";
	people[P_JENNIFER_LOPEZ] 		= "jennifer Lopez";
	people[P_JOHNNY_DEPP] 			= "johnny Depp";
	people[P_JUSTIN_TIMBERLAKE] 		= "Justin Timberlake";
	people[P_KATY_PERRY] 			= "Katy Perry";
	people[P_KEANU_REEVES] 			= "Keanu Reeves";
	people[P_NAOMI_WATTS] 			= "Naomi Watts";
	people[P_PATRICK_STEWART] 		= "Patrick Stewart";
	people[P_MATIAS_PRATS] 			= "Matias Prats";
	people[P_DESCONOCIDO] 			= "Desconocido";
	// people[P_NEWPERSON] 			= "NewPerson";

	// init...
	// reset counter
	for (int i=0;i<MAX_PEOPLE;i++)
	{
		nPictureById[i]=0;
	}
	//int bFirstDisplay	= 1;
	trace("(init) People initialized : ok");

	// Get the path to your CSV
	string fn_csv;
	RASPBERRY_MODE 			fn_csv = "/home/pi/Face_tracking/04__Face_recognition__Robidouille_API/faces.csv";
	UBUNTU_MODE 			fn_csv = "/home/maximofn/Documentos/Wall-e/Raspberry/Codigo/Vision/Face_tracking_PC/Eclipse/FaceTracking/Debug/faces.csv";
	MAQUINA_VIRTUAL_MODE		fn_csv = "/home/maximo/Escritorio/Face_tracking/Face_tracking/Debug/faces.csv";
	DEBUG cout << "(DEBUG) csv = " << fn_csv << "\n";

	// Read in the data (fails if no valid input filename is given, but you'll get an error message):
	try {
		read_csv(nPictureById, people, fn_csv, images, labels);
		DEBUG cout<<"(DEBUG) read CSV ok\n";
	}
	catch (cv::Exception& e)
	{
		cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
		exit(1);
	}

	// get heigh, witdh of 1st images--> must be the same
	im_width = images[0].cols;
	im_height = images[0].rows;
	trace("(init) taille images : ok");

	// This a Eigen model, but you could replace with Fisher model
	// in this case threshold value should be lower (try)

	// train the model with your nice collection of pictures
	trace("(init) start train images");

	//RASPBERRY_MODE model.train(images, labels);
	//RASPBERRY_MODE		model.train(images, labels);
	UBUNTU_MODE		model->train(images, labels);
	MAQUINA_VIRTUAL_MODE	model->train(images, labels);
	trace("(init) train images : ok");
}














/**
 * Load haar cascade
 *
 * @param no param.
 *
 * [CascadeClassifier& face_cascade, string& fn_haar] =
 * 		= load_haar_cascade(CascadeClassifier& face_cascade, string& fn_haar)
 *
 */
bool load_haar_cascade(CascadeClassifier& face_cascade)
{
	// set path for haar cascade
	// change fn_harr to be quicker LBP (see article)
	string fn_haar;
	switch (CASCADE_MODE){
		case LBP_CASCADE_FRONTALFACE:
			RASPBERRY_MODE 		fn_haar = "/usr/share/opencv/lbpcascades/lbpcascade_frontalface.xml";
			UBUNTU_MODE 		fn_haar = "/usr/local/share/OpenCV/lbpcascades/lbpcascade_frontalface.xml";
			MAQUINA_VIRTUAL_MODE	fn_haar = "/usr/local/share/OpenCV/lbpcascades/lbpcascade_frontalface.xml";
			break;
		case HAAR_CASCADE_FRONTALFACE_ALT:
			RASPBERRY_MODE 		fn_haar = "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml";
			UBUNTU_MODE 		fn_haar = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";
			MAQUINA_VIRTUAL_MODE	fn_haar = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";
			break;
		case HAAR_CASCADE_FRONTALFACE_ALT2:
			RASPBERRY_MODE 		fn_haar = "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt2.xml";
			UBUNTU_MODE 		fn_haar = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt2.xml";
			MAQUINA_VIRTUAL_MODE	fn_haar = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt2.xml";
			break;
		case HAAR_CASCADE_FRONTALFACE_ALT_TREE:
			RASPBERRY_MODE 		fn_haar = "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt_tree.xml";
			UBUNTU_MODE 		fn_haar = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt_tree.xml";
			MAQUINA_VIRTUAL_MODE	fn_haar = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt_tree.xml";
			break;
		case HAAR_CASCADE_FRONTALFACE_ALT_DEFAULT:
			RASPBERRY_MODE 		fn_haar = "/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml";
			UBUNTU_MODE 		fn_haar = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml";
			MAQUINA_VIRTUAL_MODE	fn_haar = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml";
			break;
		default:
			cerr << "Error opening Cascade file" << endl;
			exit(1);
	}
	DEBUG cout<<"(DEBUG) haar="<<fn_haar<<"\n";
	trace("(init) fn_haar : ok");

	// load face model
	if (!face_cascade.load(fn_haar))
   	{
		cout <<"(Error) face cascade model not loaded :" + fn_haar + "\n";
		return false;
	}
	trace("(init) Load modele : ok");

	return true;
}













/**
 *  face recognition
 *
 * @param no param
 *
 * [Mat& captureFrame, double& x_face_pos, double& y_face_pos, double& area_face] =
 * 		= face_recognition(string people[MAX_PEOPLE], CascadeClassifier& face_cascade, Mat& gray, Mat& captureFrame, int im_width, int im_height, Ptr<FaceRecognizer> model, int PREDICTION_SEUIL, double& x_face_pos, double& y_face_pos, double& area_face)
 *
 * or
 *
 * [Mat& captureFrame, double& x_face_pos, double& y_face_pos, double& area_face] =
 * 		= face_recognition(string people[MAX_PEOPLE], CascadeClassifier& face_cascade, Mat& gray, Mat& captureFrame, int im_width, int im_height, Eigenfaces model, int PREDICTION_SEUIL, double& x_face_pos, double& y_face_pos, double& area_face)
 */
//void face_recognition(string people[MAX_PEOPLE], CascadeClassifier& face_cascade, Mat& gray, Mat& captureFrame, int im_width, int im_height, Eigenfaces model, int PREDICTION_SEUIL, double& x_face_pos, double& y_face_pos, double& area_face)
void face_recognition(string people[MAX_PEOPLE], CascadeClassifier& face_cascade, Mat& gray, Mat& captureFrame, int im_width, int im_height, Ptr<FaceRecognizer> model, int PREDICTION_SEUIL, double& x_face_pos, double& y_face_pos, double& area_face)
{
	// Declaration of variables
	Mat face,face_resized;			// Face converted to gray scale and face resized
	vector< Rect_<int> > faces;		// Vector of faces
	double scaleFactor = 1.1;		// Parameter specifying how much the image size is reduced at each image scale
	int minNeighbors = 3; 			// Parameter specifying how many neighbors each candidate rectangle should have to retain it
	double fx = 1.0;			// scale factor along the horizontal axis
	double fy = 1.0;			// scale factor along the vertical axis

	// Detect faces
	face_cascade.detectMultiScale(gray, faces, scaleFactor, minNeighbors, CV_HAAR_SCALE_IMAGE, Size(80,80));

	// For each faces founded
	for(unsigned int i = 0; i < faces.size(); i++)
	{
		// crop face (pretty easy with opencv, don't you think ?
		Rect face_i = faces[i];

		face = gray(face_i);

		//  resized face and display it
		cv::resize(face, face_resized, Size(im_width, im_height), fx, fy, CV_INTER_NN); //INTER_CUBIC);

		// now, we try to predict who is it ?
		char sTmp1[256], sTmp2[256], sTmp3[256], sTmp4[256];
		double predicted_confidence = 0.0;
		int prediction = -1;
		//RASPBERRY_MODE		model.predict(face_resized,prediction,predicted_confidence);
		UBUNTU_MODE		model->predict(face_resized,prediction,predicted_confidence);
		MAQUINA_VIRTUAL_MODE	model->predict(face_resized,prediction,predicted_confidence);

		// create a rectangle around the face
		INFORMATION rectangle(captureFrame, face_i, CV_RGB(0, 255 ,0), 1);

		// get face area and position
		x_face_pos = face_i.x + face_i.width/2;
		y_face_pos = face_i.y + face_i.height/2;
		area_face = face_i.width * face_i.height;

		// if good prediction : > threshold
		if (predicted_confidence>PREDICTION_SEUIL)
		{
			// trace is commented to speed up
			DEBUG sprintf(sTmp1,"(DEBUG) prediction ok = %s (%d) confiance = (%d)",people[prediction].c_str(),prediction,(int)predicted_confidence);
			DEBUG trace((string)(sTmp1));

		 	// display name of the guy on the picture
			string box_text1, box_text2, box_text3;
			if (prediction<MAX_PEOPLE)
			{
				box_text1 = "Id: " + people[prediction];
				sprintf(sTmp2,"confiance = %d",(int)predicted_confidence);
				sprintf(sTmp3,"x = %d, y = %d",(int)x_face_pos,(int)y_face_pos);
				sprintf(sTmp4,"area = %d",(int)area_face);
			}
			else
			{
				trace("(Error) prediction id incoherent");
			}
			int pos_x = std::max(face_i.tl().x - 0,0);
			int pos_y = std::max(face_i.tl().y + face_i.height + 15,0);
			INFORMATION putText(captureFrame, box_text1, Point(pos_x, pos_y), FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(255,255,255), 1.0);

			pos_y = pos_y + 20;
			INFORMATION putText(captureFrame, sTmp2, Point(pos_x, pos_y), FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(255,255,255), 1.0);

			pos_y = pos_y + 20;
			INFORMATION putText(captureFrame, sTmp3, Point(pos_x, pos_y), FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(255,255,255), 1.0);

			pos_y = pos_y + 20;
			INFORMATION putText(captureFrame, sTmp4, Point(pos_x, pos_y), FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(255,255,255), 1.0);
		}
		else
		{
			// trace is commented to speed up
			DEBUG sprintf(sTmp1,"(DEBUG) prediction too low = %s (%d) confiance = (%d)",people[prediction].c_str(),prediction,(int)predicted_confidence);
			DEBUG trace((string)(sTmp1));
		}
	} // end for
}
