/**************************************************
Autor: Damian "RippeR" Dyńdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#include <cmath>
#include <iostream>
#include <string>
#include "Player.h"
#include "Game.h"
#include "Sprites.h"
using namespace std;

void CPlayer::Init(int x, int y, int id) {
    m_x = x; m_y = y; m_id = id;
    m_speed = 5.5;
    m_frame = 0;
    m_frame_duration = 0.0;
    m_player_width = 32;
    m_player_height = 32;
    m_can_shoot = true;
    m_bullets_in_game = 0;

    m_start_x = x;  m_start_y = y;

    SetPlayerLevel(0);
}

void CPlayer::SetPlayerLevel(int level) {
    string player_num = "one";
    if(m_id == 2) player_num = "two";
    switch(level) {
        case 0:
            m_sprite_up = "player_" + player_num + "_up_0";
            m_sprite_down = "player_" + player_num + "_down_0";
            m_sprite_left = "player_" + player_num + "_left_0";
            m_sprite_right = "player_" + player_num + "_right_0";
            m_player_level = 0;
            m_bullet_speed = 13;
            m_bullet_power = 1;
            m_max_bullets = 1;
            break;
        case 1:
            m_sprite_up = "player_" + player_num + "_up_1";
            m_sprite_down = "player_" + player_num + "_down_1";
            m_sprite_left = "player_" + player_num + "_left_1";
            m_sprite_right = "player_" + player_num + "_right_1";
            m_player_level = 1;
            m_bullet_speed = 26;
            m_max_bullets = 1;
            m_bullet_power = 1;
            break;
        case 2:
            m_sprite_up = "player_" + player_num + "_up_2";
            m_sprite_down = "player_" + player_num + "_down_2";
            m_sprite_left = "player_" + player_num + "_left_2";
            m_sprite_right = "player_" + player_num + "_right_2";
            m_player_level = 2;
            m_bullet_speed = 26;
            m_max_bullets = 2;
            m_bullet_power = 1;
            break;
        case 3:
            m_sprite_up = "player_" + player_num + "_up_3";
            m_sprite_down = "player_" + player_num + "_down_3";
            m_sprite_left = "player_" + player_num + "_left_3";
            m_sprite_right = "player_" + player_num + "_right_3";
            m_player_level = 3;
            m_bullet_speed = 26;
            m_max_bullets = 2;
            m_bullet_power = 2;
            break;
    }
}

void CPlayer::Drive() {
    SetStopping(false);
    SetYVelocity(0); SetXVelocity(0);
    m_state = PLAYER_DRIVE;
    switch(m_direction) {
        case DIR_UP:
            m_vy = m_speed;
            break;
        case DIR_DOWN:
            m_vy = -m_speed;
            break;
        case DIR_LEFT:
            m_vx = -m_speed;
            break;
        case DIR_RIGHT:
            m_vx = m_speed;
            break;
    }
}

void CPlayer::Stop(DIRECTION dir) {
    bool is_on_slide = false;
    if(CGame::Get().Level()->LevelField(int(m_x), int(m_y)) == LVL_SLIDE && CGame::Get().Level()->LevelField(int(m_x + 1), int(m_y)) == LVL_SLIDE &&
       CGame::Get().Level()->LevelField(int(m_x), int(m_y + 1)) == LVL_SLIDE && CGame::Get().Level()->LevelField(int(m_x + 1), int(m_y + 1)) == LVL_SLIDE)
        is_on_slide = true;

    if(!is_on_slide) {
        if(dir == DIR_LEFT || dir == DIR_RIGHT)
            SetXVelocity(0);
        else
            SetYVelocity(0);

        SetState(PLAYER_STOP);
    } else {
        if(dir == DIR_LEFT || dir == DIR_RIGHT) {
            m_vx = m_vx / 1.05;
            m_stopping_dir = dir;
            if(fabs(m_vx) < 0.05) {
                m_vx = 0;
                SetState(PLAYER_STOP);
                SetStopping(false);
            } else {
                SetStopping(true);
            }
        } else {
            m_vy = m_vy / 1.05;
            m_stopping_dir = dir;
            if(fabs(m_vy) < 0.05) {
                m_vy = 0;
                SetState(PLAYER_STOP);
                SetStopping(false);
            } else {
                SetStopping(true);
            }
        }
    }
}

void CPlayer::Shoot() {
    if(m_can_shoot) {
        CGame::Get().Audio()->PlayChunk(SOUND_FIRE);
        if(m_id == 1)
            CGame::Get().Bullets()->CreateBullet(m_x, m_y, m_direction, OWN_PLAYER_ONE, m_id, m_bullet_speed);
        else if(m_id == 2)
            CGame::Get().Bullets()->CreateBullet(m_x, m_y, m_direction, OWN_PLAYER_TWO, m_id, m_bullet_speed);
        ++m_bullets_in_game;
        if(m_bullets_in_game >= m_max_bullets) {
            m_can_shoot = false;
        }
    }
}

void CPlayer::DecreaseBullet() {
    --m_bullets_in_game;
    if(m_bullets_in_game < 0) m_bullets_in_game = 0;
    m_can_shoot = true;
}

void CPlayer::Draw() {
    double pos_x = m_x * CGame::Get().TailSize();
    double pos_y = m_y * CGame::Get().TailSize();

    switch (m_direction) {
        case DIR_UP:
            CGame::Get().Renderer()->DrawSprite(CGame::Get().Sprites()->Get(m_sprite_up), m_frame, pos_x, pos_y, m_player_width, m_player_height); break;
        case DIR_DOWN:
            CGame::Get().Renderer()->DrawSprite(CGame::Get().Sprites()->Get(m_sprite_down), m_frame, pos_x, pos_y, m_player_width, m_player_height); break;
        case DIR_LEFT:
            CGame::Get().Renderer()->DrawSprite(CGame::Get().Sprites()->Get(m_sprite_left), m_frame, pos_x, pos_y, m_player_width, m_player_height); break;
        case DIR_RIGHT:
            CGame::Get().Renderer()->DrawSprite(CGame::Get().Sprites()->Get(m_sprite_right), m_frame, pos_x, pos_y, m_player_width, m_player_height); break;
    }
    if(m_invincibility) {
        CGame::Get().Renderer()->DrawSprite(CGame::Get().Sprites()->Get("player_border"), m_inv_frame, pos_x, pos_y, m_player_width, m_player_height);
    }
}

void CPlayer::EarnStar() {
    switch(PlayerLevel()) {
        case 0: SetPlayerLevel(1); break;
        case 1: SetPlayerLevel(2); break;
        case 2: SetPlayerLevel(3); break;
        case 3: break;
    }
}

void CPlayer::EarnLife() {
    //Zdobywa życie
    ++m_lifes;
}

void CPlayer::Born() {
    SetPosition(m_start_x,m_start_y);
    SetAlive(true);
    SetDirection(DIR_UP);
    SetState(PLAYER_STOP);
    SetXVelocity(0);
    SetYVelocity(0);
    SetInvincibility(3.0);
}

bool CPlayer::OnMove() {
    if(m_vx != 0 || m_vy != 0)
        return true;
    return false;
}

void CPlayer::Die() {
    static int TailSize = CGame::Get().TailSize();
    if(!m_invincibility) {
        SetPlayerLevel(0);
        CGame::Get().Audio()->PlayChunk(SOUND_DIE);
        CGame::Get().Effects()->CreateEffect( GetX() * TailSize, GetY() * TailSize, EFFECT_EXPLODE);
        LoseLife();
        SetAlive(false);
        if(Lifes() < 0)
            SetPosition(26,26);
    }
}

void CPlayer::SetInvincibility(double time) {
    m_invincibility = true;
    m_invincibility_remain_time = time;
}

void CPlayer::StripInvincibility() {
    m_invincibility = false;
    m_invincibility_remain_time = 0.0;
}

void CPlayer::Update(double dt) {
    if(m_state == PLAYER_DRIVE && m_stopping) {
        Stop(m_stopping_dir);
    }

    m_x = m_x + m_vx * dt * m_speed_ratio;
    m_y = m_y + m_vy * dt * m_speed_ratio;

    if(m_invincibility) {
        m_invincibility_remain_time -= dt;
        if(m_invincibility_remain_time <= 0)    m_invincibility = false;
    }

    //Wyjechanie poza mapę
    if(m_x < 0.0)  m_x = 0.0;
    if(m_x > 24.0) m_x = 24.0;
    if(m_y < 0.0)  m_y = 0.0;
    if(m_y > 24.0) m_y = 24.0;

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
        }
    }

    //Kolizja z przeciwnikami
    list <CEnemy*> enemies = CGame::Get().Enemies()->EnemiesList();
    double x1,x2,x3,x4,y1,y2,y3,y4;

    for(list <CEnemy*>::iterator iter = enemies.begin(); iter!= enemies.end(); ++iter) {
        x1 = GetX();                y1 = GetY();
        x2 = x1+2;                  y2 = y1+2;
        x3 = (*iter)->GetX();       y3 = (*iter)->GetY();
        x4 = x3 + 2;                y4 = y3 + 2;

        if(TwoRectangles(x1,y1,x2,y2,x3,y3,x4,y4)) {
            switch(GetDirection()) {
                case DIR_UP:
                    if(y1 < y3) {
                        double new_y = y3 - 2; if(new_y < 0) new_y = 0;
                        SetPosition(x1, new_y);
                    } break;
                case DIR_DOWN:
                    if(y1 > y3) {
                        double new_y = y3 + 2; if(new_y > 24) new_y = 24;
                        SetPosition(x1, new_y);
                    } break;
                case DIR_LEFT:
                    if(x1 > x3) {
                        double new_x = x3 + 2; if(new_x > 24) new_x = 24;
                        SetPosition(new_x, y1);
                    } break;
                case DIR_RIGHT:
                    if(x1 < x3) {
                        double new_x = x3 - 2; if(new_x < 0) new_x = 0;
                        SetPosition(new_x, y1);
                    } break;
            }
        }
    }

    //Kolizja z 2gim graczem
    if(CGame::Get().PlayerTwo() != NULL) {
        if(m_id == 1) {
            x1 = CGame::Get().Player()->GetX();         y1 = CGame::Get().Player()->GetY();
            x2 = x1 + 2;                                y2 = y1 + 2;
            x3 = CGame::Get().PlayerTwo()->GetX();      y3 = CGame::Get().PlayerTwo()->GetY();
            x4 = x3 + 2;                                y4 = y3 + 2;
        } else if(m_id == 2) {
            x1 = CGame::Get().PlayerTwo()->GetX();      y1 = CGame::Get().PlayerTwo()->GetY();
            x2 = x1 + 2;                                y2 = y1 + 2;
            x3 = CGame::Get().Player()->GetX();         y3 = CGame::Get().Player()->GetY();
            x4 = x3 + 2;                                y4 = y3 + 2;
        }

        if(TwoRectangles(x1,y1,x2,y2,x3,y3,x4,y4)) {
            switch(GetDirection()) {
                case DIR_UP:
                    if(y1 < y3) {
                        double new_y = y3 - 2; if(new_y < 0) new_y = 0;
                        SetPosition(x1, new_y);
                    } break;
                case DIR_DOWN:
                    if(y1 > y3) {
                        double new_y = y3 + 2; if(new_y > 24) new_y = 24;
                        SetPosition(x1, new_y);
                    } break;
                case DIR_LEFT:
                    if(x1 > x3) {
                        double new_x = x3 + 2; if(new_x > 24) new_x = 24;
                        SetPosition(new_x, y1);
                    } break;
                case DIR_RIGHT:
                    if(x1 < x3) {
                        double new_x = x3 - 2; if(new_x < 0) new_x = 0;
                        SetPosition(new_x, y1);
                    } break;
            }
        }
    }

    //Kolizja z bonusami
    Item item = CGame::Get().Items()->GetCurrentItem();
    if(item.destroyed == false) {
        double x1,x2,x3,x4,y1,y2,y3,y4;
        x1 = item.x;        y1 = item.y;
        x2 = x1 + 2;        y2 = y1 + 2;
        x3 = GetX();        y3 = GetY();
        x4 = x3 + 2;        y4 = y3 + 2;

        if(TwoRectangles(x1,y1,x2,y2,x3,y3,x4,y4)) {
            CGame::Get().Audio()->PlayChunk(SOUND_BONUS);
            switch(item.type) {
                case ITEM_STAR:
                    EarnStar(); break;
                case ITEM_LIFE:
                    EarnLife(); break;
                case ITEM_INVINCIBILITY:
                    SetInvincibility(); break;
                case ITEM_PROTECT:
                    CGame::Get().GameTimer()->SetLevelProtect(true);
                    break;
                case ITEM_TIME:
                    CGame::Get().Enemies()->PauseEnemies();
                    break;
                case ITEM_GRANADE:
                    CGame::Get().Enemies()->DestroyAllEnemies(false); break;
            }
            CGame::Get().Items()->DestroyItem();
        }
    }

    //Kolizja z pociskami
    list<Bullet> temp = CGame::Get().Bullets()->AllBullets();

    for(list<Bullet>::iterator iter = temp.begin(); iter != temp.end(); ++iter) {
        if((*iter).owner == OWN_ENEMY) {
            x1 = GetX();        y1 = GetY();
            x2 = x1 + 2;        y2 = y1 + 2;
            x3 = (*iter).x;     y3 = (*iter).y;
            x4 = x3 + 0.5;      y4 = y3 + 0.5;

            if(TwoRectangles(x1,y1,x2,y2,x3,y3,x4,y4)) {
                //Zniszczenie gracza
                Die();

                //Zabawa z kulami
                CGame::Get().Bullets()->DestroyBullet((*iter).id);
                if(CGame::Get().Enemies()->SingleEnemy((*iter).owner_id) != NULL)
                    CGame::Get().Enemies()->SingleEnemy((*iter).owner_id)->DecreaseBullet();
                break;
            }
        }
    }

    static SpriteData temp_inv = CGame::Get().Sprites()->Get("player_border");
    if(m_invincibility) {
        m_current_inv_d += dt;
        if(m_current_inv_d >= temp_inv.frame_duration) {
            ++m_inv_frame;
            if(m_inv_frame >= temp_inv.frame_count) {
                if(temp_inv.loop)   m_inv_frame = 0;
                else                m_inv_frame = temp_inv.frame_count - 1;
            }
            m_current_inv_d = 0.0;
        }
    }

    //Sprawdzenie klatki
    if(m_vx == 0.0 && m_vy == 0.0 && m_state == PLAYER_STOP)
        m_frame = 0;
    else {
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
    }
}
