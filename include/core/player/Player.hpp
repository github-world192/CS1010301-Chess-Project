/**
 *  File: Player.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/09 23:56:47
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/10 01:10:13
 *  Description: Player Class
 */

#pragma once

#include "TPlayer.hpp"

#include <string>

namespace Chess
{

    class Player
    {
    private:
        TPlayer _type;
        std::string _name;

    public:
        Player(TPlayer type) : _type(type) {}
        Player(TPlayer type, const std::string &name) : _type(type),
                                                        _name(name) {}

    public:
        TPlayer type() const { return this->_type; }
    };

}