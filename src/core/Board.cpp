/**
 *  File: Board.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/11 01:46:16
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/17 22:36:54
 *  Description: Board Class
 */

#include "core/Board.hpp"
#include "core/MoveHandler.hpp"

using namespace Chess;

Board::Board(const Board &board)
{
    this->_width = board._width;
    this->_height = board._height;

    this->_board.resize(board._board.size());
    size_t i = 0;
    for ( const auto &it : board._board )
    {
        this->_board[i].resize(board._board[i].size(), nullptr);
        size_t j = 0;

        for ( const auto &jt : it )
        {
            IPiece *piece = nullptr;

            // If piece exist, create a copy
            if ( board._board[i][j] != nullptr )
            {
                switch ( jt->type() )
                {
                case TPiece::kBishop:
                {
                    Bishop &bishop = (Bishop &)piece;
                    piece = new Bishop(bishop);
                    break;
                }
                case TPiece::kKing:
                {
                    King &king = (King &)piece;
                    piece = new King(king);
                    break;
                }
                case TPiece::kKnight:
                {
                    Knight &knight = (Knight &)piece;
                    piece = new Knight(knight);
                    break;
                }
                case TPiece::kPawn:
                {
                    Pawn &pawn = (Pawn &)piece;
                    piece = new Pawn(pawn);
                    break;
                }
                case TPiece::kQueen:
                {
                    Queen &queen = (Queen &)piece;
                    piece = new Queen(queen);
                    break;
                }
                case TPiece::kRook:
                {
                    Rook &rook = (Rook &)piece;
                    piece = new Rook(rook);
                    break;
                }
                }
            }

            this->_board[i][j] = piece;
            ++j;
        }
        ++i;
    }
}

void Board::loadDefaultBoard()
{
    // Clear board first
    this->clear();

    // Generate default board
    // Generate pawn position
    this->_board[1][0] = new Pawn(TPlayer::kBlack);
    this->_board[1][1] = new Pawn(TPlayer::kBlack);
    this->_board[1][2] = new Pawn(TPlayer::kBlack);
    this->_board[1][3] = new Pawn(TPlayer::kBlack);
    this->_board[1][4] = new Pawn(TPlayer::kBlack);
    this->_board[1][5] = new Pawn(TPlayer::kBlack);
    this->_board[1][6] = new Pawn(TPlayer::kBlack);
    this->_board[1][7] = new Pawn(TPlayer::kBlack);
    this->_board[6][0] = new Pawn(TPlayer::kWhite);
    this->_board[6][1] = new Pawn(TPlayer::kWhite);
    this->_board[6][2] = new Pawn(TPlayer::kWhite);
    this->_board[6][3] = new Pawn(TPlayer::kWhite);
    this->_board[6][4] = new Pawn(TPlayer::kWhite);
    this->_board[6][5] = new Pawn(TPlayer::kWhite);
    this->_board[6][6] = new Pawn(TPlayer::kWhite);
    this->_board[6][7] = new Pawn(TPlayer::kWhite);

    // Generate king position
    this->_board[0][4] = new King(TPlayer::kBlack);
    this->_board[7][4] = new King(TPlayer::kWhite);

    // Generate queen position
    this->_board[0][3] = new Queen(TPlayer::kBlack);
    this->_board[7][3] = new Queen(TPlayer::kWhite);

    // Generate rook position
    this->_board[0][0] = new Rook(TPlayer::kBlack);
    this->_board[0][7] = new Rook(TPlayer::kBlack);
    this->_board[7][0] = new Rook(TPlayer::kWhite);
    this->_board[7][7] = new Rook(TPlayer::kWhite);

    // Generate bishop position
    this->_board[0][2] = new Bishop(TPlayer::kBlack);
    this->_board[0][5] = new Bishop(TPlayer::kBlack);
    this->_board[7][2] = new Bishop(TPlayer::kWhite);
    this->_board[7][5] = new Bishop(TPlayer::kWhite);

    // Generate knight position
    this->_board[0][1] = new Knight(TPlayer::kBlack);
    this->_board[0][6] = new Knight(TPlayer::kBlack);
    this->_board[7][1] = new Knight(TPlayer::kWhite);
    this->_board[7][6] = new Knight(TPlayer::kWhite);
}

void Board::clear()
{
    this->_free();
}

bool Board::move(const Position &from, const Position &to)
{
    // If positions invalid
    if ( !(this->isPositionValid(from)) || !(this->isPositionValid(to)) )
        return false;

    // If fromPosition no piece
    if ( (*this)(from) == nullptr )
        return false;

    this->_moveWithoutCheck(from, to);

    return true;
}

