/*
 * Defines.h
 *
 *  Created on: 31/05/2016
 *      Author: maximofn
 */

#ifndef SRC_DEFINES_H_
#define SRC_DEFINES_H_

#define SHOW
#ifdef SHOW
	#define INFORMATION
#endif

// for debug and trace
#define TRACE
#define DEBUG

// for device mode
//#define RASPBERRY
#define UBUNTU
//#define MAQUINA_VIRTUAL

// for face recognition mode
#define EIGENFACES
//#define FISHERFACES


#endif /* SRC_DEFINES_H_ */
