/**
 *  File: Movehandler.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/11 16:29:30
 *  Editor: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Update Date: 2023/05/16 14:58:19
 *  Description: Move handler
 */

#pragma once

#include "Board.hpp"
#include "Move.hpp"
#include "Position.hpp"
#include "piece/Bishop.hpp"
#include "piece/IPiece.hpp"
#include "piece/King.hpp"
#include "piece/Knight.hpp"
#include "piece/Pawn.hpp"
#include "piece/Queen.hpp"
#include "piece/Rook.hpp"

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

        static std::vector<Position> _getBishopMoveableRelativePos(
            Board &board, const Bishop &piece);

        static std::vector<Position> _getBishopKillableRelativePos(
            Board &board, const Bishop &piece);

        static std::vector<Position> _getKingMoveableRelativePos(
            Board &board, const King &piece);

        static std::vector<Position> _getKingKillableRelativePos(
            Board &board, const King &piece);

        static std::vector<Position> _getKnightMoveableRelativePos(
            Board &board, const Knight &piece);

        static std::vector<Position> _getKnightKillableRelativePos(
            Board &board, const Knight &piece);

        static std::vector<Position> _getPawnMoveableRelativePos(
            Board &board, const Pawn &piece);

        static std::vector<Position> _getPawnKillableRelativePos(
            Board &board, const Pawn &piece);

        static std::vector<Position> _getQueenMoveableRelativePos(
            Board &board, const Queen &piece);

        static std::vector<Position> _getQueenKillableRelativePos(
            Board &board, const Queen &piece);

        static std::vector<Position> _getRookMoveableRelativePos(
            Board &board, const Rook &piece);

        static std::vector<Position> _getRookKillableRelativePos(
            Board &board, const Rook &piece);
    };

}