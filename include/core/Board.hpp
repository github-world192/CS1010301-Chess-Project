/**
 *  File: Board.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/09 23:03:02
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/10 21:11:41
 *  Description: Board Class
 */

#pragma once

#include "Position.hpp"
#include "Spot.hpp"
#include "piece/Pawn.hpp"

#include <iostream>
#include <vector>

namespace Chess
{

    class Board
    {
    private:
        std::vector<Spot> _board;
        size_t _width;
        size_t _height;

    public:
        Board(size_t width = 9, size_t height = 8)
            : _width(width), _height(height)
        {
            for ( size_t i = 0; i < this->_height; ++i )
            {
                for ( size_t j = 0; j < this->_width; ++j )
                {
                    IPiece *pawn = new Pawn();
                    Position pos(j, i);
                    Spot spot(pawn, pos);
                    this->_board.push_back(spot);
                }
            }
        }

    public:
        inline const Spot &operator()(const Position &pos) const
        {
            for ( const Spot &s : this->_board )
            {
                if ( s.getPosition() == pos )
                    return s;
            }
            throw "Invalid position";
        }

    private:
        inline Spot &operator()(const Position &pos)
        {
            for ( Spot &s : this->_board )
            {
                if ( s.getPosition() == pos )
                    return s;
            }
            throw "Invalid position";
        }
    };

}