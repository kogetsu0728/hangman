#ifndef HANGMAN_WORDBOOK_HEADER
#define HANGMAN_WORDBOOK_HEADER

#include <stdlib.h>
#include <assert.h>
#include "word.h"
#include "word_stack.h"
#include "random.h"

// 単語帳を管理する構造体
typedef struct{
	WordStack* stack; // 単語を格納する
} WordBook;

// WordBookを作成する
WordBook* New_WordBook(const WordStack* stack){
	assert(stack!=NULL);

	WordBook* self = (WordBook*)malloc(sizeof(WordBook));
	assert(self!=NULL);

	(self->stack) = Copy_WordStack(stack);

	return self;
}

// WordBookを削除する
WordBook* Delete_WordBook(WordBook* self){
	assert(self!=NULL);

	Delete_WordStack(self->stack);
	free(self);

	return NULL;
}

// 単語の数を取得する
int WordBook_getSize(const WordBook* self){
	assert(self!=NULL);

	return WordStack_getSize(self->stack);
}

// 単語を追加する
void WordBook_push(WordBook* self, const Word* word){
	assert(self!=NULL);
	assert(word!=NULL);

	WordStack_push(self->stack, word);

	return;
}

// ランダムな単語を取得し、削除する
Word* WordBook_pop(WordBook* self){
	assert(self!=NULL);
	assert(0<WordStack_getSize(self->stack));

	const int size = WordStack_getSize(self->stack);
	const int index = Random_getRandom(0, size);

	WordStack_swap(self->stack, index, size-1);

	return WordStack_pop(self->stack);
}

#endif
