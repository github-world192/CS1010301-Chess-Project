/**
 *  File: Rook.hpp
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/10 22:57:30
 *  Editor: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Update Date: 2023/05/16 03:26:09
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
    };

}
