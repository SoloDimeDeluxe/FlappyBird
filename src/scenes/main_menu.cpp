#include "scenes/main_menu.h"

#include "raylib.h"

#include "ui/button.h"
#include "ui/text.h"

// Textos que ve el usuario
static const char* GAME_TITLE_TEXT = "FLAPPY BIRD";
static const char* MENU_HINT_TEXT = "Hace clic en una opcion";
static const char* PLAY_BUTTON_TEXT = "Jugar";
static const char* EXIT_BUTTON_TEXT = "Salir";

// Version del juego, que ahora se muestra en un borde del menu
static const char* GAME_VERSION_TEXT = "v0.2";

// Distribucion de los elementos en la pantalla
static const int TITLE_POSITION_Y = 60;
static const int TITLE_FONT_SIZE = 60;
static const int HINT_POSITION_Y = 140;
static const int SMALL_FONT_SIZE = 20;
static const int TEXT_MARGIN = 10;
static const float FIRST_BUTTON_POSITION_Y = 200.0f;
static const float BUTTON_SPACING = 70.0f; // Distancia vertical entre el comienzo de un boton y el siguiente

// Colores
static const Color MENU_BACKGROUND_COLOR = SKYBLUE;
static const Color TITLE_COLOR = DARKGREEN;
static const Color TEXT_COLOR = DARKGRAY;

// Botones del menu (solo se usan en este archivo)
static Button playButton;
static Button exitButton;

// Dibuja la version del juego en la esquina inferior derecha
static void DrawGameVersion();

void InitMainMenu()
{
    // Los botones van uno debajo del otro, centrados en la pantalla
    playButton = CreateCenteredButton(PLAY_BUTTON_TEXT, FIRST_BUTTON_POSITION_Y);
    exitButton = CreateCenteredButton(EXIT_BUTTON_TEXT, FIRST_BUTTON_POSITION_Y + BUTTON_SPACING);
}

Scene UpdateMainMenu()
{
    if (IsButtonClicked(playButton))
    {
        return Scene::Gameplay;
    }

    if (IsButtonClicked(exitButton))
    {
        return Scene::Exit;
    }

    // Si no se eligio nada, se sigue en el menu
    return Scene::MainMenu;
}

void DrawMainMenu()
{
    ClearBackground(MENU_BACKGROUND_COLOR);

    DrawCenteredText(GAME_TITLE_TEXT, TITLE_POSITION_Y, TITLE_FONT_SIZE, TITLE_COLOR);
    DrawCenteredText(MENU_HINT_TEXT, HINT_POSITION_Y, SMALL_FONT_SIZE, TEXT_COLOR);

    DrawButton(playButton);
    DrawButton(exitButton);

    DrawGameVersion();
}

static void DrawGameVersion()
{
    const int versionTextWidth = MeasureText(GAME_VERSION_TEXT, SMALL_FONT_SIZE);
    const int versionPositionX = GetScreenWidth() - versionTextWidth - TEXT_MARGIN;
    const int versionPositionY = GetScreenHeight() - SMALL_FONT_SIZE - TEXT_MARGIN;

    DrawText(GAME_VERSION_TEXT, versionPositionX, versionPositionY, SMALL_FONT_SIZE, TEXT_COLOR);
}
