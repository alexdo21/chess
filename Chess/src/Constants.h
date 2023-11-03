#pragma once

#include <cstdint>

#define U64 uint64_t
#define MAX_VALUE 0xFFFFFFFFFFFFFFFF

#define WHITE 0
#define BLACK 1

#define LEFT 0
#define MIDDLE 0
#define RIGHT 1

#define PAWN_POINTS 1
#define KNIGHT_POINTS 3
#define BISHOP_POINTS 3
#define ROOK_POINTS 5
#define QUEEN_POINTS 9

enum {
	a, b, c, d, e, f, g, h
};

enum {
	a1, b1, c1, d1, e1, f1, g1, h1,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a8, b8, c8, d8, e8, f8, g8, h8,
};