bool Board::promoting(const Position &pos, TPiece type)
{
    if ( !(this->isPositionValid(pos)) )
        return false;

    if ( !(this->isPositionPiece(pos)) )
        return false;

    if ( (*this)(pos)->type() != TPiece::kPawn )
        return false;

    TPlayer owner = (*this)(pos)->getOwner();
    switch ( type )
    {
    case TPiece::kQueen:
    {
        this->_removePiece(pos);
        this->_setPiece(pos, new Queen(owner));
        return true;
    }
    break;

    case TPiece::kBishop:
    {
        this->_removePiece(pos);
        this->_setPiece(pos, new Bishop(owner));
        return true;
    }
    break;

    case TPiece::kKnight:
    {
        this->_removePiece(pos);
        this->_setPiece(pos, new Knight(owner));
        return true;
    }
    break;

    case TPiece::kRook:
    {
        this->_removePiece(pos);
        this->_setPiece(pos, new Rook(owner));
        return true;
    }
    break;

    default:
        break;
    }

    return false;
}

std::vector<const IPiece *> Board::getPiecesByOwner(TPlayer player) const
{
    std::vector<const IPiece *> r;
    for ( const auto i : this->_board )
    {
        for ( const auto j : i )
        {
            if ( j == nullptr )
                continue;

            // If piece owner is player, append to output
            if ( j->getOwner() == player )
                r.push_back(j);
        }
    }
    return r;
}

std::vector<Position> Board::findPiecesPos(TPlayer owner) const
{
    std::vector<Position> r;
    Position pos;
    for ( pos.y = 0; pos.y < this->_board.size(); ++pos.y )
    {
        for ( pos.x = 0; pos.x < this->_board[pos.y].size(); ++pos.x )
        {
            if ( !(this->isPositionPiece(pos)) )
                continue;

            if ( (*this)(pos)->getOwner() == owner )
                r.push_back(pos);
        }
    }
    return r;
}

std::vector<Position> Board::findPiecesPos(TPlayer owner, TPiece type) const
{
    std::vector<Position> r;
    Position pos;
    for ( pos.y = 0; pos.y < this->_board.size(); ++pos.y )
    {
        for ( pos.x = 0; pos.x < this->_board[pos.y].size(); ++pos.x )
        {
            if ( !(this->isPositionPiece(pos)) )
                continue;

            if ( (*this)(pos)->getOwner() == owner &&
                 (*this)(pos)->type() == type )
                r.push_back(pos);
        }
    }
    return r;
}

std::vector<Position> Board::findPiecesPos(TPiece type) const
{
    std::vector<Position> r;
    Position pos;
    for ( pos.y = 0; pos.y < this->_board.size(); ++pos.y )
    {
        for ( pos.x = 0; pos.x < this->_board[pos.y].size(); ++pos.x )
        {
            if ( !(this->isPositionPiece(pos)) )
                continue;

            if ( (*this)(pos)->type() == type )
                r.push_back(pos);
        }
    }
    return r;
}

std::vector<Position> Board::findPiecesPosExcept(
    TPlayer owner, TPiece exceptType) const
{
    std::vector<Position> r;
    Position pos;
    for ( pos.y = 0; pos.y < this->_board.size(); ++pos.y )
    {
        for ( pos.x = 0; pos.x < this->_board[pos.y].size(); ++pos.x )
        {
            if ( !(this->isPositionPiece(pos)) )
                continue;

            if ( (*this)(pos)->getOwner() == owner &&
                 (*this)(pos)->type() != exceptType )
                r.push_back(pos);
        }
    }
    return r;
}

bool Board::_setPiece(const Position &pos, IPiece *piece)
{
    // If target position invalid
    if ( !(this->isPositionValid(pos)) )
        return false;

    // If there is already a piece at the target position, delete it
    if ( (*this)(pos) != nullptr )
        delete (*this)(pos);

    this->_board[pos.y][pos.x] = piece;

    return true;
}

bool Board::_removePiece(const Position &pos)
{
    // If target position invalid
    if ( !(this->isPositionValid(pos)) )
        return false;

    // If there is already a piece at the target position
    if ( (*this)(pos) != nullptr )
        return false;

    delete (*this)(pos);

    return true;
}

void Board::_moveWithoutCheck(const Position &from, const Position &to)
{
    // If fromPosition has no piece
    if ( (*this)(from) == nullptr )
        return;

    // If toPosition has piece
    if ( (*this)(to) != nullptr )
        _removePiece(to);

    // Set toPosition piece to fromPosition piece
    _setPiece(to, (*this)(from));
    (*this)(to)->setMoved(true);

    // Set fromPosition no piece
    this->_board[from.y][from.x] = nullptr;
}

void Board::_free()
{
    for ( size_t i = 0; i < this->_board.size(); ++i )
    {
        for ( size_t j = 0; j < this->_board[i].size(); ++j )
        {
            IPiece *piece = this->_board[i][j];
            // Delete all pieces
            if ( piece != nullptr )
            {
                delete piece;
                this->_board[i][j] = nullptr;
            }
        }
    }
}