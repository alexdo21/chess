#include "BoardUtils.h"

namespace BoardUtils {
	std::string PrintBoard(Bitboard& bitboard)
	{
		U64 value = bitboard.GetValue();
		std::string result;
		for (int rank = 7; rank >= 0; rank--)
		{
			result += std::to_string(rank + 1) + "  ";
			for (int file = 0; file < 8; file++)
			{
				int square = rank * 8 + file;
				U64 mask = SetBitPos(square);

				result.push_back((value & mask) ? '1' : '0');
				result.push_back(' ');
			}
			result += "\n";
		}
		result += "\n   a b c d e f g h\n";
		return result;
	}

	std::string GetBinRepr(Bitboard& bitboard)
	{
		std::stringstream stream;
		stream << "0b" << std::bitset<64>(bitboard.GetValue());
		return stream.str();
	}

	std::string GetHexRepr(Bitboard& bitboard)
	{
		std::stringstream stream;
		stream << "0x" << std::hex << std::setw(16) << std::setfill('0') << bitboard.GetValue() << std::dec;
		return stream.str();
	}

	std::vector<std::string> GetNotationsFromBitboard(Bitboard& bitboard)
	{
		U64 value = bitboard.GetValue();
		int rank = 0;
		int file = 97;
		std::vector<std::string> result;
		for (int i = 0; i < 64; i++)
		{
			if (i % 8 == 0)
			{
				rank++;
			}
			if ((value >> i) & 1)
			{
				result.emplace_back(std::string(1, file) + std::to_string(rank));
			}
			if (file++ == 104)
			{
				file = 97;
			}
		}
		return result;
	}

	std::pair<int, int> GetCoordsFromNotation(std::string notation)
	{
		return { notation[0] - 'a', notation[1] - '0' - 1 };
	}

	bool IsCoordsInBounds(std::pair<int, int> coords)
	{
		return (0 <= coords.first && coords.first < 8) && (0 <= coords.second && coords.second < 8);
	}

	int FindBitPos(Bitboard& bitboard)
	{
		U64 value = bitboard.GetValue();
		for (int pos = 0; pos < 63; pos++)
		{
			if ((value >> pos) & 1)
			{
				return pos;
			}
		}
		return -1;
	}

	U64 SetBitPos(int pos)
	{
		return 1ULL << pos;
	}

	bool IsSquareOccupied(U64 value, int bitPos)
	{
		return (value >> bitPos) & 1;
	}

	bool IsNewBitPosInBounds(int newBitPos, int oldBitPos, int dir)
	{
		if (newBitPos > 63 || newBitPos < 0)
		{
			return false;
		}
		int oldFilePos = oldBitPos % 8;
		int newFilePos = newBitPos % 8;
		if (newFilePos < oldFilePos && dir)
		{
			return false;
		}
		if (newFilePos > oldFilePos && !dir)
		{
			return false;
		}
		return true;
	}

