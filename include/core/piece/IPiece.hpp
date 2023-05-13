/**
 *  File: IPiece.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/09 23:07:16
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/13 07:03:06
 *  Description: Piece Interface
 */

#pragma once

#include "../Position.hpp"
#include "../player/TPlayer.hpp"
#include "PieceUtil.hpp"
#include "TPiece.hpp"

#include <string>
#include <vector>

namespace Chess
{

    class IPiece
    {
    protected:
        TPiece _type;
        TPlayer _owner;
        bool _killed{false};
        bool _moved{false};

    public:
        virtual ~IPiece() = default;

    public:
        inline TPiece type() const { return this->_type; }
        inline TPlayer getOwner() const { return this->_owner; }
        inline bool isWhite() const { return this->_owner == TPlayer::kWhite; }
        inline bool isBlack() const { return this->_owner == TPlayer::kBlack; }
        inline bool getKilled() const { return this->_killed; }
        inline void setKilled(bool killed) { this->_killed = killed; }
        inline bool dead() const { return this->_killed; }
        inline void kill() { this->setKilled(true); }
        inline void alive() { this->setKilled(false); }
        inline bool getMoved() const { return this->_killed; }
        inline void setMoved(bool moved) { this->_killed = moved; }

        inline std::string getTypeString() const
        {
            return PieceUtil::typeToString(this->_type);
        }
    };

}