#ifndef HANGMAN_WORD_HEADER
#define HANGMAN_WORD_HEADER

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "boolean.h"

// 単語を管理する構造体
typedef struct{
	const int length; // 単語の長さ
	const char* const begin; // 先頭ポインタ
	const Boolean isContainsCharactor[26]; // i番目の文字が含まれているか?
} Word;

// Wordを作成する
Word* New_Word(const char* const str){
	static const int WORD_LENGTH_MIN = 5;
	static const int WORD_LENGTH_MAX = 10;

	assert(str!=NULL);

	const int length = strlen(str);

	Boolean isValid = True;
	if(length<WORD_LENGTH_MIN) isValid = False;
	if(WORD_LENGTH_MAX<length) isValid = False;
	for(int i=0; i<length; i++){
		if(isalpha(str[i])==0){
			isValid = False;
		}
	}
	if(isValid==False){
		return NULL;
	}

	Word* self = (Word*)malloc(sizeof(Word));
	assert(self!=NULL);

	memcpy((int*)(&(self->length)), &length, sizeof(int));

	char* lower = (char*)malloc(sizeof(char)*(length+1));
	assert(lower!=NULL);
	Boolean contains[26];
	for(int i=0; i<26; i++){
		contains[i] = False;
	}
	for(int i=0; i<length; i++){
		lower[i] = tolower(str[i]);
		contains[lower[i]-'a'] = True;
	}
	lower[length] = '\0';
	memcpy((char**)(&(self->begin)), &lower, sizeof(char*));
	memcpy((char*)(self->isContainsCharactor), contains, sizeof(Boolean)*26);

	return self;
}

// Wordをコピーする
Word* Copy_Word(const Word* self){
	assert(self!=NULL);

	return New_Word(self->begin);
}

// Wordを削除する
Word* Delete_Word(Word* self){
	assert(self!=NULL);

	free((char*)(self->begin));
	free(self);

	return NULL;
}

// 単語の長さを取得する
int Word_getLength(const Word* self){
	assert(self!=NULL);

	return (self->length);
}

// index番目の文字を取得する
char Word_getCharactor(const Word* self, int index){
	assert(self!=NULL);
	assert(0<=index);
	assert(index<(self->length));

	return (self->begin)[index];
}

// cが含まれているか取得する
Boolean Word_isContainsCharactor(const Word* self, char c){
	assert(self!=NULL);
	assert(islower(c)!=0);

	return (self->isContainsCharactor)[c-'a'];
}

#endif
