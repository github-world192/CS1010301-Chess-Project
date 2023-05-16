/**
 *  File: MoveHandler.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/11 16:34:28
 *  Editor: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Update Date: 2023/05/16 15:00:40
 *  Description: Move Handler
 */

#include "core/MoveHandler.hpp"

#include <iostream>

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

    case TPiece::kBishop:
    {
        Bishop *bishop = (Bishop *)piece;
        Bishop &bishopRef = *bishop;
        movableRelativePos =
            MoveHandler::_getBishopMoveableRelativePos(board, bishopRef);
        killableRelativePos =
            MoveHandler::_getBishopKillableRelativePos(board, bishopRef);
    }
    break;

    case TPiece::kKing:
    {
        King *king = (King *)piece;
        King &kingRef = *king;
        movableRelativePos =
            MoveHandler::_getKingMoveableRelativePos(board, kingRef);
        killableRelativePos =
            MoveHandler::_getKingKillableRelativePos(board, kingRef);
    }
    break;

    case TPiece::kKnight:
    {
        Knight *knight = (Knight *)piece;
        Knight &knightRef = *knight;
        movableRelativePos =
            MoveHandler::_getKnightMoveableRelativePos(board, knightRef);
        killableRelativePos =
            MoveHandler::_getKnightKillableRelativePos(board, knightRef);
    }
    break;

    case TPiece::kPawn:
    {
        Pawn *pawn = (Pawn *)piece;
        Pawn &pawnRef = *pawn;
        movableRelativePos =
            MoveHandler::_getPawnMoveableRelativePos(board, pawnRef);
        killableRelativePos =
            MoveHandler::_getPawnKillableRelativePos(board, pawnRef);
    }
    break;

    case TPiece::kQueen:
    {
        Queen *queen = (Queen *)piece;
        Queen &queenRef = *queen;
        movableRelativePos =
            MoveHandler::_getQueenMoveableRelativePos(board, queenRef);
        killableRelativePos =
            MoveHandler::_getQueenKillableRelativePos(board, queenRef);
    }
    break;

    case TPiece::kRook:
    {
        Rook *rook = (Rook *)piece;
        Rook &rookRef = *rook;
        movableRelativePos =
            MoveHandler::_getRookMoveableRelativePos(board, rookRef);
        killableRelativePos =
            MoveHandler::_getRookKillableRelativePos(board, rookRef);
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

std::vector<Position> MoveHandler::_getBishopMoveableRelativePos(
    Board &board, const Bishop &bishop)
{
    std::vector<Position> moveablePos;
    for ( int i = 1; i < 8; i++ )
    {
        moveablePos.push_back({i, i});
        moveablePos.push_back({i, -i});
        moveablePos.push_back({-i, -i});
        moveablePos.push_back({-i, i});
    }
    return moveablePos;
}

std::vector<Position> MoveHandler::_getBishopKillableRelativePos(
    Board &board, const Bishop &bishop)
{
    return MoveHandler::_getBishopMoveableRelativePos(board, bishop);
}

std::vector<Position> MoveHandler::_getKingMoveableRelativePos(
    Board &board, const King &king)
{
    std::vector<Position> movablePos;
    movablePos.push_back({-1, 1});
    movablePos.push_back({0, 1});
    movablePos.push_back({1, 1});
    movablePos.push_back({-1, 0});
    movablePos.push_back({1, 0});
    movablePos.push_back({-1, -1});
    movablePos.push_back({0, -1});
    movablePos.push_back({1, -1});

    return movablePos;
}

std::vector<Position> MoveHandler::_getKingKillableRelativePos(
    Board &board, const King &king)
{
    return MoveHandler::_getKingMoveableRelativePos(board, king);
}

std::vector<Position> MoveHandler::_getKnightMoveableRelativePos(
    Board &board, const Knight &knight)
{
    std::vector<Position> movablePos;
    movablePos.push_back({-1, 2});
    movablePos.push_back({-2, 1});
    movablePos.push_back({-2, -1});
    movablePos.push_back({-1, -2});
    movablePos.push_back({1, -2});
    movablePos.push_back({2, -1});
    movablePos.push_back({2, 1});
    movablePos.push_back({1, 2});

    return movablePos;
}

std::vector<Position> MoveHandler::_getKnightKillableRelativePos(
    Board &board, const Knight &knight)
{
    return MoveHandler::_getKnightMoveableRelativePos(board, knight);
}

std::vector<Position> MoveHandler::_getPawnMoveableRelativePos(
    Board &board, const Pawn &pawn)
{
    int8_t dir = pawn.isBlack() ? 1 : -1;
    std::vector<Position> moveablePos;
    moveablePos.push_back({0, 1 * dir});
    // Pawn can move forward 2 steps, if wasn't moved
    if ( !(pawn.getMoved()) )
        moveablePos.push_back({0, 2 * dir});

    return moveablePos;
}

std::vector<Position> MoveHandler::_getPawnKillableRelativePos(
    Board &board, const Pawn &pawn)
{
    int8_t dir = pawn.isBlack() ? 1 : -1;
    // Killable position list
    std::vector<Position> killablePos = {
        Position(1, dir),
        Position(-1, dir),
    };

    return killablePos;
}

std::vector<Position> MoveHandler::_getQueenMoveableRelativePos(
    Board &board, const Queen &queen)
{
    std::vector<Position> moveablePos;
    for ( int i = 1; i < 8; i++ )
    {
        moveablePos.push_back({0, i});
        moveablePos.push_back({0, -i});
        moveablePos.push_back({i, 0});
        moveablePos.push_back({-i, 0});
        moveablePos.push_back({i, i});
        moveablePos.push_back({i, -i});
        moveablePos.push_back({-i, -i});
        moveablePos.push_back({-i, i});
    }
    return moveablePos;
}

std::vector<Position> MoveHandler::_getQueenKillableRelativePos(
    Board &board, const Queen &queen)
{
    return MoveHandler::_getQueenMoveableRelativePos(board, queen);
}

std::vector<Position> MoveHandler::_getRookMoveableRelativePos(
    Board &board, const Rook &rook)
{
    std::vector<Position> moveablePos;
    for ( int i = 1; i < 8; i++ )
    {
        moveablePos.push_back({0, i});
        moveablePos.push_back({0, -i});
        moveablePos.push_back({i, 0});
        moveablePos.push_back({-i, 0});
    }
    return moveablePos;
}

std::vector<Position> MoveHandler::_getRookKillableRelativePos(
    Board &board, const Rook &rook)
{
    return MoveHandler::_getRookMoveableRelativePos(board, rook);
}