/**************************************************
Autor: Damian "RippeR" Dyñdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#ifndef SPRITES_H_INCLUDED
#define SPRITES_H_INCLUDED

#include <string>
#include <map>
using namespace std;

struct SpriteData {
    SpriteData() { }
    SpriteData(int frame_count, double frame_duration, double left, double bottom, double width, double height, bool loop, string atlas) :
                frame_count(frame_count), frame_duration(frame_duration), left(left), bottom(bottom), width(width),
                height(height), loop(loop), atlas(atlas) { }

    int frame_count;
    double frame_duration, left, bottom, width, height;
    bool loop;
    string atlas;
};


class CSprites {
    public:
        CSprites();
        SpriteData& Get(const string &name);

    private:
        void Insert(const string& name, const SpriteData& data) { m_sprites.insert(make_pair(name,data)); }
        map <string, SpriteData> m_sprites;
};

#endif // SPRITES_H_INCLUDED
