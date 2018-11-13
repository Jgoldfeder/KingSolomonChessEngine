//============================================================================
// Name        : chess.cpp
// Author      : Yehuda Goldfeder
// Version     : 1.0
// Description : Chess
//============================================================================
#include <iostream>
#include <bitset>
#include <algorithm>
#include <assert.h>
#include "moveGenerator.h"
#include "staticEvaluator.h"

using namespace std;

typedef unsigned long long bitBoard;
const int infinity = 500000;//lol
//have bitboards in an array to be accessed by my board enum
bitBoard bitBoardList[13];
bitBoard& WP = bitBoardList[wp];
bitBoard& WC = bitBoardList[wc];
bitBoard& WH = bitBoardList[wh];
bitBoard& WB = bitBoardList[wb];
bitBoard& WK = bitBoardList[wk];
bitBoard& WQ = bitBoardList[wq];
bitBoard& BP = bitBoardList[bp];
bitBoard& BC = bitBoardList[bc];
bitBoard& BH = bitBoardList[bh];
bitBoard& BB = bitBoardList[bb];
bitBoard& BK = bitBoardList[bk];
bitBoard& BQ = bitBoardList[bq];
bitBoard occ;
bitBoard empty;
bitBoard notWhite;
bitBoard notBlack;

const bitBoard rankH = 9259542123273814144LL;
const bitBoard rankA = 72340172838076673;
const bitBoard rankB = rankA << 9 | 2;
const bitBoard rankC = rankB << 9 | 4;
const bitBoard rankD = rankC << 9 | 8;
const bitBoard rankE = rankD << 9 | 16;
const bitBoard rankF = rankE << 9 | 32;
const bitBoard rankG = rankH << 7 | 64;
const bitBoard file1 = 255ll;
const bitBoard file2 = 65280ll;
const bitBoard file3 = 16711680LL;
const bitBoard file4 = 4278190080LL;
const bitBoard file5 = 1095216660480LL;
const bitBoard file6 = 280375465082880LL;
const bitBoard file7 = 71776119061217280LL;
const bitBoard file8 = 18374686479671623680LL;
const bitBoard outerSquares = 0xff818181818181ffLL;
bitBoard BLACK;
bitBoard WHITE;
bitBoard moveBoards[12];
moveBoard attackBoard[64];//a square central array representation used to find captures in move generation

void drawBoard(bitBoard b){

	string s = bitset<8>((b&file8) >> 56).to_string();
	reverse(s.begin(), s.end());
	cout << s << endl;
	s = bitset<8>((b&file7) >> 48).to_string();
	reverse(s.begin(), s.end());
	cout << s << endl;
	s = bitset<8>((b&file6) >> 40).to_string();
	reverse(s.begin(), s.end());
	cout << s << endl;
	s = bitset<8>((b&file5) >> 32).to_string();
	reverse(s.begin(), s.end());
	cout << s << endl;
	s = bitset<8>((b&file4) >> 24).to_string();
	reverse(s.begin(), s.end());
	cout << s << endl;
	s = bitset<8>((b&file3) >> 16).to_string();
	reverse(s.begin(), s.end());
	cout << s << endl;
	s = bitset<8>((b&file2) >> 8).to_string();
	reverse(s.begin(), s.end());
	cout << s << endl;
	s = bitset<8>(b&file1).to_string();
	reverse(s.begin(), s.end());
	cout << s << endl;
}




