#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

// Personaje que controla el usuario: un cuadrado en el lado izquierdo de la pantalla
struct Player
{
    Rectangle body;
    float verticalVelocity; // Velocidad vertical en pixeles por segundo (negativa = sube, positiva = cae)
    Color color;
};

// Crea al jugador en el lado izquierdo de la pantalla, centrado verticalmente y quieto
Player CreatePlayer(int screenHeight);

// Aplica la gravedad y el salto al jugador, sin dejar que pase el techo
void UpdatePlayer(Player& player, float deltaTime);

// Devuelve true cuando el jugador cayo hasta el borde inferior de la pantalla
bool HasPlayerReachedFloor(const Player& player, int screenHeight);

// Dibuja al jugador como un rectangulo
void DrawPlayer(const Player& player);

#endif // PLAYER_H
