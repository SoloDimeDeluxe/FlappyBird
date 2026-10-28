#include "entities/player.h"

// Valores de configuracion del jugador (solo se usan en este archivo)
static const float PLAYER_SIZE = 40.0f;
static const float PLAYER_POSITION_X = 100.0f;
static const float GRAVITY = 1200.0f;
static const float JUMP_VELOCITY = -450.0f;
static const KeyboardKey JUMP_KEY = KEY_SPACE;
static const Color PLAYER_COLOR = YELLOW;


// Al apretar la tecla de salto, reemplazar la velocidad actual con la de salto
static void HandleJumpInput(Player& player);

// Acelera al jugador hacia abajo y lo mueve segun su velocidad
static void ApplyGravity(Player& player, float deltaTime);

// Mantiene al jugador entre el borde superior y el inferior de la pantalla
static void KeepPlayerInsideScreen(Player& player, int screenHeight);

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

void UpdatePlayer(Player& player, int screenHeight, float deltaTime)
{
    //Chequea el salto antes de moverse para que el jugador suba en el mismo frame que presionó la tecla
    HandleJumpInput(player);
    ApplyGravity(player, deltaTime);
    KeepPlayerInsideScreen(player, screenHeight);
}

void DrawPlayer(const Player& player)
{
    DrawRectangleRec(player.body, player.color);
}

static void HandleJumpInput(Player& player)
{
    // Se reemplaza la velocidad para que el salto sea inmediato independientemente de si cae rapido el jugador
    if (IsKeyPressed(JUMP_KEY))
    {
        player.verticalVelocity = JUMP_VELOCITY;
    }
}

static void ApplyGravity(Player& player, float deltaTime)
{
    // Todo se multiplica por delta time
    player.verticalVelocity += GRAVITY * deltaTime;
    player.body.y += player.verticalVelocity * deltaTime;
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
