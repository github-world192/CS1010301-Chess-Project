/**
 *  File: King.hpp
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/15 20:52:48
 *  Editor: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Update Date: 2023/05/16 03:25:38
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
    };

}