/**
 *  File: Game.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/09 22:57:37
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/11 03:05:51
 *  Description: Chess Class
 */

#include "core/Game.hpp"
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

    if ( this->_board.move(move.getFrom(), move.getTo()) )
    {
        if ( this->_currentPlayerType == TPlayer::kWhite )
            this->_currentPlayerType = TPlayer::kBlack;
        else
            this->_currentPlayerType = TPlayer::kWhite;
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