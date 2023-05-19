/**
 *  File: Rook.hpp
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/10 22:57:30
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/20 02:06:27
 *  Description: Piece Type definition
 */

#pragma once

#include "../player/TPlayer.hpp"
#include "IPiece.hpp"
#include "TPiece.hpp"

namespace Chess
{

    class Rook : public IPiece
    {
    public:
        Rook(TPlayer owner)
        {
            this->_type = TPiece::kRook;
            this->_owner = owner;
        }

        Rook(const Rook &rook)
        {
            this->_type = rook._type;
            this->_owner = rook._owner;
            this->_killed = rook._killed;
            this->_moved = rook._moved;
        }

        Rook(const IPiece *piece)
        {
            this->_type = piece->type();
            this->_owner = piece->getOwner();
            this->_killed = piece->getKilled();
            this->_moved = piece->getMoved();
        }
    };

}
