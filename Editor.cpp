/**************************************************
Autor: Damian "RippeR" Dyñdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#include "Editor.h"
#include "Game.h"
#include <iostream>
using namespace std;

void CEditor::DrawEditor() {
    static SpriteData sprEditor = CGame::Get().Sprites()->Get("editor");
    CGame::Get().Renderer()->DrawSprite(sprEditor, 0, 450, 194, sprEditor.width, sprEditor.height);
}

void CEditor::LMB(int x, int y) {
    int x_off = x - CGame::Get().GameOffsetX();
    int y_off = CGame::Get().Window()->WindowHeight() - y - CGame::Get().GameOffsetY();
    static int tail_size = CGame::Get().TailSize();

    if(x_off >= 0 && x_off < 416 && y_off >=0 && y_off < 416) {
        CGame::Get().Level()->SetLevelField(x_off/tail_size, y_off/tail_size, m_current_field);
    } else if(x_off >= 459 && x_off <=491) {
        if(y_off >=354 && y_off <= 386) {
            m_current_field = LVL_BRICK;
        } else if(y_off >= 315 && y_off <= 347) {
            m_current_field = LVL_WHITE;
        } else if(y_off >= 278 && y_off <= 310) {
            m_current_field = LVL_SLIDE;
        } else if(y_off >= 242 && y_off <= 274) {
            m_current_field = LVL_BUSH;
        } else if(y_off >= 199 && y_off <= 231) {
            m_current_field = LVL_WATER;
        }
    }
}

void CEditor::RMB(int x, int y) {
    int x_off = x - CGame::Get().GameOffsetX();
    int y_off = CGame::Get().Window()->WindowHeight() - y - CGame::Get().GameOffsetY();
    static int tail_size = CGame::Get().TailSize();

    CGame::Get().Level()->SetLevelField(x_off/tail_size, y_off/tail_size, LVL_NONE);
}
