/**
 *  File: Game.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/09 22:57:37
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/10 21:13:58
 *  Description: Chess Class
 */

#include "core/Game.hpp"
#include "core/player/Player.hpp"

using namespace Chess;

Game::Game()
{
    this->_players.push_back(Player(TPlayer::kWhite));
    this->_players.push_back(Player(TPlayer::kBlack));
    this->_currentPlayerType = TPlayer::kWhite;
}