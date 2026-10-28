#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

// Personaje que controla el usuario: un cuadrado en el lado izquierdo de la pantalla
struct Player
{
    Rectangle body;
    float verticalVelocity; // Velocidad vertical en pixeles por segundo, negativa para subir positiva para caer
    Color color;
};

// Crea al jugador en el lado izquierdo de la pantalla, centrado verticalmente
Player CreatePlayer(int screenHeight);

// Aplica la logica del salto, sin dejar que salga de la pantalla
void UpdatePlayer(Player& player, int screenHeight, float deltaTime);

// Dibuja al jugador como un rectangulo
void DrawPlayer(const Player& player);

#endif // PLAYER_H
