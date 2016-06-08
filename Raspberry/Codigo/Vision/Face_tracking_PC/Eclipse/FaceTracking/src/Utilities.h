/*
 * Utilities.h
 *
 *  Created on: 04/06/2016
 *      Author: maximofn
 */

#ifndef SRC_UTILITIES_H_
#define SRC_UTILITIES_H_


#include <iostream>
#include <fstream>
#include <sstream>
#include "time.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
using namespace std;


/////////////////////////////////////////////////
// trace if TRACE==1
/////////////////////////////////////////////////
inline void trace(string s)
{
	//printf (" TRACE: %s", s);
	cout << s ;
}
inline void trace(char* c[])
{
	//printf (" %s", c);
	cout << c ;
}
//inline void P_LOG(char* str, int level)
//{
//	if (level <= NIVEL_VERBOSE)
//		HAL_DUART__P_Printf (&pDUARTChannel[0],str);
//
//	return;
//}



/////////////////////////////////////////////////
// debug if DEBUG==1
/////////////////////////////////////////////////
inline void debug(string s)
{
	cout << "DEBUG: " << s;
}
inline void debug(char* c)
{
	printf (" %s", c);
}


#endif /* SRC_UTILITIES_H_ */
