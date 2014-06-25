/**************************************************
Autor: Damian "RippeR" Dyńdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Types.h"
#include <string>
using namespace std;

class CPlayer {
    public:
        CPlayer() : m_state(PLAYER_STOP), m_vx(0.0), m_vy(0.0), m_speed_ratio(1.0), m_max_bullets(1), m_invincibility(false),
                    m_lifes(2), m_stopping(false) { }
        void Init(int x, int y, int id);

        void Update(double dt);
        void Draw();
        void Shoot();
        void DecreaseBullet();
        void Die();
        void Born();
        void EarnStar();
        void EarnLife();
        void SetInvincibility(double time = 15.0);
        void StripInvincibility();

        int Lifes()                 { return m_lifes; }
        void LoseLife()             { --m_lifes; }
        void SetLifes(int lifes)    { m_lifes = lifes; if(lifes>=0) SetAlive(true); }

        bool OnMove();
        bool Alive()                { return m_alive; }
        void SetAlive(bool alive)   { m_alive = alive;  }
        bool Stopping()             { return m_stopping; }
        bool SetStopping(bool value){ m_stopping = value; }

        double GetX() { return m_x; }
        double GetY() { return m_y; }
        int Bullets() { return m_bullets_in_game; }
        int MaxBullets() { return m_max_bullets; }
        int PlayerLevel() { return m_player_level; }
        int BulletPower() { return m_bullet_power; }
        DIRECTION GetDirection() { return m_direction; }

        void SetPosition(double x, double y) { m_x = x; m_y = y; }
        void SetDirection(DIRECTION dir) { m_direction = dir; }
        void SetState(PLAYER_STATE state) { m_state = state; }
        void SetPlayerLevel(int level);
        void ResetBullets() { m_bullets_in_game = 0; m_can_shoot = true; }

        void Drive();
        void Stop(DIRECTION dir);
        void SetXVelocity(double v)         { m_vx = v; }
        void SetYVelocity(double v)         { m_vy = v; }

    private:
        DIRECTION m_direction;  //w którą stronę się patrzy
        DIRECTION m_stopping_dir;   //Kierunek hamowania
        PLAYER_STATE m_state;   //stan gracza

        int m_id;               //id gracza
        int m_lifes;            //ilość żyć
        bool m_alive;           //czy jeszcze żyje
        int m_frame;            //aktualnie wyswietlana klatka
        int m_inv_frame;        //aktualna klatka dla bonusu niezwyciężoności
        double m_frame_duration;//
        double m_current_inv_d; //długość aktualnie wyświetlanej klatki

        int m_player_level;     //Poziom gracza (gwiazdki)
        int m_bullets_in_game;  //Wystrzelonych istniejacych pociskow
        int m_max_bullets;      //Maksymalna ilosc istniejacych pociskow naraz
        bool m_can_shoot;       //Czy można strzelać

        bool m_invincibility;   //Czy jest niezniszczalny
        double m_invincibility_remain_time; //Czas jaki pozostał będąc niezniszczalny

        double m_start_x;       //Pozycja startowa
        double m_start_y;       //Pozycja startowa

        bool m_stopping;        //Czy hamuje?
        double m_speed;         //prędkość bazowa
        double m_x, m_y;        //pozycja gracza
        double m_vx, m_vy;      //prędkość gracza
        double m_speed_ratio;   //wspolczynnik szybkosci
        double m_bullet_speed;  //predkosc pocisku
        int m_bullet_power;     //sila pocisku

        string m_sprite_up;     //sprite przy poruszaniu się w górę
        string m_sprite_down;   //sprite przy poruszaniu się w dół
        string m_sprite_left;   //sprite przy poruszaniu się w lewo
        string m_sprite_right;  //sprite przy poruszaniu się w prawo

        int m_player_width;     //wysokość gracza w pixelach
        int m_player_height;    //wysokość gracza w pixelach
};

#endif // PLAYER_H_INCLUDED
