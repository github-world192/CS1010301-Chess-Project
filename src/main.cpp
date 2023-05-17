/**
 *  File: main.cpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/09 22:57:03
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/17 20:17:34
 *  Description: Program Entry Point
 */

#include "gui/GUI.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    GUI gui(argc, argv);
    gui.Run();

    return 0;
}