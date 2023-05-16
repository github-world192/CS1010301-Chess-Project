/**
 *  File: Board.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/11 01:46:16
 *  Editor: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Update Date: 2023/05/16 15:02:40
 *  Description: Board Class
 */

#include "core/Board.hpp"
#include "core/MoveHandler.hpp"

using namespace Chess;

bool Board::initialize()
{
    // Generate default board
    // Generate pawn position
    for ( size_t i = 0; i < this->_width; ++i )
        this->_board[1][i] = new Pawn(TPlayer::kBlack);

    for ( size_t i = 0; i < this->_width; ++i )
        this->_board[6][i] = new Pawn(TPlayer::kWhite);

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

    return true;
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
            }
        }
    }
}