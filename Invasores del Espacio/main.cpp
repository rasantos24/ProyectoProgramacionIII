#include <allegro.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>

#include "inicia.h"
#include "disparos.h"
#include "personajes.h"
#include "menu.h"

#define ANCHO 600
#define ALTO  600

int puntaje = 0;
int marca = 0;
int nuevaMarca;

using namespace std;

bool limites(struct NAVE Enemigo[], int& direccion)
{
    for(int i = 0; i < 55; i++)
    {
        if((Enemigo[i].x > 520 || Enemigo[i].x < 50) && Enemigo[i].vida != 0)
        {
            direccion = -1*direccion;
            return true;
        }
    }
    return false;
}

void movimientoEnemigo(struct NAVE Enemigo[], int& mover, int& direccion)
{
    for(int i = 0; i < 55; i++)
        Enemigo[i].x += direccion;

    if(++mover == 2)
        mover = 0;

    if(limites(Enemigo, direccion))
    {
        for(int j = 0; j < 55; j++)
        {
            Enemigo[j].y += 10;
        }
    }
}

bool limitesJefe(struct NAVE Jefe[], int& direccion)
{
    for(int i = 0; i < 55; i++)
    {
        if((Jefe[i].x > 520 || Jefe[i].x < 50) && Jefe[i].vida != 0)
        {
            direccion = -1*direccion;
            return true;
        }
    }
    return false;
}

void movimientoJefe(struct NAVE Jefe[], int& mover, int& direccion)
{
    for(int i = 0; i < 55; i++)
        Jefe[i].x += direccion;

    if(++mover == 2)
        mover = 0;

    if(limitesJefe(Jefe, direccion))
    {
        for(int j = 0; j < 55; j++)
        {
            Jefe[j].y += 10;
        }
    }
}

int main()
{
//    cout<<"Puntos: "+puntaje<<endl;
    srand(time(NULL));
    inicia_allegro(ANCHO,ALTO);
	inicia_audio(70,70);
//crear los bitmap y la musica
    BITMAP *buffer = create_bitmap(ANCHO, ALTO);
    BITMAP *menu = load_bitmap("Recursos/portada2.bmp", NULL);
    BITMAP *fondo = load_bitmap("Recursos/fondo1.bmp", NULL);
    BITMAP *muro = load_bitmap("Recursos/escudos1.bmp", NULL);
    BITMAP *ganar = load_bitmap("Recursos/victoria.bmp", NULL);
    BITMAP *derro = load_bitmap("Recursos/derrota.bmp", NULL);
    BITMAP *punt = load_bitmap("Recursos/puntos.bmp", NULL);
    MIDI *musicaFondo = load_midi("Recursos/audio.mid");
//Nave and Enemy's
    NAVE Nave;
    Nave.inicia("Recursos/nave1.bmp", "Recursos/Bala.bmp", 6, 12, 30, 20, ANCHO/2, ALTO-70, -8, 0, 3, "Recursos/0.wav", "Recursos/explosion.wav"); //Player
    NAVE Enemigo[60]; //Enemy
    NAVE Jefe[60];
    tropaEnemigos(Enemigo);
    jefeFinal(Jefe);
    Balas disparos[Nave.maxDisp];
    Balas disparosEnemigo[Enemigo[0].maxDisp];
    Balas disparosJefe[Jefe[0].maxDisp];
//escudos
    escudo mura[40];
    iniciarEscudo(mura);

    int raza = rand()%55;
    int mover = 0;
    int direc = -5;
    int velocidad = 15;
    int numEnem = 55;

    int razaJefe = rand()%55;
    int moverJefe = 0;
    int direcJefe = -5;
    int velocidadJefe = 15;
    int numJefe = 55;

    play_midi(musicaFondo,1);
    portada(menu);

    while(!key[KEY_ESC] && Nave.vida > 0 && numEnem > 0 /*&& numJefe > 0*/)
    {
        clear_to_color(buffer,0x000000);
        pintarEscudo(mura, muro, buffer);

        if(Enemigo[0].temporizador(velocidad))
            movimientoEnemigo(Enemigo, mover, direc);
        if(Enemigo[1].temporizador(300))
        {
            if(velocidad >= 2)
            {
                velocidad -= 1;
                if(direc < 0)
                    direc += -1;
                else
                    direc += 1;
            }
        }
//Nave
        Nave.pinta(buffer,0,0);
        Nave.mueve();
        Nave.maxDisp = 3;
        crearBalaNave(Nave, disparos);
        Nave.disparo(disparos, buffer);
        for(int i = 0; i < 55; i++)
        {
            if(eliminarNave(Nave,Enemigo[i],disparos))
                explosionEnemigo(Enemigo[i],buffer, numEnem);
        }
        //puntaje+=10;
        if(puntaje > marca)
        {
            ofstream out("Puntos.txt");
            out<<puntaje<<endl;
            out.close();
        }
        eliminarEscudo(Nave, mura, disparos);
//Enemy
        pintarEnemigos(Enemigo, buffer, mover);
        crearBalaEnemigo(Enemigo, raza);
        Enemigo[raza].disparo(disparosEnemigo, buffer);
        if(eliminarNave(Enemigo[raza], Nave, disparosEnemigo))
        {
            explosionNave(Nave, buffer, fondo);
        }
        eliminarEscudo(Enemigo[raza], mura, disparosEnemigo);
//winner
        if(Nave.vida == 0)
        {
            vicder(derro,buffer);
            rest(5000);
        }
        else if(numEnem == 0)
        {
//            clear_to_color(buffer,0x000000);
//            pintarEscudo(mura, muro, buffer);
//
//            if(Jefe[0].temporizador(velocidadJefe))
//                movimientoJefe(Jefe, moverJefe, direcJefe);
//            if(Jefe[1].temporizador(300))
//            {
//                if(velocidadJefe >= 2)
//                {
//                    velocidadJefe -= 1;
//                    if(direcJefe < 0)
//                        direcJefe += -1;
//                    else
//                        direcJefe += 1;
//                }
//            }
//    //Nave
//            Nave.pinta(buffer,0,0);
//            Nave.mueve();
//            Nave.maxDisp = 3;
//            crearBalaNave(Nave, disparos);
//            Nave.disparo(disparos, buffer);
//            for(int i = 0; i < 55; i++)
//            {
//                if(eliminarNave(Nave,Jefe[i],disparos))
//                    explosionJefe(Jefe[i],buffer, numJefe);
//            }
//            //puntaje+=10;
//            if(puntaje > marca)
//            {
//                ofstream out("Puntos.txt");
//                out<<puntaje<<endl;
//                out.close();
//            }
//            eliminarEscudo(Nave, mura, disparos);
//    //Enemy
//            pintarJefe(Jefe, buffer, moverJefe);
//            crearBalaJefe(Jefe, razaJefe);
//            Jefe[razaJefe].disparo(disparosJefe, buffer);
//            if(eliminarNave(Jefe[razaJefe], Nave, disparosJefe))
//            {
//                explosionNave(Nave, buffer, fondo);
//            }
//            eliminarEscudo(Jefe[razaJefe], mura, disparosJefe);

            vicder(ganar,buffer);
            rest(5000);

            if(numJefe == 0)
            {

            }
        }
//Found
        imprimirFondo(fondo, buffer);
        Nave.vidas(buffer);
        blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
        rest(15);

    }

    ifstream in("Puntos.txt");
    int nm;
    in>>nm;
    marca = nm;
    cout<<marca<<endl;
    in.close();

	return 0;
}

END_OF_MAIN();

