/**
 *  File: Game.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/09 22:57:37
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/17 14:01:04
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
    return MoveHandler::getMovablePositions((Board &)(this->_board), pos);
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
    TPlayer enemy = (this->_currentPlayerType == TPlayer::kBlack)
                        ? TPlayer::kWhite
                        : TPlayer::kBlack;

    std::vector<Position> kingPos =
        this->_board.findPiecesPos(this->_currentPlayerType, TPiece::kKing);

    // If king not exists, is checkmate
    if ( kingPos.size() < 1 )
        return true;

    // Get all pieces movable positions without king
    std::vector<Position> piecesPosWithoutKing =
        this->_board.findPiecesPosExcept(this->_currentPlayerType, TPiece::kKing);

    // Get king movable/killable positions
    std::vector<Position> kingMovablePos =
        MoveHandler::getMovableKillablePositions(this->_board, kingPos[0]);

    // If there still have a way to move
    if ( kingMovablePos.size() > 0 )
        return false;

    // Get all movable/killable position without king
    std::vector<Position> movablePosWithoutKing;
    for ( const Position &mp : piecesPosWithoutKing )
    {
        std::vector<Position> movablePos =
            MoveHandler::getMovableKillablePositions(this->_board, mp);
        movablePosWithoutKing.insert(movablePosWithoutKing.end(),
                                     movablePos.begin(), movablePos.end());
    }

    // If there still have a way to move, not checkmate
    if ( movablePosWithoutKing.size() != 0 )
        return false;

    return true;
}

void Game::updateGameState()
{
    if ( this->getPlayerTime(TPlayer::kBlack) <= 0 )
    {
        this->_state = TGameState::kWhiteWin;
        return;
    }

    if ( this->getPlayerTime(TPlayer::kWhite) <= 0 )
    {
        this->_state = TGameState::kBlackWin;
        return;
    }

    if ( this->isCheckmate() )
    {
        this->_state = (this->_currentPlayerType == TPlayer::kBlack)
                           ? TGameState::kWhiteWin
                           : TGameState::kBlackWin;
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