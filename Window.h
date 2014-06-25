/**************************************************
Autor: Damian "RippeR" Dyñdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include <string>
using namespace std;

class CWindow {
    public:
        void Init();
        void Set(int width, int height, int bits, bool fullscreen) {
            m_scr_width = width;
            m_scr_height = height;
            m_scr_bits = bits;
            m_scr_fullscreen = fullscreen;

            m_title = "Battle City PC 1.0";
        }
        int WindowWidth() { return m_scr_width; }
        int WindowHeight() { return m_scr_height; }
        string WindowTitle() { return m_title; }

    private:
        int m_scr_width;
        int m_scr_height;
        int m_scr_bits;
        bool m_scr_fullscreen;
        string m_title;

        SDL_Surface *m_screen;
};

#endif // WINDOW_H_INCLUDED
