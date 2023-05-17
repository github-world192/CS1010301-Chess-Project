/**
 *  File: PieceUtil.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/10 23:04:32
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/17 14:40:16
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

        static inline int typeToInt(TPiece type)
        {
            switch ( type )
            {
            case TPiece::kBishop:
                return 0;
            case TPiece::kKing:
                return 1;
            case TPiece::kKnight:
                return 2;
            case TPiece::kPawn:
                return 3;
            case TPiece::kQueen:
                return 4;
            case TPiece::kRook:
                return 5;
            }
            return -1;
        }

        static inline TPiece intToType(int n)
        {
            switch ( n )
            {
            case 0:
                return TPiece::kBishop;
            case 1:
                return TPiece::kKing;
            case 2:
                return TPiece::kKnight;
            case 3:
                return TPiece::kPawn;
            case 4:
                return TPiece::kQueen;
            case 5:
                return TPiece::kRook;

            default:
            break;
            }
            return TPiece::kPawn;
        }
    };

}