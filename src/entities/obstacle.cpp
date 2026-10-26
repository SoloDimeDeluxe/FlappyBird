#include "entities/obstacle.h"

// Valores de configuracion del obstaculo (solo se usan en este archivo)
static const float OBSTACLE_WIDTH = 60.0f;
static const float OBSTACLE_HEIGHT = 180.0f;
static const float OBSTACLE_SPEED = 300.0f;
static const Color OBSTACLE_COLOR = GREEN;

// Ubica el obstaculo justo afuera del borde derecho de la pantalla, a una altura al azar
static void ResetObstaclePosition(Obstacle& obstacle, int screenWidth, int screenHeight);

// Devuelve true cuando el obstaculo salio por completo por el borde izquierdo de la pantalla
static bool IsObstacleOutOfScreen(const Obstacle& obstacle);

Obstacle CreateObstacle(int screenWidth, int screenHeight)
{
    Obstacle obstacle;

    obstacle.body.width = OBSTACLE_WIDTH;
    obstacle.body.height = OBSTACLE_HEIGHT;
    obstacle.speed = OBSTACLE_SPEED;
    obstacle.color = OBSTACLE_COLOR;

    ResetObstaclePosition(obstacle, screenWidth, screenHeight);

    return obstacle;
}

void UpdateObstacle(Obstacle& obstacle, int screenWidth, int screenHeight, float deltaTime)
{
    obstacle.body.x -= obstacle.speed * deltaTime;

    if (IsObstacleOutOfScreen(obstacle))
    {
        ResetObstaclePosition(obstacle, screenWidth, screenHeight);
    }
}

void DrawObstacle(const Obstacle& obstacle)
{
    DrawRectangleRec(obstacle.body, obstacle.color);
}

static void ResetObstaclePosition(Obstacle& obstacle, int screenWidth, int screenHeight)
{
    // La Y maxima valida es la que deja el obstaculo completo visible en la parte de abajo
    const int highestPositionY = screenHeight - static_cast<int>(obstacle.body.height);

    obstacle.body.x = static_cast<float>(screenWidth);
    obstacle.body.y = static_cast<float>(GetRandomValue(0, highestPositionY));
}

static bool IsObstacleOutOfScreen(const Obstacle& obstacle)
{
    return obstacle.body.x + obstacle.body.width < 0.0f;
}
