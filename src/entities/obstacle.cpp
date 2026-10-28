#include "entities/obstacle.h"

namespace ReyesCuadra
{
    // Valores de configuracion del obstaculo (solo se usan en este archivo)
    static const float OBSTACLE_WIDTH = 60.0f;
    static const float GAP_HEIGHT = 150.0f;      // Alto del hueco por donde tiene que pasar el jugador
    static const float MIN_PART_HEIGHT = 40.0f;  // Alto minimo de cada parte, para que el hueco nunca quede pegado a un borde
    static const float OBSTACLE_SPEED = 300.0f;
    static const Color OBSTACLE_COLOR = GREEN;

    // Ubica el obstaculo justo afuera del borde derecho de la pantalla, con el hueco a una altura al azar
    static void ResetObstaclePosition(Obstacle& obstacle, int screenWidth, int screenHeight);

    // Devuelve true cuando el obstaculo salio por completo por el borde izquierdo de la pantalla
    static bool IsObstacleOutOfScreen(const Obstacle& obstacle);

    Obstacle CreateObstacle(int screenWidth, int screenHeight)
    {
        Obstacle obstacle;

        obstacle.topPart.width = OBSTACLE_WIDTH;
        obstacle.bottomPart.width = OBSTACLE_WIDTH;
        obstacle.speed = OBSTACLE_SPEED;
        obstacle.color = OBSTACLE_COLOR;

        ResetObstaclePosition(obstacle, screenWidth, screenHeight);

        return obstacle;
    }

    void UpdateObstacle(Obstacle& obstacle, int screenWidth, int screenHeight, float deltaTime)
    {
        // Las dos partes se mueven juntas, como un solo obstaculo
        const float movement = obstacle.speed * deltaTime;

        obstacle.topPart.x -= movement;
        obstacle.bottomPart.x -= movement;

        if (IsObstacleOutOfScreen(obstacle))
        {
            ResetObstaclePosition(obstacle, screenWidth, screenHeight);
        }
    }

    bool IsCollidingWithObstacle(const Obstacle& obstacle, Rectangle otherBody)
    {
        return CheckCollisionRecs(otherBody, obstacle.topPart) || CheckCollisionRecs(otherBody, obstacle.bottomPart);
    }

    void DrawObstacle(const Obstacle& obstacle)
    {
        DrawRectangleRec(obstacle.topPart, obstacle.color);
        DrawRectangleRec(obstacle.bottomPart, obstacle.color);
    }

    static void ResetObstaclePosition(Obstacle& obstacle, int screenWidth, int screenHeight)
    {
        const float screenHeightFloat = static_cast<float>(screenHeight);

        // El borde superior del hueco se elige al azar, dejando lugar para que las dos partes tengan su alto minimo
        const int lowestGapTop = static_cast<int>(MIN_PART_HEIGHT);
        const int highestGapTop = static_cast<int>(screenHeightFloat - MIN_PART_HEIGHT - GAP_HEIGHT);
        const float gapTop = static_cast<float>(GetRandomValue(lowestGapTop, highestGapTop));

        // La parte de arriba va desde el techo hasta el comienzo del hueco
        obstacle.topPart.x = static_cast<float>(screenWidth);
        obstacle.topPart.y = 0.0f;
        obstacle.topPart.height = gapTop;

        // La parte de abajo va desde el final del hueco hasta el piso
        obstacle.bottomPart.x = static_cast<float>(screenWidth);
        obstacle.bottomPart.y = gapTop + GAP_HEIGHT;
        obstacle.bottomPart.height = screenHeightFloat - obstacle.bottomPart.y;
    }

    static bool IsObstacleOutOfScreen(const Obstacle& obstacle)
    {
        return obstacle.topPart.x + obstacle.topPart.width < 0.0f;
    }
}
