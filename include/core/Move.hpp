/**
 *  File: Move.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/10 21:11:11
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/17 13:54:09
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
        inline TPlayer getPlayerType() const { return this->_player; }
        inline const Position &getFrom() const { return this->_fromPos; }
        inline const Position &getTo() const { return this->_toPos; }

    public:
        friend inline bool operator==(const Move m1, const Move m2)
        {
            return (
                m1._player == m2._player &&
                m1._fromPos == m2._fromPos &&
                m1._toPos == m2._toPos);
        }

        friend inline bool operator!=(const Move m1, const Move m2)
        {
            return (
                m1._player != m2._player ||
                m1._fromPos != m2._fromPos ||
                m1._toPos != m2._toPos);
        }
    };

}