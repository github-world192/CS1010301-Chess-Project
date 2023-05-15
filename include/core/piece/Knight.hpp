/**
 *  File: Knight.hpp
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/15 20:52:48
 *  Editor: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Update Date: 2023/05/15 20:57:35
 *  Description: Knight Piece
 */

#pragma once

#include "../player/TPlayer.hpp"
#include "IPiece.hpp"
#include "TPiece.hpp"

namespace Chess
{

    class Knight : IPiece
    {
    public:
        Knight(TPlayer owner)
        {
            this->_type = TPiece::kKnight;
            this->_owner = owner;
        }
    };

}