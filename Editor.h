/**************************************************
Autor: Damian "RippeR" Dyńdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#ifndef EDITOR_H_INCLUDED
#define EDITOR_H_INCLUDED

#include "Types.h"

class CEditor {
    public:
        CEditor() : m_current_field(LVL_NONE) { }           //Konstruktor
        void LMB(int x, int y);                             //Interakcja po wciœniêciu LPM
        void RMB(int x, int y);                             //Interakcja po wciœniêciu PPM
        void DrawEditor();                                  //Rysowanie GUI edytora

    private:
        LVL_FIELD m_current_field;                          //Aktualnie wybrane pole z menu
};


#endif // EDITOR_H_INCLUDED
