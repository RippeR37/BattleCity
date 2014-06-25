/**************************************************
Autor: Damian "RippeR" Dyñdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#ifndef ITEMS_H_INCLUDED
#define ITEMS_H_INCLUDED

#include <list>
#include "Sprites.h"
#include "Types.h"
using namespace std;

struct Item {
    int x, y;
    double frame_duration;
    bool is_visible, destroyed;
    ITEM_TYPE type;
    SpriteData sprite;
};

class CItems {
    public:
        CItems()                            { DestroyItem(); }
        void CreateItem();
        void DestroyItem()                  { m_current_item.destroyed = true; }
        void Draw();
        void Update(double dt);

        Item GetCurrentItem()               { return m_current_item; }

    private:
        Item m_current_item;
};

#endif // ITEMS_H_INCLUDED
