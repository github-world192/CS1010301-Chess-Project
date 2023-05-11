/**
 *  File: Game.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/09 22:57:49
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/11 17:58:14
 *  Description: Game Class
 */

#pragma once

#include "Board.hpp"
#include "Move.hpp"
#include "player/Player.hpp"

#include <iostream>
#include <stdexcept>

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
        inline bool isPlayerExists(TPlayer type) const
        {
            for ( const Player &p : this->_players )
            {
                if ( p.type() == type )
                    return true;
            }
            return false;
        }

        inline const Player &getPlayer(TPlayer type) const
        {
            for ( const Player &p : this->_players )
            {
                if ( p.type() == type )
                    return p;
            }

            throw std::invalid_argument("Player not exists");
        }

        inline TPlayer getCurrentPlayerType() const
        {
            return this->_currentPlayerType;
        }

        inline void setCurrentPlayerType(TPlayer type)
        {
            this->_currentPlayerType = type;
        }

        inline void swapCurrentPlayerType()
        {
            if ( this->_currentPlayerType == TPlayer::kWhite )
                this->_currentPlayerType = TPlayer::kBlack;
            else
                this->_currentPlayerType = TPlayer::kWhite;
        }

    public:
        bool makeMove(const Move &move);

        void printBoard() const;
        void print() const;
        void update();
    };

};