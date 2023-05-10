/**
 *  File: Board.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/11 01:46:16
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/11 03:05:35
 *  Description: Board Class
 */

#include "core/Board.hpp"

using namespace Chess;

bool Board::initialize()
{
    // Generate default board
    for ( size_t i = 0; i < this->_width; ++i )
        this->_board[1][i] = new Pawn(TPlayer::kBlack);

    for ( size_t i = 0; i < this->_width; ++i )
        this->_board[6][i] = new Pawn(TPlayer::kWhite);

    return true;
}

void Board::clear()
{
    this->_free();
}

void Board::moveWithoutCheck(const Position &from, const Position &to)
{
    // If fromPosition has no piece
    if ( (*this)(from) == nullptr )
        return;

    // If toPosition has piece
    if ( (*this)(to) != nullptr )
        _removePiece(to);

    // Set toPosition piece to fromPosition piece
    _setPiece(to, (*this)(from));

    // Set fromPosition no piece
    this->_board[from.y][from.x] = nullptr;
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