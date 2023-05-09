/**
 *  File: IPiece.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/09 23:07:16
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/10 01:36:41
 *  Description: Piece Interface
 */

#pragma once

#include "../Position.hpp"
#include "../player/TPlayer.hpp"

#include <vector>

namespace Chess
{

    class IPiece
    {
    protected:
        TPlayer _owner;
        bool _killed{false};
        bool _moved{false};

    public:
        inline bool getKilled() const { return this->_killed; }
        inline void setKilled(bool killed) { this->_killed = killed; }
        inline bool dead() const { return this->_killed; }
        inline void kill() { this->setKilled(true); }
        inline void alive() { this->setKilled(false); }

    public:
        virtual bool isPositionValid(const Position &pos) const = 0;
    };

}