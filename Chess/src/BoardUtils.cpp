#include "BoardUtils.h"

namespace BoardUtils {
	std::string GetBinRepr(Bitboard& bitboard)
	{
		uint64_t value = bitboard.GetValue();
		std::string result;

		for (int rank = 7; rank >= 0; rank--)
		{
			for (int file = 0; file < 8; file++)
			{
				int square = rank * 8 + file;
				uint64_t mask = 1ULL << square;

				result.push_back((value & mask) ? '1' : '0');
				result.push_back(' ');
			}
			result += "\n";
		}

		return result;
	}

	std::string GetHexRepr(Bitboard& bitboard)
	{
		std::stringstream stream;
		stream << "0x" << std::hex << std::setw(16) << std::setfill('0') << bitboard.GetValue() << std::dec;
		return stream.str();
	}

	std::vector<std::string> GetNotationsFromBitboard(Bitboard& bitboard)
	{
		uint64_t value = bitboard.GetValue();
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
		uint64_t value = bitboard.GetValue();
		for (int pos = 0; pos < 63; pos++)
		{
			if ((value >> pos) & 1)
			{
				return pos;
			}
		}
		return -1;
	}

	uint64_t SetBitPos(int rank, int file)
	{
		return 1ULL << (rank * 8 + file);
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

	Bitboard GetKnightMoves(Bitboard& bitboard)
	{
		int bitPos = FindBitPos(bitboard);
		Bitboard knightMoves(0);
		std::vector<int> bitDeltas{ 10, 6, -6, -10, 17, 15, -15, -17 };
		bool dir = true;
		for (int d : bitDeltas)
		{
			if (IsNewBitPosInBounds(bitPos + d, bitPos, dir))
			{
				knightMoves |= Bitboard(1ULL << (bitPos + d));
			}
			dir = !dir;
		}
		return knightMoves;
	}

	Bitboard GetBishopMoves(Bitboard& bitboard)
	{
		int bitPos = FindBitPos(bitboard);
		Bitboard bishopMoves(0);

		int upLeft = bitPos + 7;
		while (IsNewBitPosInBounds(upLeft, bitPos, 0))
		{
			bishopMoves |= Bitboard(1ULL << upLeft);
			upLeft += 7;
		}
		int upRight = bitPos + 9;
		while (IsNewBitPosInBounds(upRight, bitPos, 1))
		{
			bishopMoves |= Bitboard(1ULL << upRight);
			upRight += 9;
		}
		int downLeft = bitPos + -9;
		while (IsNewBitPosInBounds(downLeft, bitPos, 0))
		{
			bishopMoves |= Bitboard(1ULL << downLeft);
			downLeft += -9;
		}
		int downRight = bitPos + -7;
		while (IsNewBitPosInBounds(downRight, bitPos, 1))
		{
			bishopMoves |= Bitboard(1ULL << downRight);
			downRight += -7;
		}
		return bishopMoves;
	}

	Bitboard GetRookMoves(Bitboard& bitboard)
	{
		int bitPos = FindBitPos(bitboard);
		Bitboard rookMoves(0);

		int up = bitPos + 8;
		while (IsNewBitPosInBounds(up, bitPos, 0))
		{
			rookMoves |= Bitboard(1ULL << up);
			up += 8;
		}
		int down = bitPos + 8;
		while (IsNewBitPosInBounds(down, bitPos, 0))
		{
			rookMoves |= Bitboard(1ULL << down);
			down -= 8;
		}
		int left = bitPos - 1;
		while (IsNewBitPosInBounds(left, bitPos, 0))
		{
			rookMoves |= Bitboard(1ULL << left);
			left -= 1;
		}
		int right = bitPos + 1;
		while (IsNewBitPosInBounds(right, bitPos, 1))
		{
			rookMoves |= Bitboard(1ULL << right);
			right += 1;
		}
		return rookMoves;
	}

	Bitboard GetQueenMoves(Bitboard& bitboard)
	{
		return GetBishopMoves(bitboard) | GetRookMoves(bitboard);
	}
}
