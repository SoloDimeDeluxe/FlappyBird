#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "raylib.h"

// Obstaculo formado por dos partes (una arriba y otra abajo) con un hueco en el medio para pasar.
// Aparece por la derecha de la pantalla y se mueve hacia la izquierda
struct Obstacle
{
    Rectangle topPart;
    Rectangle bottomPart;
    float speed; // Velocidad horizontal en pixeles por segundo
    Color color;
};

// Crea el obstaculo justo afuera del borde derecho, con el hueco a una altura al azar
Obstacle CreateObstacle(int screenWidth, int screenHeight);

// Mueve el obstaculo hacia la izquierda; cuando sale de la pantalla reaparece por la derecha con el hueco a otra altura
void UpdateObstacle(Obstacle& obstacle, int screenWidth, int screenHeight, float deltaTime);

// Devuelve true si el rectangulo recibido toca alguna de las dos partes del obstaculo
bool IsCollidingWithObstacle(const Obstacle& obstacle, Rectangle otherBody);

// Dibuja las dos partes del obstaculo como rectangulos
void DrawObstacle(const Obstacle& obstacle);

#endif // OBSTACLE_H
