/*
 * typedef.h
 *
 *  Created on: 06/04/2014
 *      Author: maximo
 */

#ifndef TYPEDEF_H_
#define TYPEDEF_H_

// for show and information
#define SHOW_MODE 1
#define SHOW if (SHOW_MODE)
#define INFORMATION_MODE 1
#define INFORMATION if (INFORMATION_MODE && SHOW_MODE)

// for device mode
#define RASPBERRY 	1
#define UBUNTU 		2
#define MAQUINA_VIRTUAL	3
#define DEVICE_MODE	RASPBERRY
#define RASPBERRY_MODE 		if (DEVICE_MODE	==	RASPBERRY)
#define UBUNTU_MODE 		if (DEVICE_MODE	==	UBUNTU)
#define MAQUINA_VIRTUAL_MODE	if (DEVICE_MODE	==	MAQUINA_VIRTUAL)

// for face recognition mode
#define EIGENFACES 		1
#define FISHERFACES 		2
#define FACE_RECOGNICER_MODE 	EIGENFACES
#define EIGENFACES_MODE 	if (FACE_RECOGNICER_MODE==1)
#define FISHERFACES_MODE	if (FACE_RECOGNICER_MODE==2)

// for debug and trace
#define TRACE 1
#define DEBUG_MODE 1
#define DEBUG if (DEBUG_MODE==1)

// for Cascade mode
#define LBP_CASCADE_FRONTALFACE				1
#define HAAR_CASCADE_FRONTALFACE_ALT		2
#define HAAR_CASCADE_FRONTALFACE_ALT2		3
#define HAAR_CASCADE_FRONTALFACE_ALT_TREE	4
#define HAAR_CASCADE_FRONTALFACE_ALT_DEFAULT	5
#define CASCADE_MODE 				LBP_CASCADE_FRONTALFACE

// some constants to manage number of people to learn + id of people
#define MAX_PEOPLE 		42
#define P_MAXIMO		0
#define P_SUJETO1		1
#define P_SUJETO2		2
#define P_SUJETO3		3
#define P_SUJETO4		4
#define P_SUJETO5		5
#define P_SUJETO6		6
#define P_SUJETO7		7
#define P_SUJETO8		8
#define P_SUJETO9		9
#define P_SUJETO10		10
#define P_SUJETO11		11
#define P_SUJETO12		12
#define P_SUJETO13		13
#define P_SUJETO14		14
#define P_SUJETO15		15
#define P_SUJETO16		16
#define P_SUJETO17		17
#define P_SUJETO18		18
#define P_SUJETO19		19
#define P_SUJETO20		20
#define P_SUJETO21		21
#define P_SUJETO22		22
#define P_SUJETO23		23
#define P_SUJETO24		24
#define P_SUJETO25		25
#define P_SUJETO26		26
#define P_SUJETO27		27
#define P_SUJETO28		28
#define P_SUJETO29		29
#define P_SUJETO30		30
#define P_SUJETO31		31
#define P_SUJETO32		32
#define P_SUJETO33		33
#define P_SUJETO34		34
#define P_SUJETO35		35
#define P_SUJETO36		36
#define P_SUJETO37		37
#define P_SUJETO38		38
#define P_SUJETO39		39
#define P_SUJETO40		40
#define P_MATIAS		41
#define P_DESCONOCIDO		42
//#define P_NEWPERSON	X


#endif /* TYPEDEF_H_ */
