#ifndef SCENE_H
#define SCENE_H

// Escenas (pantallas) entre las que se puede mover el juego.
// Exit no es una pantalla real: indica que el usuario eligio salir del juego
enum class Scene
{
    MainMenu,
    Gameplay,
    Exit
};

#endif // SCENE_H
