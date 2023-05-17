/**
 *  File: MoveHandler.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/11 16:34:28
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/17 13:57:48
 *  Description: Move Handler
 */

#include "core/MoveHandler.hpp"

#include <iostream>

using namespace Chess;

bool MoveHandler::isMoveValid(const Board &board, const Move &move)
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
MoveHandler::getMovablePositions(const Board &board, const Position &pos)
{
    std::vector<Position> movablePos;
    const IPiece *piece = board(pos);
    switch ( piece->type() )
    {

    case TPiece::kBishop:
    {
        Bishop *bishop = (Bishop *)piece;
        Bishop &bishopRef = *bishop;
        movablePos = MoveHandler::getBishopMovablePos(board, bishopRef, pos);
    }
    break;

    case TPiece::kKing:
    {
        King *king = (King *)piece;
        King &kingRef = *king;
        movablePos = MoveHandler::getKingMovablePos(board, kingRef, pos);
    }
    break;

    case TPiece::kKnight:
    {
        Knight *knight = (Knight *)piece;
        Knight &knightRef = *knight;
        movablePos = MoveHandler::getKnightMovablePos(board, knightRef, pos);
    }
    break;

    case TPiece::kPawn:
    {
        Pawn *pawn = (Pawn *)piece;
        Pawn &pawnRef = *pawn;
        movablePos = MoveHandler::getPawnMovablePos(board, pawnRef, pos);
    }
    break;

    case TPiece::kQueen:
    {
        Queen *queen = (Queen *)piece;
        Queen &queenRef = *queen;
        movablePos = MoveHandler::getQueenMovablePos(board, queenRef, pos);
    }
    break;

    case TPiece::kRook:
    {
        Rook *rook = (Rook *)piece;
        Rook &rookRef = *rook;
        movablePos = MoveHandler::getRookMovablePos(board, rookRef, pos);
    }
    break;
    }

    return movablePos;
}

std::vector<Position>
MoveHandler::getKillablePositions(const Board &board, const Position &pos)
{
    std::vector<Position> killableRelativePos;
    std::vector<Position> killablePos;
    std::vector<Position> realKillablePos;
    const IPiece *piece = board(pos);
    switch ( piece->type() )
    {

    case TPiece::kBishop:
    {
        Bishop *bishop = (Bishop *)piece;
        Bishop &bishopRef = *bishop;
        killablePos = MoveHandler::getBishopKillablePos(board, bishopRef, pos);
    }
    break;

    case TPiece::kKing:
    {
        King *king = (King *)piece;
        King &kingRef = *king;
        killablePos =
            MoveHandler::getKingKillablePos(board, kingRef, pos);
    }
    break;

    case TPiece::kKnight:
    {
        Knight *knight = (Knight *)piece;
        Knight &knightRef = *knight;
        killablePos = MoveHandler::getKnightKillablePos(board, knightRef, pos);
    }
    break;

    case TPiece::kPawn:
    {
        Pawn *pawn = (Pawn *)piece;
        Pawn &pawnRef = *pawn;
        killablePos = MoveHandler::getPawnKillablePos(board, pawnRef, pos);
    }
    break;

    case TPiece::kQueen:
    {
        Queen *queen = (Queen *)piece;
        Queen &queenRef = *queen;
        killablePos = MoveHandler::getQueenKillablePos(board, queenRef, pos);
    }
    break;

    case TPiece::kRook:
    {
        Rook *rook = (Rook *)piece;
        Rook &rookRef = *rook;
        killablePos = MoveHandler::getRookKillablePos(board, rookRef, pos);
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
    const Board &board, const Position &pos)
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

std::vector<std::pair<Move, Move>>
MoveHandler::getCastlingMove(const Board &board, const Position &pos)
{
    std::vector<std::pair<Move, Move>> castlingMove;
    const IPiece *piece = board(pos);
    switch ( piece->type() )
    {
    case TPiece::kKing:
    {
        King *king = (King *)piece;
        King &kingRef = *king;
        MoveHandler::getKingCastlingPos(board, kingRef, pos, castlingMove);
    }
    break;

    default:
        break;
    }

    return castlingMove;
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

std::vector<Position> MoveHandler::getBishopMovablePos(
    const Board &board, const Bishop &bishop, const Position &pos)
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

std::vector<Position> MoveHandler::getBishopKillablePos(
    const Board &board, const Bishop &bishop, const Position &pos)
{
    return MoveHandler::getBishopMovablePos(board, bishop, pos);
}

bool MoveHandler::_isKingPosKillable(const Board &board, const Position &pos,
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

std::vector<Position> MoveHandler::getKingMovablePos(
    const Board &board, const King &king, const Position &pos)
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

    // Get castling positions
    std::vector<std::pair<Move, Move>> castlingMove;
    std::vector<Position> castlingPoss =
        MoveHandler::getKingCastlingPos(board, king, pos, castlingMove);

    movablePos.insert(movablePos.end(), castlingPoss.begin(), castlingPoss.end());

    return movablePos;
}

std::vector<Position> MoveHandler::getKingKillablePos(
    const Board &board, const King &king, const Position &pos)
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

std::vector<Position> MoveHandler::getKingCastlingPos(
    const Board &board, const King &king,
    const Position &pos, std::vector<std::pair<Move, Move>> &castlingMove)
{
    castlingMove.clear(); // For save valid castling move pair
    std::vector<Position> movablePos;

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
                    Position castlingPos = pos + (cd * 2);       // King new pos
                    Position rookCastlingPos = castlingPos - cd; // Rook new pos
                    // If the castling position will not let king death
                    if ( !(MoveHandler::_isKingPosKillable(board, castlingPos,
                                                           king.getOwner())) )
                    {
                        movablePos.push_back(castlingPos);
                        // Save valid castling move pair
                        castlingMove.push_back(
                            std::pair<Move, Move>(
                                Move(king.getOwner(), pos, castlingPos),
                                Move(king.getOwner(), rookP, rookCastlingPos)));
                    }
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

std::vector<Position> MoveHandler::getKnightMovablePos(
    const Board &board, const Knight &knight, const Position &pos)
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

std::vector<Position> MoveHandler::getKnightKillablePos(
    const Board &board, const Knight &knight, const Position &pos)
{
    return MoveHandler::getKnightMovablePos(board, knight, pos);
}

std::vector<Position> MoveHandler::getPawnMovablePos(
    const Board &board, const Pawn &pawn, const Position &pos)
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

std::vector<Position> MoveHandler::getPawnKillablePos(
    const Board &board, const Pawn &pawn, const Position &pos)
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

std::vector<Position> MoveHandler::getQueenMovablePos(
    const Board &board, const Queen &queen, const Position &pos)
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

std::vector<Position> MoveHandler::getQueenKillablePos(
    const Board &board, const Queen &queen, const Position &pos)
{
    return MoveHandler::getQueenMovablePos(board, queen, pos);
}

std::vector<Position> MoveHandler::getRookMovablePos(
    const Board &board, const Rook &rook, const Position &pos)
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

std::vector<Position> MoveHandler::getRookKillablePos(
    const Board &board, const Rook &rook, const Position &pos)
{
    return MoveHandler::getRookMovablePos(board, rook, pos);
}