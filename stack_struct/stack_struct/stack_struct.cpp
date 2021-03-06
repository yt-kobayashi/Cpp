/*==================================================================================================
|
|   概要                :       シンプルな整数型のスタックを実装するためのルーチン
|   作成者              :       小林由尭
|	作成日時			:		2018/09/10
|   目的                :       スタックを学ぶ
|	プロシジャ			:		stack_init	--	スタックを初期化する
|								stack_push	--	スタックに要素をプッシュする
|								stack_pop	--	スタックから要素をポップする
|	GitHub				:		yt-kobayashi/Cpp
|
==================================================================================================*/
//>>>>>>>>>>>>>>>>>>>> ヘッダファイル <<<<<<<<<<<<<<<<<<<<<//
#include "stdafx.h"				// プリコンパイル済みヘッダ[ビルド時間の短縮 一番最初にインクルードする必要がある]
#include <assert.h>				// プログラムに診断機能を追加する
#include <cstdlib>				// std名前空間に属する<stdio.h>と同等の機能を提供する
#include <iostream>				// 標準入出力オブジェクトを提供する
//>>>>>>>>>>>>>>>>>>>> 名前空間の使用 <<<<<<<<<<<<<<<<<<<<<//
using namespace std;			// std名前空間の使用

/*--------------------------------------------------------------------------------------------------
|   概要		        :       スタック本体の定義と関数の宣言
|   目的                :       スタックに関する構造体と機能を提供する
--------------------------------------------------------------------------------------------------*/
//>>>>>>>>>>>>>>>>>>>> 定数の宣言 <<<<<<<<<<<<<<<<<<<<<//
const int STACK_SIZE = 100;		// スタックの最大サイズ
//>>>>>>>>>>>>>>>>>>>> スタック本体 <<<<<<<<<<<<<<<<<<<<<//
struct stack {
	int count;					// スタック内の要素の数
	int data[STACK_SIZE];		// 要素
};
/*
*	stack_init	--	スタックを初期化する
*
*	引数
*		the_stack	--	初期化するスタック
*/
inline void stack_init(struct stack& the_stack) {
	the_stack.count = 0;		// スタックの要素数を0とする
}
/*
*	stack_push	--	スタックに要素をプッシュする
*
*	**警告 : オーバーフローはチェックしない**
*
*	引数
*		the_stack	--	要素を格納するためのスタック
*		item		--	スタックに入れる要素
*/
inline void stack_push(struct stack& the_stack, const int item) {
	int numberStack = static_cast<int>(sizeof(the_stack.data) / sizeof(the_stack.data[0]));		// スタックの配列の数を取得
	assert((0 <= the_stack.count) && (the_stack.count < numberStack));							// the_stack.countの値が範囲内でなければならない

	the_stack.data[the_stack.count] = item;
	++the_stack.count;
}
/*
*	stack_pop	--	スタックから要素をポップする
*
*	**警告 : スタックのアンダーフローはチェックしない**
*
*	引数
*		the_stack	--	要素を格納するためのスタック
*
*	戻り値
*		スタックの先頭の要素
*/
inline int stack_pop(struct stack& the_stack) {
	// スタックの要素数をデクリメントする
	--the_stack.count;

	int numberStack = static_cast<int>(sizeof(the_stack.data) / sizeof(the_stack.data[0]));		// スタックの配列の数を取得
	assert((0 <= the_stack.count) && (the_stack.count < numberStack));							// the_stack.countの値が範囲内でなければならない

	return (the_stack.data[the_stack.count]);
}

/*--------------------------------------------------------------------------------------------------
|   概要		        :       スタックをテストするための簡単なルーチン
|   目的                :       スタックのテスト
--------------------------------------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
	struct stack a_stack;		// 使用するスタック

	stack_init(a_stack);		// スタックの初期化

	// 3つの要素をスタックにプッシュする
	stack_push(a_stack, 1);
	stack_push(a_stack, 2);
	stack_push(a_stack, 3);

	// スタックから要素をポップする
	cout << "Expect a 3 -> " << stack_pop(a_stack) << endl;
	cout << "Expect a 2 -> " << stack_pop(a_stack) << endl;
	cout << "Expect a 1 -> " << stack_pop(a_stack) << endl;

	return (0);
}