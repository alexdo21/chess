#include "Bitboard.h"

Bitboard::Bitboard(U64 value) : m_Value(value)
{
}

U64 Bitboard::GetValue()
{
	return m_Value;
}

Bitboard Bitboard::operator|(const Bitboard& other) const
{
	return Bitboard(m_Value | other.m_Value);
}

Bitboard Bitboard::operator&(const Bitboard& other) const
{
	return Bitboard(m_Value & other.m_Value);
}

Bitboard Bitboard::operator~()
{
	return Bitboard(~m_Value);
}

Bitboard& Bitboard::operator|=(const Bitboard& other)
{
	m_Value |= other.m_Value;
	return *this;
}

Bitboard& Bitboard::operator&=(const Bitboard& other)
{
	m_Value &= other.m_Value;
	return *this;
}

// h  e d  a h  e d  a h  e d  a h  e d  a h  e d  a h  e d  a h  e d  a h  e d  a
// 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
//         8         7         6         5         4         3         2         1
// (60) (56) (52) (48) (44) (40) (36) (32) (28) (24) (20) (16) (12) (08) (04) (00)
//
// every 1st 4th is a-d, every 2nd 4th is e-h
// every 8th is a rank

/*
* 0000 0000 0000 0000
*
* 0000 0000     0000    e8*a8*e7*a7
* 0000 0000
*
* 0000 0000     0000    e6*a6*e5*a5
* 0000 0000
*
*
* 0000 0000     0000    e4*a4*e3*a3
* 0000 0000
*
* 0000 0000     0000    e2*a2*e1*a1
* 0000 0000
*/