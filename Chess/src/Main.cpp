#include <vector>
#include <string>
#include <iostream>

#include "Bitboard.h"
#include "BoardUtils.h"

void InitBoard()
{
    Bitboard whitePawns(0x000000000000FF00);
    Bitboard whiteKnights(0x0000000000000042);
    Bitboard whiteBishops(0x0000000000000024);
    Bitboard whiteRooks(0x0000000000000081);
    Bitboard whiteQueen(0x0000000000000008);
    Bitboard whiteKing(0x0000000000000010);

    Bitboard blackPawns(0x00FF000000000000);
    Bitboard blackKnights(0x4200000000000000);
    Bitboard blackBishops(0x2400000000000000);
    Bitboard blackRooks(0x8100000000000000);
    Bitboard blackQueen(0x0800000000000000);
    Bitboard blackKing(0x1000000000000000);
}

int main()
{
    InitBoard();
    //Bitboard knightAtD4(0x0000000008000000);
    //std::cout << BoardUtils::GetBinRepr(knightAtD4) << std::endl;
    //Bitboard knightD4Moves = BoardUtils::GetKnightMoves(knightAtD4);
    //std::cout << BoardUtils::GetBinRepr(knightD4Moves) << std::endl;

    //Bitboard knightAtG6(0x0000400000000000);
    //std::cout << BoardUtils::GetBinRepr(knightAtG6) << std::endl;
    //Bitboard knightG6Moves = BoardUtils::GetKnightMoves(knightAtG6);
    //std::cout << BoardUtils::GetBinRepr(knightG6Moves) << std::endl;
    //return 0;

    //Bitboard bishopAtD4(0x0000400000000000);
    //std::cout << BoardUtils::GetBinRepr(bishopAtD4) << std::endl;
    //Bitboard bishopD4Moves = BoardUtils::GetBishopMoves(bishopAtD4);
    //std::cout << BoardUtils::GetBinRepr(bishopD4Moves) << std::endl;

    //Bitboard rookAtD4(0x0000000008000000);
    //std::cout << BoardUtils::GetBinRepr(rookAtD4) << std::endl;
    //Bitboard rookD4Moves = BoardUtils::GetRookMoves(rookAtD4);
    //std::cout << BoardUtils::GetBinRepr(rookD4Moves) << std::endl;

    Bitboard queenAtD4(BoardUtils::SetBitPos(3, 3));
    std::cout << BoardUtils::GetBinRepr(queenAtD4) << std::endl;
    Bitboard queenD4Moves = BoardUtils::GetQueenMoves(queenAtD4);
    std::cout << BoardUtils::GetBinRepr(queenD4Moves) << std::endl;
    Bitboard pawnAtD7(BoardUtils::SetBitPos(6, 3));
    std::cout << BoardUtils::GetBinRepr(queenD4Moves &= ~pawnAtD7);
}