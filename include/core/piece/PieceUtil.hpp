/**
 *  File: PieceUtil.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/10 23:04:32
 *  Editor: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Update Date: 2023/05/16 17:26:37
 *  Description: Piece Utility
 */

#pragma once

#include "TPiece.hpp"

#include <string>

namespace Chess
{

    class PieceUtil
    {
    public:
        static inline std::string typeToString(TPiece type)
        {
            switch ( type )
            {
            case TPiece::kBishop:
                return "bishop";
            case TPiece::kKing:
                return "king";
            case TPiece::kKnight:
                return "knight";
            case TPiece::kPawn:
                return "pawn";
            case TPiece::kQueen:
                return "queen";
            case TPiece::kRook:
                return "rook";
            }
            return "undefined";
        }
    };

}