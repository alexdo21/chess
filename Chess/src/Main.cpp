#include <vector>
#include <string>
#include <iostream>

#include "Bitboard.h"
#include "BoardUtils.h"
#include "Constants.h"
#include "Game.h"

int main()
{
    //Bitboard knightAtD4(d4);
    //std::cout << BoardUtils::PrintBoard(knightAtD4) << std::endl;
    //Bitboard knightD4Moves = BoardUtils::GetKnightMoves(knightAtD4);
    //std::cout << BoardUtils::PrintBoard(knightD4Moves) << std::endl;

    //Bitboard knightAtG6(g6);
    //std::cout << BoardUtils::PrintBoard(knightAtG6) << std::endl;
    //Bitboard knightG6Moves = BoardUtils::GetKnightMoves(knightAtG6);
    //std::cout << BoardUtils::PrintBoard(knightG6Moves) << std::endl;
    //return 0;

    //Bitboard bishopAtD4(d4);
    //std::cout << BoardUtils::PrintBoard(bishopAtD4) << std::endl;
    //Bitboard bishopD4Moves = BoardUtils::GetBishopMoves(bishopAtD4);
    //std::cout << BoardUtils::PrintBoard(bishopD4Moves) << std::endl;

    //Bitboard rookAtD4(d4);
    //std::cout << BoardUtils::PrintBoard(rookAtD4) << std::endl;
    //Bitboard rookD4Moves = BoardUtils::GetRookMoves(rookAtD4);
    //std::cout << BoardUtils::PrintBoard(rookD4Moves) << std::endl;

    // Bitboard queenAtD4(BoardUtils::SetBitPos(d4));
    // std::cout << BoardUtils::PrintBoard(queenAtD4) << std::endl;
    // Bitboard queenD4Moves = BoardUtils::GetQueenMoves(queenAtD4);
    // std::cout << BoardUtils::PrintBoard(queenD4Moves) << std::endl;
    // Bitboard pawnAtD7(BoardUtils::SetBitPos(d7));
    // std::cout << BoardUtils::PrintBoard(queenD4Moves &= ~pawnAtD7);

    // std::cout << Square::a1 << std::endl;
    // std::cout << BoardUtils::SetBitPos(a1) << std::endl;
    
    // Bitboard pawnAtD4(BoardUtils::SetBitPos(d4));
    // std::cout << BoardUtils::PrintBoard(pawnAtD4) << std::endl;
    // Bitboard blackPawnD4Moves = BoardUtils::GetPawnMoves(pawnAtD6, BLACK);
    // std::cout << BoardUtils::PrintBoard(blackPawnD4Moves) << std::endl;

    // std::cout << BoardUtils::PrintBoard(pawnAtD4) << std::endl;
    // Bitboard whitePawnD4Moves = BoardUtils::GetPawnMoves(pawnAtD4, WHITE);
    // std::cout << BoardUtils::PrintBoard(whitePawnD4Moves) << std::endl;
    
    // Bitboard kingAtD4(BoardUtils::SetBitPos(a1));
    // std::cout << BoardUtils::PrintBoard(kingAtD4) << std::endl;
    // Bitboard kingD4Moves = BoardUtils::GetKingMoves(kingAtD4);
    // std::cout << BoardUtils::PrintBoard(kingD4Moves) << std::endl;

  Game player1(WHITE);
  Game player2(BLACK);

  Bitboard player1Board = player1.GetPawns() | player1.GetKnights() | player1.GetBishops() | player1.GetRooks() | player1.GetQueen() | player1.GetKing();
  Bitboard player2Board = player2.GetPawns() | player2.GetKnights() | player2.GetBishops() | player2.GetRooks() | player2.GetQueen() | player2.GetKing();
  std::cout << BoardUtils::PrintBoard(player1Board) << std::endl;
  std::cout << BoardUtils::PrintBoard(player2Board) << std::endl;
}
