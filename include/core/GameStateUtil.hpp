/**
 *  File: GameStateUtil.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/17 04:12:17
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/17 04:15:42
 *  Description: Game State Utility
 */

#pragma once

#include "TGameState.hpp"

#include <string>

namespace Chess
{

    class GameStateUtil
    {
    public:
        static inline std::string typeToStr(TGameState state)
        {
            switch ( state )
            {
            case TGameState::kActive:
                return "active";
            case TGameState::kBlackWin:
                return "blackWin";
            case TGameState::kForfeit:
                return "forfeit";
            case TGameState::kResignation:
                return "resignation";
            case TGameState::kStalement:
                return "stalement";
            case TGameState::kWhiteWin:
                return "whiteWin";
            }
            return "undefined";
        }
    };

}