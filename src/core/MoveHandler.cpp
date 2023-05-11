/**
 *  File: MoveHandler.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/11 16:34:28
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/11 18:19:50
 *  Description: Move Handler
 */

#include "core/MoveHandler.hpp"

using namespace Chess;

bool MoveHandler::isMoveValid(Board &board, const Move &move)
{
    // If there are no piece
    if ( board(move.getFrom()) == nullptr )
        return false;

    // If the piece not owned by the player
    if ( board(move.getFrom())->getOwner() != move.getPlayerType() )
        return false;

    std::vector<Position> movablePos =
        MoveHandler::getMovablePositions(board, move.getFrom());

    for ( const Position &p : movablePos )
    {
        if ( p.x == move.getTo().x && p.y == move.getTo().y )
            return true;
    }

    return false;
}

std::vector<Position>
MoveHandler::getMovablePositions(Board &board,
                                 const Position &pos)
{
    std::vector<Position> movableRelativePos;
    std::vector<Position> movablePos;
    std::vector<Position> killableRelativePos;
    std::vector<Position> killablePos;
    IPiece *piece = board(pos);
    switch ( piece->type() )
    {
    case TPiece::kPawn:
    {
        Pawn *pawn = (Pawn *)piece;
        Pawn &pawnRef = *pawn;
        movableRelativePos =
            MoveHandler::_getPawnMovableRelativePos(board, pawnRef);
        killableRelativePos =
            MoveHandler::_getPawnKillableRelativePos(board, pawnRef);
    }
    break;

    default:
        break;
    }

    movablePos = MoveHandler::_toRealPos(board, pos, movableRelativePos);
    killablePos = MoveHandler::_toRealPos(board, pos, killableRelativePos);

    for ( const Position &p : killablePos )
    {
        if ( board(p) == nullptr )
            continue;

        // Check if the pos piece killable, push into movablePos
        if ( board(p)->getOwner() != piece->getOwner() )
            movablePos.push_back(p);
    }

    return movablePos;
}

std::vector<Position> MoveHandler::_toRealPos(
    Board &board, const Position &pos,
    const std::vector<Position> &poss)
{
    std::vector<Position> r;
    for ( const Position &p : poss )
    {
        Position realPos = (Position)pos + p;
        // Save only the real pos valid
        if ( board.isPositionValid(realPos) )
            r.push_back(realPos);
    }
    return r;
}

std::vector<Position> MoveHandler::_getPawnMovableRelativePos(
    Board &board, const Pawn &pawn)
{
    int8_t dir = pawn.isBlack() ? 1 : -1;
    std::vector<Position> movablePos;
    movablePos.push_back({0, 1 * dir});
    // Pawn can move forward 2 steps, if wasn't moved
    if ( !(pawn.getMoved()) )
        movablePos.push_back({0, 2 * dir});

    return movablePos;
}

std::vector<Position> MoveHandler::_getPawnKillableRelativePos(
    Board &board, const Pawn &pawn)
{
    int8_t dir = pawn.isBlack() ? 1 : -1;
    // Killable position list
    std::vector<Position> killablePos = {
        {1, 1 * dir},
        {-1, -1 * dir},
    };

    return killablePos;
}