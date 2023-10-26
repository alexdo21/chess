#pragma once

#include "Constants.h"
#include "Bitboard.h"

class Game
{
public:
  Game(int side);

  int GetSide();
  int GetMoves();
  bool HasKingMoved();
  bool CanCastle();
  int* GetPawnMoveStates();
  int* GetRookMoveStates();
  
  Bitboard GetPawns();
  Bitboard GetKnights();
  Bitboard GetBishops();
  Bitboard GetRooks();
  Bitboard GetQueen();
  Bitboard GetKing();
private:
  int m_Side;
  Bitboard m_Pawns;
  Bitboard m_Knights;
  Bitboard m_Bishops;
  Bitboard m_Rooks;
  Bitboard m_Queen;
  Bitboard m_King;

  int m_Moves = 0;
  bool m_HasKingMoved = false;
  bool m_CanCastle = false;
  int m_PawnMoveStates[8] = { 0, 0, 0, 0, 0, 0, 0, 0 }; // 0 = not moved, 1 = moved 1 or moved after moved 2, 2 = moved 2 (en passant)
  int m_RookMovesStates[2] = { 0, 0 };
};
