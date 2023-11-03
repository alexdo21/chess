#include <vector>
#include <string>
#include <iostream>

#include "Bitboard.h"
#include "BoardUtils.h"
#include "Constants.h"
#include "Game.h"

int main()
{
	//Game p1(WHITE);
	//Game p2(BLACK);

	//Bitboard p1Board = p1.GetBoard();
	//Bitboard p2Board = p2.GetBoard();
	//Bitboard gameBoard = p1Board | p2Board;

	//std::cout << BoardUtils::PrintBoard(p1Board) << std::endl;
	//std::cout << BoardUtils::PrintBoard(p2Board) << std::endl;
	//std::cout << BoardUtils::PrintBoard(gameBoard) << std::endl;

	//Bitboard test(BoardUtils::SetBitss(d4));
	//Bitboard testMoves = BoardUtils::GetKingMoves(test, p1, p2);
	//std::cout << BoardUtils::PrintBoard(testMoves) << std::endl;

	//Game p1;
	//Game p2;
	//p1.SetSide(WHITE);
	//p2.SetSide(BLACK);

	//p1.SetPawns(BoardUtils::SetBits({ d2, e2, f2 }));
	//p2.SetRooks(BoardUtils::SetBits(e7));
	//p2.SetPawns(BoardUtils::SetBits({ b5, c2, f5, e2 }));
	//p2.SetKnights(BoardUtils::SetBits(d3));

	//Bitboard test(BoardUtils::SetBits(e2));
	//p1.SetPawnMoveState(d, 1);
	//p2.SetPawnMoveState(c, 2);

	//Bitboard testMoves = BoardUtils::GetKingMoves(test, p1, p2);
	//std::cout << BoardUtils::PrintBoard(testMoves) << std::endl;

	Game p1(WHITE);
	Game p2(BLACK);

	int turn = WHITE;
	while (1)
	{
		p1, p2 = turn == WHITE ? (p1, p2) : (p2, p1);
		Bitboard checkers = BoardUtils::IsKingInCheck(BoardUtils::FindBitPos(p1.GetKing()), p1, p2);
		Bitboard captureMask(MAX_VALUE);
		Bitboard pushMask(MAX_VALUE);
		if (checkers)
		{
			p1.ToggleIsKingInCheck();
			int numCheckers = checkers.GetPopCount();
			if (numCheckers > 1)
			{
				Bitboard kingMoves = BoardUtils::GetKingMoves(p1.GetKing(), p1, p2);
				if (!kingMoves)
				{
					// checkmate
					break;
				}
				// make king move to evade or capture checking piece				
			}
			else
			{
				captureMask = checkers;
				if ((captureMask & p2.GetBishops()) || (captureMask & p2.GetRooks()) || (captureMask & p2.GetQueen()))
				{
					// calculate squares between p1 King and checking square
				}
				else
				{
					pushMask.SetValue(0);
				}
			}
		}
		// calculate moves filtered by capture and push masks
		// calculate pins
		// calculate en passant pins
		// make move

		p1.IncrementMoves();
		turn = ~turn;
	}
}
