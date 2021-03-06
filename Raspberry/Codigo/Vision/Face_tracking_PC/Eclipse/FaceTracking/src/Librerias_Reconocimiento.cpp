/*
 * Librerias_Reconocimiento.cpp
 *
 *  Created on: 21/03/2014
 *      Author: Máximo Fernández Núñez
 */


#include "Librerias_Reconocimiento.h"
#include "Utilities.h"


#ifdef RECOGNITION


void read_csv(int nPictureById[MAX_PEOPLE], string people[MAX_PEOPLE], const string& filename, vector<Mat>& images,
		vector<int>& labels, char separator) {
	string s;
	char sTmp[255];

	// Read CSV file
    ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "\n (Error read CSV file) No valid input csv file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }

    // Read path and classlabel for each person
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
#ifdef TRACE
    sprintf(sTmp,"\n (init read CSV file) %d pictures read to train",nLine);
    trace(sTmp);
	for (int j=0;j<MAX_PEOPLE;j++)
	{
		sprintf(sTmp,"\n (init read CSV file) %d pictures of %s (%d) read to train",nPictureById[j],people[j].c_str(),j);
   	 	trace(sTmp);
	}
#endif
}



void train_model_recognition(int nPictureById[MAX_PEOPLE], string people[MAX_PEOPLE], Ptr<FaceRecognizer> model,
		int& im_width, int& im_height)
{
	vector<Mat> images;
	vector<int> labels;
	char sTmp[1000];

	// init people, should be do in a config file, but I don't have time, I need to go to swimming pool
	// with my daughters and they prefer to swimm than to see their father do a config file, life is
	// hard "Pierre (http://thinkrpi.wordpress.com/)"
	people[P_MAXIMO] 				= "Maximo";
	people[P_ANGELINA_JOLIE] 		= "Angelina Jolie";
	people[P_ARNOLD_SCHWARZENEGGER] = "Arnold Schwarzenegger";
	people[P_BRAD_PITT] 			= "Brad Pitt";
	people[P_EMMA_WATSON] 			= "Emma Watson";
	people[P_GEROGE_CLOONEY] 		= "George Clooney";
	people[P_JENNIFER_LOPEZ] 		= "ennifer Lopez";
	people[P_JOHNNY_DEPP] 			= "Johnny Depp";
	people[P_JUSTIN_TIMBERLAKE] 	= "Justin Timberlake";
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
#ifdef TRACE
	trace("\n (init train model) People initialized : ok");
#endif

	// Get the path to your CSV
	string fn_csv;
	fn_csv = get_csvFileDirectory ();

#ifdef DEBUG
    sprintf(sTmp,"\n (init train model) csv = ");
    debug(sTmp);
	cout << fn_csv;
#endif

	// Read in the data (fails if no valid input filename is given, but you'll get an error message):
	try {
		read_csv(nPictureById, people, fn_csv, images, labels);
#ifdef DEBUG
	    sprintf(sTmp,"\n (init train model) read CSV ok");
	    debug(sTmp);
#endif
	}
	catch (cv::Exception& e)
	{
		cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
		exit(1);
	}

	// get heigh, witdh of 1st images--> must be the same
	im_width = images[0].cols;
	im_height = images[0].rows;
#ifdef DEBUG
	    sprintf(sTmp,"\n (init train model) im_width = %i, im_height = %i", im_width, im_height);
	    debug(sTmp);
#endif
#ifdef TRACE
	trace("\n (init train model) taille images : ok");
#endif

	// This a Eigen model, but you could replace with Fisher model
	// in this case threshold value should be lower (try)

	// train the model with your nice collection of pictures
#ifdef TRACE
	trace("\n (init train model) start train images");
#endif

	model->train(images, labels);

#ifdef TRACE
	trace("\n (init train model) train images : ok");
#endif
}



void face_recognition(string people[MAX_PEOPLE], Mat& gray, Mat& captureFrame, vector< Rect_<int> > *faces,
		int im_width, int im_height, Ptr<FaceRecognizer> model,
		int prediction_seuil, double& x_face_pos, double& y_face_pos, double& area_face)
{
	// Declaration of variables
	Mat face,face_resized;			// Face converted to gray scale and face resized
//	vector< Rect_<int> > faces;		// Vector of faces
	double fx = 1.0;				// scale factor along the horizontal axis
	double fy = 1.0;				// scale factor along the vertical axis

	// For each faces founded
	for(unsigned int i = 0; i < (*faces).size(); i++)
	{
		// crop face (pretty easy with opencv, don't you think ?
		Rect face_i = (*faces)[i];

		face = gray(face_i);

		//  resized face and display it
		cv::resize(face, face_resized, Size(im_width, im_height), fx, fy, CV_INTER_NN); //INTER_CUBIC);

		// now, we try to predict who is it ?
		char sTmp1[256], sTmp2[256], sTmp3[256], sTmp4[256];
		double predicted_confidence = 0.0;
		int prediction = -1;
		model->predict(face_resized,prediction,predicted_confidence);

		// if good prediction : > threshold
		if (predicted_confidence>prediction_seuil)
		{
			// trace is commented to speed up
#ifdef DEBUG
			sprintf(sTmp1,"\n (face recognition) prediction ok = %s (%d) confiance = (%d)",
					people[prediction].c_str(),prediction,(int)predicted_confidence);
			debug(sTmp1);
#endif

		 	// display name of the guy on the picture
			string box_text1, box_text2, box_text3;
			if (prediction<MAX_PEOPLE)
			{
				box_text1 = "Id: " + people[prediction];
				sprintf(sTmp2,"confiance = %d",(int)predicted_confidence);
				sprintf(sTmp3,"x = %d, y = %d",(int)x_face_pos,(int)y_face_pos);
				sprintf(sTmp4,"area = %d",(int)area_face);
			}
#ifdef TRACE
			else
			{
				trace("(Error face recognition) prediction id incoherent");
			}
#endif

			int pos_x = std::max(face_i.tl().x - 0,0);
			int pos_y = std::max(face_i.tl().y + face_i.height + 15,0);

#ifdef INFORMATION
			putText(captureFrame, box_text1, Point(pos_x, pos_y), FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(255,255,255), 1.0);

			pos_y = pos_y + 20;
			putText(captureFrame, sTmp2, Point(pos_x, pos_y), FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(255,255,255), 1.0);

			pos_y = pos_y + 20;
			putText(captureFrame, sTmp3, Point(pos_x, pos_y), FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(255,255,255), 1.0);

			pos_y = pos_y + 20;
			putText(captureFrame, sTmp4, Point(pos_x, pos_y), FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(255,255,255), 1.0);
#endif
		}
		else
		{
			// trace is commented to speed up
#ifdef DEBUG
			sprintf(sTmp1,"(face recognition) prediction too low = %s (%d) confiance = (%d)",
					people[prediction].c_str(),prediction,(int)predicted_confidence);
#endif
		}
	} // end for
}


#endif




