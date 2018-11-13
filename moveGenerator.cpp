#include <assert.h>
#include <iostream>
typedef unsigned long long bitBoard;
const bitBoard magicBishop[64] = {
	0x2910054208004104L, 0x2100630a7020180L, 0x5822022042000000L, 0x2ca804a100200020L,
	0x204042200000900L, 0x2002121024000002L, 0x80404104202000e8L, 0x812a020205010840L,
	0x8005181184080048L, 0x1001c20208010101L, 0x1001080204002100L, 0x1810080489021800L,
	0x62040420010a00L, 0x5028043004300020L, 0xc0080a4402605002L, 0x8a00a0104220200L,
	0x940000410821212L, 0x1808024a280210L, 0x40c0422080a0598L, 0x4228020082004050L,
	0x200800400e00100L, 0x20b001230021040L, 0x90a0201900c00L, 0x4940120a0a0108L,
	0x20208050a42180L, 0x1004804b280200L, 0x2048020024040010L, 0x102c04004010200L,
	0x20408204c002010L, 0x2411100020080c1L, 0x102a008084042100L, 0x941030000a09846L,
	0x244100800400200L, 0x4000901010080696L, 0x280404180020L, 0x800042008240100L,
	0x220008400088020L, 0x4020182000904c9L, 0x23010400020600L, 0x41040020110302L,
	0x412101004020818L, 0x8022080a09404208L, 0x1401210240484800L, 0x22244208010080L,
	0x1105040104000210L, 0x2040088800c40081L, 0x8184810252000400L, 0x4004610041002200L,
	0x40201a444400810L, 0x4611010802020008L, 0x80000b0401040402L, 0x20004821880a00L,
	0x8200002022440100L, 0x9431801010068L, 0x1040c20806108040L, 0x804901403022a40L,
	0x2400202602104000L, 0x208520209440204L, 0x40c000022013020L, 0x2000104000420600L,
	0x400000260142410L, 0x800633408100500L, 0x2404080a1410L, 0x138200122002900L
};


const bitBoard magicRook[64] = {
	0xa180022080400230L, 0x40100040022000L, 0x80088020001002L, 0x80080280841000L,
	0x4200042010460008L, 0x4800a0003040080L, 0x400110082041008L, 0x8000a041000880L,
	0x10138001a080c010L, 0x804008200480L, 0x10011012000c0L, 0x22004128102200L,
	0x200081201200cL, 0x202a001048460004L, 0x81000100420004L, 0x4000800380004500L,
	0x208002904001L, 0x90004040026008L, 0x208808010002001L, 0x2002020020704940L,
	0x8048010008110005L, 0x6820808004002200L, 0xa80040008023011L, 0xb1460000811044L,
	0x4204400080008ea0L, 0xb002400180200184L, 0x2020200080100380L, 0x10080080100080L,
	0x2204080080800400L, 0xa40080360080L, 0x2040604002810b1L, 0x8c218600004104L,
	0x8180004000402000L, 0x488c402000401001L, 0x4018a00080801004L, 0x1230002105001008L,
	0x8904800800800400L, 0x42000c42003810L, 0x8408110400b012L, 0x18086182000401L,
	0x2240088020c28000L, 0x1001201040c004L, 0xa02008010420020L, 0x10003009010060L,
	0x4008008008014L, 0x80020004008080L, 0x282020001008080L, 0x50000181204a0004L,
	0x102042111804200L, 0x40002010004001c0L, 0x19220045508200L, 0x20030010060a900L,
	0x8018028040080L, 0x88240002008080L, 0x10301802830400L, 0x332a4081140200L,
	0x8080010a601241L, 0x1008010400021L, 0x4082001007241L, 0x211009001200509L,
	0x8015001002441801L, 0x801000804000603L, 0xc0900220024a401L, 0x1000200608243L
};

