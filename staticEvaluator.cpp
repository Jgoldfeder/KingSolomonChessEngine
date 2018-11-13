#include "moveGenerator.h"
int P = 100;
int N = 320;
int B = 330;
int R = 500;
int Q = 900;
int K = 20000;
typedef unsigned long long bitBoard;
const int Mirror64[64] = {
	56, 57, 58, 59, 60, 61, 62, 63,
	48, 49, 50, 51, 52, 53, 54, 55,
	40, 41, 42, 43, 44, 45, 46, 47,
	32, 33, 34, 35, 36, 37, 38, 39,
	24, 25, 26, 27, 28, 29, 30, 31,
	16, 17, 18, 19, 20, 21, 22, 23,
	8, 9, 10, 11, 12, 13, 14, 15,
	0, 1, 2, 3, 4, 5, 6, 7
};


int pawnTable[64] =
{ 0, 0, 0, 0, 0, 0, 0, 0,
50, 50, 50, 50, 50, 50, 50, 50,
10, 10, 20, 30, 30, 20, 10, 10,
5, 5, 10, 25, 25, 10, 5, 5,
0, 0, 0, 20, 20, 0, 0, 0,
5, -5, -10, 0, 0, -10, -5, 5,
5, 10, 10, -20, -20, 10, 10, 5,
0, 0, 0, 0, 0, 0, 0, 0 };

int knightTable[64] = {
	-50, -40, -30, -30, -30, -30, -40, -50,
	-40, -20, 0, 0, 0, 0, -20, -40,
	-30, 0, 10, 15, 15, 10, 0, -30,
	-30, 5, 15, 20, 20, 15, 5, -30,
	-30, 0, 15, 20, 20, 15, 0, -30,
	-30, 5, 10, 15, 15, 10, 5, -30,
	-40, -20, 0, 5, 5, 0, -20, -40,
	-50, -40, -30, -30, -30, -30, -40, -50,
};

int bishopTable[64] = {
	-20, -10, -10, -10, -10, -10, -10, -20,
	-10, 0, 0, 0, 0, 0, 0, -10,
	-10, 0, 5, 10, 10, 5, 0, -10,
	-10, 5, 5, 10, 10, 5, 5, -10,
	-10, 0, 10, 10, 10, 10, 0, -10,
	-10, 10, 10, 10, 10, 10, 10, -10,
	-10, 5, 0, 0, 0, 0, 5, -10,
	-20, -10, -10, -10, -10, -10, -10, -20,
};

int rookTable[64] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	5, 10, 10, 10, 10, 10, 10, 5,
	-5, 0, 0, 0, 0, 0, 0, -5,
	-5, 0, 0, 0, 0, 0, 0, -5,
	-5, 0, 0, 0, 0, 0, 0, -5,
	-5, 0, 0, 0, 0, 0, 0, -5,
	-5, 0, 0, 0, 0, 0, 0, -5,
	0, 0, 0, 5, 5, 0, 0, 0
};

int queenTable[64] = {
	//queen
	-20, -10, -10, -5, -5, -10, -10, -20,
	-10, 0, 0, 0, 0, 0, 0, -10,
	-10, 0, 5, 5, 5, 5, 0, -10,
	-5, 0, 5, 5, 5, 5, 0, -5,
	0, 0, 5, 5, 5, 5, 0, -5,
	-10, 5, 5, 5, 5, 5, 0, -10,
	-10, 0, 5, 0, 0, 0, 0, -10,
	-20, -10, -10, -5, -5, -10, -10, -20
};

int kingMidTable[64] = {
	-30, -40, -40, -50, -50, -40, -40, -30,
	-30, -40, -40, -50, -50, -40, -40, -30,
	-30, -40, -40, -50, -50, -40, -40, -30,
	-30, -40, -40, -50, -50, -40, -40, -30,
	-20, -30, -30, -40, -40, -30, -30, -20,
	-10, -20, -20, -20, -20, -20, -20, -10,
	20, 20, 0, 0, 0, 0, 20, 20,
	20, 30, 10, 0, 0, 10, 30, 20
};
int kingEndTable[64] = {
	-50, -40, -30, -20, -20, -30, -40, -50,
	-30, -20, -10, 0, 0, -10, -20, -30,
	-30, -10, 20, 30, 30, 20, -10, -30,
	-30, -10, 30, 40, 40, 30, -10, -30,
	-30, -10, 30, 40, 40, 30, -10, -30,
	-30, -10, 20, 30, 30, 20, -10, -30,
	-30, -30, 0, 0, 0, 0, -30, -30,
	-50, -30, -30, -30, -30, -30, -30, -50
};

class evaluator{
public:
	int getVal(bitBoard WP, bitBoard WC, bitBoard WH, bitBoard WB, bitBoard WQ, bitBoard WK, bitBoard BP, bitBoard BC, bitBoard BH, bitBoard BB, bitBoard BQ, bitBoard BK);
	
};
	int evaluator :: getVal(bitBoard WP, bitBoard WC, bitBoard WH, bitBoard WB, bitBoard WQ, bitBoard WK, bitBoard BP, bitBoard BC, bitBoard BH, bitBoard BB, bitBoard BQ, bitBoard BK){
	int value = 0;
	//material evaluation,assuming + is good for white and - for black
	int location = 0;
	while (WP){
	location = bitScanForward(WP);
	WP ^= 1LL << location;
	value += (P + pawnTable[location]);
	}
	while (WC){
	location = bitScanForward(WC);
	WC ^= 1LL << location;
	value += (R + rookTable[location]);
	}
	while (WH){
	location = bitScanForward(WH);
	WH ^= 1LL << location;
	value += (N + knightTable[location]);
	}
	while (WB){
	location = bitScanForward(WB);
	WB ^= 1LL << location;
	value += (B + bishopTable[location]);
	}
	while (WQ){
	location = bitScanForward(WQ);
	WQ ^= 1LL << location;
	value += (Q + queenTable[location]);
	}
	//black
	while (BP){
	location = bitScanForward(BP);
	BP ^= 1LL << location;
	value -= (P + pawnTable[Mirror64[location]]);
	}
	while (BC){
	location = bitScanForward(BC);
	BC ^= 1LL << location;
	value -= (R + rookTable[Mirror64[location]]);
	}
	while (BH){
	location = bitScanForward(BH);
	BH ^= 1LL << location;
	value -= (N + knightTable[Mirror64[location]]);
	}
	while (BB){
	location = bitScanForward(BB);
	BB ^= 1LL << location;
	value -= (B + bishopTable[Mirror64[location]]);
	}
	while (BQ){
	location = bitScanForward(BQ);
	BQ ^= 1LL << location;
	value -= (Q + queenTable[Mirror64[location]]);
	}
	if (WK){
	value += K;
	}
	if (BK){
	value -= K;
	}
	return value;

};



