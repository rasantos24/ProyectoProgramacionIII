#include "condicion.h"
#include "menu.h"
#include <allegro.h>

void victoria(BITMAP* v)
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
            blit(v, screen, 0, y, 0, 10, 600, 600);
        }

        if(key[KEY_ESC])
        {
            y = 400;
            cargar = true;
        }

        if(cargar)
            cont++;
        if(cont > 400)
            salir = true;

        rest(10);
        if(++cambio == 50)
            cambio = 0;

        portada(v);
    }

    clear_to_color(screen, 0x000000);
}

void imprimir(BITMAP* fondo, BITMAP* buffer)
{
    masked_blit(fondo, buffer, 0, 0, 0, 0, 600, 600);
}
