#include "menu.h"
#include <allegro.h>

void portada(BITMAP* m)
{
    int cambio = 0;
    int y = 0;
    int cont = 0;
    bool salir = false;
    bool cargar = false;

    while(!salir)
    {
        if(cambio < 25)
        {
            blit(m, screen, 0, y, 0, 100, 600, 400);
        }
        else
        {
            blit(m, screen, 600, y, 0, 100, 600, 400);
        }

        if(key[KEY_ENTER])
        {
            y = 400;
            cargar = true;
        }

        if(key[KEY_ESC])
        {
            exit(0);
        }

        if(cargar)
            cont++;
        if(cont > 400)
            salir = true;

        rest(15);
        if(++cambio == 50)
            cambio = 0;
    }

    clear_to_color(screen, 0x000000);
}

void imprimirFondo(BITMAP* fondo, BITMAP* buffer)
{
    masked_blit(fondo, buffer, 0, 0, 0, 0, 600, 600);
}
