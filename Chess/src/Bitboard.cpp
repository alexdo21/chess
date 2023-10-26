#include "Bitboard.h"

Bitboard::Bitboard() : m_Value(0)
{
}

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

/*
* Can't move a King into check
* 
* 1.) moving a King into an attacked sqauare
* 2.) moving a King into a square that puts it into check but is not currently attacked (checking slider)
*       - calculate attacked squares as if the King is not there
* 
* 3.) for each piece type, pretend there's a piece of that type on the King square, and then check legal moves     from that square to see if an actual piece of that type is there.
* 4.) Double check
*       - only valid moves are King (because a piece cannot block or capture two pieces at the same time)
* 
* 5.) Capture mask and push mask
*       - if in check, the piece to capture must be checking piece
*       - if the checking piece is a sliding piece, then the push mask is limited to the squares between the           King and checking piece
* 
* 6.) Pins
*       - intersection of oppoonent sliding pieces and King's sliding piece moves (files, ranks, diagonals),           whichever piece lands on this intersection is pinned.
*       - legal moves for pinned piece is calculated via removing the pinned piece (diagonals: Bishops, Queens,        Pawns (captures); non-diagonals: Rooks, Queens, Pawns (pushes))
* 
* 7.) En Passant
*       - discovery check on horizontals
*/
