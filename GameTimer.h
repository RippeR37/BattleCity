/**************************************************
Autor: Damian "RippeR" Dyńdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#ifndef GAMETIMER_H_INCLUDED
#define GAMETIMER_H_INCLUDED

class CGameTimer {
    public:
        CGameTimer() : m_selected_level(1), m_showed_level(1), m_enemy_spawn_animation(false) { Init(); }
        void Init();
        void Update(double dt);
        void SetLevelProtect(bool protect);
        void SetSelectedLevel(int num)          { m_selected_level = m_showed_level = 1; }
        void ChooseLevel();

        void DrawStageSelect();         //Wybór mapy / przejœcie do nastêpnej
        void ProcessEvents();           //Jeœli wybór mapy -> obs³u¿ wejœcie

        int SelectedLevel()         { return m_selected_level; }
        int ShowedLevel()           { return m_showed_level; }

    private:
        int     m_enemies_at_once;
        int     m_selected_level;
        int     m_showed_level;

        bool    m_levelprotect;
        bool    m_enemy_spawn_animation;

        double  m_current_enemy_time;
        double  m_current_player_time;
        double  m_current_nextmap_time;
        double  m_current_levelprotect_time;
        double  m_current_ressurection_player_one;
        double  m_current_ressurection_player_two;
        double  m_current_game_lost_time;

        double  m_enemy_spawn_time;
        double  m_player_spawn_time;
        double  m_nextmap_change_time;
        double  m_levelprotect_time;
        double  m_ressurection_player;
        double  m_game_lost_time;
};

#endif // GAMETIMER_H_INCLUDED
