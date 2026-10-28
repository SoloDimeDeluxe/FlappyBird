#ifndef TEXT_H
#define TEXT_H

#include "raylib.h"

namespace ReyesCuadra
{
    // Dibuja un texto centrado horizontalmente en la pantalla, a la altura indicada
    void DrawCenteredText(const char* text, int positionY, int fontSize, Color color);
}

#endif // TEXT_H
