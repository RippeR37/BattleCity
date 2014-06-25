/**************************************************
Autor: Damian "RippeR" Dyńdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#include <iostream>
#include "GameTimer.h"
#include "Game.h"
using namespace std;

void CGameTimer::Init() {
    m_enemy_spawn_time = 3;                 m_current_enemy_time = 2.5;
    m_player_spawn_time = 1;                m_current_player_time = 0;
    m_nextmap_change_time = 3;              m_current_nextmap_time = 0;
    m_current_levelprotect_time = 0;        m_levelprotect_time = 15.0;
    m_current_ressurection_player_one=0;    m_current_ressurection_player_two=0;
    m_current_game_lost_time = 0;           m_game_lost_time = 6.0;

    m_levelprotect = false;

    m_enemies_at_once = 4;
    m_ressurection_player = 0.5;
}

void CGameTimer::SetLevelProtect(bool protect) {
    m_levelprotect = true;

    LVL_FIELD field;
    if(protect) field = LVL_WHITE;
    else        field = LVL_BRICK;

    CGame::Get().Level()->SetLevelField(11, 0, field);
    CGame::Get().Level()->SetLevelField(11, 1, field);
    CGame::Get().Level()->SetLevelField(11, 2, field);
    CGame::Get().Level()->SetLevelField(12, 2, field);
    CGame::Get().Level()->SetLevelField(13, 2, field);
    CGame::Get().Level()->SetLevelField(14, 0, field);
    CGame::Get().Level()->SetLevelField(14, 1, field);
    CGame::Get().Level()->SetLevelField(14, 2, field);
}

void CGameTimer::DrawStageSelect() {
    CGame::Get().GUI()->RenderText("STAGE " + ToString(m_showed_level), 230, 230, COLOR_BLACK);
}

void CGameTimer::ProcessEvents() {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            CGame::Get().EndGame();
        } else if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.sym == SDLK_ESCAPE) {
                CGame::Get().SetGameState(GS_MENU);
            } else if(CGame::Get().Level()->LevelNum() == 0) {
                if(event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_RIGHT) {
                    int i = m_selected_level + 1;
                    if(i>CGame::Get().Level()->AllLevels()) i = CGame::Get().Level()->AllLevels();
                    m_selected_level = m_showed_level = i;
                } else if(event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_LEFT) {
                    int i = m_selected_level - 1;
                    if(i < 1) i = 1;
                    m_selected_level = m_showed_level = i;
                } else if(event.key.keysym.sym == SDLK_RETURN) {
                    ChooseLevel();
                }
            }
        }
    }
}

void CGameTimer::ChooseLevel() {
    if(m_selected_level > CGame::Get().Level()->AllLevels()) m_selected_level = 1;
    string level = "data/levels/" + ToString(m_selected_level) + ".lvl";

    CGame::Get().Level()->LoadLevel(level);
    CGame::Get().Audio()->PlayChunk(SOUND_GAMESTART);

    CGame::Get().Bullets()->DestroyAllBullets();
    CGame::Get().Effects()->DestroyAllEffects();
    CGame::Get().Enemies()->DestroyAllEnemies();
    CGame::Get().Enemies()->UnPause();

    CGame::Get().Player()->SetInvincibility(5);
    CGame::Get().Player()->Born();
    if(CGame::Get().PlayerTwo() != NULL) {
        CGame::Get().PlayerTwo()->SetInvincibility(5);
        CGame::Get().PlayerTwo()->Born();
    }

    CGame::Get().Items()->DestroyItem();
    CGame::Get().StartGameplay();
    CGame::Get().SetGameState(GS_GAMEPLAY);
    Init();
}

void CGameTimer::Update(double dt) {
    static int TailSize = CGame::Get().TailSize();
    if(CGame::Get().GameState() == GS_GAMEPLAY) {
        //Sprawdzanie ilości przeciwników, ew. respawn przeciwników
        if(CGame::Get().Enemies()->AliveEnemies() < m_enemies_at_once && CGame::Get().Enemies()->Enemies() < 20) {
            m_current_enemy_time += dt;
            if(m_current_enemy_time >= m_enemy_spawn_time) {
                CGame::Get().Enemies()->CreateEnemy();
                m_current_enemy_time = 0;
                m_enemy_spawn_animation = false;
            } else if(m_current_enemy_time >= m_enemy_spawn_time - 0.5 && m_enemy_spawn_animation == false) {
                int x = CGame::Get().Enemies()->NextSpawnX();
                CGame::Get().Effects()->CreateEffect(TailSize*x, TailSize*24, EFFECT_SPAWN);
                m_enemy_spawn_animation = true;
            }

        } else if(CGame::Get().Enemies()->Enemies() == 20 && CGame::Get().Enemies()->AliveEnemies() == 0 && CGame::Get().GameLost() == false) {
            m_current_nextmap_time += dt;
            if(m_current_nextmap_time >= m_nextmap_change_time) {
                //Zmiana poziomu [!!!]
                CGame::Get().SetGameState(GS_STAGESELECT);
                ++m_selected_level;
                ++m_showed_level;
                m_current_nextmap_time = 0.0;
            }
        }

        if(CGame::Get().Player()->Lifes() < 0 && (CGame::Get().PlayerTwo() == NULL || CGame::Get().PlayerTwo()->Lifes() < 0)) {
            CGame::Get().SetGameLost(true);
        }

        if(CGame::Get().GameLost()) {
            if(m_current_game_lost_time == 0.0)
                CGame::Get().Audio()->PlayChunk(SOUND_GAMEOVER);

            m_current_game_lost_time += dt;
            if(m_current_game_lost_time >= m_game_lost_time) {
                CGame::Get().SetGameState(GS_MENU);
                m_current_game_lost_time = 0.0;
            }
        }

        //Narodziny gracza
        if(CGame::Get().Player()->Alive() == false && CGame::Get().Player()->Lifes() >= 0) {
            if(m_current_ressurection_player_one == 0.0)
                CGame::Get().Effects()->CreateEffect(TailSize*8, 0, EFFECT_SPAWN);

            m_current_ressurection_player_one += dt;
            if(m_current_ressurection_player_one >= m_ressurection_player) {
                CGame::Get().Player()->Born();
                m_current_ressurection_player_one = 0;
            }
        }
        if(CGame::Get().PlayerTwo() != NULL) {
            if(CGame::Get().PlayerTwo()->Alive() == false && CGame::Get().PlayerTwo()->Lifes() >= 0) {
                if(m_current_ressurection_player_two == 0.0)
                    CGame::Get().Effects()->CreateEffect(TailSize*16, 0, EFFECT_SPAWN);

                m_current_ressurection_player_two += dt;
                if(m_current_ressurection_player_two >= m_ressurection_player) {
                    CGame::Get().PlayerTwo()->Born();
                    m_current_ressurection_player_two = 0;
                }
            }
        }

        //Ochrona godła
        if(m_levelprotect) {
            m_current_levelprotect_time += dt;
            if(m_current_levelprotect_time >= m_levelprotect_time) {
                m_levelprotect = false;
                SetLevelProtect(false);
                m_current_levelprotect_time = 0.0;
            }

            if(m_current_levelprotect_time >= m_levelprotect_time - 0.5)
                SetLevelProtect(true);
            else if(m_current_levelprotect_time >= m_levelprotect_time - 1)
                SetLevelProtect(false);
            else if(m_current_levelprotect_time >= m_levelprotect_time - 1.5)
                SetLevelProtect(true);
            else if(m_current_levelprotect_time >= m_levelprotect_time - 2)
                SetLevelProtect(false);
        }
    } else if(CGame::Get().GameState() == GS_STAGESELECT) {
        if(CGame::Get().Level()->LevelNum() != 0) {
            m_current_nextmap_time += dt;
            if(m_current_nextmap_time >= m_nextmap_change_time) {
                m_current_nextmap_time = 0.0;
                ChooseLevel();
            }
        }
    }
}
