#include <vector>
#include <string>
#include <iostream>

#include "Bitboard.h"
#include "BoardUtils.h"
#include "Constants.h"
#include "Game.h"

int main()
{
  Game p1(WHITE);
  Game p2(BLACK);

  Bitboard p1Board = p1.GetBoard();
  Bitboard p2Board = p2.GetBoard();
  Bitboard gameBoard = p1Board | p2Board;

  std::cout << BoardUtils::PrintBoard(p1Board) << std::endl;
  std::cout << BoardUtils::PrintBoard(p2Board) << std::endl;
  std::cout << BoardUtils::PrintBoard(gameBoard) << std::endl;

  Bitboard test(BoardUtils::SetBitPos(d4));
  Bitboard testMoves = BoardUtils::GetKingMoves(test, p1, p2);
  std::cout << BoardUtils::PrintBoard(testMoves) << std::endl;
}
