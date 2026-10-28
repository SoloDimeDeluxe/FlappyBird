#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "scenes/scene.h"

namespace ReyesCuadra
{
    // Prepara los botones del menu (llamar una vez, despues de abrir la ventana)
    void InitMainMenu();

    // Revisa si se eligio alguna opcion y devuelve la escena a la que hay que ir
    Scene UpdateMainMenu();

    // Dibuja el titulo, los botones y la version del juego
    void DrawMainMenu();
}

#endif // MAIN_MENU_H
