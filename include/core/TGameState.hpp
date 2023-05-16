/**
 *  File: Filename
 *  Author: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Create Date: 2023/05/16 21:34:23
 *  Editor: 鄭健廷 (B11130225@mail.ntust.edu.tw)
 *  Update Date: 2023/05/16 22:08:11
 *  Description:
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