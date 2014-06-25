/**************************************************
Autor: Damian "RippeR" Dyńdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#include <iostream>
#include "Bullets.h"
#include "Game.h"
#include "Sprites.h"
using namespace std;

void CBullets::DestroyAllBullets() {
    m_bullets.clear();
    m_bullets_num = 0;

    CGame::Get().Player()->ResetBullets();
    if(CGame::Get().PlayerTwo() != NULL) CGame::Get().PlayerTwo()->ResetBullets();
}

void CBullets::CreateBullet(double x, double y, DIRECTION dir, OWNER owner, int owner_id, double speed = 0) {
    Bullet temp_bullet;
    temp_bullet.owner = owner;
    temp_bullet.owner_id = owner_id;
    temp_bullet.destroyed = false;
    temp_bullet.id = m_bullets_num + 1;
    ++m_bullets_num;

    static int tile_size = CGame::Get().TailSize();

    if(speed == 0) speed = m_speed;

    switch(dir) {
        case DIR_UP:
            temp_bullet.x  = x + (12/double(tile_size));
            temp_bullet.y  = y + (24/double(tile_size));
            temp_bullet.xv = 0.0;
            temp_bullet.yv = speed;
            break;
        case DIR_DOWN:
            temp_bullet.x  = x + (12/double(tile_size));
            temp_bullet.y  = y;
            temp_bullet.xv = 0.0;
            temp_bullet.yv = -speed;
            break;
        case DIR_LEFT:
            temp_bullet.x  = x;
            temp_bullet.y  = y + (12/double(tile_size));
            temp_bullet.xv = -speed;
            temp_bullet.yv = 0.0;
            break;
        case DIR_RIGHT:
            temp_bullet.x  = x + (24/double(tile_size));
            temp_bullet.y  = y + (12/double(tile_size));
            temp_bullet.xv = speed;
            temp_bullet.yv = 0.0;
            break;
    }

    m_bullets.insert(m_bullets.end(), temp_bullet);
}

void CBullets::Draw() {
    double pos_x;
    double pos_y;
    SpriteData temp;
    for(list<Bullet>::iterator iter = m_bullets.begin(); iter != m_bullets.end(); ++iter) {
        pos_x = (*iter).x * CGame::Get().TailSize();
        pos_y = (*iter).y * CGame::Get().TailSize();

        temp = CGame::Get().Sprites()->Get("bullet");
        if((*iter).xv < 0)              //W lewo
            CGame::Get().Renderer()->DrawSprite(temp, 3, pos_x, pos_y, temp.width, temp.height);
        else if((*iter).xv > 0)         //W prawo
            CGame::Get().Renderer()->DrawSprite(temp, 1, pos_x, pos_y, temp.width, temp.height);
        else if((*iter).yv < 0)         //W dol
            CGame::Get().Renderer()->DrawSprite(temp, 2, pos_x, pos_y, temp.width, temp.height);
        else if((*iter).yv > 0)          //W gore
            CGame::Get().Renderer()->DrawSprite(temp, 0, pos_x, pos_y, temp.width, temp.height);
    }
}

void CBullets::Update(double dt) {
    for(list<Bullet>::iterator iter=m_bullets.begin(); iter != m_bullets.end(); ) {
        (*iter).x = (*iter).x + (*iter).xv * dt;
        (*iter).y = (*iter).y + (*iter).yv * dt;

        bool already_destroyed = false;

        if((*iter).x <= 0)                      { (*iter).x = -1; iter = DestroyBullet(iter, DIR_LEFT); already_destroyed = true; }
        else if(((*iter).x + 0.5) >= 26)        { iter = DestroyBullet(iter, DIR_RIGHT); already_destroyed = true; }
        else if((*iter).y <= 0)                 { (*iter).y = -1; iter = DestroyBullet(iter, DIR_DOWN); already_destroyed = true; }
        else if(((*iter).y + 0.5) >= 26)        { iter = DestroyBullet(iter, DIR_UP); already_destroyed = true; }
        else {
            int pos_x_l = (*iter).x, pos_x_s = ((*iter).x + 0.5);
            int pos_y_d = (*iter).y, pos_y_s = ((*iter).y + 0.5);
            sBrick brick1, brick2;

            if((*iter).xv < 0 && (*iter).x > 0.0) {             //w lewo
                brick1 = CGame::Get().Level()->BrickField(pos_x_l, pos_y_d);
                brick2 = CGame::Get().Level()->BrickField(pos_x_l, pos_y_s);
                if(CGame::Get().Level()->LevelField(pos_x_l,pos_y_d) == LVL_BRICK ||
                   (CGame::Get().Level()->LevelField(pos_x_l,pos_y_d) == LVL_BRICK_DAMAGED && (brick1.top_right || brick1.top_left)) ||
                   CGame::Get().Level()->LevelField(pos_x_l,pos_y_d) == LVL_WHITE ||
                   CGame::Get().Level()->LevelField(pos_x_l,pos_y_s) == LVL_BRICK ||
                   (CGame::Get().Level()->LevelField(pos_x_l,pos_y_s) == LVL_BRICK_DAMAGED && (brick2.bottom_right || brick2.bottom_left)) ||
                   CGame::Get().Level()->LevelField(pos_x_l,pos_y_s) == LVL_WHITE) {
                    iter = DestroyBullet(iter, DIR_LEFT); already_destroyed = true;
                }
            } else if((*iter).xv > 0 && (*iter).x < 25.5) {     //w prawo
                brick1 = CGame::Get().Level()->BrickField(pos_x_s, pos_y_d);
                brick2 = CGame::Get().Level()->BrickField(pos_x_s, pos_y_s);
                if(CGame::Get().Level()->LevelField(pos_x_s,pos_y_d) == LVL_BRICK ||
                   (CGame::Get().Level()->LevelField(pos_x_s,pos_y_d) == LVL_BRICK_DAMAGED && (brick1.top_left || brick1.top_right)) ||
                   CGame::Get().Level()->LevelField(pos_x_s,pos_y_d) == LVL_WHITE ||
                   CGame::Get().Level()->LevelField(pos_x_s,pos_y_s) == LVL_BRICK ||
                   (CGame::Get().Level()->LevelField(pos_x_s,pos_y_s) == LVL_BRICK_DAMAGED && (brick2.bottom_left || brick2.bottom_right)) ||
                   CGame::Get().Level()->LevelField(pos_x_s,pos_y_s) == LVL_WHITE) {
                    iter = DestroyBullet(iter, DIR_RIGHT); already_destroyed = true;
                }
            } else if((*iter).yv < 0 && (*iter).y > 0.0) {      //w dol
                brick1 = CGame::Get().Level()->BrickField(pos_x_l, pos_y_d);
                brick2 = CGame::Get().Level()->BrickField(pos_x_s, pos_y_d);
                if(CGame::Get().Level()->LevelField(pos_x_l,pos_y_d) == LVL_BRICK ||
                   (CGame::Get().Level()->LevelField(pos_x_l,pos_y_d) == LVL_BRICK_DAMAGED && (brick1.top_right || brick1.bottom_right)) ||
                   CGame::Get().Level()->LevelField(pos_x_l,pos_y_d) == LVL_WHITE ||
                   CGame::Get().Level()->LevelField(pos_x_s,pos_y_d) == LVL_BRICK ||
                   (CGame::Get().Level()->LevelField(pos_x_s,pos_y_d) == LVL_BRICK_DAMAGED && (brick2.top_left || brick2.bottom_left)) ||
                   CGame::Get().Level()->LevelField(pos_x_s,pos_y_d) == LVL_WHITE) {
                    iter = DestroyBullet(iter, DIR_DOWN); already_destroyed = true;
                }
            } else if((*iter).yv > 0 && (*iter).y < 25.5) {     //w gore
                brick1 = CGame::Get().Level()->BrickField(pos_x_l, pos_y_s);
                brick2 = CGame::Get().Level()->BrickField(pos_x_s, pos_y_s);
                if(CGame::Get().Level()->LevelField(pos_x_l,pos_y_s) == LVL_BRICK ||
                   (CGame::Get().Level()->LevelField(pos_x_l,pos_y_s) == LVL_BRICK_DAMAGED && (brick1.bottom_right || brick1.top_right)) ||
                   CGame::Get().Level()->LevelField(pos_x_l,pos_y_s) == LVL_WHITE ||
                   CGame::Get().Level()->LevelField(pos_x_s,pos_y_s) == LVL_BRICK ||
                   (CGame::Get().Level()->LevelField(pos_x_s,pos_y_s) == LVL_BRICK_DAMAGED && (brick2.bottom_left || brick2.top_left) ) ||
                   CGame::Get().Level()->LevelField(pos_x_s,pos_y_s) == LVL_WHITE) {
                    iter = DestroyBullet(iter, DIR_UP); already_destroyed = true;
                }
            }
        }

        if(!already_destroyed) {
            double x1,x2,x3,x4,y1,y2,y3,y4;

            //Kolizja 'kula <-> kula'
            for(list<Bullet>::iterator iter2=m_bullets.begin(); iter2 != m_bullets.end(); ++iter2) {
                if(iter != iter2) {
                    x1 = (*iter).x;     y1 = (*iter).y;
                    x2 = x1 + 0.5;      y2 = y1 + 0.5;
                    x3 = (*iter2).x;    y3 = (*iter2).y;
                    x4 = x3 + 0.5;      y4 = y3 + 0.5;

                    if(TwoRectangles(x1,y1,x2,y2,x3,y3,x4,y4)) {
                        (*iter).destroyed = true;
                        (*iter2).destroyed = true;
                        break;
                    }
                }
            }

            //Kolizja z godłem
            x1 = (*iter).x;     y1 = (*iter).y; //Współrzędne kuli
            x2 = x1 + 0.5;      y2 = y1 + 0.5;
            x3 = 12;            y3 = 0;         //Współrzędne godła
            x4 = x3+2;          y4 = y3 + 2;
            if(TwoRectangles(x1,y1,x2,y2,x3,y3,x4,y4)) {
                (*iter).destroyed = true;
                CGame::Get().SetGameLost(true);
            }

            if((*iter).destroyed) {
                if((*iter).x > 12)
                    iter = DestroyBullet(iter, DIR_LEFT);
                else
                    iter = DestroyBullet(iter, DIR_RIGHT);
            } else {
                ++iter;
            }
        }
    }
}

list<Bullet>::iterator CBullets::DestroyBullet(list<Bullet>::iterator iter, DIRECTION dir) {
    static int TailSize = CGame::Get().TailSize();
    int power;

    if((*iter).owner == OWN_PLAYER_ONE) {
        power = CGame::Get().Player()->BulletPower();
        CGame::Get().Player()->DecreaseBullet();
    } else if((*iter).owner == OWN_PLAYER_TWO) {
        power = CGame::Get().PlayerTwo()->BulletPower();
        CGame::Get().PlayerTwo()->DecreaseBullet();
    } else {
        power = 1;
        CGame::Get().Enemies()->DecreaseBullet((*iter).owner_id);
    }

    int pos_x = (*iter).x;
    int pos_y = (*iter).y;
    switch(dir) {
        case DIR_UP:
            CGame::Get().Level()->DestroyTile(pos_x, pos_y + 1, pos_x + 1, pos_y +1, power, dir); break;
        case DIR_DOWN:
            CGame::Get().Level()->DestroyTile(pos_x, pos_y, pos_x + 1, pos_y, power, dir); break;
        case DIR_LEFT:
            CGame::Get().Level()->DestroyTile(pos_x, pos_y, pos_x, pos_y + 1, power, dir); break;
        case DIR_RIGHT:
            CGame::Get().Level()->DestroyTile(pos_x + 1, pos_y, pos_x + 1, pos_y + 1, power, dir); break;
    }

    CGame::Get().Effects()->CreateEffect( int((*iter).x - 0.5) * TailSize, int((*iter).y - 0.5) * TailSize, EFFECT_EXPLODE);
    CGame::Get().Audio()->PlayChunk(SOUND_EXPLOSION);
    return m_bullets.erase(iter);
}

void CBullets::DestroyBullet(int id) {
    for(list<Bullet>::iterator iter=m_bullets.begin(); iter != m_bullets.end();) {
        if((*iter).id == id) {
            if((*iter).owner == OWN_PLAYER_ONE) {
                CGame::Get().Player()->DecreaseBullet();
            } else if((*iter).owner == OWN_PLAYER_TWO) {
                CGame::Get().PlayerTwo()->DecreaseBullet();
            }
            iter = m_bullets.erase(iter); break;
        } else {
            ++iter;
        }
    }
}
