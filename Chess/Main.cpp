#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <iostream>

struct Piece
{
    enum Color
    {
        EMPTY, WHITE, BLACK
    };
    enum Type
    {
        EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
    };
    Piece::Color color;
    Piece::Type type;
};

void InitBoard(std::vector<std::vector<Piece>>& board)
{
    // white pieces
    board[0][0] = Piece{ Piece::Color::WHITE, Piece::Type::ROOK };
    board[0][1] = Piece{ Piece::Color::WHITE, Piece::Type::KNIGHT };
    board[0][2] = Piece{ Piece::Color::WHITE, Piece::Type::BISHOP };
    board[0][3] = Piece{ Piece::Color::WHITE, Piece::Type::QUEEN };
    board[0][4] = Piece{ Piece::Color::WHITE, Piece::Type::KING };
    board[0][5] = Piece{ Piece::Color::WHITE, Piece::Type::BISHOP };
    board[0][6] = Piece{ Piece::Color::WHITE, Piece::Type::KNIGHT };
    board[0][7] = Piece{ Piece::Color::WHITE, Piece::Type::ROOK };

    for (int j = 0; j < 8; j++)
    {
        board[1][j] = Piece{ Piece::Color::WHITE, Piece::Type::PAWN };
    }

    // black pieces
    board[7][0] = Piece{ Piece::Color::BLACK, Piece::Type::ROOK };
    board[7][1] = Piece{ Piece::Color::BLACK, Piece::Type::KNIGHT };
    board[7][2] = Piece{ Piece::Color::BLACK, Piece::Type::BISHOP };
    board[7][3] = Piece{ Piece::Color::BLACK, Piece::Type::QUEEN };
    board[7][4] = Piece{ Piece::Color::BLACK, Piece::Type::KING };
    board[7][5] = Piece{ Piece::Color::BLACK, Piece::Type::BISHOP };
    board[7][6] = Piece{ Piece::Color::BLACK, Piece::Type::KNIGHT };
    board[7][7] = Piece{ Piece::Color::BLACK, Piece::Type::ROOK };
    
    for (int j = 0; j < 8; j++)
    {
        board[6][j] = Piece{ Piece::Color::BLACK, Piece::Type::PAWN };
    }
}

std::string GetNotationFromCoord(int x, int y)
{
    std::string rank = std::to_string(x + 1);
    std::string file(1, char(y + 97));
    return file + rank;
}

std::pair<int, int> GetCoordFromNotation(std::string position)
{
    return { position[0] - 'a', position[1] - '0' - 1 };
}

bool IsInBounds(int x, int y)
{
    return (0 <= x && x < 8) && (0 <= y && y < 8);
}

struct Check
{
    bool status;
    std::string position;
};

Check IsKingInCheck(std::vector<std::vector<Piece>>& board, std::string position)
{
    const auto& [x, y] = GetCoordFromNotation(position);
    Piece::Color opponentColor = board[x][y].color == Piece::Color::WHITE ? Piece::Color::BLACK : Piece::Color::WHITE;
    
    // pawn check
    std::vector<int> pawnDirections{ -1, 1 };
    int dx = opponentColor == Piece::Color::BLACK ? 1 : -1;
    for (int dy : pawnDirections)
    {
        if (IsInBounds(x + dx, y + dy) && board[x + dx][y + dy].type == Piece::Type::PAWN)
        {
            return { true, GetNotationFromCoord(x + dx, y + dy) };
        }
    }

    // knight check
    std::vector<std::pair<int, int>> knightDirections
    {
        {-1, -2}, {1, -2}, {-1, 2}, {1, 2}, {-2, -1}, {-2, 1}, {2, -1}, {2, 1}
    };
    for (auto& [dx, dy] : knightDirections)
    {
        if (IsInBounds(x + dx, y + dy) && board[x + dx][y + dy].type == Piece::Type::KNIGHT && board[x + dx][y + dy].color == opponentColor)
        {
            return { true, GetNotationFromCoord(x + dx, y + dy) };
        }
    }

    // upper left diagonal check
    int currX = x, currY = y;
    while (IsInBounds(currX, currY) && board[currX][currY].color != opponentColor)
    {
        if (board[currX][currY].type == Piece::Type::BISHOP && board[currX][currY].type == Piece::Type::QUEEN)
        {
            return { true, GetNotationFromCoord(currX, currY) };
        }
        currX--, currY--;
    }

    // upper right diagonal check
    int currX = x, currY = y;
    while (IsInBounds(currX, currY) && board[currX][currY].color != opponentColor)
    {
        if (board[currX][currY].type == Piece::Type::BISHOP && board[currX][currY].type == Piece::Type::QUEEN)
        {
            return { true, GetNotationFromCoord(currX, currY) };
        }
        currX--, currY++;
    }

    // lower left diagonal check
    int currX = x, currY = y;
    while (IsInBounds(currX, currY) && board[currX][currY].color != opponentColor)
    {
        if (board[currX][currY].type == Piece::Type::BISHOP && board[currX][currY].type == Piece::Type::QUEEN)
        {
            return { true, GetNotationFromCoord(currX, currY) };
        }
        currX++, currY--;
    }

    // lower right diagonal check
    int currX = x, currY = y;
    while (IsInBounds(currX, currY) && board[currX][currY].color != opponentColor)
    {
        if (board[currX][currY].type == Piece::Type::BISHOP && board[currX][currY].type == Piece::Type::QUEEN)
        {
            return { true, GetNotationFromCoord(currX, currY) };
        }
        currX++, currY++;
    }

    // up
    int currX = x;
    while (IsInBounds(currX, y) && board[currX][y].color != opponentColor)
    {
        if (board[currX][y].type == Piece::Type::ROOK && board[currX][y].type == Piece::Type::QUEEN)
        {
            return { true, GetNotationFromCoord(currX, y) };
        }
        currX--;
    }

    // right
    int currY = y;
    while (IsInBounds(x, currY) && board[x][currY].color != opponentColor)
    {
        if (board[x][currY].type == Piece::Type::ROOK && board[x][currY].type == Piece::Type::QUEEN)
        {
            return { true, GetNotationFromCoord(x, currY) };
        }
        currY++;
    }

    // down
    int currX = x;
    while (IsInBounds(currX, y) && board[currX][y].color != opponentColor)
    {
        if (board[currX][y].type == Piece::Type::ROOK && board[currX][y].type == Piece::Type::QUEEN)
        {
            return { true, GetNotationFromCoord(currX, y) };
        }
        currX++;
    }

    // left
    int currY = y;
    while (IsInBounds(x, currY) && board[x][currY].color != opponentColor)
    {
        if (board[x][currY].type == Piece::Type::ROOK && board[x][currY].type == Piece::Type::QUEEN)
        {
            return { true, GetNotationFromCoord(x, currY) };
        }
        currY--;
    }

    return { false, nullptr };
}

