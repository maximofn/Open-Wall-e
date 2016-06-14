/*
 * Utilities.cpp
 *
 *  Created on: 04/06/2016
 *      Author: maximofn
 */

#include "Utilities.h"



string get_ProgramDirectory(){
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));

	return cwd;
}



string print_time(double t){
	int us;
	double s, ms;
//	int min;
	char sTmp[255];

	us = (int) t;
	s = t/1000000;
	ms = t/1000;
//	min = ( (int) s)/60;

	sprintf(sTmp,"%f us = %f ms = %f s", t, ms, s);

	return sTmp;
}