const int magicNumberShiftsRook[64] = {
	52, 53, 53, 53, 53, 53, 53, 52, 53, 54, 54, 54, 54, 54, 54, 53,
	53, 54, 54, 54, 54, 54, 54, 53, 53, 54, 54, 54, 54, 54, 54, 53,
	53, 54, 54, 54, 54, 54, 54, 53, 53, 54, 54, 54, 54, 54, 54, 53,
	53, 54, 54, 54, 54, 54, 54, 53, 52, 53, 53, 53, 53, 53, 53, 52
};
const int magicNumberShiftsBishop[64] = {
	58, 59, 59, 59, 59, 59, 59, 58, 59, 59, 59, 59, 59, 59, 59, 59,
	59, 59, 57, 57, 57, 57, 59, 59, 59, 59, 57, 55, 55, 57, 59, 59,
	59, 59, 57, 55, 55, 57, 59, 59, 59, 59, 57, 57, 57, 57, 59, 59,
	59, 59, 59, 59, 59, 59, 59, 59, 58, 59, 59, 59, 59, 59, 59, 58
};
const int index64[64] = {
	0, 47, 1, 56, 48, 27, 2, 60,
	57, 49, 41, 37, 28, 16, 3, 61,
	54, 58, 35, 52, 50, 42, 21, 44,
	38, 32, 29, 23, 17, 11, 4, 62,
	46, 55, 26, 59, 40, 36, 15, 53,
	34, 51, 20, 43, 31, 22, 10, 45,
	25, 39, 14, 33, 19, 30, 9, 24,
	13, 18, 8, 12, 7, 6, 5, 63
};
enum moveBoard { noCapture ,wk, bk, bq, wq, bb, wb, bh, wh, bc, wc, wp, bp };
struct Move{
	int target;
	int current;
	moveBoard board;
	moveBoard capture;
};
int bitScanForward(bitBoard bb) {
	const bitBoard debruijn64 = 0x03f79d71b4cb0a89LL;
	//assert(bb != 0);
	return index64[((bb ^ (bb - 1)) * debruijn64) >> 58];
}

class moveGenerator{
public:


private:

	bitBoard occ;
	bitBoard empty;
	bitBoard notWhite;
	bitBoard notBlack;
	bitBoard BLACK;
	bitBoard WHITE;
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
	int moveIndex;
	bitBoard kingMoves[64];
	bitBoard knightMoves[64];
	bitBoard rookMask[64];
	bitBoard bishopMask[64];
	bitBoard rookMoves[64][4096];
	bitBoard bishopMoves[64][128];
	void initRookMask(){
	for (int x = 0; x < 64; x++){
	bitBoard bb = 0;
	switch (x / 8)
	{
	case 0:
	bb ^= file1;
	break;
	case 1:
	bb ^= file2;
	break;
	case 2:
	bb ^= file3;
	break;
	case 3:
	bb ^= file4;
	break;
	case 4:
	bb ^= file5;
	break;
	case 5:
	bb ^= file6;
	break;
	case 6:
	bb ^= file7;
	break;
	case 7:
	bb ^= file8;
	break;
	}
	switch (x % 8)
	{
	case 0:
	bb ^= rankA;
	break;
	case 1:
	bb ^= rankB;
	break;
	case 2:
	bb ^= rankC;
	break;
	case 3:
	bb ^= rankD;
	break;
	case 4:
	bb ^= rankE;
	break;
	case 5:
	bb ^= rankF;
	break;
	case 6:
	bb ^= rankG;
	break;
	case 7:
	bb ^= rankH;
	break;
	}
	if (x % 8 != 0){
	bb &= ~rankA;
	}
	if (x % 8 != 7){
	bb &= ~rankH;
	}
	if (x / 8 != 0){
	bb &= ~file1;
	}
	if (x / 8 != 7){
	bb &= ~file8;
	}
	bb &= ~(0 | (1 << 7) | (1LL << 56) | (1LL << 63));//corners
	rookMask[x] = bb;
	}
	}
	void initBishopMask(){
	bitBoard b1;
	bitBoard b2;
	int temp;

	for (int x = 0; x < 64; x++){
	b1 = (1LL << x);
	b2 = b1;
	temp = x;
	while ((temp % 8 != 0) && (temp / 8 != 0)){// left bottom
	b1 |= b1 >> 9;
	temp -= 9;
	}
	temp = x;
	while ((temp % 8 != 7) && (temp / 8 != 7)){//top right
	b1 |= b1 << 9;
	temp += 9;
	}

	temp = x;
	while ((temp % 8 != 0) && (temp / 8 != 7)){//top left;
	b2 |= b2 << 7;
	temp += 7;
	}
	temp = x;
	while ((temp % 8 != 7) && (temp / 8 != 0)){//bottom right
	b2 |= b2 >> 7;
	temp -= 7;
	}
	b1 |= b2;
	bishopMask[x] = b1 & ~(1ll << x)&~outerSquares;
	}
	}
	void initKnightDatabase(){
	bitBoard bb;
	for (int x = 0; x<64; x++){
	bb = 0;
	bb |= (1LL << (x + 6));
	bb |= (1LL << (x + 10));
	bb |= (1LL << (x - 6));
	bb |= (1LL << (x - 10));
	bb |= (1LL << (x + 15));
	bb |= (1LL << (x + 17));
	bb |= (1LL << (x - 15));
	bb |= (1LL << (x - 17));
	if (x % 8<4){//knight is on left side
	//erase right  side
	bb &= ~(rankH | rankG);
	}
	if (x % 8>3){//knight is on right side
	//erase left side
	bb &= ~(rankA | rankB);
	}
	if (x<32){//clear top rows
	bb &= ~(file8 | file7);
	}
	if (x>31){//clear botto rows
	bb &= ~(file1 | file2);
	}
	knightMoves[x] = bb;
	}
	}
	void initKingDatabase(){
	bitBoard bb;
	for (int x = 0; x<64; x++){
	bb = 0;
	bb |= (1LL << (x - 1));
	bb |= (1LL << (x + 1));
	bb |= (1LL << (x - 8));
	bb |= (1LL << (x + 8));
	bb |= (1LL << (x - 7));
	bb |= (1LL << (x + 7));
	bb |= (1LL << (x - 9));
	bb |= (1LL << (x + 9));
	if (x % 8 == 0){//king is on left rank
	//erase right  rank
	bb &= ~rankH;
	}
	if (x % 8 == 7){//king is on right rank
	//erase left rank
	bb &= ~rankA;
	}
	if (x<8){//king is on bottom file
	//erase top file
	bb &= ~file8;
	}
	if (x>55){//king is on bottom file
	//erase top file
	bb &= ~file1;
	}
	kingMoves[x] = bb;
	}
	}

