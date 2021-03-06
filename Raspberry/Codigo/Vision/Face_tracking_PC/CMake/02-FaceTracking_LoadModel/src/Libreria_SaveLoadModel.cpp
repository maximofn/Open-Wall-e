/*
 * Libreria_SaveLoadModel.cpp
 *
 *  Created on: 12/06/2016
 *      Author: maximofn
 */




#include "Libreria_SaveLoadModel.h"




void write_measures_file(int im_width, int im_height)
{
	char sTmp1[256];
	ofstream myfile;
	string directory;

	//Open file
	trace("\n (init write measure file) start write measures file");
	directory = get_measureFileDirectory();
	myfile.open(directory.c_str());

	// Write image width
	sprintf(sTmp1,"width=%d \n",im_width);
	myfile << sTmp1;

	// Write image heigh
	sprintf(sTmp1,"height=%d",im_height);
	myfile << sTmp1;

	//Close file
	myfile.close();
	trace("\n (init write measure file) measures file saved");
}



void read_measures_file(int& im_width, int& im_height, char separator)
{
	string filename;

	filename = get_measureFileDirectory();

	trace("\n (init read measure file) start read measures file");
	std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "(E) No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, measure, value;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, measure, separator);
        getline(liness, value);
        if(!measure.empty() && !value.empty())
        {
        	if(measure == "width")
        		im_width = atoi(value.c_str());
        	if(measure == "height")
        		im_height = atoi(value.c_str());
        }
    }
    trace("\n (init read measure file) measures file saved");
}



void write_people_file(string people[MAX_PEOPLE])
{
	char sTmp1[256];
	ofstream myfile;
	string text;
	string directory;

	//Open file
	trace("\n (init write people file) start write people file");
	directory = get_peopleFileDirectory();
	myfile.open(directory.c_str());

	// Write people in file
	for(unsigned int i=0;i<MAX_PEOPLE;i++){
		sprintf(sTmp1,"person(%d)",i);
		text = sTmp1 + people[i] + "\n";
		myfile << text;
	}

	//Close file
	myfile.close();
	trace("\n (init write people file) people file saved");
}



void read_people_file(string people[MAX_PEOPLE], char separator1, char separator2, char separator3)
{
	string filename;

	filename = get_peopleFileDirectory();

	trace("\n (init read people file) start read people file");
	std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "(E) No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, measure, person;
    int i;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, measure, separator1);
        getline(liness, measure, separator2);
        i = atoi(measure.c_str());
        getline(liness, person);
        if(!measure.empty() && !person.empty())
        {
        	people[i] = person;
        }
    }
    trace("\n (init read people file) people file saved");
}



void save_model_recognition(Ptr<FaceRecognizer> model)
{
	string directory;
	directory = get_modelFileDirectory();

	// train the model with your nice collection of pictures
	trace("\n (init save model file) start save model");
	model->save(directory);
	trace("\n (init save model file) save model : ok");
}



void load_model_recognition(Ptr<FaceRecognizer> model)
{
	string directory;
	directory = get_modelFileDirectory();

	// train the model with your nice collection of pictures
	trace("\n (init load model file) start load model");
	model->load(directory);
	trace("\n (init load model file) load model : ok");
}

