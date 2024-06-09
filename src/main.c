#include <stdio.h>
#include "get_char.h"
#include "boolean.h"
#include "word.h"
#include "word_stack.h"
#include "word_book.h"
#include "file_reader.h"
#include "question.h"

int main(){
	// 単語一覧の作成
	WordStack* stack = FileReader_read("data/words");

	// 単語帳の作成
	WordBook* book = New_WordBook(stack);

	// 不要になった単語一覧の削除
	stack = Delete_WordStack(stack);

	Boolean con = True;
	while(con){
		// 単語帳の残り単語数が0なら終了する
		if(WordBook_getSize(book)==0){
			printf("You have already played all words! Thanks.\n");
			break;
		}

		// 単語帳からランダムに単語を取り出す
		Word* word = WordBook_pop(book);

		// クイズを作成する
		Question* que = New_Question(word);

		// 不要になった単語の削除
		word = Delete_Word(word);

		// クイズが続いている間、続ける
		while(Question_isOver(que)==False){
			Question_play(que);
		}

		// クイズを削除する
		que = Delete_Question(que);

		// 続けるかの確認を行う
		printf("Continue?(y/n): ");
		char c = tolower(GetCharactor_get());
		printf("\n");
		if(c=='y'){
			con = True;
		}else{
			con = False;
		}
	}

	// 不要になった単語帳を削除する
	book = Delete_WordBook(book);

	return 0;
}
