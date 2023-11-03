#pragma once

#include "Constants.h"
#include "Bitboard.h"

class Game
{
public:
	Game();
	Game(int side);

	int GetSide();
	int GetScore();
	int GetMoves();
	bool IsKingInCheck();
	bool HasKingMoved();
	int* GetPawnMoveStates();
	int* GetRookMoveStates();
	Bitboard GetBoard();

	Bitboard& GetPawns();
	Bitboard& GetKnights();
	Bitboard& GetBishops();
	Bitboard& GetRooks();
	Bitboard& GetQueen();
	Bitboard& GetKing();

	void SetSide(int side);
	void UpdateScore(int pieceValue);
	void IncrementMoves();
	void ToggleIsKingInCheck();
	void SetHasKingMoved();
	void SetPawnMoveState(int pawn, int moveState);
	void SetRookMoveState(int rook);

	bool CanCastle(int side);

	void SetPawns(U64 value);
	void SetKnights(U64 value);
	void SetBishops(U64 value);
	void SetRooks(U64 value);
	void SetQueen(U64 value);
	void SetKing(U64 value);
private:
	int m_Side;
	Bitboard m_Pawns;
	Bitboard m_Knights;
	Bitboard m_Bishops;
	Bitboard m_Rooks;
	Bitboard m_Queen;
	Bitboard m_King;

	int m_Moves = 0;
	int m_Score = 0;
	bool m_IsKingInCheck = false;
	bool m_HasKingMoved = false;
	int m_PawnMoveStates[8] = { 0, 0, 0, 0, 0, 0, 0, 0 }; // 0 = not moved, 1 = moved 1 or moved after moved 2, 2 = moved 2 (en passant)
	int m_RookMoveStates[2] = { 0, 0 }; // 0 = not moved, 1 = has moved
};