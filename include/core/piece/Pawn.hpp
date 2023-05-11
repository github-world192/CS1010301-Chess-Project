/**
 *  File: Pawn.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/10 00:35:48
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/11 17:04:21
 *  Description: Pawn Piece Class
 */

#pragma once

#include "../Move.hpp"
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
    };

}