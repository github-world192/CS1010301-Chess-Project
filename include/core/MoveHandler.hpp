/**
 *  File: Movehandler.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/11 16:29:30
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/17 02:02:58
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

        static std::vector<Position> getMovablePositions(
            Board &board, const Position &pos);

        static std::vector<Position> getKillablePositions(
            Board &board, const Position &pos);

        static std::vector<Position> getMovableKillablePositions(
            Board &board, const Position &pos);

    private:
        static Position _toRealPos(const Position &origin,
                                   const Position &relative);

        static std::vector<Position> _removeRepeatPos(
            const std::vector<Position> &poss);

        static std::vector<Position> _getBishopMovablePos(
            Board &board, const Bishop &piece, const Position &pos);

        static std::vector<Position> _getBishopKillablePos(
            Board &board, const Bishop &piece, const Position &pos);

        static bool _isKingPosKillable(Board &board, const Position &pos,
                                       TPlayer player);

        static std::vector<Position> _getKingMovablePos(
            Board &board, const King &piece, const Position &pos);

        static std::vector<Position> _getKingKillablePos(
            Board &board, const King &piece, const Position &pos);

        static std::vector<Position> _getKnightMovablePos(
            Board &board, const Knight &piece, const Position &pos);

        static std::vector<Position> _getKnightKillablePos(
            Board &board, const Knight &piece, const Position &pos);

        static std::vector<Position> _getPawnMovablePos(
            Board &board, const Pawn &piece, const Position &pos);

        static std::vector<Position> _getPawnKillablePos(
            Board &board, const Pawn &piece, const Position &pos);

        static std::vector<Position> _getQueenMovablePos(
            Board &board, const Queen &piece, const Position &pos);

        static std::vector<Position> _getQueenKillablePos(
            Board &board, const Queen &piece, const Position &pos);

        static std::vector<Position> _getRookMovablePos(
            Board &board, const Rook &piece, const Position &pos);

        static std::vector<Position> _getRookKillablePos(
            Board &board, const Rook &piece, const Position &pos);
    };

}