	bool WillKingBeInCheck(int bitPos, Game& p1, Game& p2)
	{
		// pawns
		int p1Side = p1.GetSide();
		U64 p2PawnsValue = p2.GetPawns().GetValue();
		int sidesAndDeltas[2][2] = { { 7, 9 }, { -9, -7 } };
		if (IsNewBitPosInBounds(bitPos + sidesAndDeltas[p1Side][0], bitPos, LEFT) && IsSquareOccupied(p2PawnsValue, bitPos + sidesAndDeltas[p1Side][0]))
		{
			return true;
		}
		if (IsNewBitPosInBounds(bitPos + sidesAndDeltas[p1Side][1], bitPos, RIGHT) && IsSquareOccupied(p2PawnsValue, bitPos + sidesAndDeltas[p1Side][1]))
		{
			return true;
		}

		// knights
		U64 p2KnightsValue = p2.GetKnights().GetValue();
		Bitboard dummyKnight(SetBitPos(bitPos));
		Bitboard dummyKnightAttacks = GetKnightMoves(dummyKnight, p1, p2);
		if (dummyKnightAttacks.GetValue() & p2KnightsValue)
		{
			return true;
		}

		// bishops
		U64 p2BishopsValue = p2.GetBishops().GetValue();
		Bitboard dummyBishop(SetBitPos(bitPos));
		Bitboard dummyBishopAttacks = GetBishopMoves(dummyBishop, p1, p2);
		if (dummyBishopAttacks.GetValue() & p2BishopsValue)
		{
			return true;
		}

		// rooks
		U64 p2RooksValue = p2.GetRooks().GetValue();
		Bitboard dummyRook(SetBitPos(bitPos));
		Bitboard dummyRookAttacks = GetRookMoves(dummyRook, p1, p2);
		if (dummyRookAttacks.GetValue() & p2RooksValue)
		{
			return true;
		}

		// queen
		U64 p2QueenValue = p2.GetQueen().GetValue();
		Bitboard dummyQueen(SetBitPos(bitPos));
		Bitboard dummyQueenAttacks = GetQueenMoves(dummyQueen, p1, p2);
		if (dummyQueenAttacks.GetValue() & p2QueenValue)
		{
			return true;
		}

		// king
		U64 p2KingValue = p2.GetKing().GetValue();
		int leftDeltas[3] = { 7, -1, -9 };
		for (int d : leftDeltas)
		{
			if (IsNewBitPosInBounds(bitPos + d, bitPos, LEFT) && IsSquareOccupied(p2KingValue, bitPos + d))
			{
				return true;
			}
		}
		int middleDeltas[2] = { -8, 8 };
		for (int d : middleDeltas)
		{
			if (IsNewBitPosInBounds(bitPos + d, bitPos, MIDDLE) && IsSquareOccupied(p2KingValue, bitPos + d))
			{
				return true;
			}
		}
		int rightDeltas[3] = { -7, 1, 9 };
		for (int d : rightDeltas)
		{
			if (IsNewBitPosInBounds(bitPos + d, bitPos, RIGHT) && IsSquareOccupied(p2KingValue, bitPos + d))
			{
				return true;
			}
		}

		return false;
	}

	Bitboard GetPawnMoves(Bitboard& bitboard, Game& p1, Game& p2)
	{
		int bitPos = FindBitPos(bitboard);
		Bitboard pawnMoves;
		int p1Side = p1.GetSide();
		U64 p1BoardValue = p1.GetBoard().GetValue();
		U64 p2BoardValue = p2.GetBoard().GetValue();
		U64 p2PawnsValue = p2.GetPawns().GetValue();
		int* p1PawnMoveStates = p1.GetPawnMoveStates();
		int* p2PawnMoveStates = p2.GetPawnMoveStates();
		int sidesAndDeltas[2][6] = { { 16, 7, 8, 9, 7, 9 }, { -16, -9, -8, -7, -9, -7 } };

		// move 2
		if (IsNewBitPosInBounds(bitPos + sidesAndDeltas[p1Side][0], bitPos, MIDDLE) && !IsSquareOccupied(p1BoardValue | p2BoardValue, bitPos + sidesAndDeltas[p1Side][0]) && p1PawnMoveStates[bitPos % 8] == 0)
		{
			pawnMoves |= Bitboard(SetBitPos(bitPos + sidesAndDeltas[p1Side][0]));
		}
		// attack left
		if (IsNewBitPosInBounds(bitPos + sidesAndDeltas[p1Side][1], bitPos, LEFT) && IsSquareOccupied(p2BoardValue, bitPos + sidesAndDeltas[p1Side][1]))
		{
			pawnMoves |= Bitboard(SetBitPos(bitPos + sidesAndDeltas[p1Side][1]));
		}
		// move 1
		if (IsNewBitPosInBounds(bitPos + sidesAndDeltas[p1Side][2], bitPos, MIDDLE) && !IsSquareOccupied(p1BoardValue | p2BoardValue, bitPos + sidesAndDeltas[p1Side][2]))
		{
			pawnMoves |= Bitboard(SetBitPos(bitPos + sidesAndDeltas[p1Side][2]));
		}
		// attack right
		if (IsNewBitPosInBounds(bitPos + sidesAndDeltas[p1Side][3], bitPos, RIGHT) && IsSquareOccupied(p2BoardValue, bitPos + sidesAndDeltas[p1Side][3]))
		{
			pawnMoves |= Bitboard(SetBitPos(bitPos + sidesAndDeltas[p1Side][3]));
		}
		// en passant left
		if (IsNewBitPosInBounds(bitPos + -1, bitPos, LEFT) && IsSquareOccupied(p2PawnsValue, bitPos + -1) && p2PawnMoveStates[(bitPos + -1) % 8] == 2)
		{
			pawnMoves |= Bitboard(SetBitPos(bitPos + sidesAndDeltas[p1Side][4]));
		}
		// en passant right
		if (IsNewBitPosInBounds(bitPos + 1, bitPos, RIGHT) && IsSquareOccupied(p2PawnsValue, bitPos + 1) && p2PawnMoveStates[(bitPos + 1) % 8] == 2)
		{
			pawnMoves |= Bitboard(SetBitPos(bitPos + sidesAndDeltas[p1Side][5]));
		}
		return pawnMoves;
	}

