/**
 *  File: Board.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/09 23:03:02
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/16 16:39:09
 *  Description: Board Class
 */

#pragma once

#include "Position.hpp"
#include "piece/Bishop.hpp"
#include "piece/IPiece.hpp"
#include "piece/King.hpp"
#include "piece/Knight.hpp"
#include "piece/Pawn.hpp"
#include "piece/Queen.hpp"
#include "piece/Rook.hpp"

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

        ~Board()
        {
            this->_free();
        }

        Board(const Board &board);

    public:
        void loadDefaultBoard();
        void clear();

        inline size_t width() const { return this->_width; }
        inline size_t height() const { return this->_height; }

        inline bool isPositionValid(const Position &pos) const
        {
            return ((pos.x >= 0 && pos.x <= this->_width - 1) &&
                    (pos.y >= 0 && pos.y <= this->_height - 1));
        }

        inline bool isPositionPiece(const Position &pos) const
        {
            return (this->_board[pos.y][pos.x] != nullptr);
        }

        bool move(const Position &from, const Position &to);

        std::vector<const IPiece *> getPiecesByOwner(TPlayer player) const;

        inline std::string toString() const
        {
            std::string str;
            for ( std::vector<IPiece *> i : this->_board )
            {
                for ( IPiece *j : i )
                {
                    if ( j == nullptr )
                        str = str + "null" + '\t';
                    else
                        str = str + j->getTypeString() + '\t';
                }
                str += '\n';
            }
            return str;
        }

    private:
        bool _setPiece(const Position &pos, IPiece *piece);
        bool _removePiece(const Position &pos);
        void _moveWithoutCheck(const Position &from, const Position &to);

        void _free();

    public:
        inline IPiece *operator()(const Position &pos)
        {
            return this->_board[pos.y][pos.x];
        }

        inline const IPiece *operator()(const Position &pos) const
        {
            return this->_board[pos.y][pos.x];
        }
    };

}