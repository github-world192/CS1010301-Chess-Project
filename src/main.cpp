/**
 *  File: main.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/09 22:57:03
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/11 03:04:21
 *  Description: Program Entry Point
 */

// #include "gui/GUI.hpp"
#include "core/Game.hpp"
#include "core/Move.hpp"

using namespace Chess;
using namespace std;

int main(int argc, char *argv[])
{
    // GUI gui;
    // gui.Run();

    Game game;
    for ( ;; )
    {
        game.print();

        Position from, to;
        cin >> from.x >> from.y;
        cin >> to.x >> to.y;

        Move move(game.getCurrentPlayerType(), from, to);
        bool success = game.makeMove(move);
        cout << "Success: " << success << endl;
    }

    return 0;
}