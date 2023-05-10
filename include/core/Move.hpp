/**
 *  File: Move.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/10 21:11:11
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/11 01:48:11
 *  Description: Move Class
 */

#pragma once

#include "Position.hpp"
#include "player/TPlayer.hpp"

namespace Chess
{

    class Move
    {
    private:
        TPlayer _player;
        Position _fromPos;
        Position _toPos;

    public:
        Move(TPlayer player, const Position &from, const Position &to)
            : _player(player), _fromPos(from), _toPos(to) {}

    public:
        inline TPlayer getPlayer() const { return this->_player; }
        inline const Position &getFrom() const { return this->_fromPos; }
        inline const Position &getTo() const { return this->_toPos; }
    };

}