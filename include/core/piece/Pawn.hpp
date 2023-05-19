/**
 *  File: Pawn.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/10 00:35:48
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/20 02:04:26
 *  Description: Pawn Piece Class
 */

#pragma once

#include "../player/TPlayer.hpp"
#include "IPiece.hpp"
#include "TPiece.hpp"

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

        Pawn(const Pawn &pawn)
        {
            this->_type = pawn._type;
            this->_owner = pawn._owner;
            this->_killed = pawn._killed;
            this->_moved = pawn._moved;
        }

        Pawn(const IPiece *piece)
        {
            this->_type = piece->type();
            this->_owner = piece->getOwner();
            this->_killed = piece->getKilled();
            this->_moved = piece->getMoved();
        }
    };

}