	inline void pieceBoardToList(int current, bitBoard bb, Move moves[], moveBoard board, moveBoard attackBoard[]){
	while (bb){

	moves[moveIndex].target = bitScanForward(bb);
	bb = (1LL << moves[moveIndex].target) ^ bb;
	moves[moveIndex].current = current;
	moves[moveIndex].board = board;
	moves[moveIndex].capture = attackBoard[moves[moveIndex].target];
	moveIndex++;
	}
	}

	inline void pawnBoardToList(int backShift, bitBoard bb, Move moves[], moveBoard board, moveBoard attackBoard[]){//backshift is used to get the peices current square
	while (bb){
	moves[moveIndex].target = bitScanForward(bb);
	bb = (1LL << moves[moveIndex].target) ^ bb;
	moves[moveIndex].current = moves[moveIndex].target + backShift;
	moves[moveIndex].board = board;
	moves[moveIndex].capture = attackBoard[moves[moveIndex].target];
	moveIndex++;
	}
	}
	void initRookDataBase(){
	//value is the value to store in the database
	//index is used to put possobility on the mask
	//moves is the blocker-mask
	for (int square = 0; square < 64; square++)//the square we are initializing for
	{
	int possibility = 1LL << (64 - magicNumberShiftsRook[square]);// the number of possible blocker boards for a given square

	bitBoard attackBoard = rookMask[square];//the attack mask for the given square
	for (int i = 0; i < possibility; i++){
	bitBoard tempP = i;
	attackBoard = rookMask[square];
	bitBoard moves = 0;
	bitBoard value = 0;
	while (attackBoard){
	int index = bitScanForward(attackBoard);
	attackBoard &= ~(1LL << index);
	moves |= ((tempP & 1) << index);
	tempP = tempP >> 1;
	}

	int dataIndex = moves * magicRook[square] >> magicNumberShiftsRook[square];
	for (int index = square + 8; index < 64; index += 8){
	value |= 1ll << index;
	if (((1LL << index)&moves) != 0){

	break;
	}
	}
	for (int index = square - 8; index >= 0; index -= 8){
	value |= 1ll << index;
	if (((1LL << index)&moves) != 0){

	break;
	}
	}

	for (int index = square + 1; index % 8 != 0; index++){
	value |= 1ll << index;
	if (((1LL << index)&moves) != 0){

	break;
	}
	}

	for (int index = square - 1; (index % 8 != 7) && (index >= 0); index--){
	value |= 1ll << index;
	if (((1LL << index)&moves) != 0){

	break;
	}
	}


	rookMoves[square][dataIndex] = value;
	}
	}
	}

