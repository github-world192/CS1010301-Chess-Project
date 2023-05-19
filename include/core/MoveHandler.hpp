/**
 *  File: Movehandler.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/11 16:29:30
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/20 02:21:06
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
        static bool isMoveValid(const Board &board, const Move &move);

        static bool isPromoting(const Board &board, const Position &pos);

        static bool isCheck(const Board &board, const Position &pos);

        static std::vector<Position> getMovablePositions(
            const Board &board, const Position &pos, bool kingCantDie = true);

        static std::vector<Position> getKillablePositions(
            const Board &board, const Position &pos,
            bool kingCantDie = true, bool includeBlankSpot = false);

        static std::vector<Position> getMovableKillablePositions(
            const Board &board, const Position &pos, bool kingCantDie = true);

        static std::vector<std::pair<Move, Move>> getCastlingMove(
            const Board &board, const Position &pos);

        static std::vector<Position> getBishopMovablePos(
            const Board &board, const Bishop &piece, const Position &pos);

        static std::vector<Position> getBishopKillablePos(
            const Board &board, const Bishop &piece, const Position &pos);

        static bool isKingPosKillable(const Board &board, const Position &pos,
                                      TPlayer player);

        static bool isKingCheck(const Board &board, const King &piece,
                                const Position &pos);

        static std::vector<Position> getKingMovablePos(
            const Board &board, const King &piece, const Position &pos,
            bool kingCantDie = true);

        static std::vector<Position> getKingKillablePos(
            const Board &board, const King &piece, const Position &pos,
            bool kingCantDie = true);

        static std::vector<Position> getKingCastlingPos(
            const Board &board, const King &piece, const Position &pos,
            std::vector<std::pair<Move, Move>> &castlingMove,
            bool kingCantDie = true);

        static std::vector<Position> getKnightMovablePos(
            const Board &board, const Knight &piece, const Position &pos);

        static std::vector<Position> getKnightKillablePos(
            const Board &board, const Knight &piece, const Position &pos);

        static std::vector<Position> getPawnMovablePos(
            const Board &board, const Pawn &piece, const Position &pos);

        static std::vector<Position> getPawnKillablePos(
            const Board &board, const Pawn &piece, const Position &pos,
            bool includeBlankSpot = false);

        static std::vector<Position> getQueenMovablePos(
            const Board &board, const Queen &piece, const Position &pos);

        static std::vector<Position> getQueenKillablePos(
            const Board &board, const Queen &piece, const Position &pos);

        static std::vector<Position> getRookMovablePos(
            const Board &board, const Rook &piece, const Position &pos);

        static std::vector<Position> getRookKillablePos(
            const Board &board, const Rook &piece, const Position &pos);

    private:
        static Position _toRealPos(const Position &origin,
                                   const Position &relative);

        static std::vector<Position> _removeRepeatPos(
            const std::vector<Position> &poss);
    };

}