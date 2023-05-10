/**
 *  File: Game.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/09 22:57:49
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/11 03:02:14
 *  Description: Game Class
 */

#pragma once

#include "Board.hpp"
#include "Move.hpp"
#include "player/Player.hpp"

#include <iostream>

namespace Chess
{

    class Game
    {
    private:
        Board _board;
        std::vector<Player> _players;
        TPlayer _currentPlayerType;

    public:
        Game();

    public:
        inline TPlayer getCurrentPlayerType() const
        {
            return this->_currentPlayerType;
        }

    public:
        bool makeMove(const Move &move);

        void printBoard() const;
        void print() const;
    };

};