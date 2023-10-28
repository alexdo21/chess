#pragma once

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <bitset>

#include "Bitboard.h"
#include "Constants.h"
#include "Game.h"

namespace BoardUtils {
  std::string PrintBoard(Bitboard& bitboard);
	std::string GetBinRepr(Bitboard& bitboard);
	std::string GetHexRepr(Bitboard& bitboard);
	std::vector<std::string> GetNotationsFromBitboard(Bitboard& bitboard);
	std::pair<int, int> GetCoordsFromNotation(std::string notation);
	bool IsCoordsInBounds(std::pair<int, int> coords);
	int FindBitPos(Bitboard& bitboard);
	U64 SetBitPos(int pos);
	bool IsSquareOccupied(U64 value, int bitPos);
	
	Bitboard GetPawnMoves(Bitboard& bitboard, Game& p1, Game& p2);
	Bitboard GetKnightMoves(Bitboard& bitboard, Game& p1, Game& p2);
	Bitboard GetBishopMoves(Bitboard& bitboard, Game& p1, Game& p2);
	Bitboard GetRookMoves(Bitboard& bitboard, Game& p1, Game& p2);
	Bitboard GetQueenMoves(Bitboard& bitboard, Game& p1, Game& p2);
	Bitboard GetKingMoves(Bitboard& bitboard, Game& p1, Game& p2);
}
