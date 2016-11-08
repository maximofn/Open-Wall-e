/*
 ============================================================================
 Name        : Prueba_Libsprec_C.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

//#include <stdio.h>
//#include <stdlib.h>
//
//int main(void) {
//	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
//	return EXIT_SUCCESS;
//}

#include <sprec/sprec.h>

#define SYNCHRONOUS
#ifdef SYNCHRONOUS

int main(int argc, char *argv[])
{
	char *res = sprec_recognize_sync(argv[1], argv[2], strtod(argv[3], NULL));
	printf("%s\n", res);
	free(res);
	return 0;
}

#else

static void callback(const char *res, void *data)
{
	printf("Thread: %lld\n", (long long)pthread_self());
	printf("%s\n", res);
}

int main(int argc, char *argv[])
{
	pthread_t pid;
	void *retval;

	pid = sprec_recognize_async(argv[1], argv[2], strtod(argv[3], NULL), callback, NULL);
	printf("Thread: %lld\n", (long long)pthread_self());
	pthread_join(pid, &retval);
	return 0;
}

#endif
