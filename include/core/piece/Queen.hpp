/**
 *  File: Queen.hpp
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/15 20:52:48
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/20 02:06:08
 *  Description: Knight Piece
 */

#pragma once

#include "../player/TPlayer.hpp"
#include "IPiece.hpp"
#include "TPiece.hpp"

namespace Chess
{

    class Queen : public IPiece
    {
    public:
        Queen(TPlayer owner)
        {
            this->_type = TPiece::kQueen;
            this->_owner = owner;
        }

        Queen(const Queen &queen)
        {
            this->_type = queen._type;
            this->_owner = queen._owner;
            this->_killed = queen._killed;
            this->_moved = queen._moved;
        }

        Queen(const IPiece *piece)
        {
            this->_type = piece->type();
            this->_owner = piece->getOwner();
            this->_killed = piece->getKilled();
            this->_moved = piece->getMoved();
        }
    };

}