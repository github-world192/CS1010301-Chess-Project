/**
 *  File: MoveHandler.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/11 16:34:28
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/16 22:06:41
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
MoveHandler::getKillablePositions(Board &board, const Position &pos)
{
    std::vector<Position> killableRelativePos;
    std::vector<Position> killablePos;
    std::vector<Position> realKillablePos;
    IPiece *piece = board(pos);
    switch ( piece->type() )
    {

    case TPiece::kBishop:
    {
        Bishop *bishop = (Bishop *)piece;
        Bishop &bishopRef = *bishop;
        killablePos = MoveHandler::_getBishopKillablePos(board, bishopRef, pos);
    }
    break;

    case TPiece::kKing:
    {
        King *king = (King *)piece;
        King &kingRef = *king;
        killablePos =
            MoveHandler::_getKingKillablePos(board, kingRef, pos);
    }
    break;

    case TPiece::kKnight:
    {
        Knight *knight = (Knight *)piece;
        Knight &knightRef = *knight;
        killableRelativePos =
            MoveHandler::_getKnightKillableRelativePos(board, knightRef);
        killablePos = MoveHandler::_toRealPos(board, pos, killableRelativePos);
    }
    break;

    case TPiece::kPawn:
    {
        Pawn *pawn = (Pawn *)piece;
        Pawn &pawnRef = *pawn;
        killableRelativePos =
            MoveHandler::_getPawnKillableRelativePos(board, pawnRef);
        killablePos = MoveHandler::_toRealPos(board, pos, killableRelativePos);
    }
    break;

    case TPiece::kQueen:
    {
        Queen *queen = (Queen *)piece;
        Queen &queenRef = *queen;
        killablePos = MoveHandler::_getQueenKillablePos(board, queenRef, pos);
    }
    break;

    case TPiece::kRook:
    {
        Rook *rook = (Rook *)piece;
        Rook &rookRef = *rook;
        killableRelativePos =
            MoveHandler::_getRookKillableRelativePos(board, rookRef);
        killablePos = MoveHandler::_toRealPos(board, pos, killableRelativePos);
    }
    break;

    default:
        break;
    }

    // for ( const Position &p : killablePos )
    // {
    //     if ( board(p) == nullptr )
    //         continue;

    //     // Check if the pos piece killable, push into movablePos
    //     if ( board(p)->getOwner() != piece->getOwner() )
    //         realKillablePos.push_back(p);
    // }
    realKillablePos = killablePos;

    return realKillablePos;
}

std::vector<Position>
MoveHandler::getMovablePositions(Board &board, const Position &pos)
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
        movablePos =
            MoveHandler::_getBishopMovablePos(board, bishopRef, pos);
        killablePos =
            MoveHandler::_getBishopKillablePos(board, bishopRef, pos);
    }
    break;

    case TPiece::kKing:
    {
        King *king = (King *)piece;
        King &kingRef = *king;
        movablePos =
            MoveHandler::_getKingMovablePos(board, kingRef, pos);
        killablePos =
            MoveHandler::_getKingKillablePos(board, kingRef, pos);
    }
    break;

    case TPiece::kKnight:
    {
        Knight *knight = (Knight *)piece;
        Knight &knightRef = *knight;
        movableRelativePos =
            MoveHandler::_getKnightMovableRelativePos(board, knightRef);
        killableRelativePos =
            MoveHandler::_getKnightKillableRelativePos(board, knightRef);
        movablePos = MoveHandler::_toRealPos(board, pos, movableRelativePos);
        killablePos = MoveHandler::_toRealPos(board, pos, killableRelativePos);
    }
    break;

    case TPiece::kPawn:
    {
        Pawn *pawn = (Pawn *)piece;
        Pawn &pawnRef = *pawn;
        movableRelativePos =
            MoveHandler::_getPawnMovableRelativePos(board, pawnRef);
        killableRelativePos =
            MoveHandler::_getPawnKillableRelativePos(board, pawnRef);
        movablePos = MoveHandler::_toRealPos(board, pos, movableRelativePos);
        killablePos = MoveHandler::_toRealPos(board, pos, killableRelativePos);
    }
    break;

    case TPiece::kQueen:
    {
        Queen *queen = (Queen *)piece;
        Queen &queenRef = *queen;
        movablePos =
            MoveHandler::_getQueenMovablePos(board, queenRef, pos);
        killablePos =
            MoveHandler::_getQueenKillablePos(board, queenRef, pos);
    }
    break;

    case TPiece::kRook:
    {
        Rook *rook = (Rook *)piece;
        Rook &rookRef = *rook;
        movableRelativePos =
            MoveHandler::_getRookMovableRelativePos(board, rookRef);
        killableRelativePos =
            MoveHandler::_getRookKillableRelativePos(board, rookRef);
        movablePos = MoveHandler::_toRealPos(board, pos, movableRelativePos);
        killablePos = MoveHandler::_toRealPos(board, pos, killableRelativePos);
    }
    break;

    default:
        break;
    }

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

Position MoveHandler::_toRealPos(const Position &origin,
                                 const Position &relative)
{
    return (origin + relative);
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

std::vector<Position> MoveHandler::_getBishopMovablePos(
    Board &board, const Bishop &bishop, const Position &pos)
{
    std::vector<Position> movablePos;

    // Define 4 move directions
    std::vector<Position> movableDir = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    for ( const Position &cd : movableDir )
    {
        for ( size_t i = 1; i < board.width(); ++i )
        {
            // Calculate position
            Position cp = cd * i;
            Position realCp = MoveHandler::_toRealPos(pos, cp);

            // If position invalid, break
            if ( !(board.isPositionValid(realCp)) )
                break;

            // If there a piece at position
            if ( board.isPositionPiece(realCp) )
            {
                if ( board(realCp)->getOwner() != bishop.getOwner() )
                    // Append to movablePos
                    movablePos.push_back(realCp);
                break;
            }
            else
                movablePos.push_back(realCp);
        }
    }

    return movablePos;
}

std::vector<Position> MoveHandler::_getBishopKillablePos(
    Board &board, const Bishop &bishop, const Position &pos)
{
    return MoveHandler::_getBishopMovablePos(board, bishop, pos);
}

bool MoveHandler::_isKingPosKillable(Board &board, const Position &pos,
                                     TPlayer player)
{
    TPlayer enemy = (player == TPlayer::kBlack)
                        ? TPlayer::kWhite
                        : TPlayer::kBlack;
    // Find all enemy's pieces position
    std::vector<Position> enemyPos = board.findPiecesPos(enemy);
    for ( const Position &p : enemyPos )
    {
        std::cout << "enemy_pos = (" << p.x << ", " << p.y << ")" << std::endl;
        std::vector<Position> enemyKillablePos =
            MoveHandler::getKillablePositions(board, p);
        for ( const Position &ekp : enemyKillablePos )
        {
            std::cout << "(" << ekp.x << ", " << ekp.y << ")" << std::endl;
            if ( ekp == pos )
                return true;
        }
    }
    return false;
}

// TODO: Fix movable pos will let king death
std::vector<Position> MoveHandler::_getKingMovablePos(
    Board &board, const King &king, const Position &pos)
{
    std::vector<Position> movablePos;

    // Define 8 possible move
    std::vector<Position> possibleMove = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    movablePos = MoveHandler::_toRealPos(board, pos, possibleMove);

    // If king moved, no need to do castling check
    if ( king.getMoved() )
        return movablePos;

    // Find player's rook pieces position
    std::vector<Position> rookPos =
        board.findPiecesPos(king.getOwner(), TPiece::kRook);

    // Check any rook not moved
    for ( const Position &rookP : rookPos )
    {
        // If rook moved, skip
        if ( (board(rookP)->getMoved()) )
            continue;

        // Castling Directions
        std::vector<Position> castlingDir = {{-1, 0}, {1, 0}};
        for ( const Position &cd : castlingDir )
        {
            for ( size_t i = 1; i < board.width(); ++i )
            {
                // Calculate position
                Position cp = cd * i;
                Position realCp = MoveHandler::_toRealPos(pos, cp);

                // If position invalid, break
                if ( !(board.isPositionValid(realCp)) )
                    break;

                // If it's a way to find rook
                if ( realCp == rookP )
                {
                    // Calculate castling position
                    Position castlingPos = pos + (cd * 2);
                    // If the castling position will not let king death
                    if ( !(MoveHandler::_isKingPosKillable(board, castlingPos,
                                                           king.getOwner())) )
                        movablePos.push_back(castlingPos);
                    break;
                }

                // If position has a piece, break
                if ( board.isPositionPiece(realCp) )
                    break;
            }
        }
    }

    return movablePos;
}

// TODO: Fix movable pos will let king death
std::vector<Position> MoveHandler::_getKingKillablePos(
    Board &board, const King &king, const Position &pos)
{
    // Define 8 possible move
    std::vector<Position> movablePos = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    return MoveHandler::_toRealPos(board, pos, movablePos);
}

// TODO: Fix movable pos shoule not on player's piece position
std::vector<Position> MoveHandler::_getKnightMovableRelativePos(
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

// TODO: Fix movable pos shoule not on player's piece position
std::vector<Position> MoveHandler::_getKnightKillableRelativePos(
    Board &board, const Knight &knight)
{
    return MoveHandler::_getKnightMovableRelativePos(board, knight);
}

// TODO: Fix movable pos shoule not on player's piece position
std::vector<Position> MoveHandler::_getPawnMovableRelativePos(
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

// TODO: Fix movable pos shoule not on player's piece position
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

std::vector<Position> MoveHandler::_getQueenMovablePos(
    Board &board, const Queen &queen, const Position &pos)
{
    std::vector<Position> movablePos;

    // Define 8 move directions
    std::vector<Position> movableDir = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for ( const Position &cd : movableDir )
    {
        for ( size_t i = 1; i < board.width(); ++i )
        {
            // Calculate position
            Position cp = cd * i;
            Position realCp = MoveHandler::_toRealPos(pos, cp);

            // If position invalid, break
            if ( !(board.isPositionValid(realCp)) )
                break;

            // If there a piece at position
            if ( board.isPositionPiece(realCp) )
            {
                if ( board(realCp)->getOwner() != queen.getOwner() )
                    // Append to movablePos
                    movablePos.push_back(realCp);
                break;
            }
            else
                movablePos.push_back(realCp);
        }
    }

    return movablePos;
}

std::vector<Position> MoveHandler::_getQueenKillablePos(
    Board &board, const Queen &queen, const Position &pos)
{
    return MoveHandler::_getQueenMovablePos(board, queen, pos);
}

// TODO: Fix movable pos shoule not on player's piece position
std::vector<Position> MoveHandler::_getRookMovableRelativePos(
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

// TODO: Fix movable pos shoule not on player's piece position
std::vector<Position> MoveHandler::_getRookKillableRelativePos(
    Board &board, const Rook &rook)
{
    return MoveHandler::_getRookMovableRelativePos(board, rook);
}