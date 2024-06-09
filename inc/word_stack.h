#ifndef HANGMAN_WORDSTACK_HEADER
#define HANGMAN_WORDSTACK_HEADER

#include <stdlib.h>
#include <assert.h>
#include "word.h"

// 単語をスタックで管理する構造体
typedef struct{
	int usedSize; // すでに使われた領域のサイズ
	int reservedSize; // 確保されている領域のサイズ
	Word** begin; // 先頭のポインタ
} WordStack;

// WordStackを作成する
WordStack* New_WordStack(){
	WordStack* self = (WordStack*)malloc(sizeof(WordStack));
	assert(self!=NULL);

	(self->usedSize) = 0;
	(self->reservedSize) = 1;
	(self->begin) = (Word**)malloc(sizeof(Word*));
	assert((self->begin)!=NULL);

	return self;
}

// WordStackをコピーする
WordStack* Copy_WordStack(const WordStack* self){
	assert(self!=NULL);

	WordStack* copy = (WordStack*)malloc(sizeof(WordStack));
	(copy->usedSize) = (self->usedSize);
	(copy->reservedSize) = (self->reservedSize);
	(copy->begin) = (Word**)malloc(sizeof(Word*)*(self->reservedSize));
	assert((copy->begin)!=NULL);
	for(int i=0; i<(self->usedSize); i++){
		(copy->begin)[i] = Copy_Word((self->begin)[i]);
	}

	return copy;
}

// WordStackを削除する
WordStack* Delete_WordStack(WordStack* self){
	assert(self!=NULL);

	for(int i=0; i<(self->usedSize); i++){
		Delete_Word((self->begin)[i]);
	}
	free(self->begin);
	free(self);

	return NULL;
}

// 格納されている単語の個数を取得する
int WordStack_getSize(const WordStack* self){
	assert(self!=NULL);

	return (self->usedSize);
}

// 単語を追加する
void WordStack_push(WordStack* self, const Word* word){
	assert(self!=NULL);
	assert(word!=NULL);

	if((self->reservedSize)==(self->usedSize)){
		(self->reservedSize) *= 2;
		(self->begin) = (Word**)realloc(self->begin, sizeof(Word*)*(self->reservedSize));
		assert((self->begin)!=NULL);
	}

	(self->usedSize)++;
	(self->begin)[(self->usedSize)-1] = Copy_Word(word);
	assert((self->begin)[self->usedSize-1]!=NULL);

	return;
}

// 先頭にある単語を取得し、削除する
Word* WordStack_pop(WordStack* self){
	assert(self!=NULL);
	assert(0<(self->usedSize));

	Word* res = (self->begin)[(self->usedSize)-1];
	(self->usedSize)--;

	return res;
}

// a番目の単語とb番目の単語を入れ返る
void WordStack_swap(WordStack* self, const int a, const int b){
	assert(self!=NULL);
	assert(0<=a);
	assert(a<(self->usedSize));
	assert(0<=b);
	assert(b<(self->usedSize));

	Word* temp = (self->begin)[a];
	(self->begin[a]) = (self->begin)[b];
	(self->begin[b]) = temp;

	return;
}

#endif
