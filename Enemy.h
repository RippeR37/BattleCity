/**************************************************
Autor: Damian "RippeR" Dyńdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "Types.h"
#include <string>
using namespace std;

class CEnemy {
    public:
        CEnemy() : m_vx(0.0), m_vy(0.0), m_speed_ratio(1.0), m_max_bullets(1), m_direction(DIR_DOWN),
                   m_current_shoot_time(0.2), m_shoot_wait_time(0.7), m_current_turn_wait_time(0.0),
                   m_turn_wait_time(2.0), m_destroyed(false), m_current_collision_turn_time(0.0), m_collision_turn_time(1) { }
        void Init(int x, int y, ENEMY_TYPE type);       //Inicjalizacja przeciwnika

        void Update(double dt);                         //Aktualizacja przeciwnika
        void UpdatePaused(double dt);                   //Aktualizacja podczas pauzy
        void Draw();                                    //Rysowanie przeciwnika

        void Drive();                                   //Wyruszenie przeciwnika
        void ChooseDirection(bool collision);           //Wybór kierunku

        void Shoot();                                   //Oddanie strzału
        void DecreaseBullet();                          //Aktualizacja po wybuchu pocisku
        void DecreaseLevel()        { --m_level; }      //Zmniejszenie poziomu
        int Level()                 { return m_level; } //Poziom przeciwnika

        int Id()                    { return m_id; }    //ID
        void SetId(int id)          { m_id = id; }      //Ustawia ID
        void SetColide(bool colide) {m_colide = colide;}//Ustawia wartość o zaistniałej kolizji
        void Destroy() { m_destroyed = true; }          //Niszczy przeciwnika

        bool Destroyed()            { return m_destroyed; }         //Czy zniszczony
        double GetX()               { return m_x; }                 //Aktualna pozycja na osi X
        double GetY()               { return m_y; }                 //-||- na osi Y
        int Bullets()               { return m_bullets_in_game; }   //Ilość wystrzelonych pocisków
        int MaxBullets()            { return m_max_bullets; }       //Maksymalna ilość wystrzelonych pocisków
        int EnemyType()             { return m_enemy_type; }        //Typ przeciwnika
        int BulletPower()           { return m_bullet_power; }      //Siła pocisku
        DIRECTION GetDirection()    { return m_direction; }         //Kierunek
        ENEMY_TYPE Type()           { return m_enemy_type; }        //Typ

        void SetEnemyType(ENEMY_TYPE type);                         //Ustaw typ
        void SetPosition(double x, double y) { m_x = x; m_y = y; }  //Ustaw pozycję
        void SetDirection(DIRECTION dir)    { m_direction = dir; }  //Ustaw kierunek

        void SetXVelocity(double v) { m_vx = v; }   //Ustaw prędkość na osi X
        void SetYVelocity(double v) { m_vy = v; }   //Ustaw prędkość na osi Y

    private:
        int m_id;               //id przeciwnika
        DIRECTION m_direction;  //w którą stronę się patrzy
        ENEMY_TYPE m_enemy_type;//typ przeciwnika

        int m_frame;            //aktualnie wyswietlana klatka
        double m_frame_duration;//długość trwania aktualnej klatki

        int m_bullets_in_game;  //Wystrzelonych istniejacych pociskow
        int m_max_bullets;      //Maksymalna ilosc istniejacych pociskow naraz
        bool m_can_shoot;       //Czy można strzelać
        bool m_destroyed;       //Czy nalezy zniszczyc
        bool m_colide;          //Czy koliduje z czyms
        int m_level;            //Poziom czołgu (tylko dla wersji SLOW/BIG)

        double m_current_shoot_time;            //Czas aktualnej przerwy między strzałami
        double m_shoot_wait_time;               //Ile czasu między strzałami

        double m_current_turn_wait_time;        //Aktualny czas miedzy zmiana kierunku
        double m_turn_wait_time;                //Ile czasu ma czekać między zmianą kierunku

        double m_current_collision_turn_time;   //Czas aktualny do zmiany kierunku
        double m_collision_turn_time;           //Czas po którym zmieniamy kierunek przy kolizji

        double m_speed;         //prędkość bazowa
        double m_x, m_y;        //pozycja przeciwnika
        double m_vx, m_vy;      //prędkość przeciwnika
        double m_speed_ratio;   //wspolczynnik szybkosci
        double m_bullet_speed;  //predkość pocisku
        int m_bullet_power;     //siła pocisku

        string m_sprite_up;     //sprite przy poruszaniu się w górę
        string m_sprite_down;   //sprite przy poruszaniu się w dół
        string m_sprite_left;   //sprite przy poruszaniu się w lewo
        string m_sprite_right;  //sprite przy poruszaniu się w prawo

        int m_enemy_width;      //wysokość gracza w pixelach
        int m_enemy_height;     //wysokość gracza w pixelach
};

#endif // ENEMY_H_INCLUDED
