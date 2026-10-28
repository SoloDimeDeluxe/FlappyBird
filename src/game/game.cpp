#include "game/game.h"

#include "raylib.h"

#include "scenes/scene.h"
#include "scenes/main_menu.h"
#include "scenes/gameplay.h"
#include "scenes/credits.h"

// Configuracion de la ventana
static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 450;
static const int TARGET_FPS = 60;
static const char* WINDOW_TITLE = "Flappy Bird";

// Escena con la que arranca el juego
static const Scene FIRST_SCENE = Scene::MainMenu;

// Abre la ventana y prepara las escenas
static void InitGame();

// Actualiza la escena actual y devuelve la escena en la que tiene que estar el juego el proximo frame
static Scene UpdateCurrentScene(Scene currentScene);

// Prepara la escena a la que se acaba de entrar
static void EnterScene(Scene scene);

// Dibuja la escena actual
static void DrawCurrentScene(Scene currentScene);

// Cierra la ventana
static void CloseGame();

void RunGame()
{
    InitGame();

    Scene currentScene = FIRST_SCENE;

    // La cruz de la ventana o la opcion Salir del menu terminan el loop
    while (!WindowShouldClose() && currentScene != Scene::Exit)
    {
        currentScene = UpdateCurrentScene(currentScene);
        DrawCurrentScene(currentScene);
    }

    CloseGame();
}

static void InitGame()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(TARGET_FPS);

    // ESC deja de cerrar el juego (es la tecla de salida por defecto de raylib), ahora se usa para volver al menu
    SetExitKey(KEY_NULL);

    InitMainMenu();
}

static Scene UpdateCurrentScene(Scene currentScene)
{
    Scene nextScene = currentScene;

    switch (currentScene)
    {
    case Scene::MainMenu:
        nextScene = UpdateMainMenu();
        break;

    case Scene::Gameplay:
        nextScene = UpdateGameplay();
        break;

    case Scene::Credits:
        nextScene = UpdateCredits();
        break;

    case Scene::Exit:
        break;
    }

    // Solo se prepara la escena cuando se cambia, no en todos los frames
    if (nextScene != currentScene)
    {
        EnterScene(nextScene);
    }

    return nextScene;
}

static void EnterScene(Scene scene)
{
    // Cada vez que se entra al gameplay desde el menu arranca una partida nueva
    if (scene == Scene::Gameplay)
    {
        InitGameplay();
    }
}

static void DrawCurrentScene(Scene currentScene)
{
    BeginDrawing();

    switch (currentScene)
    {
    case Scene::MainMenu:
        DrawMainMenu();
        break;

    case Scene::Gameplay:
        DrawGameplay();
        break;

    case Scene::Credits:
        DrawCredits();
        break;

    case Scene::Exit:
        break;
    }

    EndDrawing();
}

static void CloseGame()
{
    CloseWindow();
}
