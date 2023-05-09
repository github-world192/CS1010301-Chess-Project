/**
 *  File: Position.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/10 00:12:29
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/10 01:26:10
 *  Description: Position Class
 */

#pragma once

namespace Chess
{

    class Position
    {
    private:
        int _x;
        int _y;

    public:
        Position(int x, int y) : _x(x), _y(y) {}

    public:
        inline int x() const { return this->_x; }
        inline int y() const { return this->_y; }
        inline void x(int x) { this->_x = x; }
        inline void y(int y) { this->_y = y; }

    public:
        inline Position operator+(const Position &pos)
        {
            Position r = (*this);
            r._x += pos._x;
            r._y += pos._y;
            return r;
        }

        inline Position operator-(const Position &pos)
        {
            Position r = (*this);
            r._x -= pos._x;
            r._y -= pos._y;
            return r;
        }

        inline bool operator==(const Position &pos) const
        {
            return (this->_x == pos._x && this->_y == pos._y);
        }
    };

}