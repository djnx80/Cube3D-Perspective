//#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include "allegro5/allegro.h"
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_image.h"
#include "allegroStart.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* sin */
#include <string>

#define PI 3.14159265

void point(unsigned char *pt, int xx, int yy, unsigned char r, unsigned char g, unsigned char b);
void ustawPunkty();
void ustawPunktyStozek();
void rysujPunkty();
void obrocX(double alfa);
void obrocY(double alfa);
void obrocZ(double alfa);
void przesunXY(double x, double y, bool);

using namespace std;

allegroStart mA(800,600);
ALLEGRO_DISPLAY *okno = mA.openWindow();
ALLEGRO_BITMAP  *bitmapa = mA.openBitmap(800,600);
ALLEGRO_KEYBOARD_STATE klawisz;
ALLEGRO_LOCKED_REGION *lr;
unsigned char *ptr;

double pX[100], pY[100], pZ[100];
int edges[50][2];
int ileP=8, ileKrawedzi=12;
double xC=400, yC=300;
bool wPrawo = true;

void *__gxx_personality_v0;


int main()  {

    ustawPunkty();
  //  ustawPunktyStozek();
    double txc, tyc;
    float dX=4;


    while( !al_key_down( & klawisz, ALLEGRO_KEY_ESCAPE ) )    {
        lr = al_lock_bitmap(bitmapa, ALLEGRO_PIXEL_FORMAT_ABGR_8888, ALLEGRO_LOCK_WRITEONLY);
        ptr = (unsigned char *)lr->data;

		al_clear_to_color(al_map_rgb(100,0,0));
		obrocX(0.6);
		obrocY(0.6);
		obrocZ(0.6);
		przesunXY(dX,0, wPrawo);

		rysujPunkty();
/*
        txc=xC;
        tyc=yC;
		rysujPunkty();
		przesunXY(150,0);
		rysujPunkty();
		przesunXY(150,0);
		rysujPunkty();
		przesunXY(150,0);
		rysujPunkty();
		przesunXY(150,0);
		rysujPunkty();
        xC=txc;
        yC=tyc;
*/

        al_draw_bitmap(bitmapa,0,0,0);
        al_unlock_bitmap(bitmapa);
        al_flip_display();
        al_get_keyboard_state( & klawisz );
        al_rest(0.004);
        }

	return 0;
}

void przesunXY(double x, double y, bool kierunek)   {
    if (kierunek == true)
        xC+=x;
    if (kierunek == false)
        xC-=x;
    if (xC > 700)
        wPrawo = false;
    if (xC < 100)
        wPrawo = true;
    yC+=y;
    for (int n=0; n<ileP; n++)  {
 //       pX[n]+=x;
    }
}

void obrocX(double alfa)    {
    double yt,zt;
    alfa = (alfa*PI)/180;
    for (int n=0; n<ileP; n++)  {
        yt = (cos(alfa)*pY[n]) - (sin(alfa)*pZ[n]);
        zt = (sin(alfa)*pY[n]) + (cos(alfa)*pZ[n]);
        pY[n] = yt;
        pZ[n] = zt;
    }
}

void obrocY(double alfa)    {
    double xt,zt;
    alfa = (alfa*PI)/180;
    for (int n=0; n<ileP; n++)  {
        xt = (cos(alfa)*pX[n]) - (sin(alfa)*pZ[n]);
        zt = (sin(alfa)*pX[n]) + (cos(alfa)*pZ[n]);
        pX[n] = xt;
        pZ[n] = zt;
    }
}

void obrocZ(double alfa)    {
    double xt,yt;
    alfa = (alfa*PI)/180;
    for (int n=0; n<ileP; n++)  {
        xt = (cos(alfa)*pX[n]) - (sin(alfa)*pY[n]);
        yt = (sin(alfa)*pX[n]) + (cos(alfa)*pY[n]);
        pX[n] = xt;
        pY[n] = yt;
    }
}

