/**************************************************
Autor: Damian "RippeR" Dyńdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#ifndef ENEMIES_H_INCLUDED
#define ENEMIES_H_INCLUDED

#include <list>
#include <iostream>
#include <vector>
#include "Enemy.h"
#include "Types.h"
using namespace std;

class CEnemies {
    public:
        CEnemies() : m_number_of_enemies(0), m_pause_time(15), m_enemies_paused(false) { m_EnemiesType.resize(20); }
        ~CEnemies() { DestroyAllEnemies(); }

        void Update(double dt);                                                     //Aktualizacja wszystkich przeciwnikow
        void Draw();                                                                //Narysowanie wszystkich przeciwnikow
        void CreateEnemy(ENEMY_TYPE type);                                          //Stworzenie przeciwnika danego typu o wsp = (x,y)
        void CreateEnemy();                                                         //Stworzenie przeciwnika o typie wyznaczonym przez mapę
        list<CEnemy*>::iterator DestroyEnemy(list<CEnemy*>::iterator iter);         //Niszczenie przeciwnika
        void DestroyAllEnemies(bool wipe = true);                                   //Niszczenie wszystkic przeciwników
        void DecreaseBullet(int id);                                                //Zmiensza ilość wystrzelonych pociskow


        void PauseEnemies() { m_enemies_paused = true; m_current_pause_time = 0; }  //Pauzuje przeciwników
        void UnPause()      { m_enemies_paused = false; m_current_pause_time = 0; } //Wył. pauzy
        void SetEnemyType(int id, ENEMY_TYPE type) { m_EnemiesType[id] = type; }    //Zmiana typu przeciwnika o id
        void SetEnemiesNum(int num) { m_number_of_enemies = num; }                  //Zmienia ilość przeciwników

        bool Paused()       { return m_enemies_paused; }                            //Czy pauza aktywna
        int Enemies()       { return m_number_of_enemies; }                         //Ile przeciwników już stworzono (na mapę)
        int AliveEnemies()  { return m_Enemies.size(); }                            //Ile żywych przeciwników
        int NextSpawnX();                                                           //Pozycja na osi X następnego przeciwnika

        CEnemy* SingleEnemy(int id);                                                //Zwrócenie pojedyńzego przeciwnika o id
        list<CEnemy*> EnemiesList() { return m_Enemies; }                           //zwrócenie listy przeciwników

    private:
        bool m_enemies_paused;              //Czy przeciwnicy sa pod wplywem bonusu (pauza)
        double m_current_pause_time;        //Aktualny czas pauzy przeciwników
        double m_pause_time;                //Czas pauzy przeciwników

        list <CEnemy*> m_Enemies;           //Lista przeciwnikow
        vector <ENEMY_TYPE> m_EnemiesType;  //Typ przeciwników
        int m_number_of_enemies;            //Liczba przeciwnikow
};

#endif // ENEMIES_H_INCLUDED
