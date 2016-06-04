/*
 * Utilities.h
 *
 *  Created on: 04/06/2016
 *      Author: maximofn
 */

#ifndef SRC_UTILITIES_H_
#define SRC_UTILITIES_H_

#include "Librerias_Reconocimiento.h"
#include "Defines.h"


/////////////////////////////////////////////////
// trace if TRACE==1
/////////////////////////////////////////////////
inline void trace(string s)
{
	printf (" TRACE: %s", s);
}
inline void trace(char* c)
{
	printf (" %s", c);
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