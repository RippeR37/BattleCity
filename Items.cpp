/**************************************************
Autor: Damian "RippeR" Dyñdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#include "Items.h"
#include "Game.h"
using namespace std;

void CItems::Draw() {
    static double tail_size = CGame::Get().TailSize();
    if(m_current_item.destroyed == false) {
        CGame::Get().Renderer()->DrawSprite(m_current_item.sprite, 0, m_current_item.x * tail_size, m_current_item.y * tail_size, tail_size*2, tail_size*2);
    }
}

void CItems::Update(double dt) {
    if(m_current_item.destroyed == false) {
        m_current_item.frame_duration += dt;
        if(m_current_item.frame_duration >= m_current_item.sprite.frame_duration) {
            m_current_item.is_visible = !m_current_item.is_visible;
            m_current_item.frame_duration = 0;
        }
    }
}

void CItems::CreateItem() {
    m_current_item.x = rand()%21 + 2;
    m_current_item.y = rand()%21 + 2;
    m_current_item.type = ITEM_TYPE(rand()%6);
    m_current_item.frame_duration = 0.0;
    m_current_item.is_visible = true;
    m_current_item.destroyed = false;
    switch(m_current_item.type) {
        case ITEM_STAR:
            m_current_item.sprite = CGame::Get().Sprites()->Get("item_star"); break;
        case ITEM_LIFE:
            m_current_item.sprite = CGame::Get().Sprites()->Get("item_life"); break;
        case ITEM_INVINCIBILITY:
            m_current_item.sprite = CGame::Get().Sprites()->Get("item_invincibility"); break;
        case ITEM_PROTECT:
            m_current_item.sprite = CGame::Get().Sprites()->Get("item_protect"); break;
        case ITEM_TIME:
            m_current_item.sprite = CGame::Get().Sprites()->Get("item_time"); break;
        case ITEM_GRANADE:
            m_current_item.sprite = CGame::Get().Sprites()->Get("item_granade"); break;
    }
}
