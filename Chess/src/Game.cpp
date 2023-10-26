#include "Game.h"

Game::Game(int side) : m_Side(side)
{
  m_Pawns = side == WHITE ? Bitboard(0x000000000000FF00) : Bitboard(0x00FF000000000000);
  m_Knights = side == WHITE ? Bitboard(0x0000000000000042) : Bitboard(0x4200000000000000);
  m_Bishops = side == WHITE ? Bitboard(0x0000000000000024) : Bitboard(0x2400000000000000);
  m_Rooks = side == WHITE ? Bitboard(0x0000000000000081) : Bitboard(0x8100000000000000);
  m_Queen = side == WHITE ? Bitboard(0x0000000000000008) : Bitboard(0x0800000000000000);
  m_King = side == WHITE ? Bitboard(0x0000000000000010) : Bitboard(0x1000000000000000);
}

Bitboard Game::GetPawns()
{
  return m_Pawns;
}

Bitboard Game::GetKnights()
{
  return m_Knights;
}

Bitboard Game::GetBishops()
{
  return m_Bishops;
}

Bitboard Game::GetRooks()
{
  return m_Rooks;
}

Bitboard Game::GetQueen()
{
  return m_Queen;
}

Bitboard Game::GetKing()
{
  return m_King;
}
