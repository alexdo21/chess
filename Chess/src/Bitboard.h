#pragma once

#include <cstdint>
#include <vector>
#include <string>

class Bitboard
{
public:
	Bitboard(uint64_t value);

	uint64_t GetValue();

	Bitboard operator|(const Bitboard& other) const;
	Bitboard operator&(const Bitboard& other) const;
	Bitboard operator~();

	Bitboard& operator|=(const Bitboard& other);
	Bitboard& operator&=(const Bitboard& other);
private:
	uint64_t m_Value;
};