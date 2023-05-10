/**
 *  File: Board.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/09 23:03:02
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/11 02:08:13
 *  Description: Board Class
 */

#pragma once

#include "Position.hpp"
#include "piece/IPiece.hpp"
#include "piece/Pawn.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

namespace Chess
{

    class Board
    {
    private:
        std::vector<std::vector<IPiece *>> _board;
        size_t _width;
        size_t _height;

    public:
        Board(size_t width = 8, size_t height = 8)
            : _width(width), _height(height)
        {
            // Initialize board size
            this->_board.resize(height, std::vector<IPiece *>(width, nullptr));
        }

        ~Board() { this->_free(); }

    public:
        inline bool isPositionValid(const Position &pos) const
        {
            return ((pos.x() >= 0 && pos.x() <= this->_width - 1) &&
                    (pos.y() >= 0 && pos.y() <= this->_height - 1));
        }

        bool initialize();
        inline void clear();

        void moveWithoutCheck(const Position &from, const Position &to);

    private:
        bool _setPiece(const Position &pos, IPiece *piece);
        bool _removePiece(const Position &pos);

        inline void _free()
        {
            for ( std::vector<IPiece *> i : this->_board )
            {
                for ( IPiece *j : i )
                {
                    // Delete all pieces
                    if ( j != nullptr )
                        delete j;
                }
            }
        }

    private:
        inline IPiece *operator()(const Position &pos)
        {
            return this->_board[pos.y()][pos.x()];
        }
    };

}