/**
 *  File: Spot.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/10 00:11:05
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/10 01:32:30
 *  Description: Spot Class
 */

#pragma once

#include "Position.hpp"
#include "piece/IPiece.hpp"

namespace Chess
{

    class Spot
    {
    private:
        IPiece *_piece;
        Position _pos;

    public:
        Spot(IPiece *piece, Position pos) : _piece(piece), _pos(pos) {}

    public:
        inline IPiece *piece() { return this->_piece; }
        inline const Position &getPosition() const { return this->_pos; }
        inline void setPosition(const Position &pos) { this->_pos = pos; }
    };

}