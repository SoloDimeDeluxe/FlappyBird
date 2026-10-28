#include "ui/text.h"

namespace ReyesCuadra
{
    void DrawCenteredText(const char* text, int positionY, int fontSize, Color color)
    {
        // Se usa el ancho real de la ventana, asi sirve para cualquier escena
        const int textWidth = MeasureText(text, fontSize);
        const int positionX = (GetScreenWidth() - textWidth) / 2;

        DrawText(text, positionX, positionY, fontSize, color);
    }
}
