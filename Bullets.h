/**************************************************
Autor: Damian "RippeR" Dyńdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#ifndef BULLETS_H_INCLUDED
#define BULLETS_H_INCLUDED

#include <list>
#include "Types.h"

using namespace std;

struct Bullet {
    Bullet() {}
    Bullet(double x, double y, OWNER owner) : x(x), y(y), owner(owner) { }

    int id;
    double x, y;
    double xv, yv;
    OWNER owner;
    int owner_id;
    bool destroyed;
};

class CBullets {
    public:
        CBullets() : m_speed(10), m_bullets_num(0) { }          //konstruktor
        void Update(double dt);                                 //aktualizacja pocisków
        void Draw();                                            //rysowanie pocisków
        void CreateBullet(double x, double y, DIRECTION dir,    //stworzenie pocisku
            OWNER owner, int owner_id, double speed);

        list<Bullet>::iterator DestroyBullet(                   //niszczenie pocisku o wsk.
            list<Bullet>::iterator iter, DIRECTION dir);

        void DestroyBullet(int id);                             //zniszczenie pocisku o id
        void DestroyAllBullets();                               //zniszczenie wszystkich pocisków

        int BulletsNum() { return m_bullets.size(); }           //iloœæ pocisków
        list <Bullet> AllBullets() { return m_bullets; }        //zwraca kopie listy pocisków

    private:
        list <Bullet> m_bullets;                                //instancja listy pocisków
        double m_speed;                                         //standardowa prêdkoœæ pociskó
        int m_bullets_num;                                      //iloœæ pocisków
};

#endif // BULLETS_H_INCLUDED