void rysujPunkty()  {
    double d = 400;
    double x0,y0,z0,x1,y1,z1;

    for (int n=0; n<ileKrawedzi; n++)   {
        x0 = pX[edges[n][0]];
        y0 = -pY[edges[n][0]];
        z0 = pZ[edges[n][0]];

        x1 = pX[edges[n][1]];
        y1 = -pY[edges[n][1]];
        z1 = pZ[edges[n][1]];

        x0 = (d*x0)/(z0+d);
        y0 = (d*y0)/(z0+d);
        x1 = (d*x1)/(z1+d);
        y1 = (d*y1)/(z1+d);

        al_draw_line(xC+x0,yC+y0,xC+x1,yC+y1,al_map_rgb(200,200,200),1);
    }
}

void ustawPunktyStozek()    {
    ileP = 5;
    ileKrawedzi = 8;
    pX[0] = -50;
    pY[0] = 50;
    pZ[0] = 50;
    pX[1] = 50;
    pY[1] = 50;
    pZ[1] = 50;
    pX[2] = 50;
    pY[2] = -50;
    pZ[2] = 50;
    pX[3] = -50;
    pY[3] = -50;
    pZ[3] = 50;

    pX[4] = 0;
    pY[4] = 0;
    pZ[4] = -100;

    edges[0][0] = 0;
    edges[0][1] = 1;
    edges[1][0] = 1;
    edges[1][1] = 2;
    edges[2][0] = 2;
    edges[2][1] = 3;
    edges[3][0] = 3;
    edges[3][1] = 0;

    edges[4][0] = 0;
    edges[4][1] = 4;
    edges[5][0] = 1;
    edges[5][1] = 4;
    edges[6][0] = 2;
    edges[6][1] = 4;
    edges[7][0] = 3;
    edges[7][1] = 4;
}

void ustawPunkty()  {
    ileP = 8;
    ileKrawedzi = 12;
    pX[0] = -50;
    pY[0] = 50;
    pZ[0] = 50;
    pX[1] = 50;
    pY[1] = 50;
    pZ[1] = 50;
    pX[2] = 50;
    pY[2] = -50;
    pZ[2] = 50;
    pX[3] = -50;
    pY[3] = -50;
    pZ[3] = 50;

    pX[4] = -50;
    pY[4] = 50;
    pZ[4] = -50;
    pX[5] = 50;
    pY[5] = 50;
    pZ[5] = -50;
    pX[6] = 50;
    pY[6] = -50;
    pZ[6] = -50;
    pX[7] = -50;
    pY[7] = -50;
    pZ[7] = -50;

    edges[0][0] = 0;
    edges[0][1] = 1;
    edges[1][0] = 1;
    edges[1][1] = 2;
    edges[2][0] = 2;
    edges[2][1] = 3;
    edges[3][0] = 3;
    edges[3][1] = 0;

    edges[4][0] = 4;
    edges[4][1] = 5;
    edges[5][0] = 5;
    edges[5][1] = 6;
    edges[6][0] = 6;
    edges[6][1] = 7;
    edges[7][0] = 7;
    edges[7][1] = 4;

    edges[8][0] = 0;
    edges[8][1] = 4;
    edges[9][0] = 1;
    edges[9][1] = 5;
    edges[10][0] = 2;
    edges[10][1] = 6;
    edges[11][0] = 3;
    edges[11][1] = 7;


}

void point(unsigned char *pt, int xx, int yy,unsigned char r, unsigned char g, unsigned char b) {
    // rysuje pixel w (xx,yy) o kolorze (r,g,b) i alfa=250;
    if (xx<mA.screenW && yy<mA.screenH && xx>0 && yy>0) {
        int pixel;
        pixel = xx+yy*mA.screenW;
        pt[pixel*4] = r;
        pt[pixel*4+1] = g;
        pt[pixel*4+2] = b;
        pt[pixel*4+3] = 250;
    }
}



