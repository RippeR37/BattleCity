/**************************************************
Autor: Damian "RippeR" Dyńdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#ifndef EFFECTS_H_INCLUDED
#define EFFECTS_H_INCLUDED

#include <list>
#include "Sprites.h"
#include "Types.h"
using namespace std;

struct Effect {
    Effect() : current_duration(0.0), frame(0) { }
    Effect(int id, double x, double y) : id(id), x(x), y(y), current_duration(0.0), frame(0), current_frame_duration(0.0) { }
    int id;
    double x, y;            //Wspó³rzêdne
    SpriteData sprite;      //Sprite do wyœwietlenia efektu
    double current_duration;
    double current_frame_duration;
    double duration;
    int frame;
    bool destroyed;
};

class CEffects {
    public:
        CEffects() : m_effects_num(0) { }                                   //Konstruktor
        void Update(double dt);                                             //Aktualizacja efektów
        void Draw();                                                        //Rysowanie efektów
        void CreateEffect(double x, double y, EFFECT_TYPE type);            //Tworzenie efektu

        void DestroyAllEffects();                                           //Niszczenie wszystkich efektów
        list<Effect>::iterator DestroyEffect(list<Effect>::iterator iter);  //Niszczenie konkretnego efektu

        int HowMany()               { return m_effects_num; }               //Ile efektów
        list<Effect> AllEffects()   { return m_effects; }                   //Zwraca kopie listy efektów

    private:
        int             m_effects_num;          //Ilość efektów
        list <Effect>   m_effects;              //Lista efektów
};

#endif // EFFECTS_H_INCLUDED