	void initBishopDataBase(){
	//b1 | b2 is the value to store in the database
	//index is used to put possobility on the mask
	//moves is the blocker-mask
	for (int square = 0; square < 64; square++)//the square we are initializing for
	{
	int possibility = 1LL << (64 - magicNumberShiftsBishop[square]);// the number of possible blocker boards for a given square

	bitBoard attackBoard = bishopMask[square];//the attack mask for the given square
	for (int i = 0; i < possibility; i++){
	bitBoard tempP = i;
	attackBoard = bishopMask[square];
	bitBoard moves = 0;
	bitBoard b1, b2;
	while (attackBoard){
	int index = bitScanForward(attackBoard);
	attackBoard &= ~(1LL << index);
	moves |= ((tempP & 1) << index);
	tempP = tempP >> 1;
	}
	int dataIndex = moves * magicBishop[square] >> magicNumberShiftsBishop[square];
	b1 = (1LL << square);
	b2 = b1;
	int temp = square;
	while ((temp % 8 != 0) && (temp / 8 != 0)){// left bottom
	b1 |= b1 >> 9;
	temp -= 9;
	if (((1LL << temp)&moves) != 0){

	break;
	}

	}
	temp = square;
	while ((temp % 8 != 7) && (temp / 8 != 7)){//top right
	temp += 9;
	b1 |= b1 << 9;
	if (((1LL << temp)&moves) != 0){

	break;
	}

	}

	temp = square;
	while ((temp % 8 != 0) && (temp / 8 != 7)){//top left;
	b2 |= b2 << 7;
	temp += 7;
	if (((1LL << temp)&moves) != 0){

	break;
	}

	}
	temp = square;
	while ((temp % 8 != 7) && (temp / 8 != 0)){//bottom right
	b2 |= b2 >> 7;
	temp -= 7;
	if (((1LL << temp)&moves) != 0){

	break;
	}

	}
	bishopMoves[square][dataIndex] = b1 ^ b2;
	}
	}
	}


public:
	int getMoves(int isWhite, Move moves[],moveBoard attackBoard[], bitBoard BP, bitBoard BH, bitBoard BB, bitBoard BC, bitBoard BQ, bitBoard BK, bitBoard WP, bitBoard WC, bitBoard WH, bitBoard WB, bitBoard WQ, bitBoard WK);
	moveGenerator();

};
//give it 12 bitboards and a bool isWhite,  and an array of moves
//it fills the array with all possible moves and returns the amount of moves to iterate throught the array

