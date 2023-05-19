/**
 *  File: TGameState.hpp
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/16 21:34:23
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/20 02:41:20
 *  Description: GameState Type definition
 */

#pragma once

namespace Chess
{

    enum class TGameState
    {
        kActive,
        kBlackWin,
        kWhiteWin,
        kForfeit,
        kStalement,
        kResignation
    };

}