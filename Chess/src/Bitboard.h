#pragma once

#include <vector>
#include <string>

#include "Constants.h"

class Bitboard
{
public:
	Bitboard(U64 value);

	U64 GetValue();

	Bitboard operator|(const Bitboard& other) const;
	Bitboard operator&(const Bitboard& other) const;
	Bitboard operator~();

	Bitboard& operator|=(const Bitboard& other);
	Bitboard& operator&=(const Bitboard& other);
private:
	U64 m_Value;
};