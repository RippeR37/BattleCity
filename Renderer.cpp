/**************************************************
Autor: Damian "RippeR" Dyńdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#include <SDL/SDL.h>
#include <iostream>
#include "Game.h"
#include "Renderer.h"
using namespace std;

CRenderer::~CRenderer() {
    map<string, Atlas>::iterator iter;
    for(iter = m_atlasses.begin(); iter != m_atlasses.end(); ++iter) {
        glDeleteTextures(1, &m_atlasses[(*iter).first].texture);
        cout << "Zwolniono atlas '" << (*iter).first << "'\n";
    }
}

void CRenderer::Init() {
    LoadAtlasFromFile("data/sprite/sprite.bmp", "atlas");
}

void CRenderer::LoadAtlasFromFile(const string &fileName, const string &atlasName) {
    //Ladowanie atlasu z pliku i dodawanie jako nowy atlas do mapy m_atlasses

    Atlas NewAtlas;                                                         //Atlas który zostanie dodany
    SDL_Surface* temp_surface = SDL_LoadBMP(fileName.c_str());              //Tymczasowa powierzchnia
    if(!temp_surface) {
        cout << "Nie mozna bylo zaladowac atlasu z pliku '" << fileName << "'!\n";
        exit(1);
    }

    NewAtlas.width  = temp_surface->w;                                      //Szerokość atlasu
    NewAtlas.height = temp_surface->h;                                      //Wysokość atlasu

    if (((NewAtlas.width & (NewAtlas.width - 1)) != 0) ||                   //Sprawdzanie atlasu pod kątem rozmiaru
        ((NewAtlas.height & (NewAtlas.height - 1)) != 0)) {
        cout << "Nieprawidlowy rozmiar (" << fileName << ")!\n";
        exit(1);
    }

    GLenum format;                                                          //Format pliku bmp
    switch (temp_surface->format->BytesPerPixel) {
        case 3:                                                             //Bez przezroczystosci
            format = GL_BGR;
            break;
        case 4:                                                             //Z przezroczystoscia
            format = GL_BGRA;
            break;
        default:                                                            //Nieznany format
            cout << "Nieznany format pliku (" << fileName << ")!\n";
            exit(1);
    }

    glGenTextures(1, &NewAtlas.texture);                                    //Tworzenie tekstury
    glBindTexture(GL_TEXTURE_2D, NewAtlas.texture);                         //Użycie tekstury
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);       //Filtrowanie tekstury
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    //Przycinanie tekstury
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, temp_surface->format->BytesPerPixel,     //Stworzenie obrazu tekstury
                 NewAtlas.width, NewAtlas.height, 0, format, GL_UNSIGNED_BYTE, temp_surface->pixels);

    if (temp_surface)                                                       //Zwolnienie pamięci
        SDL_FreeSurface(temp_surface);

    InsertAtlas(atlasName, NewAtlas);
    cout << "- Zaladowano nowy atlas '" << atlasName << "' z pliku '" << fileName << "'.\n";
}

void CRenderer::StartRendering() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
        glBegin(GL_QUADS);
}

void CRenderer::StopRendering() {
        glEnd();
    glPopMatrix();

    SDL_GL_SwapBuffers();
}

void CRenderer::DrawSprite(SpriteData &sprite_data, int frame, double scr_x, double scr_y, int width, int height, COLOR color) {
    static int offX = CGame::Get().GameOffsetX();
    static int offY = CGame::Get().GameOffsetY();
    scr_x += offX;
    scr_y += offY;

    if(color != COLOR_NONE) {
        double r,g,b;
        switch(color) {
                case COLOR_BLACK:       r = 0; g = 0; b = 0; break;
                case COLOR_RED:         r = 1; g = 0; b = 0; break;
                case COLOR_GREEN:       r = 0; g = 1; b = 0; break;
                case COLOR_BLUE:        r = 0; g = 0; b = 1; break;
        }
        glColor3d(r,g,b);
    }

    //Współrzędne na teksturze, ponieważ ma ona współrzędne lewego górnego rogu (0,0) i prawego dolnego (1,1)
    double left = (sprite_data.left + (sprite_data.width * frame)) / m_atlasses[sprite_data.atlas].width;
    double right = left + (sprite_data.width / m_atlasses[sprite_data.atlas].width);
    double bottom = sprite_data.bottom / m_atlasses[sprite_data.atlas].height;
    double top = bottom - (sprite_data.height/m_atlasses[sprite_data.atlas].height);


    glTexCoord2f(right, top);       glVertex2f(scr_x + width, scr_y + height);
    glTexCoord2f(left, top);        glVertex2f(scr_x, scr_y + height);
    glTexCoord2f(left, bottom);     glVertex2f(scr_x, scr_y);
    glTexCoord2f(right, bottom);    glVertex2f(scr_x + width, scr_y);

    if(color != COLOR_NONE) {
        glColor3d(1,1,1);
    }
}