	Bitboard GetKnightMoves(Bitboard& bitboard, Game& p1, Game& p2)
	{
		int bitPos = FindBitPos(bitboard);
		Bitboard knightMoves;
		int p1BoardValue = p1.GetBoard().GetValue();
		std::vector<int> bitDeltas{ 10, 6, -6, -10, 17, 15, -15, -17 };
		bool dir = true;
		for (int d : bitDeltas)
		{
			if (IsNewBitPosInBounds(bitPos + d, bitPos, dir) && !IsSquareOccupied(p1BoardValue, bitPos + d))
			{
				knightMoves |= Bitboard(SetBitPos(bitPos + d));
			}
			dir = !dir;
		}
		return knightMoves;
	}

	Bitboard GetBishopMoves(Bitboard& bitboard, Game& p1, Game& p2)
	{
		int bitPos = FindBitPos(bitboard);
		Bitboard bishopMoves;
		U64 p1BoardValue = p1.GetBoard().GetValue();
		U64 p2BoardValue = p2.GetBoard().GetValue();

		int upLeft = bitPos + 7;
		while (IsNewBitPosInBounds(upLeft, bitPos, LEFT))
		{
			if (IsSquareOccupied(p1BoardValue, upLeft))
			{
				break;
			}
			bishopMoves |= Bitboard(SetBitPos(upLeft));
			if (IsSquareOccupied(p2BoardValue, upLeft))
			{
				break;
			}
			upLeft += 7;
		}
		int upRight = bitPos + 9;
		while (IsNewBitPosInBounds(upRight, bitPos, RIGHT))
		{
			if (IsSquareOccupied(p1BoardValue, upRight))
			{
				break;
			}
			bishopMoves |= Bitboard(SetBitPos(upRight));
			if (IsSquareOccupied(p2BoardValue, upRight))
			{
				break;
			}
			upRight += 9;
		}
		int downLeft = bitPos + -9;
		while (IsNewBitPosInBounds(downLeft, bitPos, LEFT))
		{
			if (IsSquareOccupied(p1BoardValue, downLeft))
			{
				break;
			}
			bishopMoves |= Bitboard(SetBitPos(downLeft));
			if (IsSquareOccupied(p2BoardValue, downLeft))
			{
				break;
			}
			downLeft += -9;
		}
		int downRight = bitPos + -7;
		while (IsNewBitPosInBounds(downRight, bitPos, RIGHT))
		{
			if (IsSquareOccupied(p1BoardValue, downRight))
			{
				break;
			}
			bishopMoves |= Bitboard(SetBitPos(downRight));
			if (IsSquareOccupied(p2BoardValue, downRight))
			{
				break;
			}
			downRight += -7;
		}
		return bishopMoves;
	}