void initBitBoards(){
	
	char board[][8] = {
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },//8      top right is most significant
	{ ' ', ' ', 'P', ' ', ' ', ' ', ' ', ' ' },//7
	{ ' ', ' ', ' ', 'P', ' ', ' ', ' ', ' ' },//6
	{ 'k', 'p', ' ', ' ', ' ', ' ', ' ', 'C' },//5
	{ ' ', 'c', ' ', ' ', ' ', 'P', ' ', 'K' },//4
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },//3
	{ ' ', ' ', ' ', ' ', 'p', ' ', 'p', ' ' },//2
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' } };//1     bottom left is least significant
	//iterate board to initialize bitBoards
	for (int x = 0; x<8; x++){
	for (int y = 0; y<8; y++){
	switch (board[y][x])
	{
	case 'k':
	WK |= 1LL << ((7 - y) * 8 + x);
	break;
	case 'K':
	BK |= 1LL << ((7 - y) * 8 + x);
	break;
	case 'q':
	WQ |= 1LL << ((7 - y) * 8 + x);
	break;
	case 'Q':
	BQ |= 1LL << ((7 - y) * 8 + x);
	break;
	case 'b':
	WB |= 1LL << ((7 - y) * 8 + x);
	break;
	case 'B':
	BB |= 1LL << ((7 - y) * 8 + x);
	break;
	case 'h':
	WH |= 1LL << ((7 - y) * 8 + x);
	break;
	case 'H':
	BH |= 1LL << ((7 - y) * 8 + x);
	break;
	case 'c':
	WC |= 1LL << ((7 - y) * 8 + x);
	break;
	case 'C':
	BC |= 1LL << ((7 - y) * 8 + x);
	break;
	case 'p':
	WP |= 1LL << ((7 - y) * 8 + x);
	break;
	case 'P':
	BP |= 1LL << ((7 - y) * 8 + x);
	break;
	}
	}
	}
}

//sync attackboard to bitboards
void syncAttackBoard(){
	for (int x = 1; x < 13; x++){
	for (int y = 0; y < 64; y++){
	if (bitBoardList[x] & (1LL << y)){
	attackBoard[y] = (moveBoard)(x);
	}
	}
	}
}
int k=0;
void makeMove(Move m){
	bitBoardList[m.board] ^= (1LL << m.current);
	bitBoardList[m.board] ^= (1LL << m.target);
	if (m.capture){
	bitBoardList[m.capture] ^= (1ll << m.target);//kill capture
	}
	attackBoard[m.target] = m.board;
	attackBoard[m.current] = (moveBoard)0;
}
void unMakeMove(Move m){
	bitBoardList[m.board] ^= (1LL << m.current);
	bitBoardList[m.board] ^= (1LL << m.target);
	
	if (m.capture){
	k++;	
	bitBoardList[m.capture] ^= (1ll << m.target);//kill capture
	}
	attackBoard[m.target] = m.capture;
	attackBoard[m.current] = m.board;
}
int y = 0;
//search function
moveGenerator gen = moveGenerator();
evaluator eval = evaluator();
Move list[10][200];
int negamax(int depth, int  alpha, int beta, int player){
	if (depth == 0){//or terminal node
	int x = player*eval.getVal(WP, WC, WH, WB, WQ, WK, BP, BC, BH, BB, BQ, BK);
	//std::cout << x  << endl;
	y++;
	return x;
	}
	int bestValue = -infinity;
	int childNodes = gen.getMoves(player, list[depth],attackBoard, BP, BH, BB, BC, BQ, BK, WP, WC, WH, WB, WQ, WK);//generate psuedo-legal moves returns amount of moves
	for (int childIndex = 0; childIndex < childNodes; childIndex++){//for each child of node
	//make move
	makeMove(list[depth][childIndex]);
	int value = -negamax(depth - 1, -beta, -alpha, -player);
	//unmake move
	unMakeMove(list[depth][childIndex]);
	bestValue = max(value, bestValue);//minimax in action
	//alpha-beta pruning
	alpha = max(alpha, value);
	if (alpha >= beta){//prune
	//return infinity;//parent sees it as -infinity and imediately prunes
	}
	
	}
	return bestValue;
}


int main() {
	cout << "Chess cmd" << endl; // begins user interface

	//int x = eval.getVal(WP, WC, WH, WB, WQ, WK, BP, BC, BH, BB, BQ, BK);
	initBitBoards();
	syncAttackBoard();
	cout << negamax(2, -infinity, infinity, 1) << endl;
	cout << "k - y" << endl;
	cout << k << endl;
	cout << y << endl;
	
	return 0;
}


