/**
 *  File: Game.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/09 22:57:37
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/11 18:22:56
 *  Description: Chess Class
 */

#include "core/Game.hpp"
#include "core/MoveHandler.hpp"
#include "core/player/Player.hpp"
#include "core/player/PlayerUtil.hpp"

using namespace Chess;

Game::Game()
{
    this->_players.push_back(Player(TPlayer::kWhite));
    this->_players.push_back(Player(TPlayer::kBlack));
    this->_currentPlayerType = TPlayer::kWhite;
    this->_board.initialize();
}

bool Game::makeMove(const Move &move)
{
    if ( move.getPlayerType() != this->_currentPlayerType )
        return false;

    if ( !MoveHandler::isMoveValid(this->_board, move) )
        return false;

    if ( this->_board.move(move.getFrom(), move.getTo()) )
    {
        this->swapCurrentPlayerType();
        return true;
    }

    return false;
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