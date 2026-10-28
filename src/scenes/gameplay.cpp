#include "scenes/gameplay.h"

#include "raylib.h"

#include "entities/player.h"
#include "entities/obstacle.h"
#include "ui/text.h"

// Estados posibles dentro de una partida
enum class RunState
{
    Playing,
    GameOver
};

// Motivos por los que se puede perder
enum class DefeatReason
{
    ObstacleCollision,
    FellToFloor
};

// Teclas de esta escena
static const KeyboardKey BACK_TO_MENU_KEY = KEY_ESCAPE;
static const KeyboardKey RESTART_KEY = KEY_R;

// Textos que ve el usuario
static const char* CONTROLS_TEXT = "ESPACIO para saltar. Pasa por el hueco del obstaculo verde";
static const char* BACK_TO_MENU_TEXT = "ESC para volver al menu";
static const char* GAME_OVER_TITLE_TEXT = "PERDISTE";
static const char* OBSTACLE_DEFEAT_TEXT = "Chocaste contra el obstaculo";
static const char* FLOOR_DEFEAT_TEXT = "Caiste al piso";
static const char* GAME_OVER_OPTIONS_TEXT = "Presiona R para reiniciar o ESC para volver al menu";

// Distribucion de los textos
static const int TEXT_MARGIN = 10;
static const int SMALL_FONT_SIZE = 20;
static const int TITLE_FONT_SIZE = 60;
static const int GAME_OVER_LINE_SPACING = 50;

// Colores
static const Color GAMEPLAY_BACKGROUND_COLOR = SKYBLUE;
static const Color TEXT_COLOR = DARKGRAY;
static const Color GAME_OVER_TITLE_COLOR = RED;

// Todo lo que la partida necesita mientras se juega
struct GameplayState
{
    Player player;
    Obstacle obstacle;
    RunState runState;
    DefeatReason defeatReason;
};

// Estado de la partida actual (solo se usa en este archivo)
static GameplayState gameplay;

// Mueve al jugador y al obstaculo y chequea las condiciones de derrota
static void UpdatePlaying(float deltaTime);

// Termina la partida guardando el motivo, para mostrarlo en el mensaje de derrota
static void EndRun(DefeatReason reason);

// Espera a que el usuario elija reiniciar despues de perder
static void UpdateGameOver();

// Dibuja los controles en la parte de arriba de la pantalla
static void DrawHud();

// Dibuja el mensaje de derrota, su motivo y las opciones disponibles
static void DrawGameOverMessage(DefeatReason reason);

// Devuelve el texto que explica el motivo de la derrota
static const char* GetDefeatReasonText(DefeatReason reason);

void InitGameplay()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    gameplay.player = CreatePlayer(screenHeight);
    gameplay.obstacle = CreateObstacle(screenWidth, screenHeight);
    gameplay.runState = RunState::Playing;
    gameplay.defeatReason = DefeatReason::ObstacleCollision;
}

Scene UpdateGameplay()
{
    // Se puede volver al menu en cualquier momento, tanto jugando como despues de perder
    if (IsKeyPressed(BACK_TO_MENU_KEY))
    {
        return Scene::MainMenu;
    }

    switch (gameplay.runState)
    {
    case RunState::Playing:
        UpdatePlaying(GetFrameTime());
        break;

    case RunState::GameOver:
        UpdateGameOver();
        break;
    }

    return Scene::Gameplay;
}

void DrawGameplay()
{
    ClearBackground(GAMEPLAY_BACKGROUND_COLOR);

    // Los elementos se siguen dibujando despues de perder, para que el jugador vea como fue el choque
    DrawObstacle(gameplay.obstacle);
    DrawPlayer(gameplay.player);

    DrawHud();

    if (gameplay.runState == RunState::GameOver)
    {
        DrawGameOverMessage(gameplay.defeatReason);
    }
}

static void UpdatePlaying(float deltaTime)
{
    UpdatePlayer(gameplay.player, deltaTime);
    UpdateObstacle(gameplay.obstacle, GetScreenWidth(), GetScreenHeight(), deltaTime);

    // Condiciones de derrota: el jugador toca el obstaculo o cae hasta el piso
    if (IsCollidingWithObstacle(gameplay.obstacle, gameplay.player.body))
    {
        EndRun(DefeatReason::ObstacleCollision);
    }
    else if (HasPlayerReachedFloor(gameplay.player, GetScreenHeight()))
    {
        EndRun(DefeatReason::FellToFloor);
    }
}

static void EndRun(DefeatReason reason)
{
    gameplay.runState = RunState::GameOver;
    gameplay.defeatReason = reason;
}

static void UpdateGameOver()
{
    // Reiniciar arranca otra partida sin tener que pasar por el menu
    if (IsKeyPressed(RESTART_KEY))
    {
        InitGameplay();
    }
}

static void DrawHud()
{
    DrawText(CONTROLS_TEXT, TEXT_MARGIN, TEXT_MARGIN, SMALL_FONT_SIZE, TEXT_COLOR);
    DrawText(BACK_TO_MENU_TEXT, TEXT_MARGIN, TEXT_MARGIN * 2 + SMALL_FONT_SIZE, SMALL_FONT_SIZE, TEXT_COLOR);
}

static void DrawGameOverMessage(DefeatReason reason)
{
    const int titlePositionY = GetScreenHeight() / 2 - TITLE_FONT_SIZE;
    const int reasonPositionY = titlePositionY + TITLE_FONT_SIZE + TEXT_MARGIN;
    const int optionsPositionY = reasonPositionY + GAME_OVER_LINE_SPACING;

    DrawCenteredText(GAME_OVER_TITLE_TEXT, titlePositionY, TITLE_FONT_SIZE, GAME_OVER_TITLE_COLOR);
    DrawCenteredText(GetDefeatReasonText(reason), reasonPositionY, SMALL_FONT_SIZE, TEXT_COLOR);
    DrawCenteredText(GAME_OVER_OPTIONS_TEXT, optionsPositionY, SMALL_FONT_SIZE, TEXT_COLOR);
}

static const char* GetDefeatReasonText(DefeatReason reason)
{
    if (reason == DefeatReason::FellToFloor)
    {
        return FLOOR_DEFEAT_TEXT;
    }

    return OBSTACLE_DEFEAT_TEXT;
}
