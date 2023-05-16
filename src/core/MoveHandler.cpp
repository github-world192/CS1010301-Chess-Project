/**
 *  File: MoveHandler.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/11 16:34:28
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/17 02:02:50
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
MoveHandler::getMovablePositions(Board &board, const Position &pos)
{
    std::vector<Position> movablePos;
    IPiece *piece = board(pos);
    switch ( piece->type() )
    {

    case TPiece::kBishop:
    {
        Bishop *bishop = (Bishop *)piece;
        Bishop &bishopRef = *bishop;
        movablePos = MoveHandler::_getBishopMovablePos(board, bishopRef, pos);
    }
    break;

    case TPiece::kKing:
    {
        King *king = (King *)piece;
        King &kingRef = *king;
        movablePos = MoveHandler::_getKingMovablePos(board, kingRef, pos);
    }
    break;

    case TPiece::kKnight:
    {
        Knight *knight = (Knight *)piece;
        Knight &knightRef = *knight;
        movablePos = MoveHandler::_getKnightMovablePos(board, knightRef, pos);
    }
    break;

    case TPiece::kPawn:
    {
        Pawn *pawn = (Pawn *)piece;
        Pawn &pawnRef = *pawn;
        movablePos = MoveHandler::_getPawnMovablePos(board, pawnRef, pos);
    }
    break;

    case TPiece::kQueen:
    {
        Queen *queen = (Queen *)piece;
        Queen &queenRef = *queen;
        movablePos = MoveHandler::_getQueenMovablePos(board, queenRef, pos);
    }
    break;

    case TPiece::kRook:
    {
        Rook *rook = (Rook *)piece;
        Rook &rookRef = *rook;
        movablePos = MoveHandler::_getRookMovablePos(board, rookRef, pos);
    }
    break;
    }

    return movablePos;
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
        killablePos = MoveHandler::_getKnightKillablePos(board, knightRef, pos);
    }
    break;

    case TPiece::kPawn:
    {
        Pawn *pawn = (Pawn *)piece;
        Pawn &pawnRef = *pawn;
        killablePos = MoveHandler::_getPawnKillablePos(board, pawnRef, pos);
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
        killablePos = MoveHandler::_getRookKillablePos(board, rookRef, pos);
    }
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

std::vector<Position> MoveHandler::getMovableKillablePositions(
    Board &board, const Position &pos)
{
    std::vector<Position> positions;
    std::vector<Position> movablePositions =
        MoveHandler::getMovablePositions(board, pos);
    std::vector<Position> killablePositions =
        MoveHandler::getKillablePositions(board, pos);

    // Get movable positions
    positions.insert(positions.end(),
                     movablePositions.begin(), movablePositions.end());

    // Get killable positions
    positions.insert(positions.end(), killablePositions.begin(),
                     killablePositions.end());

    // Remove repeat
    positions = MoveHandler::_removeRepeatPos(positions);

    return positions;
}

Position MoveHandler::_toRealPos(const Position &origin,
                                 const Position &relative)
{
    return (origin + relative);
}

std::vector<Position> MoveHandler::_removeRepeatPos(
    const std::vector<Position> &poss)
{
    std::vector<Position> r;
    for ( const Position &p : poss )
    {
        bool repeat = false;
        for ( const Position &rp : r )
        {
            if ( rp == p )
            {
                repeat = true;
                break;
            }
        }
        if ( !repeat )
            r.push_back(p);
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

std::vector<Position> MoveHandler::_getKingMovablePos(
    Board &board, const King &king, const Position &pos)
{
    std::vector<Position> movablePos;

    // Define 8 possible move
    std::vector<Position> possibleMove = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for ( const Position &p : possibleMove )
    {
        Position realP = MoveHandler::_toRealPos(pos, p);

        // If position invalid, break
        if ( !(board.isPositionValid(realP)) )
            continue;

        // If there a piece at position
        if ( board.isPositionPiece(realP) )
        {
            if ( board(realP)->getOwner() != king.getOwner() )
                // Append to movablePos
                movablePos.push_back(realP);
        }
        else
            movablePos.push_back(realP);
    }

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

std::vector<Position> MoveHandler::_getKingKillablePos(
    Board &board, const King &king, const Position &pos)
{
    std::vector<Position> movablePos;

    // Define 8 possible move
    std::vector<Position> possibleMove = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for ( const Position &p : possibleMove )
    {
        Position realP = MoveHandler::_toRealPos(pos, p);

        // If position invalid, break
        if ( !(board.isPositionValid(realP)) )
            continue;

        // If there a piece at position
        if ( board.isPositionPiece(realP) )
        {
            if ( board(realP)->getOwner() != king.getOwner() )
                // Append to movablePos
                movablePos.push_back(realP);
        }
        else
            movablePos.push_back(realP);
    }

    return movablePos;
}

std::vector<Position> MoveHandler::_getKnightMovablePos(
    Board &board, const Knight &knight, const Position &pos)
{
    std::vector<Position> movablePos;

    // Define 8 possible move
    std::vector<Position> possibleMove = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

    for ( const Position &p : possibleMove )
    {
        Position realP = MoveHandler::_toRealPos(pos, p);

        // If position invalid, break
        if ( !(board.isPositionValid(realP)) )
            continue;

        // If there a piece at position
        if ( board.isPositionPiece(realP) )
        {
            if ( board(realP)->getOwner() != knight.getOwner() )
                // Append to movablePos
                movablePos.push_back(realP);
        }
        else
            movablePos.push_back(realP);
    }

    return movablePos;
}

std::vector<Position> MoveHandler::_getKnightKillablePos(
    Board &board, const Knight &knight, const Position &pos)
{
    return MoveHandler::_getKnightMovablePos(board, knight, pos);
}

std::vector<Position> MoveHandler::_getPawnMovablePos(
    Board &board, const Pawn &pawn, const Position &pos)
{
    int8_t dir = pawn.isBlack() ? 1 : -1;

    std::vector<Position> movablePos;

    // Define 1 possible move
    std::vector<Position> possibleMove = {{0, 1 * dir}};

    // If the piece not moved, it can move 2 steps
    if ( !pawn.getMoved() )
        possibleMove.push_back({0, 2 * dir});

    for ( const Position &p : possibleMove )
    {
        Position realP = MoveHandler::_toRealPos(pos, p);

        // If position invalid, contiune
        if ( !(board.isPositionValid(realP)) )
            continue;

        // If there a piece at position, contiune
        if ( board.isPositionPiece(realP) )
            continue;

        movablePos.push_back(realP);
    }

    return movablePos;
}

std::vector<Position> MoveHandler::_getPawnKillablePos(
    Board &board, const Pawn &pawn, const Position &pos)
{
    int8_t dir = pawn.isBlack() ? 1 : -1;

    std::vector<Position> movablePos;

    // Define 2 possible move
    std::vector<Position> possibleMove = {{-1, dir}, {1, dir}};

    for ( const Position &p : possibleMove )
    {
        Position realP = MoveHandler::_toRealPos(pos, p);

        // If position invalid, break
        if ( !(board.isPositionValid(realP)) )
            continue;

        // If there a piece at position
        if ( board.isPositionPiece(realP) )
        {
            if ( board(realP)->getOwner() != pawn.getOwner() )
                // Append to movablePos
                movablePos.push_back(realP);
        }
        else
            movablePos.push_back(realP);
    }

    return movablePos;
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

std::vector<Position> MoveHandler::_getRookMovablePos(
    Board &board, const Rook &rook, const Position &pos)
{
    std::vector<Position> movablePos;

    // Define 4 move directions
    std::vector<Position> movableDir = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

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
                if ( board(realCp)->getOwner() != rook.getOwner() )
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

std::vector<Position> MoveHandler::_getRookKillablePos(
    Board &board, const Rook &rook, const Position &pos)
{
    return MoveHandler::_getRookMovablePos(board, rook, pos);
}