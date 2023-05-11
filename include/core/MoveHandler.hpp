/**
 *  File: Movehandler.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/11 16:29:30
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/11 17:41:07
 *  Description: Move handler
 */

#pragma once

#include "Board.hpp"
#include "Position.hpp"
#include "piece/IPiece.hpp"
#include "piece/Pawn.hpp"

#include <vector>

namespace Chess
{

    class MoveHandler
    {
    public:
        static bool isMoveValid(Board &board, const Move &move);

        static std::vector<Position> getMovablePositions(Board &board,
                                                         const Position &pos);

    private:
        static std::vector<Position> _toRealPos(
            Board &board, const Position &pos,
            const std::vector<Position> &poss);

        static std::vector<Position> _getPawnMovableRelativePos(
            Board &board, const Pawn &piece);

        static std::vector<Position> _getPawnKillableRelativePos(
            Board &board, const Pawn &piece);
    };

}