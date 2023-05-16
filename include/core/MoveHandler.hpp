/**
 *  File: Movehandler.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/11 16:29:30
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/16 21:44:45
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

    private:
        static Position _toRealPos(const Position &origin,
                                   const Position &relative);

        static std::vector<Position> _toRealPos(
            Board &board, const Position &pos,
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

        static std::vector<Position> _getKnightMovableRelativePos(
            Board &board, const Knight &piece);

        static std::vector<Position> _getKnightKillableRelativePos(
            Board &board, const Knight &piece);

        static std::vector<Position> _getPawnMovableRelativePos(
            Board &board, const Pawn &piece);

        static std::vector<Position> _getPawnKillableRelativePos(
            Board &board, const Pawn &piece);

        static std::vector<Position> _getQueenMovablePos(
            Board &board, const Queen &piece, const Position &pos);

        static std::vector<Position> _getQueenKillablePos(
            Board &board, const Queen &piece, const Position &pos);

        static std::vector<Position> _getRookMovableRelativePos(
            Board &board, const Rook &piece);

        static std::vector<Position> _getRookKillableRelativePos(
            Board &board, const Rook &piece);
    };

}