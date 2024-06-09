#ifndef HANGMAN_RANDOM_HEADER
#define HANGMAN_RANDOM_HEADER

#include <stdlib.h>
#include <time.h>
#include "boolean.h"

// begin以上end未満の乱数を返す
int Random_getRandom(int begin, int end){
	static Boolean init = False;

	assert(begin<end);

	if(!init){
		srand((unsigned)time(NULL));
		init = True;
	}

	return rand()%(end-begin)+begin;
}

#endif
