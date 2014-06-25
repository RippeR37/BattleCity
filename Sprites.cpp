/**************************************************
Autor: Damian "RippeR" Dyñdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#include <SDL/SDL.h>
#include <iostream>
#include "Sprites.h"
using namespace std;

CSprites::CSprites() {  //Now that should be from file or smthing, but for now lets keep it simple and just load as it is
    //"name",SpriteData([n] frame_count, [d] frame_duration, [d]left, [d] bottom, d] width, [d] height, [b] loop, [s] atlas)

    /***                Player One              ***/
    Insert("player_one_up_0", SpriteData(2, 0.05, 0, 32, 32, 32, true, "atlas"));
    Insert("player_one_right_0", SpriteData(2, 0.05, 0, 64, 32, 32, true, "atlas"));
    Insert("player_one_down_0", SpriteData(2, 0.05, 0, 96, 32, 32, true, "atlas"));
    Insert("player_one_left_0", SpriteData(2, 0.05, 0, 128, 32, 32, true, "atlas"));
    Insert("player_one_up_1", SpriteData(2, 0.05, 64, 32, 32, 32, true, "atlas"));
    Insert("player_one_right_1", SpriteData(2, 0.05, 64, 64, 32, 32, true, "atlas"));
    Insert("player_one_down_1", SpriteData(2, 0.05, 64, 96, 32, 32, true, "atlas"));
    Insert("player_one_left_1", SpriteData(2, 0.05, 64, 128, 32, 32, true, "atlas"));
    Insert("player_one_up_2", SpriteData(2, 0.05, 128, 32, 32, 32, true, "atlas"));
    Insert("player_one_right_2", SpriteData(2, 0.05, 128, 64, 32, 32, true, "atlas"));
    Insert("player_one_down_2", SpriteData(2, 0.05, 128, 96, 32, 32, true, "atlas"));
    Insert("player_one_left_2", SpriteData(2, 0.05, 128, 128, 32, 32, true, "atlas"));
    Insert("player_one_up_3", SpriteData(2, 0.05, 192, 32, 32, 32, true, "atlas"));
    Insert("player_one_right_3", SpriteData(2, 0.05, 192, 64, 32, 32, true, "atlas"));
    Insert("player_one_down_3", SpriteData(2, 0.05, 192, 96, 32, 32, true, "atlas"));
    Insert("player_one_left_3", SpriteData(2, 0.05, 192, 128, 32, 32, true, "atlas"));

    /***                Player Two              ***/
    Insert("player_two_up_0", SpriteData(2, 0.05, 0, 160, 32, 32, true, "atlas"));
    Insert("player_two_right_0", SpriteData(2, 0.05, 0, 192, 32, 32, true, "atlas"));
    Insert("player_two_down_0", SpriteData(2, 0.05, 0, 224, 32, 32, true, "atlas"));
    Insert("player_two_left_0", SpriteData(2, 0.05, 0, 256, 32, 32, true, "atlas"));
    Insert("player_two_up_1", SpriteData(2, 0.05, 64, 160, 32, 32, true, "atlas"));
    Insert("player_two_right_1", SpriteData(2, 0.05, 64, 192, 32, 32, true, "atlas"));
    Insert("player_two_down_1", SpriteData(2, 0.05, 64, 224, 32, 32, true, "atlas"));
    Insert("player_two_left_1", SpriteData(2, 0.05, 64, 256, 32, 32, true, "atlas"));
    Insert("player_two_up_2", SpriteData(2, 0.05, 128, 160, 32, 32, true, "atlas"));
    Insert("player_two_right_2", SpriteData(2, 0.05, 128, 192, 32, 32, true, "atlas"));
    Insert("player_two_down_2", SpriteData(2, 0.05, 128, 224, 32, 32, true, "atlas"));
    Insert("player_two_left_2", SpriteData(2, 0.05, 128, 256, 32, 32, true, "atlas"));
    Insert("player_two_up_3", SpriteData(2, 0.05, 192, 160, 32, 32, true, "atlas"));
    Insert("player_two_right_3", SpriteData(2, 0.05, 192, 192, 32, 32, true, "atlas"));
    Insert("player_two_down_3", SpriteData(2, 0.05, 192, 224, 32, 32, true, "atlas"));
    Insert("player_two_left_3", SpriteData(2, 0.05, 192, 256, 32, 32, true, "atlas"));

    /***                Level Sprites           ***/
    Insert("lvl_brick", SpriteData(2, 1, 0, 272, 16, 16, false, "atlas"));
    Insert("lvl_white", SpriteData(1, 1, 0, 288, 16, 16, false, "atlas"));
    Insert("lvl_slide", SpriteData(1, 1, 0, 304, 16, 16, false, "atlas"));
    Insert("lvl_bush",  SpriteData(1, 1, 0, 320, 16, 16, false, "atlas"));
    Insert("lvl_water", SpriteData(1, 1, 0, 336, 16, 16, false, "atlas"));
    Insert("lvl_background", SpriteData(1, 1, 3, 347, 1, 1, false, "atlas"));
    Insert("lvl_eagle", SpriteData(2, 1, 0, 392, 32, 32, false, "atlas"));

    /***                Items                   ***/
    Insert("item_star", SpriteData(1, 0.15, 0, 424, 32, 32, false, "atlas"));
    Insert("item_life", SpriteData(1, 0.15, 32, 424, 32, 32, false, "atlas"));
    Insert("item_invincibility", SpriteData(1, 0.15, 64, 424, 32, 32, false, "atlas"));
    Insert("item_protect", SpriteData(1, 0.15, 96, 424, 32, 32, false, "atlas"));
    Insert("item_time", SpriteData(1, 0.15, 64, 392, 32, 32, false, "atlas"));
    Insert("item_granade", SpriteData(1, 0.15, 96, 392, 32, 32, false, "atlas"));

    /***                Enemies                 ***/
    Insert("enemy_slow_up", SpriteData(2, 0.15, 0, 456, 32, 32, true, "atlas"));
    Insert("enemy_slow_right", SpriteData(2, 0.15, 0, 488, 32, 32, true, "atlas"));
    Insert("enemy_slow_down", SpriteData(2, 0.15, 0, 520, 32, 32, true, "atlas"));
    Insert("enemy_slow_left", SpriteData(2, 0.15, 0, 552, 32, 32, true, "atlas"));
        Insert("enemy_slow_bonus_up", SpriteData(4, 0.1, 64, 456, 32, 32, true, "atlas"));
        Insert("enemy_slow_bonus_right", SpriteData(4, 0.1, 64, 488, 32, 32, true, "atlas"));
        Insert("enemy_slow_bonus_down", SpriteData(4, 0.15, 64, 520, 32, 32, true, "atlas"));
        Insert("enemy_slow_bonus_left", SpriteData(4, 0.15, 64, 552, 32, 32, true, "atlas"));
    Insert("enemy_fast_up", SpriteData(2, 0.15, 0, 584, 32, 32, true, "atlas"));
    Insert("enemy_fast_right", SpriteData(2, 0.15, 0, 616, 32, 32, true, "atlas"));
    Insert("enemy_fast_down", SpriteData(2, 0.15, 0, 648, 32, 32, true, "atlas"));
    Insert("enemy_fast_left", SpriteData(2, 0.15, 0, 680, 32, 32, true, "atlas"));
        Insert("enemy_fast_bonus_up", SpriteData(4, 0.15, 64, 584, 32, 32, true, "atlas"));
        Insert("enemy_fast_bonus_right", SpriteData(4, 0.15, 64, 616, 32, 32, true, "atlas"));
        Insert("enemy_fast_bonus_down", SpriteData(4, 0.15, 64, 648, 32, 32, true, "atlas"));
        Insert("enemy_fast_bonus_left", SpriteData(4, 0.15, 64, 680, 32, 32, true, "atlas"));
    Insert("enemy_medium_up", SpriteData(2, 0.15, 0, 712, 32, 32, true, "atlas"));
    Insert("enemy_medium_right", SpriteData(2, 0.15, 0, 744, 32, 32, true, "atlas"));
    Insert("enemy_medium_down", SpriteData(2, 0.15, 0, 776, 32, 32, true, "atlas"));
    Insert("enemy_medium_left", SpriteData(2, 0.15, 0, 808, 32, 32, true, "atlas"));
        Insert("enemy_medium_bonus_up", SpriteData(4, 0.15, 64, 712, 32, 32, true, "atlas"));
        Insert("enemy_medium_bonus_right", SpriteData(4, 0.15, 64, 744, 32, 32, true, "atlas"));
        Insert("enemy_medium_bonus_down", SpriteData(4, 0.15, 64, 776, 32, 32, true, "atlas"));
        Insert("enemy_medium_bonus_left", SpriteData(4, 0.15, 64, 808, 32, 32, true, "atlas"));
    Insert("enemy_big_up", SpriteData(2, 0.15, 0, 840, 32, 32, true, "atlas"));
    Insert("enemy_big_right", SpriteData(2, 0.15, 0, 872, 32, 32, true, "atlas"));
    Insert("enemy_big_down", SpriteData(2, 0.15, 0, 904, 32, 32, true, "atlas"));
    Insert("enemy_big_left", SpriteData(2, 0.15, 0, 936, 32, 32, true, "atlas"));
        Insert("enemy_big_bonus_up", SpriteData(4, 0.15, 64, 840, 32, 32, true, "atlas"));
        Insert("enemy_big_bonus_right", SpriteData(4, 0.15, 64, 872, 32, 32, true, "atlas"));
        Insert("enemy_big_bonus_down", SpriteData(4, 0.15, 64, 904, 32, 32, true, "atlas"));
        Insert("enemy_big_bonus_left", SpriteData(4, 0.15, 64, 936, 32, 32, true, "atlas"));


    /***                Effects                 ***/
    Insert("effect_spawn", SpriteData(6, 0.05, 256, 64, 32, 32, true, "atlas"));
    Insert("effect_explode", SpriteData(3, 0.05, 256, 96, 32, 32, true, "atlas"));

    /***                Other                   ***/
    Insert("bullet", SpriteData(4, 1, 0, 360, 8, 8, false, "atlas"));
    Insert("editor", SpriteData(1, 1, 462, 223, 50, 223, false, "atlas"));
    Insert("menu_logo", SpriteData(1, 1, 135, 409, 376, 136, false, "atlas"));
    Insert("menu_options", SpriteData(1, 1, 324, 500, 188, 78, false, "atlas"));
    Insert("player_border", SpriteData(2, 0.05, 256, 32, 32, 32, true, "atlas"));
    Insert("player_stat", SpriteData(1, 1, 32, 288, 16, 16, false, "atlas"));
    Insert("enemy_stat", SpriteData(1, 1, 48, 288, 16, 16, false, "atlas"));
    Insert("flag", SpriteData(1, 1, 64, 304, 32, 32, false, "atlas"));

    Insert("chars", SpriteData(26, 1, 0, 1008, 16, 16, false, "atlas"));
    Insert("signs", SpriteData(18, 1, 0, 1024, 16, 16, false, "atlas"));
}

SpriteData& CSprites::Get(const string &name) {
    if((m_sprites.find(name) != m_sprites.end()))
        return m_sprites.find(name)->second;
    else {
        cout << "- Nie znaleziono informacji o sprite'cie '" << name << "'.\n";
        exit(1);
    }
}
