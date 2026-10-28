#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"

namespace ReyesCuadra
{
    // Boton rectangular con un texto en el medio, que se aprieta con el mouse
    struct Button
    {
        Rectangle bounds;
        const char* text;
    };

    // Crea un boton centrado horizontalmente en la pantalla, con su borde superior en la altura indicada
    Button CreateCenteredButton(const char* text, float positionY);

    // Devuelve true si el mouse esta encima del boton
    bool IsButtonHovered(const Button& button);

    // Devuelve true en el frame en que se hace clic izquierdo sobre el boton
    bool IsButtonClicked(const Button& button);

    // Dibuja el boton, resaltado si el mouse esta encima
    void DrawButton(const Button& button);
}

#endif // BUTTON_H
