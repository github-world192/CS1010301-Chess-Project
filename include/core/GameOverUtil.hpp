/**
 *  File: GameOverUtil.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/20 02:49:43
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/20 02:55:26
 *  Description: Game Over Utility
 */

#pragma once

#include "TGameOver.hpp"

#include <string>

namespace Chess
{

    class GameOverUtil
    {
    public:
        static inline std::string typeToStr(TGameOver type)
        {
            switch ( type )
            {
            case TGameOver::kCheckmate:
                return "checkmate";
            case TGameOver::kForfeit:
                return "forfeit";
            case TGameOver::kNone:
                return "none";
            case TGameOver::kResignation:
                return "resignation";
            case TGameOver::kTimeout:
                return "timeout";
            }
        }
    };

}