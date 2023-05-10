/**
 *  File: Position.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/10 00:12:29
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/11 02:51:01
 *  Description: Position Class
 */

#pragma once

namespace Chess
{

    class Position
    {
    public:
        int x;
        int y;

    public:
        Position() : x(0), y(0) {}
        Position(int x, int y) : x(x), y(y) {}

    public:
        inline Position operator+(const Position &pos)
        {
            Position r = (*this);
            r.x += pos.x;
            r.y += pos.y;
            return r;
        }

        inline Position operator-(const Position &pos)
        {
            Position r = (*this);
            r.x -= pos.x;
            r.y -= pos.y;
            return r;
        }

        inline bool operator==(const Position &pos) const
        {
            return (this->x == pos.x && this->y == pos.y);
        }
    };

}