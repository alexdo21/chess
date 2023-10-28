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

int Game::GetSide()
{
	return m_Side;
}

int Game::GetScore()
{
	return m_Score;
}

int Game::GetMoves()
{
	return m_Moves;
}

bool Game::IsKingInCheck()
{
	return m_IsKingInCheck;
}

bool Game::HasKingMoved()
{
	return m_HasKingMoved;
}

int* Game::GetPawnMoveStates()
{
	return m_PawnMoveStates;
}

int* Game::GetRookMoveStates()
{
	return m_RookMoveStates;
}

Bitboard Game::GetBoard()
{
	return m_Pawns | m_Knights | m_Bishops | m_Rooks | m_Queen | m_King;
}

Bitboard& Game::GetPawns()
{
  return m_Pawns;
}

Bitboard& Game::GetKnights()
{
  return m_Knights;
}

Bitboard& Game::GetBishops()
{
  return m_Bishops;
}

Bitboard& Game::GetRooks()
{
  return m_Rooks;
}

Bitboard& Game::GetQueen()
{
  return m_Queen;
}

Bitboard& Game::GetKing()
{
  return m_King;
}

void Game::UpdateScore(int pieceValue)
{
	m_Score += pieceValue;
}

void Game::IncrementMoves()
{
	m_Moves++;
}

void Game::ToggleIsKingInCheck()
{
	m_IsKingInCheck = !m_IsKingInCheck;
}

void Game::SetHasKingMoved()
{
	m_HasKingMoved = true;
}

void Game::SetPawnMoveState(int pawn, int value)
{
	m_PawnMoveStates[pawn] += value;
}

void Game::SetRookMoveState(int rook)
{
	m_RookMoveStates[rook]++;
}

bool Game::CanCastle(int side)
{
	return !m_IsKingInCheck && !m_HasKingMoved && !m_RookMoveStates[side];
}