/**
 *  File: Pawn.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/10 00:35:48
 *  Editor: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Update Date: 2023/05/15 21:21:28
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
    };

}