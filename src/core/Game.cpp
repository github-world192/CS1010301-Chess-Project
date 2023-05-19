/**
 *  File: Game.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/09 22:57:37
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/20 02:47:30
 *  Description: Chess Class
 */

#include "core/Game.hpp"
#include "core/MoveHandler.hpp"
#include "core/player/Player.hpp"
#include "core/player/PlayerUtil.hpp"

using namespace Chess;

Game::Game()
{
    this->initialize();
}

std::vector<Position> Game::getBoardPieceMovablePos(const Position &pos) const
{
    return MoveHandler::getMovableKillablePositions((Board &)(this->_board), pos);
}

bool Game::makeMove(const Move &move)
{
    if ( this->_state != TGameState::kActive )
        return false;

    if ( move.getPlayerType() != this->_currentPlayerType )
        return false;

    if ( !MoveHandler::isMoveValid(this->_board, move) )
        return false;

    // Check is a castling move?
    std::vector<std::pair<Move, Move>> castlingMove =
        MoveHandler::getCastlingMove(this->_board, move.getFrom());

    for ( const auto &mp : castlingMove )
    {
        // if is a castling move
        if ( mp.first == move )
        {
            // do castling
            this->_board.move(mp.second.getFrom(), mp.second.getTo());
            break;
        }
    }

    if ( this->_board.move(move.getFrom(), move.getTo()) )
    {
        this->swapCurrentPlayerType();
        updateGame();
        return true;
    }

    return false;
}

bool Game::isCheckmate() const
{
    std::vector<Position> kingPos =
        this->_board.findPiecesPos(this->_currentPlayerType, TPiece::kKing);

    // If king not exists, is checkmate
    if ( kingPos.empty() )
        return true;

    // If king is check
    if ( MoveHandler::isCheck(this->_board, kingPos[0]) )
    {
        // Check is king movable
        std::vector<Position> kingMovablePos =
            MoveHandler::getMovableKillablePositions(this->_board, kingPos[0]);
        // If king can move, not checkmate
        if ( !kingMovablePos.empty() )
            return false;

        // Can the current player's pieces stop checkmate
        std::vector<Position> currentPlayerPiecesPos =
            this->_board.findPiecesPos(this->_currentPlayerType);
        for ( const Position &pos : currentPlayerPiecesPos )
        {
            std::vector<Position> movablePos =
                MoveHandler::getMovableKillablePositions(this->_board, pos);
            for ( const Position &movePos : movablePos )
            {
                // Try to move the piece
                Board tempBoard(this->_board);
                tempBoard.move(pos, movePos);
                std::cout << tempBoard.toString() << std::endl;
                // If stop checkmate after this move, not checkmate
                if ( !(MoveHandler::isCheck(tempBoard, kingPos[0])) )
                    return false;
            }
        }
    }
    else
        return false;

    return true;
}

bool Game::isPromoting() const
{
    std::vector<Position> pawnPos = this->_board.findPiecesPos(TPiece::kPawn);
    for ( const Position &p : pawnPos )
    {
        if ( MoveHandler::isPromoting(this->_board, p) )
            return true;
    }
    return false;
}

bool Game::promoting(TPiece type)
{
    std::vector<Position> pawnPos = this->_board.findPiecesPos(TPiece::kPawn);
    for ( const Position &p : pawnPos )
    {
        if ( MoveHandler::isPromoting(this->_board, p) )
            return this->_board.promoting(p, type);
    }

    return false;
}

void Game::updateGameState()
{
    if ( this->getPlayerTime(TPlayer::kBlack) <= 0 )
    {
        this->_state = TGameState::kWhiteWin;
        this->_gameOverType = TGameOver::kTimeout;
        return;
    }

    if ( this->getPlayerTime(TPlayer::kWhite) <= 0 )
    {
        this->_state = TGameState::kBlackWin;
        this->_gameOverType = TGameOver::kTimeout;
        return;
    }

    if ( this->isCheckmate() )
    {
        this->_state = (this->_currentPlayerType == TPlayer::kBlack)
                           ? TGameState::kWhiteWin
                           : TGameState::kBlackWin;
        this->_gameOverType = TGameOver::kCheckmate;
    }
}

void Game::updateTimer()
{
    if ( this->_state != TGameState::kActive )
    {
        this->_timerBlack.pause();
        this->_timerWhite.pause();
        return;
    }

    if ( this->_currentPlayerType == TPlayer::kBlack )
    {
        this->_timerBlack.start();
        this->_timerWhite.pause();
    }
    else
    {
        this->_timerBlack.pause();
        this->_timerWhite.start();
    }
}

void Game::printBoard() const
{
    std::cout << this->_board.toString() << std::endl;
}

void Game::print() const
{
    std::cout << "Current Player: "
              << PlayerUtil::typeToString(this->_currentPlayerType)
              << std::endl;
    this->printBoard();
}

void Game::update()
{
    for ( ;; )
    {
        this->print();

        Position from, to;
        std::cin >> from.x >> from.y;

        if ( !this->_board.isPositionValid(from) ||
             this->_board(from) == nullptr )
        {
            std::cout << "Invalid position" << std::endl;
            continue;
        }

        std::cout
            << "(" << from.x << ", " << from.y << ") "
            << "type=" << this->_board(from)->getTypeString() << ", "
            << "owner="
            << PlayerUtil::typeToString(this->_board(from)->getOwner())
            << std::endl;

        std::vector<Position> movablePos =
            MoveHandler::getMovablePositions(this->_board, from);

        std::cout << "Movable Positions:" << std::endl;
        for ( const Position &p : movablePos )
            std::cout << "(" << p.x << "," << p.y << ")" << std::endl;

        std::cin >>
            to.x >> to.y;

        Move move(this->getCurrentPlayerType(), from, to);
        bool success = this->makeMove(move);
        std::cout << "Success: " << success << std::endl;
    }
}