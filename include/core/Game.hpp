/**
 *  File: Game.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/09 22:57:49
 *  Editor: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Update Date: 2023/05/16 23:05:38
 *  Description: Game Class
 */

#pragma once

#include "Board.hpp"
#include "Move.hpp"
#include "TGameState.hpp"
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
        TGameState _state;

    public:
        Game();

    public:
        inline void initialize()
        {
            this->_players.clear();
            this->_players.push_back(Player(TPlayer::kWhite));
            this->_players.push_back(Player(TPlayer::kBlack));
            this->_currentPlayerType = TPlayer::kWhite;
            this->_state = TGameState::kActive;
            this->_board.loadDefaultBoard();
        }

        inline void initialize(TPlayer first)
        {
            this->_players.clear();
            this->_players.push_back(Player(TPlayer::kWhite));
            this->_players.push_back(Player(TPlayer::kBlack));
            this->_currentPlayerType = first;
            this->_state = TGameState::kActive;
            this->_board.loadDefaultBoard();
        }

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

        inline const Board &getBoard() const { return this->_board; }

        inline TGameState getGameState() const { return this->_state; }

        inline void resign()
        {
            (this->_currentPlayerType == TPlayer::kBlack)
                ? this->_state = TGameState::kWhiteWin
                : this->_state = TGameState::kBlackWin;
        }

        std::vector<Position> getBoardPieceMovablePos(const Position &pos) const;

    public:
        bool makeMove(const Move &move);

        void printBoard() const;
        void print() const;
        void update();
    };

};