/*
 * FaceTracking_SaveModel.cpp
 *
 *  Created on: 12/06/2016
 *      Author: maximofn
 */


// Librerias
#include "Libreria_SaveLoadModel.h"
#include "../Resources/Defines.h"
#include "../Resources/Resources.h"
#include "Utilities.h"
#include "Librerias_Reconocimiento.h"



int main( int argc, char** argv )
{
	// Declaration of variables
	int nPictureById[MAX_PEOPLE]; 	// Id of each person of the model of face recognition
	int im_width, im_height;		// heigh, witdh of 1st images of the model of face recognition
	string people[MAX_PEOPLE];		// Each person of the model of face recognition
	//Eigenfaces model;				// Model of face recognition
	Ptr<FaceRecognizer> model;		// Model of face recognition
	char sTmp[255];

#ifdef TRACE
	sprintf(sTmp,"\n Directorio de ejecucion del programa: ");
	trace (sTmp);
	cout << get_ProgramDirectory();
#endif

	// Model of face recognition
	#ifdef EIGENFACES
		model = createEigenFaceRecognizer();
	#else
		model = createFisherFaceRecognizer();
	#endif

	// Training Model of face recognition
	train_model_recognition(nPictureById, people, model, im_width, im_height);

	//write measures file
	write_measures_file(im_width, im_height);

	//write people file
	write_people_file(people);

	// Save model
	save_model_recognition(model);

	#ifdef TRACE
		trace ("\n");
	#endif

	return 0;
}