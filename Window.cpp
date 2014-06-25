/**************************************************
Autor: Damian "RippeR" Dyńdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#include <iostream>
#include "Window.h"
#include "Game.h"

using namespace std;

void CWindow::Init() {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0)
        cout << "- Pomyslnie zainicjalizowano bibliteke SDL.\n";
    else
        cout << "# Nie udalo sie zaladowac biblioteki SDL!\n";

    SDL_WM_SetCaption(m_title.c_str(), NULL);

    if(m_scr_fullscreen)    m_screen = SDL_SetVideoMode(m_scr_width, m_scr_height, m_scr_bits, SDL_OPENGL | SDL_FULLSCREEN | SDL_SWSURFACE);
    else                    m_screen = SDL_SetVideoMode(m_scr_width, m_scr_height, m_scr_bits, SDL_OPENGL | SDL_HWSURFACE);

    if(m_screen != NULL)    cout << "- Zainicjalizowano tryb wideo.\n";
    else                    cout << "# Nie zainicjalizowano trybu wideo!";



    glViewport(0, 0, m_scr_width, m_scr_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, m_scr_width, 0, m_scr_height, -1, 5);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 0);

    glClearColor(0.455, 0.455, 0.455, 1);       //szare tło
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GEQUAL, 0.5);                //Jeśli byłby problem z kanałem alpha - zmień na więcej!
}
