/**************************************************
Autor: Damian "RippeR" Dyñdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

enum GAME_STATE {
    GS_MENU,
    GS_STAGESELECT,
    GS_GAMEPLAY,
    GS_SCORES,
    GS_EDITOR
};

enum LVL_FIELD {
    LVL_NONE = 0,
    LVL_BRICK = 1,
    LVL_BRICK_DAMAGED = 11,
    LVL_WHITE = 2,
    LVL_SLIDE = 3,
    LVL_BUSH  = 4,
    LVL_WATER = 5,
    LVL_EAGLE = 9
};

enum DIRECTION {
    DIR_UP = 0,
    DIR_RIGHT = 1,
    DIR_DOWN = 2,
    DIR_LEFT = 3,
    //DIR_NONE = 4
};

enum PLAYER_STATE {
    PLAYER_STOP = 0,
    PLAYER_DRIVE = 1,
};

enum OWNER {
    OWN_PLAYER_ONE = 0,
    OWN_PLAYER_TWO = 1,
    OWN_ENEMY = 2
};

enum ENEMY_TYPE {
    ENEMY_SLOW = 0,
    ENEMY_FAST = 1,
    ENEMY_MEDIUM = 2,
    ENEMY_BIG = 3,
    ENEMY_SLOW_BONUS = 4,
    ENEMY_FAST_BONUS = 5,
    ENEMY_MEDIUM_BONUS = 6,
    ENEMY_BIG_BONUS = 7
};

enum ITEM_TYPE {
    ITEM_STAR = 0,
    ITEM_LIFE = 1,
    ITEM_INVINCIBILITY = 2,
    ITEM_PROTECT = 3,
    ITEM_TIME = 4,
    ITEM_GRANADE = 5
};

enum COLOR {
    COLOR_NONE,
    COLOR_BLACK,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_BLUE
};

enum EFFECT_TYPE {
    EFFECT_SPAWN,
    EFFECT_EXPLODE
};

enum SOUNDS {
    SOUND_ONMOVE = 0,
    SOUND_FIRE = 1,
    SOUND_EXPLOSION = 2,
    SOUND_BONUS = 3,
    SOUND_GAMESTART = 4,
    SOUND_GAMEOVER = 5,
    SOUND_DIE = 6
};

#endif // TYPES_H_INCLUDED
