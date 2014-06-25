/**************************************************
Autor: Damian "RippeR" Dyńdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#include <iostream>
#include "Game.h"
#include "Menu.h"
#include "Renderer.h"
using namespace std;

void CMenu::Init() {
    m_Background = CGame::Get().Sprites()->Get("lvl_background");
    m_Logo = CGame::Get().Sprites()->Get("menu_logo");
    m_MenuOptions = CGame::Get().Sprites()->Get("menu_options");
    m_Pointer = CGame::Get().Sprites()->Get("player_one_right_0");
}

void CMenu::DrawMenu() {
    //Czarne tło
    CGame::Get().Renderer()->DrawSprite(m_Background, 0, -32, -16, 640, 480);  //Wymiary całego okna
    CGame::Get().Renderer()->DrawSprite(m_Logo, 0, 110, 260, m_Logo.width, m_Logo.height);
    CGame::Get().Renderer()->DrawSprite(m_MenuOptions, 0, 232, 150, m_MenuOptions.width, m_MenuOptions.height);

    switch(m_selected_item) {
        case 1:
            CGame::Get().Renderer()->DrawSprite(m_Pointer, 0, 190, 205, m_Pointer.width, m_Pointer.height); break;
        case 2:
            CGame::Get().Renderer()->DrawSprite(m_Pointer, 0, 190, 173, m_Pointer.width, m_Pointer.height); break;
        case 3:
            CGame::Get().Renderer()->DrawSprite(m_Pointer, 0, 190, 140, m_Pointer.width, m_Pointer.height); break;
    }

    CGame::Get().GUI()->RenderText("RIPPER", 500, 0);
}

void CMenu::ChooseItem() {
    switch(m_selected_item) {
        case 1:
            CGame::Get().SetGameState(GS_STAGESELECT);
            CGame::Get().Player()->SetLifes(2);
            CGame::Get().Player()->Born();
            CGame::Get().DeletePlayerTwo();
            break;
        case 2:
            CGame::Get().SetGameState(GS_STAGESELECT);
            CGame::Get().SetupPlayerTwo();
            CGame::Get().Player()->SetLifes(2);
            CGame::Get().PlayerTwo()->SetLifes(2);
            CGame::Get().Player()->Born();
            CGame::Get().PlayerTwo()->Born();
            break;
        case 3:
            CGame::Get().SetGameState(GS_EDITOR);
            CGame::Get().Level()->LoadLevel("data/levels/temp.lvl");
            break;
    }
}

void CMenu::ProcessEvents() {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            CGame::Get().EndGame();
        } else if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.sym == SDLK_ESCAPE) {
                CGame::Get().EndGame();
            } else if(event.key.keysym.sym == SDLK_UP) {
                int i = SelectedItem() - 1;
                if(i==0) i = 3;
                SelectItem(i);
            } else if(event.key.keysym.sym == SDLK_DOWN) {
                int i = SelectedItem() + 1;
                if(i==4) i = 1;
                SelectItem(i);
            } else if(event.key.keysym.sym == SDLK_RETURN) {
                ChooseItem();
            }
        }
    }
}
