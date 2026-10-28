#include "ui/button.h"

namespace ReyesCuadra
{
    // Tamano y estilo de los botones (solo se usan en este archivo)
    static const float BUTTON_WIDTH = 200.0f;
    static const float BUTTON_HEIGHT = 50.0f;
    static const float BUTTON_BORDER_THICKNESS = 3.0f;
    static const int BUTTON_FONT_SIZE = 25;

    static const Color BUTTON_COLOR = LIGHTGRAY;
    static const Color BUTTON_HOVER_COLOR = YELLOW;
    static const Color BUTTON_BORDER_COLOR = DARKGRAY;
    static const Color BUTTON_TEXT_COLOR = DARKGRAY;

    Button CreateCenteredButton(const char* text, float positionY)
    {
        Button button;

        button.bounds.width = BUTTON_WIDTH;
        button.bounds.height = BUTTON_HEIGHT;
        button.bounds.x = (static_cast<float>(GetScreenWidth()) - BUTTON_WIDTH) / 2.0f;
        button.bounds.y = positionY;
        button.text = text;

        return button;
    }

    bool IsButtonHovered(const Button& button)
    {
        return CheckCollisionPointRec(GetMousePosition(), button.bounds);
    }

    bool IsButtonClicked(const Button& button)
    {
        return IsButtonHovered(button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    }

    void DrawButton(const Button& button)
    {
        // Se resalta el boton cuando el mouse esta encima, para que el usuario sepa que se puede apretar
        const Color fillColor = IsButtonHovered(button) ? BUTTON_HOVER_COLOR : BUTTON_COLOR;

        DrawRectangleRec(button.bounds, fillColor);
        DrawRectangleLinesEx(button.bounds, BUTTON_BORDER_THICKNESS, BUTTON_BORDER_COLOR);

        // El texto va centrado dentro del boton
        const int textWidth = MeasureText(button.text, BUTTON_FONT_SIZE);
        const int textPositionX = static_cast<int>(button.bounds.x + (button.bounds.width - static_cast<float>(textWidth)) / 2.0f);
        const int textPositionY = static_cast<int>(button.bounds.y + (button.bounds.height - static_cast<float>(BUTTON_FONT_SIZE)) / 2.0f);

        DrawText(button.text, textPositionX, textPositionY, BUTTON_FONT_SIZE, BUTTON_TEXT_COLOR);
    }
}
