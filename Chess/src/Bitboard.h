#pragma once

#include <vector>
#include <string>

#include "Constants.h"

class Bitboard
{
public:
	Bitboard();
	Bitboard(U64 value);

	U64 GetValue();
	int GetPopCount();
	void SetValue(U64 value);

	Bitboard operator|(const Bitboard& other) const;
	Bitboard operator&(const Bitboard& other) const;
	Bitboard operator~();

	Bitboard& operator|=(const Bitboard& other);
	Bitboard& operator&=(const Bitboard& other);

	operator bool() const;
private:
	U64 m_Value;
};
