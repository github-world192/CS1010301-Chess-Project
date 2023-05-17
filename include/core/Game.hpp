/**
 *  File: Game.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/09 22:57:49
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/17 22:26:44
 *  Description: Game Class
 */

#pragma once

#include "Board.hpp"
#include "Move.hpp"
#include "TGameState.hpp"
#include "Timer.hpp"
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
        Timer _timerBlack;
        Timer _timerWhite;
        time_t _matchTime;

    public:
        Game();

    public:
        inline void initialize()
        {
            this->initialize(TPlayer::kWhite);
        }

        inline void initialize(TPlayer first)
        {
            this->initialize(first, 600);
        }

        inline void initialize(TPlayer first, time_t matchTime)
        {
            this->_players.clear();
            this->_players.push_back(Player(TPlayer::kWhite));
            this->_players.push_back(Player(TPlayer::kBlack));
            this->_currentPlayerType = first;
            this->_state = TGameState::kActive;
            this->_board.clear();
            this->_board.loadDefaultBoard();
            this->_timerBlack.reset();
            this->_timerWhite.reset();
            this->_matchTime = matchTime;

            updateGameState();
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

        inline time_t getPlayerTime(TPlayer player) const
        {
            time_t time = (this->_matchTime - this->_getTimer(player).get());
            return time;
        }

        inline std::string getPlayerTimeStr(TPlayer player) const
        {
            Timer timer(this->getPlayerTime(player));
            return timer.str();
        }

    public:
        bool makeMove(const Move &move);

        bool isCheckmate() const;
        bool isPromoting() const;
        bool promoting(TPiece type);

        void updateGameState();
        void updateTimer();

        inline void updateGame()
        {
            updateGameState();
            updateTimer();
        }

        void printBoard() const;
        void print() const;
        void update();

    private:
        inline const Timer &_getTimer(TPlayer player) const
        {
            if ( player == TPlayer::kBlack )
                return this->_timerBlack;
            else
                return this->_timerWhite;
        }

        inline Timer &_getTimer(TPlayer player)
        {
            if ( player == TPlayer::kBlack )
                return this->_timerBlack;
            else
                return this->_timerWhite;
        }
    };

};