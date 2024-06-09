#ifndef HANGMAN_FILEREADER_HEADER
#define HANGMAN_FILEREADER_HEADER

#include <stdlib.h>
#include <assert.h>
#include "word.h"
#include "word_stack.h"

// ファイルを読み、含まれる単語を保持したWordStackを返す
WordStack* FileReader_read(const char* const filename){
	static const int BUF_LENGTH = 100;

	assert(filename!=NULL);

	WordStack* stack = New_WordStack();

	FILE* fp = fopen(filename, "r");
	assert(fp!=NULL);
	char* buf = (char*)malloc(sizeof(char)*BUF_LENGTH);
	assert(buf!=NULL);

	while(fscanf(fp, "%s", &buf[0])!=EOF){
		Word* word = New_Word(&buf[0]);
		if(word==NULL) continue;

		WordStack_push(stack, word);

		Delete_Word(word);
	}
	free(buf);
	fclose(fp);

	const int size = WordStack_getSize(stack);
	for(int i=0; i<(size/2); i++){
		WordStack_swap(stack, i, size-1-i);
	}

	return stack;
}

#endif
