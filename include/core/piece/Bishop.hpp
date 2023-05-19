/**
 *  File: Bishop.hpp
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/15 20:52:48
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/20 02:02:26
 *  Description: Knight Piece
 */

#pragma once

#include "../player/TPlayer.hpp"
#include "IPiece.hpp"
#include "TPiece.hpp"

namespace Chess
{

    class Bishop : public IPiece
    {
    public:
        Bishop(TPlayer owner)
        {
            this->_type = TPiece::kBishop;
            this->_owner = owner;
        }

        Bishop(const Bishop &bishop)
        {
            this->_type = bishop._type;
            this->_owner = bishop._owner;
            this->_killed = bishop._killed;
            this->_moved = bishop._moved;
        }

        Bishop(const IPiece *piece)
        {
            this->_type = piece->type();
            this->_owner = piece->getOwner();
            this->_killed = piece->getKilled();
            this->_moved = piece->getMoved();
        }
    };

}