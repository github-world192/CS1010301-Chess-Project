/**
 *  File: Bishop.hpp
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/15 20:52:48
 *  Editor: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Update Date: 2023/05/16 02:58:07
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
    };

}