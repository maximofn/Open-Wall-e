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
