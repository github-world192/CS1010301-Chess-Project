/**
 *  File: King.hpp
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/15 20:52:48
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/20 02:03:31
 *  Description: Knight Piece
 */

#pragma once

#include "../player/TPlayer.hpp"
#include "IPiece.hpp"
#include "TPiece.hpp"

namespace Chess
{

    class King : public IPiece
    {
    public:
        King(TPlayer owner)
        {
            this->_type = TPiece::kKing;
            this->_owner = owner;
        }

        King(const King &king)
        {
            this->_type = king._type;
            this->_owner = king._owner;
            this->_killed = king._killed;
            this->_moved = king._moved;
        }

        King(const IPiece *piece)
        {
            this->_type = piece->type();
            this->_owner = piece->getOwner();
            this->_killed = piece->getKilled();
            this->_moved = piece->getMoved();
        }
    };

}