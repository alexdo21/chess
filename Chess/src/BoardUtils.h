#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <cstdlib>

#include "Bitboard.h"

namespace BoardUtils {
	std::string GetBinRepr(Bitboard& bitboard);
	std::string GetHexRepr(Bitboard& bitboard);
	std::vector<std::string> GetNotationsFromBitboard(Bitboard& bitboard);
	std::pair<int, int> GetCoordsFromNotation(std::string notation);
	bool IsCoordsInBounds(std::pair<int, int> coords);
	int FindBitPos(Bitboard& bitboard);
	uint64_t SetBitPos(int rank, int file);
	
	Bitboard GetPawnMoves(Bitboard& bitboard);
	Bitboard GetKnightMoves(Bitboard& bitboard);
	Bitboard GetBishopMoves(Bitboard& bitboard);
	Bitboard GetRookMoves(Bitboard& bitboard);
	Bitboard GetQueenMoves(Bitboard& bitboard);
	Bitboard GetKingMoves(Bitboard& bitboard);
}