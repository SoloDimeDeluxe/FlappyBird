#include "entities/player.h"

// Valores de configuracion del jugador (solo se usan en este archivo)
static const float PLAYER_SIZE = 40.0f;
static const float PLAYER_POSITION_X = 100.0f;
static const float GRAVITY = 1200.0f;      // Aceleracion hacia abajo en pixeles por segundo al cuadrado
static const float JUMP_VELOCITY = -450.0f; // Velocidad que recibe al saltar (negativa porque va hacia arriba)
static const KeyboardKey JUMP_KEY = KEY_SPACE;
static const Color PLAYER_COLOR = YELLOW;

// Si se presiona la tecla de salto, reemplaza la velocidad actual por la del salto
static void HandleJumpInput(Player& player);

// Acelera al jugador hacia abajo y lo mueve segun su velocidad vertical
static void ApplyGravity(Player& player, float deltaTime);

// Frena al jugador cuando choca contra el borde superior de la pantalla (el techo)
static void StopPlayerAtCeiling(Player& player);

Player CreatePlayer(int screenHeight)
{
    Player player;

    player.body.width = PLAYER_SIZE;
    player.body.height = PLAYER_SIZE;
    player.body.x = PLAYER_POSITION_X;
    player.body.y = (static_cast<float>(screenHeight) - PLAYER_SIZE) / 2.0f;
    player.verticalVelocity = 0.0f;
    player.color = PLAYER_COLOR;

    return player;
}

void UpdatePlayer(Player& player, float deltaTime)
{
    // El salto se chequea antes de mover, para que el jugador suba en el mismo frame en que se presiona
    HandleJumpInput(player);
    ApplyGravity(player, deltaTime);
    StopPlayerAtCeiling(player);
}

bool HasPlayerReachedFloor(const Player& player, int screenHeight)
{
    const float playerBottom = player.body.y + player.body.height;

    return playerBottom >= static_cast<float>(screenHeight);
}

void DrawPlayer(const Player& player)
{
    DrawRectangleRec(player.body, player.color);
}

static void HandleJumpInput(Player& player)
{
    // Se reemplaza la velocidad (no se suma) para que el salto sea inmediato aunque el jugador venga cayendo rapido
    if (IsKeyPressed(JUMP_KEY))
    {
        player.verticalVelocity = JUMP_VELOCITY;
    }
}

static void ApplyGravity(Player& player, float deltaTime)
{
    // Todo se multiplica por el delta time para que el movimiento sea igual con cualquier cantidad de FPS
    player.verticalVelocity += GRAVITY * deltaTime;
    player.body.y += player.verticalVelocity * deltaTime;
}

static void StopPlayerAtCeiling(Player& player)
{
    if (player.body.y < 0.0f)
    {
        // Al chocar contra el techo se frena la subida, para que empiece a caer enseguida
        player.body.y = 0.0f;
        player.verticalVelocity = 0.0f;
    }
}
