#include <vector>
#include <string>

struct Piece
{
    enum Color
    {
        NEUTRAL, WHITE, BLACK
    };
    enum Type
    {
        EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
    };
    Piece::Color color;
    Piece::Type type;
};

class Game
{
public:
    Game() : m_Board(8, std::vector<Piece>(8, Piece{ Piece::Color::NEUTRAL, Piece::Type::EMPTY })), m_IsWhiteKingInCheck(false), m_IsBlackKingInCheck(false)
    {
        InitBoard();
    }

private:
    std::vector<std::vector<Piece>> m_Board;
    bool m_IsWhiteKingInCheck;
    bool m_IsBlackKingInCheck;

    void InitBoard()
    {
        // white pieces
        m_Board[0][0] = Piece{ Piece::Color::WHITE, Piece::Type::ROOK };
        m_Board[0][1] = Piece{ Piece::Color::WHITE, Piece::Type::KNIGHT };
        m_Board[0][2] = Piece{ Piece::Color::WHITE, Piece::Type::BISHOP };
        m_Board[0][3] = Piece{ Piece::Color::WHITE, Piece::Type::QUEEN };
        m_Board[0][4] = Piece{ Piece::Color::WHITE, Piece::Type::KING };
        m_Board[0][5] = Piece{ Piece::Color::WHITE, Piece::Type::BISHOP };
        m_Board[0][6] = Piece{ Piece::Color::WHITE, Piece::Type::KNIGHT };
        m_Board[0][7] = Piece{ Piece::Color::WHITE, Piece::Type::ROOK };

        for (int j = 0; j < 8; j++)
        {
            m_Board[1][j] = Piece{ Piece::Color::WHITE, Piece::Type::PAWN };
        }

        // black pieces
        m_Board[7][0] = Piece{ Piece::Color::BLACK, Piece::Type::ROOK };
        m_Board[7][1] = Piece{ Piece::Color::BLACK, Piece::Type::KNIGHT };
        m_Board[7][2] = Piece{ Piece::Color::BLACK, Piece::Type::BISHOP };
        m_Board[7][3] = Piece{ Piece::Color::BLACK, Piece::Type::QUEEN };
        m_Board[7][4] = Piece{ Piece::Color::BLACK, Piece::Type::KING };
        m_Board[7][5] = Piece{ Piece::Color::BLACK, Piece::Type::BISHOP };
        m_Board[7][6] = Piece{ Piece::Color::BLACK, Piece::Type::KNIGHT };
        m_Board[7][7] = Piece{ Piece::Color::BLACK, Piece::Type::ROOK };

        for (int j = 0; j < 8; j++)
        {
            m_Board[6][j] = Piece{ Piece::Color::BLACK, Piece::Type::PAWN };
        }
    }

    std::vector<std::string> GetMovesForKing(std::vector<std::vector<Piece>>& board, std::string position)
    {
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
        return {};
    }
};