	Bitboard GetRookMoves(Bitboard& bitboard, Game& p1, Game& p2)
	{
		int bitPos = FindBitPos(bitboard);
		Bitboard rookMoves;
		U64 p1BoardValue = p1.GetBoard().GetValue();
		U64 p2BoardValue = p2.GetBoard().GetValue();

		int up = bitPos + 8;
		while (IsNewBitPosInBounds(up, bitPos, MIDDLE))
		{
			if (IsSquareOccupied(p1BoardValue, up))
			{
				break;
			}
			rookMoves |= Bitboard(SetBitPos(up));
			if (IsSquareOccupied(p2BoardValue, up))
			{
				break;
			}
			up += 8;
		}
		int down = bitPos + -8;
		while (IsNewBitPosInBounds(down, bitPos, MIDDLE))
		{
			if (IsSquareOccupied(p1BoardValue, down))
			{
				break;
			}
			rookMoves |= Bitboard(SetBitPos(down));
			if (IsSquareOccupied(p2BoardValue, down))
			{
				break;
			}
			down += -8;
		}
		int left = bitPos + -1;
		while (IsNewBitPosInBounds(left, bitPos, LEFT))
		{
			if (IsSquareOccupied(p1BoardValue, left))
			{
				break;
			}
			rookMoves |= Bitboard(SetBitPos(left));
			if (IsSquareOccupied(p2BoardValue, left))
			{
				break;
			}
			left += -1;
		}
		int right = bitPos + 1;
		while (IsNewBitPosInBounds(right, bitPos, RIGHT))
		{
			if (IsSquareOccupied(p1BoardValue, right))
			{
				break;
			}
			rookMoves |= Bitboard(SetBitPos(right));
			if (IsSquareOccupied(p2BoardValue, right))
			{
				break;
			}
			right += 1;
		}
		return rookMoves;
	}

	Bitboard GetQueenMoves(Bitboard& bitboard, Game& p1, Game& p2)
	{
		return GetBishopMoves(bitboard, p1, p2) | GetRookMoves(bitboard, p1, p2);
	}

	Bitboard GetKingMoves(Bitboard& bitboard, Game& p1, Game& p2)
	{
		int bitPos = FindBitPos(bitboard);
		Bitboard kingMoves;
		U64 p1BoardValue = p1.GetBoard().GetValue();
		U64 p2BoardValue = p2.GetBoard().GetValue();

		int leftDeltas[3] = { 7, -1, -9 };
		for (int d : leftDeltas)
		{
			if (IsNewBitPosInBounds(bitPos + d, bitPos, LEFT) && !IsSquareOccupied(p1BoardValue, bitPos + d) && !WillKingBeInCheck(bitPos + d, p1, p2))
			{
				kingMoves |= Bitboard(SetBitPos(bitPos + d));
			}
		}
		int middleDeltas[2] = { -8, 8 };
		for (int d : middleDeltas)
		{
			if (IsNewBitPosInBounds(bitPos + d, bitPos, MIDDLE) && !IsSquareOccupied(p1BoardValue, bitPos + d) && !WillKingBeInCheck(bitPos + d, p1, p2))
			{
				kingMoves |= Bitboard(SetBitPos(bitPos + d));
			}
		}
		int rightDeltas[3] = { -7, 1, 9 };
		for (int d : rightDeltas)
		{
			if (IsNewBitPosInBounds(bitPos + d, bitPos, RIGHT) && !IsSquareOccupied(p1BoardValue, bitPos + d) && !WillKingBeInCheck(bitPos + d, p1, p2))
			{
				kingMoves |= Bitboard(SetBitPos(bitPos + d));
			}
		}
		// castle left
		if ((p1.CanCastle(LEFT)) && (!IsSquareOccupied(p1BoardValue | p2BoardValue, bitPos + -1) && !IsSquareOccupied(p1BoardValue | p2BoardValue, bitPos + -2)) && (!WillKingBeInCheck(bitPos + -1, p1, p2) && !WillKingBeInCheck(bitPos + -2, p1, p2)))
		{
			kingMoves |= Bitboard(SetBitPos(bitPos + -2));
		}
		// castle right
		if (p2.CanCastle(RIGHT) && (!IsSquareOccupied(p1BoardValue | p2BoardValue, bitPos + 1) && !IsSquareOccupied(p1BoardValue | p2BoardValue, bitPos + 2)) && (!WillKingBeInCheck(bitPos + 1, p1, p2) && !WillKingBeInCheck(bitPos + -2, p1, p2)))
		{
			kingMoves |= Bitboard(SetBitPos(bitPos + 2));
		}
		return kingMoves;
	}
}