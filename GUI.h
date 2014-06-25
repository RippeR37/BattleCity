/**************************************************
Autor: Damian "RippeR" Dyńdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <string>
#include "Types.h"
using namespace std;

class CGUI {
    public:
        void DrawGameplayStats();                               //Ryoswanie statystyk
        void RenderText(const string& text,                     //Rysowanie tekstu czcionk¹
            double x, double y, COLOR color = COLOR_NONE);

    private:

};

#endif // GUI_H_INCLUDED
