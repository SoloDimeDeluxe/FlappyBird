#ifndef SCENE_H
#define SCENE_H

namespace ReyesCuadra
{
    // Escenas (pantallas) entre las que se puede mover el juego.
    // Exit no es una pantalla real: indica que el usuario eligio salir del juego
    enum class Scene
    {
        MainMenu,
        Gameplay,
        Credits,
        Exit
    };
}

#endif // SCENE_H
