/**************************************************
Autor: Damian "RippeR" Dyńdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#include <cmath>
#include <iostream>
#include "Enemy.h"
#include "Game.h"
#include "Sprites.h"
using namespace std;

void CEnemy::Init(int x, int y, ENEMY_TYPE type) {
    m_x = x; m_y = y;
    m_speed = 3;

    if(int(type) >= 4)
        m_frame = 1;
    else
        m_frame = 0;

    m_frame_duration = 0.0;
    m_enemy_width = 32;
    m_enemy_height = 32;
    m_can_shoot = true;
    m_bullets_in_game = 0;
    m_turn_wait_time = (rand()%36 + 5)/10.0;

    if(int(type) == 3 || int(type) == 7)
        m_level = 4;
    else
        m_level = 1;

    SetEnemyType(type);
    Drive();
}

void CEnemy::Drive() {
    SetXVelocity(0); SetYVelocity(0);

    switch(m_direction) {
        case DIR_UP:
            m_vy = m_speed; break;
        case DIR_DOWN:
            m_vy = -m_speed; break;
        case DIR_LEFT:
            m_vx = -m_speed; break;
        case DIR_RIGHT:
            m_vx = m_speed; break;
    }
}

void CEnemy::SetEnemyType(ENEMY_TYPE type) {
    switch(type) {
        case ENEMY_SLOW:
            m_sprite_up = "enemy_slow_up";
            m_sprite_down = "enemy_slow_down";
            m_sprite_left = "enemy_slow_left";
            m_sprite_right = "enemy_slow_right";
            m_enemy_type = type;
            m_bullet_speed = 8;
            m_bullet_power = 1;
            m_max_bullets = 1;
            break;
        case ENEMY_SLOW_BONUS:
            m_sprite_up = "enemy_slow_bonus_up";
            m_sprite_down = "enemy_slow_bonus_down";
            m_sprite_left = "enemy_slow_bonus_left";
            m_sprite_right = "enemy_slow_bonus_right";
            m_enemy_type = type;
            m_bullet_speed = 8;
            m_bullet_power = 1;
            m_max_bullets = 1;
            break;
        case ENEMY_FAST:
            m_sprite_up = "enemy_fast_up";
            m_sprite_down = "enemy_fast_down";
            m_sprite_left = "enemy_fast_left";
            m_sprite_right = "enemy_fast_right";
            m_enemy_type = type;
            m_speed = 7;
            m_bullet_speed = 15;
            m_bullet_power = 1;
            m_max_bullets = 1;
            break;
        case ENEMY_FAST_BONUS:
            m_sprite_up = "enemy_fast_bonus_up";
            m_sprite_down = "enemy_fast_bonus_down";
            m_sprite_left = "enemy_fast_bonus_left";
            m_sprite_right = "enemy_fast_bonus_right";
            m_enemy_type = type;
            m_speed = 7;
            m_bullet_speed = 15;
            m_bullet_power = 1;
            m_max_bullets = 1;
            break;
        case ENEMY_MEDIUM:
            m_sprite_up = "enemy_medium_up";
            m_sprite_down = "enemy_medium_down";
            m_sprite_left = "enemy_medium_left";
            m_sprite_right = "enemy_medium_right";
            m_enemy_type = type;
            m_bullet_speed = 23;
            m_bullet_power = 1;
            m_max_bullets = 1;
            break;
        case ENEMY_MEDIUM_BONUS:
            m_sprite_up = "enemy_medium_bonus_up";
            m_sprite_down = "enemy_medium_bonus_down";
            m_sprite_left = "enemy_medium_bonus_left";
            m_sprite_right = "enemy_medium_bonus_right";
            m_enemy_type = type;
            m_bullet_speed = 23;
            m_bullet_power = 1;
            m_max_bullets = 1;
            break;
        case ENEMY_BIG:
            m_sprite_up = "enemy_big_up";
            m_sprite_down = "enemy_big_down";
            m_sprite_left = "enemy_big_left";
            m_sprite_right = "enemy_big_right";
            m_enemy_type = type;
            m_speed = 3;
            m_bullet_speed = 15;
            m_bullet_power = 1;
            m_max_bullets = 1;
            break;
        case ENEMY_BIG_BONUS:
            m_sprite_up = "enemy_big_bonus_up";
            m_sprite_down = "enemy_big_bonus_down";
            m_sprite_left = "enemy_big_bonus_left";
            m_sprite_right = "enemy_big_bonus_right";
            m_enemy_type = type;
            m_speed = 3;
            m_bullet_speed = 15;
            m_bullet_power = 1;
            m_max_bullets = 1;
            break;
    }
}

void CEnemy::Shoot() {
    if(m_can_shoot) {
        CGame::Get().Audio()->PlayChunk(SOUND_FIRE);
        CGame::Get().Bullets()->CreateBullet(m_x, m_y, m_direction, OWN_ENEMY, m_id, m_bullet_speed);
        ++m_bullets_in_game;
        if(m_bullets_in_game >= m_max_bullets) {
            m_can_shoot = false;
        }
    }
}

void CEnemy::DecreaseBullet() {
    --m_bullets_in_game;
    m_can_shoot = true;
}

void CEnemy::Draw() {
    double pos_x = m_x * CGame::Get().TailSize();
    double pos_y = m_y * CGame::Get().TailSize();

    int frame = m_frame;
    if(m_enemy_type == ENEMY_BIG) {
        switch(m_level) {
            case 2: frame += 6; break;
            case 3: frame += 8; break;
            case 4: frame += 10; break;
        }
    }

    switch (m_direction) {
        case DIR_UP:
            CGame::Get().Renderer()->DrawSprite(CGame::Get().Sprites()->Get(m_sprite_up), frame, pos_x, pos_y, m_enemy_width, m_enemy_height); break;
        case DIR_DOWN:
            CGame::Get().Renderer()->DrawSprite(CGame::Get().Sprites()->Get(m_sprite_down), frame, pos_x, pos_y, m_enemy_width, m_enemy_height); break;
        case DIR_LEFT:
            CGame::Get().Renderer()->DrawSprite(CGame::Get().Sprites()->Get(m_sprite_left), frame, pos_x, pos_y, m_enemy_width, m_enemy_height); break;
        case DIR_RIGHT:
            CGame::Get().Renderer()->DrawSprite(CGame::Get().Sprites()->Get(m_sprite_right), frame, pos_x, pos_y, m_enemy_width, m_enemy_height); break;
    }
}

void CEnemy::Update(double dt) {
    m_x = m_x + m_vx * dt * m_speed_ratio;
    m_y = m_y + m_vy * dt * m_speed_ratio;

    m_colide = false;

    //Wyjechanie poza mapę
    if(m_x < 0.0)  { m_x = 0.0; m_colide = true; }
    if(m_x > 24.0) { m_x = 24.0; m_colide = true; }
    if(m_y < 0.0)  { m_y = 0.0; m_colide = true; }
    if(m_y > 24.0) { m_y = 24.0; m_colide = true; }

    int pos_x_l = m_x, pos_x_s = m_x + 1, pos_x_p = m_x + 2;
    int pos_y_d = m_y, pos_y_s = m_y + 1, pos_y_g = m_y + 2;

    //Detekcja kolizji
    if(m_vx < 0 && m_x > 0.0) {
        if(CGame::Get().Level()->LevelField(pos_x_l,pos_y_d) == LVL_BRICK ||
           CGame::Get().Level()->LevelField(pos_x_l,pos_y_d) == LVL_BRICK_DAMAGED ||
           CGame::Get().Level()->LevelField(pos_x_l,pos_y_d) == LVL_WHITE ||
           CGame::Get().Level()->LevelField(pos_x_l,pos_y_d) == LVL_WATER ||
           CGame::Get().Level()->LevelField(pos_x_l,pos_y_d) == LVL_EAGLE ||
           CGame::Get().Level()->LevelField(pos_x_l,pos_y_s) == LVL_BRICK ||
           CGame::Get().Level()->LevelField(pos_x_l,pos_y_s) == LVL_BRICK_DAMAGED ||
           CGame::Get().Level()->LevelField(pos_x_l,pos_y_s) == LVL_WHITE ||
           CGame::Get().Level()->LevelField(pos_x_l,pos_y_s) == LVL_WATER ||
           CGame::Get().Level()->LevelField(pos_x_l,pos_y_s) == LVL_EAGLE) {
            //Kolizja od lewej strony czolgu
            m_x = pos_x_s;
            m_colide = true;
        }
    } else if(m_vx > 0 && m_x < 24.0) {
        if(CGame::Get().Level()->LevelField(pos_x_p,pos_y_d) == LVL_BRICK ||
           CGame::Get().Level()->LevelField(pos_x_p,pos_y_d) == LVL_BRICK_DAMAGED ||
           CGame::Get().Level()->LevelField(pos_x_p,pos_y_d) == LVL_WHITE ||
           CGame::Get().Level()->LevelField(pos_x_p,pos_y_d) == LVL_WATER ||
           CGame::Get().Level()->LevelField(pos_x_p,pos_y_d) == LVL_EAGLE ||
           CGame::Get().Level()->LevelField(pos_x_p,pos_y_s) == LVL_BRICK ||
           CGame::Get().Level()->LevelField(pos_x_p,pos_y_s) == LVL_BRICK_DAMAGED ||
           CGame::Get().Level()->LevelField(pos_x_p,pos_y_s) == LVL_WHITE ||
           CGame::Get().Level()->LevelField(pos_x_p,pos_y_s) == LVL_WATER ||
           CGame::Get().Level()->LevelField(pos_x_p,pos_y_s) == LVL_EAGLE) {
            //Kolizja od lewej strony czolgu
            m_x = pos_x_l;
            m_colide = true;
        }
    } else if(m_vy < 0 && m_y > 0.0) {
        if(CGame::Get().Level()->LevelField(pos_x_l,pos_y_d) == LVL_BRICK ||
           CGame::Get().Level()->LevelField(pos_x_l,pos_y_d) == LVL_BRICK_DAMAGED ||
           CGame::Get().Level()->LevelField(pos_x_l,pos_y_d) == LVL_WHITE ||
           CGame::Get().Level()->LevelField(pos_x_l,pos_y_d) == LVL_WATER ||
           CGame::Get().Level()->LevelField(pos_x_l,pos_y_d) == LVL_EAGLE ||
           CGame::Get().Level()->LevelField(pos_x_s,pos_y_d) == LVL_BRICK ||
           CGame::Get().Level()->LevelField(pos_x_s,pos_y_d) == LVL_BRICK_DAMAGED ||
           CGame::Get().Level()->LevelField(pos_x_s,pos_y_d) == LVL_WHITE ||
           CGame::Get().Level()->LevelField(pos_x_s,pos_y_d) == LVL_WATER ||
           CGame::Get().Level()->LevelField(pos_x_s,pos_y_d) == LVL_EAGLE) {
            //Kolizja od lewej strony czolgu
            m_y = pos_y_s;
            m_colide = true;
        }
    } else if(m_vy > 0 && m_y < 24.0) {
        if(CGame::Get().Level()->LevelField(pos_x_l,pos_y_g) == LVL_BRICK ||
           CGame::Get().Level()->LevelField(pos_x_l,pos_y_g) == LVL_BRICK_DAMAGED ||
           CGame::Get().Level()->LevelField(pos_x_l,pos_y_g) == LVL_WHITE ||
           CGame::Get().Level()->LevelField(pos_x_l,pos_y_g) == LVL_WATER ||
           CGame::Get().Level()->LevelField(pos_x_l,pos_y_g) == LVL_EAGLE ||
           CGame::Get().Level()->LevelField(pos_x_s,pos_y_g) == LVL_BRICK ||
           CGame::Get().Level()->LevelField(pos_x_s,pos_y_g) == LVL_BRICK_DAMAGED ||
           CGame::Get().Level()->LevelField(pos_x_s,pos_y_g) == LVL_WHITE ||
           CGame::Get().Level()->LevelField(pos_x_s,pos_y_g) == LVL_WATER ||
           CGame::Get().Level()->LevelField(pos_x_s,pos_y_g) == LVL_EAGLE) {
            //Kolizja od lewej strony czolgu
            m_y = pos_y_d;
            m_colide = true;
        }
    }

    //Sprawdzenie klatki animacji
    SpriteData temp;
    switch(m_direction) {
        case DIR_UP:
            if(abs(m_x - int(m_x)) < 0.5) m_x = int(m_x);
            else                          m_x = int(m_x)+1;
            temp = CGame::Get().Sprites()->Get(m_sprite_up); break;
        case DIR_DOWN:
            if(abs(m_x - int(m_x)) < 0.5) m_x = int(m_x);
            else                          m_x = int(m_x)+1;
            temp = CGame::Get().Sprites()->Get(m_sprite_down); break;
        case DIR_LEFT:
            if(abs(m_y - int(m_y)) < 0.5) m_y = int(m_y);
            else                          m_y = int(m_y)+1;
            temp = CGame::Get().Sprites()->Get(m_sprite_left); break;
        case DIR_RIGHT:
            if(abs(m_y - int(m_y) < 0.5)) m_y = int(m_y);
            else                          m_y = int(m_y)+1;
            temp = CGame::Get().Sprites()->Get(m_sprite_right); break;
    }

    m_frame_duration += dt;
    if(m_frame_duration >= temp.frame_duration) {
        ++m_frame;
        if(m_frame >= temp.frame_count) {
            if(temp.loop) m_frame = 0;
            else          m_frame = temp.frame_count -1;
        }
        m_frame_duration = 0.0;
    }

    //Auto strzelanie
    if(m_can_shoot) {
        m_current_shoot_time += dt;
        if(m_current_shoot_time >= m_shoot_wait_time) {
            Shoot();
            m_current_shoot_time = 0;
        }
    }

    //Wybieranie kierunku
    m_current_turn_wait_time += dt;
    if(m_current_turn_wait_time >= m_turn_wait_time) {
        ChooseDirection(false);
        m_current_turn_wait_time = 0;
        m_current_collision_turn_time = 0;
    }

    //W przypadku kolizji - specjalny tryb zmiany kierunku
    if(m_colide) {
        m_current_collision_turn_time += dt;

        if(m_current_collision_turn_time > m_collision_turn_time) {
            ChooseDirection(true);
            m_current_collision_turn_time = 0;
            m_collision_turn_time = (rand()%10) / (double(m_speed)*1.5);
        }
    }
}

void CEnemy::UpdatePaused(double dt) {
    //Sprawdzenie klatki animacji
    SpriteData temp;
    switch(m_direction) {
        case DIR_UP:
            if(abs(m_x - int(m_x)) < 0.5) m_x = int(m_x);
            else                          m_x = int(m_x)+1;
            temp = CGame::Get().Sprites()->Get(m_sprite_up); break;
        case DIR_DOWN:
            if(abs(m_x - int(m_x)) < 0.5) m_x = int(m_x);
            else                          m_x = int(m_x)+1;
            temp = CGame::Get().Sprites()->Get(m_sprite_down); break;
        case DIR_LEFT:
            if(abs(m_y - int(m_y)) < 0.5) m_y = int(m_y);
            else                          m_y = int(m_y)+1;
            temp = CGame::Get().Sprites()->Get(m_sprite_left); break;
        case DIR_RIGHT:
            if(abs(m_y - int(m_y) < 0.5)) m_y = int(m_y);
            else                          m_y = int(m_y)+1;
            temp = CGame::Get().Sprites()->Get(m_sprite_right); break;
    }

    m_frame_duration += dt;
    if(m_frame_duration >= temp.frame_duration) {
        if(m_frame == 0)
            m_frame = 1;
        else
            m_frame = 0;
        m_frame_duration = 0;
    }
}

void CEnemy::ChooseDirection(bool collision) {
    if(m_colide) {
        int test = rand()%4;
        if(test == 3 || test == 1) {
            m_turn_wait_time = 1;
            return;
        } else {
            m_turn_wait_time = 2;
        }
    }

    int randed;
    if(int(m_y) < 10) {      //Jeśli może w poziomie zbić godło
        randed = rand()%5;
    } else {                //Jeśli nie może zbić godło
        randed = rand()%6;
    }

    DIRECTION dir;
    if(m_x < 10) {
        switch(randed) {
            case 0: dir = DIR_DOWN; break;
            case 1: dir = DIR_RIGHT; break;
            case 2: dir = DIR_LEFT; break;
            case 3: dir = DIR_UP; break;
            case 4: dir = DIR_RIGHT; break;
            case 5: dir = DIR_DOWN; break;
            default: dir = DIR_DOWN; break;
        }
    } else if(m_x <= 12) {
        switch(randed) {
            case 0: dir = DIR_DOWN; break;
            case 1: dir = DIR_RIGHT; break;
            case 2: dir = DIR_LEFT; break;
            case 3: dir = DIR_UP; break;
            case 4: dir = DIR_UP; break;
            default: dir = DIR_UP; break;
        }
    } else {
        switch(randed) {
            case 0: dir = DIR_DOWN; break;
            case 1: dir = DIR_RIGHT; break;
            case 2: dir = DIR_LEFT; break;
            case 3: dir = DIR_UP; break;
            case 4: dir = DIR_LEFT; break;
            case 5: dir = DIR_DOWN; break;
            default: dir = DIR_DOWN; break;
        }
    }

    SetDirection(dir); Drive();
    m_turn_wait_time = (rand()%31 + 5)/(double(m_speed)*1.5);
}