int moveGenerator::getMoves(int isWhite, Move moves[],moveBoard attackBoard[], bitBoard BP, bitBoard BH, bitBoard BB, bitBoard BC, bitBoard BQ, bitBoard BK, bitBoard WP, bitBoard WC, bitBoard WH, bitBoard WB, bitBoard WQ, bitBoard WK){
	BLACK = BP | BH | BB | BC | BQ | BK;
	WHITE = WP | WC | WH | WB | WQ | WK;
	occ = BLACK | WHITE;
	empty = ~occ;
	moveIndex = 0;
	int location;//to use in the database
	bitBoard pieceBoard;//to use for non pawns to get locations using bitscanning
	bitBoard temp;//the attack board;
	if (isWhite==1){
	notWhite = ~WHITE;//will be needed
	//regular white pawn moves
	temp = WP << 8 & empty;
	pawnBoardToList(-8, temp, moves, wp, attackBoard);
	//double push
	temp = ((temp << 8)&file4)&empty;
	pawnBoardToList(-16, temp, moves, wp, attackBoard);

	temp = (WP&~rankA) << 7 & BLACK;
	pawnBoardToList(-7, temp, moves, wp, attackBoard);
	temp = (WP&~rankH) << 9 & BLACK;
	pawnBoardToList(-9, temp, moves, wp, attackBoard);
	
	//kingMoves
	if (WK){
	location = bitScanForward(WK);
	temp = (kingMoves[location] & (notWhite));
	pieceBoardToList(location, temp, moves, wk, attackBoard);
	}
	//horse moves
	pieceBoard = WH;
	while (pieceBoard){
	location = bitScanForward(pieceBoard);
	pieceBoard ^= 1LL << location;
	temp = knightMoves[location] & notWhite;
	pieceBoardToList(location, temp, moves, wh, attackBoard);
	}
	//castle moves
	pieceBoard = WC;
	while (pieceBoard){
	location = bitScanForward(pieceBoard);
	pieceBoard ^= 1LL << location;
	bitBoard blockers = ((occ&(rookMask[location])));
	int index = blockers * magicRook[location] >> magicNumberShiftsRook[location];
	temp = rookMoves[location][index] & notWhite;
	pieceBoardToList(location, temp, moves, wc, attackBoard);
	}
	//bishop moves
	pieceBoard = WB;
	while (pieceBoard){
	location = bitScanForward(pieceBoard);
	pieceBoard ^= 1LL << location;
	bitBoard blockers = occ&bishopMask[location];
	int index = blockers * magicBishop[location] >> magicNumberShiftsBishop[location];
	temp = bishopMoves[location][index] & notWhite;
	pieceBoardToList(location, temp, moves, wb, attackBoard);
	}
	//queen moves
	pieceBoard = WQ;
	while (pieceBoard){
	location = bitScanForward(pieceBoard);
	pieceBoard ^= 1LL << location;
	bitBoard blockers = occ&bishopMask[location];
	int index = blockers * magicBishop[location] >> magicNumberShiftsBishop[location];
	temp = bishopMoves[location][index];
	blockers = occ&rookMask[location];
	index = blockers * magicRook[location] >> magicNumberShiftsRook[location];
	temp |= rookMoves[location][index];
	temp &= notWhite;
	pieceBoardToList(location, temp, moves, wq, attackBoard);
	}
	}
	else{
	notBlack = ~BLACK;//will be needed

	//regular black pawn moves
	temp = BP >> 8 & empty;
	pawnBoardToList(8, temp, moves, bp, attackBoard);
	//double push
	temp = ((temp >> 8)&file5)&empty;
	pawnBoardToList(16, temp, moves, bp, attackBoard);
	temp = (BP&~rankH) >> 7 & WHITE;
	pawnBoardToList(7, temp, moves, bp, attackBoard);
	temp = (BP&~rankA) >> 9 & WHITE;
	pawnBoardToList(9, temp, moves, bp, attackBoard);
	
	//kingMoves
	if (BK)
	{	location = bitScanForward(BK);
	temp = (kingMoves[location] & (notBlack));
	pieceBoardToList(location, temp, moves, bk, attackBoard);
	}
	//horse moves
	pieceBoard = BH;
	while (pieceBoard){
	location = bitScanForward(pieceBoard);
	pieceBoard ^= 1LL << location;
	temp = knightMoves[location] & notBlack;
	pieceBoardToList(location, temp, moves, bh, attackBoard);
	}
	//castle moves
	pieceBoard = BC;
	while (pieceBoard){
	location = bitScanForward(pieceBoard);
	pieceBoard ^= 1LL << location;
	bitBoard blockers = occ&rookMask[location];
	int index = blockers * magicRook[location] >> magicNumberShiftsRook[location];
	temp = rookMoves[location][index] & notBlack;
	pieceBoardToList(location, temp, moves, bc, attackBoard);
	}
	//bishop moves
	pieceBoard = BB;
	while (pieceBoard){
	location = bitScanForward(pieceBoard);
	pieceBoard ^= 1LL << location;
	bitBoard blockers = occ&bishopMask[location];
	int index = blockers * magicBishop[location] >> magicNumberShiftsBishop[location];
	temp = bishopMoves[location][index] & notBlack;
	pieceBoardToList(location, temp, moves, bb, attackBoard);
	}
	//queen moves
	pieceBoard = BQ;
	while (pieceBoard){
	location = bitScanForward(pieceBoard);
	pieceBoard ^= 1LL << location;
	bitBoard blockers = occ&bishopMask[location];
	int index = blockers * magicBishop[location] >> magicNumberShiftsBishop[location];
	temp = bishopMoves[location][index];
	blockers = occ&rookMask[location];
	index = blockers * magicRook[location] >> magicNumberShiftsRook[location];
	temp |= rookMoves[location][index];
	temp &= notBlack;
	pieceBoardToList(location, temp, moves, bq, attackBoard);
	}
	}
	return moveIndex;
}