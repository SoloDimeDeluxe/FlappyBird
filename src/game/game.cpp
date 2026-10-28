    #include "game/game.h"

#include "raylib.h"

#include "entities/player.h"
#include "entities/obstacle.h"

// Estados posibles del gameplay
enum class GameState
{
    Playing,
    GameOver
};

// Configuracion de la ventana
static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 450;
static const int TARGET_FPS = 60;
static const char* WINDOW_TITLE = "Flappy Bird";

// Version del juego que se muestra en una esquina de la pantalla
static const char* GAME_VERSION_TEXT = "v0.1";

// Textos que ve el usuario
static const char* CONTROLS_TEXT = "Espacio para saltar. Esquiva el bloque verde";
static const char* GAME_OVER_TITLE_TEXT = "PERDISTE";
static const char* GAME_OVER_REASON_TEXT = "Chocaste contra el obstaculo";
static const char* GAME_OVER_OPTIONS_TEXT = "Presiona R para reiniciar o ESC para salir";

// Distribucion de los textos
static const int TEXT_MARGIN = 10;
static const int SMALL_FONT_SIZE = 20;
static const int TITLE_FONT_SIZE = 60;
static const int GAME_OVER_LINE_SPACING = 50;

// Colores
static const Color BACKGROUND_COLOR = SKYBLUE;
static const Color TEXT_COLOR = DARKGRAY;
static const Color GAME_OVER_TITLE_COLOR = RED;

// Todo lo que el juego necesita mientras se ejecuta
struct Game
{
    Player player;
    Obstacle obstacle;
    GameState state;
};

// Crea la ventana y los elementos iniciales del juego
static void InitGame(Game& game);

// Vuelve a poner al jugador y al obstaculo en sus posiciones iniciales
static void ResetGame(Game& game);

// Actualiza la logica del juego segun el estado actual
static void UpdateGame(Game& game);

// Mueve al jugador y al obstaculo y chequea la condicion de derrota
static void UpdateGameplay(Game& game, float deltaTime);

// Espera a que el usuario elija reiniciar despues de perder
static void UpdateGameOver(Game& game);

// Dibuja todo en la pantalla
static void DrawGame(const Game& game);

// Dibuja los controles y la version del juego
static void DrawHud();

// Dibuja el mensaje de derrota y las opciones disponibles
static void DrawGameOverMessage();

// Dibuja un texto centrado horizontalmente en la pantalla
static void DrawCenteredText(const char* text, int positionY, int fontSize, Color color);

// Cierra la ventana
static void CloseGame();

void RunGame()
{
    Game game;

    InitGame(game);

    // ESC o la cruz de la ventana terminan el loop (ESC es la tecla de salida por defecto de raylib)
    while (!WindowShouldClose())
    {
        UpdateGame(game);
        DrawGame(game);
    }

    CloseGame();
}

static void InitGame(Game& game)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);

    ResetGame(game);
}

static void ResetGame(Game& game)
{
    game.player = CreatePlayer(SCREEN_HEIGHT);
    game.obstacle = CreateObstacle(SCREEN_WIDTH, SCREEN_HEIGHT);
    game.state = GameState::Playing;
}

static void UpdateGame(Game& game)
{
    switch (game.state)
    {
    case GameState::Playing:
        UpdateGameplay(game, GetFrameTime());
        break;

    case GameState::GameOver:
        UpdateGameOver(game);
        break;
    }
}

static void UpdateGameplay(Game& game, float deltaTime)
{
    UpdatePlayer(game.player, SCREEN_HEIGHT, deltaTime);
    UpdateObstacle(game.obstacle, SCREEN_WIDTH, SCREEN_HEIGHT, deltaTime);

    // Condicion de derrota: el jugador toca el obstaculo
    if (CheckCollisionRecs(game.player.body, game.obstacle.body))
    {
        game.state = GameState::GameOver;
    }
}

static void UpdateGameOver(Game& game)
{
    if (IsKeyPressed(KEY_R))
    {
        ResetGame(game);
    }
}

static void DrawGame(const Game& game)
{
    BeginDrawing();
    ClearBackground(BACKGROUND_COLOR);

    // Los elementos se siguen dibujando despues de perder, para que el jugador vea como fue el choque
    DrawObstacle(game.obstacle);
    DrawPlayer(game.player);

    DrawHud();

    if (game.state == GameState::GameOver)
    {
        DrawGameOverMessage();
    }

    EndDrawing();
}

static void DrawHud()
{
    DrawText(CONTROLS_TEXT, TEXT_MARGIN, TEXT_MARGIN, SMALL_FONT_SIZE, TEXT_COLOR);

    // Version del juego en la esquina inferior derecha
    const int versionTextWidth = MeasureText(GAME_VERSION_TEXT, SMALL_FONT_SIZE);
    const int versionPositionX = SCREEN_WIDTH - versionTextWidth - TEXT_MARGIN;
    const int versionPositionY = SCREEN_HEIGHT - SMALL_FONT_SIZE - TEXT_MARGIN;

    DrawText(GAME_VERSION_TEXT, versionPositionX, versionPositionY, SMALL_FONT_SIZE, TEXT_COLOR);
}

static void DrawGameOverMessage()
{
    const int titlePositionY = SCREEN_HEIGHT / 2 - TITLE_FONT_SIZE;
    const int reasonPositionY = titlePositionY + TITLE_FONT_SIZE + TEXT_MARGIN;
    const int optionsPositionY = reasonPositionY + GAME_OVER_LINE_SPACING;

    DrawCenteredText(GAME_OVER_TITLE_TEXT, titlePositionY, TITLE_FONT_SIZE, GAME_OVER_TITLE_COLOR);
    DrawCenteredText(GAME_OVER_REASON_TEXT, reasonPositionY, SMALL_FONT_SIZE, TEXT_COLOR);
    DrawCenteredText(GAME_OVER_OPTIONS_TEXT, optionsPositionY, SMALL_FONT_SIZE, TEXT_COLOR);
}

static void DrawCenteredText(const char* text, int positionY, int fontSize, Color color)
{
    const int textWidth = MeasureText(text, fontSize);
    const int positionX = (SCREEN_WIDTH - textWidth) / 2;

    DrawText(text, positionX, positionY, fontSize, color);
}

static void CloseGame()
{
    CloseWindow();
}
