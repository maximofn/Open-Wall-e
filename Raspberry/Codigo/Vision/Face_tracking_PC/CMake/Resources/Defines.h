/*
 * Defines.h
 *
 *  Created on: 31/05/2016
 *      Author: maximofn
 */

#ifndef SRC_DEFINES_H_
#define SRC_DEFINES_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include "time.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

using namespace std;


#define SHOW
#ifdef SHOW
	#define INFORMATION
#endif

// for debug and trace
#define TRACE
#define DEBUG

// for device mode
//#define RASPBERRY
#ifndef RASPBERRY
	#define UBUNTU
#endif

// for prediction
	#define RECOGNITION

// for face recognition mode
#ifdef RECOGNITION
	#define EIGENFACES
	#ifndef EIGENFACES
		#define FISHERFACES
	#endif
#endif


#endif /* SRC_DEFINES_H_ */
