# Flappy Bird

Juego tipo **Flappy Bird** hecho en C++ con [raylib](https://www.raylib.com/) para la materia
Práctica Profesional I: Desarrollo de Videojuegos I (Image Campus, 2026).

El proyecto se desarrolla de forma iterativa: cada versión agrega funcionalidades nuevas.

## Versión actual: 0.2

- El juego arranca en un menú con las opciones **Jugar**, **Créditos** y **Salir**; la versión se ve en una esquina del menú.
- El jugador controla un cuadrado amarillo en el lado izquierdo de la pantalla: la gravedad lo hace caer y con ESPACIO salta.
- Un obstáculo verde de dos partes (arriba y abajo, con un hueco en el medio) aparece por la derecha y avanza hacia la izquierda; al salir de la pantalla vuelve a aparecer por la derecha con el hueco a otra altura.
- Se pierde al chocar con el obstáculo o al caer al piso. El techo frena al jugador.

## Controles

| Tecla | Acción |
| --- | --- |
| Clic izquierdo | Elegir una opción del menú |
| ESPACIO | Saltar |
| R | Reiniciar después de perder |
| ESC | Volver al menú desde el gameplay o los créditos |

## Cómo compilar

1. Clonar el repositorio.
2. Abrir `FlappyBird.slnx` con Visual Studio 2026.
3. Compilar en configuración **Debug** o **Release** (x64).

raylib 6.2 ya viene incluida en la carpeta `lib/raylib`.

## Autor

Valentin Reyes — [GitHub](https://github.com/SoloDimeDeluxe) · [itch.io](https://solodim3deluxe.itch.io/)
