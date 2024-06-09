#ifndef HANGMAN_QUESTION_HEADER
#define HANGMAN_QUESTION_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "word.h"
#include "boolean.h"
#include "get_char.h"

// クイズを管理する構造体
typedef struct{
	Word* word; // 正解となる単語
	int remainingTriesCount; // 残り試行回数
	int correctCount; // 正解した文字の個数
	Boolean isUsedCharactor[26]; // i番目の文字が既に入力されたか？
} Question;

// Questionを作成する
Question* New_Question(const Word* word){
	static const int MAX_TRIESCOUNT = 10;

	assert(word!=NULL);

	Question* self = (Question*)malloc(sizeof(Question));
	assert(self!=NULL);

	(self->word) = Copy_Word(word);
	(self->remainingTriesCount) = MAX_TRIESCOUNT;
	(self->correctCount) = 0;
	for(int i=0; i<26; i++){
		(self->isUsedCharactor)[i] = False;
	}

	return self;
}

// Questionを削除する
Question* Delete_Question(Question* self){
	assert(self!=NULL);

	Delete_Word(self->word);
	free(self);

	return NULL;
}

// 正解したかを取得する
Boolean Question_isCorrect(const Question* self){
	assert(self!=NULL);

	for(char c='a'; c<='z'; c++){
		if(Word_isContainsCharactor(self->word, c)){
			if((self->isUsedCharactor)[c-'a']==False){
				return False;
			}
		}
	}

	return True;
}

// ゲームが終了したかを取得する
Boolean Question_isOver(const Question* self){
	assert(self!=NULL);

	return (Question_isCorrect(self) || ((self->remainingTriesCount)==0));
}

// ステータスを表示する
void Question_displayState(const Question* self){
	assert(self!=NULL);

	const int length = Word_getLength(self->word);

	printf("Word: ");
	for(int i=0; i<length; i++){
		const char c = Word_getCharactor(self->word, i);

		if((self->isUsedCharactor)[c-'a']){
			printf("%c", c);
		}else{
			printf("-");
		}
	}
	printf("\n");

	printf("Used charactors: ");
	for(int i=0; i<26; i++){
		if((self->isUsedCharactor[i])==False) continue;

		printf("%c", i+'a');
	}
	printf("\n");

	printf("Remaining tries count: %d\n", self->remainingTriesCount);

	return;
}

// 文字を読んで、成功かどうか返す
Boolean Question_inputCharactor(Question* self){
	assert(self!=NULL);

	printf("Please input alphabet: ");
	char c = tolower(GetCharactor_get());
	printf("\n");

	if(islower(c)==0){
		printf("'%c' is not alphabet.\n", c);

		return False;
	}

	if((self->isUsedCharactor)[c-'a']){
		printf("'%c' is already used.\n", c);

		return False;
	}

	if(Word_isContainsCharactor(self->word, c)){
		(self->correctCount)++;
	}else{
		(self->remainingTriesCount)--;
	}
	(self->isUsedCharactor)[c-'a'] = True;

	return True;
}

// 表示の最後の部分を出力する
void Question_displayTerminal(const Question* self){
	if(Question_isOver(self)){
		if(Question_isCorrect(self)){
			printf("Accepted!\n");
		}else{
			printf("Wrong answer.\n");
		}

		printf("Correct answer is \"");
		const int length = Word_getLength(self->word);
		for(int i=0; i<length; i++){
			printf("%c", Word_getCharactor(self->word, i));
		}
		printf("\".\n");
	}

	printf("\n");
	return;
}

// 1ステップ進める
void Question_play(Question* self){
	assert(self!=NULL);
	assert(Question_isOver(self)==False);

	Question_displayState(self);

	while(Question_inputCharactor(self)==False);

	Question_displayTerminal(self);

	return;
}

#endif
