/**************************************************
Autor: Damian "RippeR" Dyñdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#include <iostream>
#include "Bullets.h"
#include "Game.h"
#include "Sprites.h"
using namespace std;

void CEffects::DestroyAllEffects() {
    m_effects.clear();
    m_effects_num = 0;
}

void CEffects::CreateEffect(double x, double y, EFFECT_TYPE type) {
    Effect temp_effect(m_effects_num, x, y);
    ++m_effects_num;

    temp_effect.destroyed = false;
    switch(type) {
        case EFFECT_SPAWN:
            temp_effect.sprite = CGame::Get().Sprites()->Get("effect_spawn");
            temp_effect.duration = 0.5;
            break;
        case EFFECT_EXPLODE:
            temp_effect.sprite = CGame::Get().Sprites()->Get("effect_explode");
            temp_effect.duration = 0.15;
            break;
    }

    m_effects.insert(m_effects.end(), temp_effect);
}

void CEffects::Draw() {
    for(list<Effect>::iterator iter = m_effects.begin(); iter != m_effects.end(); ++iter) {
        CGame::Get().Renderer()->DrawSprite((*iter).sprite, (*iter).frame, (*iter).x, (*iter).y, (*iter).sprite.width, (*iter).sprite.height);
    }
}

void CEffects::Update(double dt) {
    for(list<Effect>::iterator iter = m_effects.begin(); iter != m_effects.end(); ) {
        (*iter).current_duration += dt;
        (*iter).current_frame_duration += dt;

        if((*iter).current_duration >= (*iter).duration) {
            iter = DestroyEffect(iter);
        } else {
            if((*iter).current_frame_duration >= (*iter).sprite.frame_duration) {
                ++(*iter).frame;
                if((*iter).frame >= (*iter).sprite.frame_count) {
                    if((*iter).sprite.loop) (*iter).frame = 0;
                    else                    (*iter).frame = (*iter).sprite.frame_count - 1;
                }
                (*iter).current_frame_duration = 0;
            }
            ++iter;
        }
    }
}

list<Effect>::iterator CEffects::DestroyEffect(list<Effect>::iterator iter) {
    return m_effects.erase(iter);
}
