/**************************************************
Autor: Damian "RippeR" Dyńdo
URL: http://warsztat.gd/projects.php?x=view&id=2063
**************************************************/

#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

#include <SDL/SDL_mixer.h>
#include "Types.h"
using namespace std;

struct Sound {
    Sound() : is_played(false) { }
    bool is_played;
    Mix_Chunk *sound;
};

class CAudio {
    public:
        ~CAudio();                          //konstruktor
        void Init();                        //inicjalizacja

        void PlayChunk(SOUNDS type);        //odtworzenie dŸwiêku typu 'type'
        void StopChunk(SOUNDS type);        //zatrzymanie dŸwieku typu 'type'
        void StopAll();                     //zatrzymanie wszystkich dŸwiêków

    private:
        Sound OnMove;                       //instancja dŸwiêku podczas ruchu gracza
        Sound Fire;                         //-||- strza³u gracza
        Sound Explosion;                    //-||-
        Sound Bonus;                        //-||-
        Sound GameStart;                    //-||-
        Sound GameOver;                     //-||-
};

#endif // AUDIO_H_INCLUDED
