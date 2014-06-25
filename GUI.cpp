/**************************************************
Autor: Damian "RippeR" Dyńdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#include "GUI.h"
#include "Game.h"
using namespace std;

void CGUI::DrawGameplayStats() {
    //Rysowanie ilosci przeciwników
    static int x = 27;
    static int y = 25;
    static int TailSize = CGame::Get().TailSize();
    static SpriteData EnemyTank = CGame::Get().Sprites()->Get("enemy_stat");
    static SpriteData PlayerTank = CGame::Get().Sprites()->Get("player_stat");
    static SpriteData Flag = CGame::Get().Sprites()->Get("flag");

    for(int i=0; i< 20 - CGame::Get().Enemies()->Enemies(); ++i) {
        if(i%2 == 0)
            CGame::Get().Renderer()->DrawSprite(EnemyTank, 0, x*TailSize, int(y-(i/2))*TailSize, EnemyTank.width, EnemyTank.height);
        else
            CGame::Get().Renderer()->DrawSprite(EnemyTank, 0, (x+1)*TailSize, int(y-(i/2))*TailSize, EnemyTank.width, EnemyTank.height);
    }

    //Statystyki pierwszego gracza
    string lifes = "0";
    if(CGame::Get().Player()->Lifes() > 0)  lifes = ToString(CGame::Get().Player()->Lifes());

    RenderText("IP", x*TailSize, 10*TailSize, COLOR_BLACK);
    CGame::Get().Renderer()->DrawSprite(PlayerTank, 0, x*TailSize, 9*TailSize, PlayerTank.width, PlayerTank.height);
    RenderText(lifes, (x+1)*TailSize, 9*TailSize, COLOR_BLACK);

    if(CGame::Get().PlayerTwo() != NULL) {
        //Statystyki drugiego gracza
        lifes = "0";
        if(CGame::Get().PlayerTwo()->Lifes() > 0)  lifes = ToString(CGame::Get().PlayerTwo()->Lifes());

        RenderText("IIP", x*TailSize, 7*TailSize, COLOR_BLACK);
        CGame::Get().Renderer()->DrawSprite(PlayerTank, 0, x*TailSize, 6*TailSize, PlayerTank.width, PlayerTank.height);
        RenderText(lifes, (x+1)*TailSize, 6*TailSize, COLOR_BLACK);
    }

    CGame::Get().Renderer()->DrawSprite(Flag, 0, x*TailSize, 3*TailSize, Flag.width, Flag.height);
    RenderText(ToString(CGame::Get().GameTimer()->ShowedLevel()), (x+1)*TailSize, 2*TailSize, COLOR_BLACK);

    if(CGame::Get().GameLost()) {
        RenderText("GAME", 11*TailSize, 14*TailSize, COLOR_RED);
        RenderText("OVER", 11*TailSize, 13*TailSize, COLOR_RED);
    }
}

void CGUI::RenderText(const string& text, double x, double y, COLOR color) {
    static SpriteData chars = CGame::Get().Sprites()->Get("chars");
    static SpriteData signs = CGame::Get().Sprites()->Get("signs");
    static int pixels_per_one_sign = max(chars.width, signs.width);

    //Rysowanie
    int temp;
    for(int i=0; i<text.length(); ++i) {
        temp = int(text[i]);
        if(temp >= 65 && temp <=90) {               //Drukowane litery
            CGame::Get().Renderer()->DrawSprite(chars, temp-65, x + i*pixels_per_one_sign, y, chars.width, chars.height, color);
        } else if(temp >= 48 && temp <= 57) {       //Cyfry
            CGame::Get().Renderer()->DrawSprite(signs, temp-48, x + i*pixels_per_one_sign, y, chars.width, chars.height, color);
        }
    }
}