std::vector<std::string> GetMovesInCheck(std::vector<std::vector<Piece>>& board, std::string position, std::string kingPosition, std::string checkPosition)
{
    std::vector<std::string> result;

    // only king moves
    if (position == kingPosition)
    {
        const auto& [checkX, checkY] = GetCoordFromNotation(checkPosition);
        const auto& [kingX, kingY] = GetCoordFromNotation(kingPosition);

        std::unordered_set<std::string> possibleKingMoves;
        std::vector<std::pair<int, int>> possibleKingMoveDirections
        {
            {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
        };

        for (auto& [dx, dy] : possibleKingMoveDirections)
        {
            if (IsInBounds(kingX + dx, kingY + dy) && board[kingX + dx][kingX + dy].type == Piece::Type::EMPTY)
            {
                possibleKingMoves.insert(GetNotationFromCoord(kingX + dx, kingY + dy));
            }
        }

        // check bishop
        if (board[checkX][checkY].type == Piece::Type::BISHOP)
        {
            // positive slope
            if ((kingX + kingY) == (checkX + checkY))
            {
                possibleKingMoves.erase(GetNotationFromCoord(kingX - 1, kingY + 1));
                possibleKingMoves.erase(GetNotationFromCoord(kingX + 1, kingY - 1));
            }

            // negative slope
            if ((kingY - kingX) == (checkY - checkX))
            {
                possibleKingMoves.erase(GetNotationFromCoord(kingX - 1, kingY - 1));
                possibleKingMoves.erase(GetNotationFromCoord(kingX + 1, kingY + 1));
            }
        }

        // check rook
        if (board[checkX][checkY].type == Piece::Type::ROOK)
        {
            // left-right
            if (kingX == checkX)
            {
                possibleKingMoves.erase(GetNotationFromCoord(kingX - 1, kingY));
                possibleKingMoves.erase(GetNotationFromCoord(kingX + 1, kingY));
            }

            // up-down
            if (kingY == checkY)
            {
                possibleKingMoves.erase(GetNotationFromCoord(kingX, kingY - 1));
                possibleKingMoves.erase(GetNotationFromCoord(kingX, kingY + 1));
            }
        }
    }
}

std::vector<std::string> GetMoves(std::vector<std::vector<Piece>>& board, std::string position)
{
    return {};
}

int main()
{
    std::vector<std::vector<Piece>> board(8, std::vector<Piece>(8, Piece{Piece::Color::EMPTY, Piece::Type::EMPTY}));
    InitBoard(board);

    while (1)
    {
        //int x, y;
        //std::cout << "Enter x: " << std::endl;
        //std::cin >> x;
        //std::cout << "Enter y: " << std::endl;
        //std::cin >> y;
        //std::cout << "FileRank is: " + GetNotationFromCoord(x, y) << std::endl;

        std::string fileRank;
        std::cout << "Enter fileRank: " << std::endl;
        std::cin >> fileRank;
        std::pair<int, int> position = GetCoordFromNotation(fileRank);
        std::cout << "Position is: (" + std::to_string(position.first) + ", " + std::to_string(position.second) + ")" << std::endl;
    }

    return 0;
}