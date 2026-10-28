#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "scenes/scene.h"

// Arranca una partida nueva: jugador y obstaculo en sus posiciones iniciales
void InitGameplay();

// Actualiza la partida y devuelve la escena a la que hay que ir (sigue en Gameplay o vuelve al menu)
Scene UpdateGameplay();

// Dibuja la partida y, si se perdio, el mensaje de derrota
void DrawGameplay();

#endif // GAMEPLAY_H
