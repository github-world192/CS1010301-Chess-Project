/**
 *  File: Knight.hpp
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/15 20:52:48
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/20 02:03:53
 *  Description: Knight Piece
 */

#pragma once

#include "../player/TPlayer.hpp"
#include "IPiece.hpp"
#include "TPiece.hpp"

namespace Chess
{

    class Knight : public IPiece
    {
    public:
        Knight(TPlayer owner)
        {
            this->_type = TPiece::kKnight;
            this->_owner = owner;
        }

        Knight(const Knight &knight)
        {
            this->_type = knight._type;
            this->_owner = knight._owner;
            this->_killed = knight._killed;
            this->_moved = knight._moved;
        }

        Knight(const IPiece *piece)
        {
            this->_type = piece->type();
            this->_owner = piece->getOwner();
            this->_killed = piece->getKilled();
            this->_moved = piece->getMoved();
        }
    };

}