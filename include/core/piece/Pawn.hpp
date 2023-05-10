/**
 *  File: Pawn.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/10 00:35:48
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/10 23:00:12
 *  Description: Pawn Piece Class
 */

#pragma once

#include "IPiece.hpp"

namespace Chess
{

    class Pawn : public IPiece
    {
    public:
        Pawn(TPlayer owner)
        {
            this->_type = TPiece::kPawn;
            this->_owner = owner;
        }

    public:
        bool isPositionValid(const Position &pos) const
        {
            return true;
        }
    };

}