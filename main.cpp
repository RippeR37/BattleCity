/**************************************************
Autor: Damian "RippeR" Dyñdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#include <ctime>
#include "Game.h"
#undef main

int main() {
    srand(time(NULL));

    CGame &Game = CGame::Get();
    Game.Window()->Set(640, 480, 32, false);
    Game.Init();

    return 0;
}
