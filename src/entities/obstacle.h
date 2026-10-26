#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "raylib.h"

// Obstaculo que aparece por la derecha de la pantalla y se mueve hacia la izquierda
struct Obstacle
{
    Rectangle body;
    float speed; // Velocidad horizontal en pixeles por segundo
    Color color;
};

// Crea el obstaculo justo afuera del borde derecho, a una altura al azar
Obstacle CreateObstacle(int screenWidth, int screenHeight);

// Mueve el obstaculo hacia la izquierda; cuando sale de la pantalla reaparece por la derecha a otra altura
void UpdateObstacle(Obstacle& obstacle, int screenWidth, int screenHeight, float deltaTime);

// Dibuja el obstaculo como un rectangulo
void DrawObstacle(const Obstacle& obstacle);

#endif // OBSTACLE_H
