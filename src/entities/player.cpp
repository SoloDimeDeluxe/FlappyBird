#include "entities/player.h"

// Valores de configuracion del jugador (solo se usan en este archivo)
static const float PLAYER_SIZE = 40.0f;
static const float PLAYER_POSITION_X = 100.0f;
static const float PLAYER_SPEED = 400.0f;
static const Color PLAYER_COLOR = YELLOW;

// Mueve al jugador con las flechas (movimiento simple, todavia sin gravedad)
static void MovePlayerWithInput(Player& player, float deltaTime);

// Mantiene al jugador entre el borde superior y el inferior de la pantalla
static void KeepPlayerInsideScreen(Player& player, int screenHeight);

Player CreatePlayer(int screenHeight)
{
    Player player;

    player.body.width = PLAYER_SIZE;
    player.body.height = PLAYER_SIZE;
    player.body.x = PLAYER_POSITION_X;
    player.body.y = (static_cast<float>(screenHeight) - PLAYER_SIZE) / 2.0f;
    player.speed = PLAYER_SPEED;
    player.color = PLAYER_COLOR;

    return player;
}

void UpdatePlayer(Player& player, int screenHeight, float deltaTime)
{
    MovePlayerWithInput(player, deltaTime);
    KeepPlayerInsideScreen(player, screenHeight);
}

void DrawPlayer(const Player& player)
{
    DrawRectangleRec(player.body, player.color);
}

static void MovePlayerWithInput(Player& player, float deltaTime)
{
    // La velocidad se multiplica por el delta time para que el movimiento sea igual con cualquier cantidad de FPS
    if (IsKeyDown(KEY_UP))
    {
        player.body.y -= player.speed * deltaTime;
    }

    if (IsKeyDown(KEY_DOWN))
    {
        player.body.y += player.speed * deltaTime;
    }
}

static void KeepPlayerInsideScreen(Player& player, int screenHeight)
{
    const float lowestPositionY = static_cast<float>(screenHeight) - player.body.height;

    if (player.body.y < 0.0f)
    {
        player.body.y = 0.0f;
    }
    else if (player.body.y > lowestPositionY)
    {
        player.body.y = lowestPositionY;
    }
}
