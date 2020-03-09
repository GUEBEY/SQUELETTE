/*Patrick GUEBEY traitement d'images december 2016*/
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <iostream>
#include <fstream>
#include <ctime>
#include "traitimage.h"
#include <QFileDialog>
#include <QColorDialog>
#include <QtCore/QCoreApplication>
using namespace std;

QImage Squelette(QImage image)
{
    bool fin = false;
    int r,g,b,v,vb;         //v contiendra l'indexe dans la table des configuration de voisins

    char v0,v1,v2,v3,v4,v5,v6,v7;
    char vb0,vb1,vb2,vb3,vb4,vb5,vb6,vb7;
    int nb = 0;

    int table[256] = {
   0,0,0,1,0,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
   0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,1,1,0,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,0,1,
   0,1,0,1,0,0,0,0,0,1,0,1,1,1,0,1,1,0,1,0,1,1,0,1,1,0,1,0,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,
   0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,1,1,0,1,0,1,0,1,
   0,0,0,0,0,1,0,1,1,1,0,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,1,1,0,1,1,0,1,0,1,1,
   0,1,1,0,1,0};

    cout << "H = " << image.height() << "     L =  " << image.width() << endl;
    while (fin == false){

        fin = true;
        nb++;

        for (int y = 1; y < image.height()-1; ++y){ //On décalle de 1 pour permettre l'analyse des 8 voisins
            for (int x = 1; x < image.width()-1; ++x) {
//                cout << "x =  " << x << "   y =  " << y;
                v = 0;                       //Mise à 0 de l'indexe dans la table des configuration de voisins
                vb = 0;
                QColor pxl(image.pixel(x,y));
                r = pxl.red();
                g = pxl.green();
                b = pxl.blue();

                if (r == 0){                            //Si le point est noir
//                    cout << "x = " << x << "   y =  " << y << endl;

                    image.setPixel(x, y,qRgb(0,0,0));   //alors r=v=b=noir
                    QColor pxl1(image.pixel(x,y-1));
                    if (pxl1.red() == 0 ) {v=1; v0 ='X';} else v0 ='-';             //if V0 black
                    if (pxl1.blue() == 0) {vb=1; vb0 = 'X';} else vb0 = '-';
                    QColor pxl2(image.pixel(x+1,y-1));
                    if (pxl2.red() == 0) {v=v+2; v1 ='X';} else v1 ='-';            //if V1 black
                    if (pxl2.blue() == 0) {vb=vb+2; vb1 = 'X';} else vb1 = '-';
                    QColor pxl3(image.pixel(x+1,y));
                    if (pxl3.red() == 0) {v=v+4; v2 ='X';} else v2 ='-';            //if V2 black
                    if (pxl3.blue() == 0) {vb=vb+4; vb2 = 'X';} else vb2 = '-';
                    QColor pxl4(image.pixel(x+1,y+1));
                    if (pxl4.red() == 0) {v=v+8; v3 ='X';} else v3 ='-';            //if V3 black
                    if (pxl4.blue() == 0) {vb=vb+8; vb3 = 'X';} else vb3 = '-';
                    QColor pxl5(image.pixel(x,y+1));
                    if (pxl5.red() == 0) {v=v+16; v4 ='X';} else v4 ='-';           //if V4 black
                    if (pxl5.blue() == 0) {vb=vb+16; vb4 = 'X';} else vb4 = '-';
                    QColor pxl6(image.pixel(x-1,y+1));
                    if (pxl6.red() == 0) {v=v+32; v5 ='X';} else v5 ='-';           //if V5 black
                    if (pxl6.blue() == 0) {vb=vb+32; vb5 = 'X';} else vb5 = '-';
                    QColor pxl7(image.pixel(x-1,y));
                    if (pxl7.red() == 0) {v=v+64; v6 ='X';} else v6 ='-';            //if V6 black
                    if (pxl7.blue() == 0) {vb=vb+64; vb6 = 'X';} else vb6 = '-';
                    QColor pxl8(image.pixel(x-1,y-1));
                    if (pxl8.red() == 0) {v=v+128; v7 ='X';} else v7 ='-';           //if V7 black
                    if (pxl8.blue() == 0) {vb=vb+128; vb7 = 'X';} else vb7 = '-';

                    if (table[v] > 0 and //Detecton des bouts
                      (vb==2 or vb==8 or vb==32 or vb==128 or vb==1 or vb==4 or vb==16 or vb==64))
                    {image.setPixel(x, y,qRgb(r,255,50)); fin = false;}

                    if (table[v] > 0 and table[vb] > 0) {        //Le point est inessentiel
                        image.setPixel(x, y,qRgb(r,255,50));
                        fin = false;

//                        cout << v7 << v0 << v1 << "        " << vb7 << vb0 << vb1 << endl;
//                        cout << v6 << 'X' << v2 << "        " << vb6 << 'X' << vb2 << endl;
//                        cout << v5 << v4 << v3 << "        " << vb5 << vb4 << vb3 << endl << endl;
                    }
                 }
            }           //Fin de ligne
        }   //Fin de la passe
        //Copie du resultat de la passe dans l'image originale
        cout << "Fin de la passe:   " << nb << "\n" << flush;
        if (nb == 500) fin = true;
        for (int y = 1; y < image.height()-1; ++y){ //On décalle de 1 pour permettre l'analyse des 8 voisins
            for (int x = 1; x < image.width()-1; ++x){
                QColor pxl(image.pixel(x,y));
                r = pxl.red();
                g = pxl.green();
                b = pxl.blue();
                if (g == 255) image.setPixel(x, y,qRgb(255,255,b));
             }
        }

      QString fichier = "C:/Users/patri/Documents/PATRICK/ETUDES/Squelettisation/TRISKEL_SQUELETTE"+QString::number(nb)+".jpg";
     image.save(fichier);
//      cout << "Enregistrement Nr " << nb << endl;

    }
//Balayage du squelette pour repérer les bouts et le noeuds et les enregistrer
    ofstream points_remarquables ("C:/Users/patri/Documents/PATRICK/ETUDES/Squelettisation/points_remarquables.txt");

    for (int y = 1; y < image.height()-1; ++y){ //On décalle de 1 poureviter les bords
        for (int x = 1; x < image.width()-1; ++x){
            v = 0;
            vb = 0;
            QColor pxl(image.pixel(x,y));
            r = pxl.red();
            g = pxl.green();
            b = pxl.blue();
            if (r == 0){
                image.setPixel(x, y,qRgb(0,0,0));   //alors r=v=b=noir
                QColor pxl1(image.pixel(x,y-1));
                if (pxl1.red() == 0 ) {v=1; v0 ='X';} else v0 ='-';             //if V0 black
                if (pxl1.blue() == 0) {vb=1; vb0 = 'X';} else vb0 = '-';
                QColor pxl2(image.pixel(x+1,y-1));
                if (pxl2.red() == 0) {v=v+2; v1 ='X';} else v1 ='-';            //if V1 black
                if (pxl2.blue() == 0) {vb=vb+2; vb1 = 'X';} else vb1 = '-';
                QColor pxl3(image.pixel(x+1,y));
                if (pxl3.red() == 0) {v=v+4; v2 ='X';} else v2 ='-';            //if V2 black
                if (pxl3.blue() == 0) {vb=vb+4; vb2 = 'X';} else vb2 = '-';
                QColor pxl4(image.pixel(x+1,y+1));
                if (pxl4.red() == 0) {v=v+8; v3 ='X';} else v3 ='-';            //if V3 black
                if (pxl4.blue() == 0) {vb=vb+8; vb3 = 'X';} else vb3 = '-';
                QColor pxl5(image.pixel(x,y+1));
                if (pxl5.red() == 0) {v=v+16; v4 ='X';} else v4 ='-';           //if V4 black
                if (pxl5.blue() == 0) {vb=vb+16; vb4 = 'X';} else vb4 = '-';
                QColor pxl6(image.pixel(x-1,y+1));
                if (pxl6.red() == 0) {v=v+32; v5 ='X';} else v5 ='-';           //if V5 black
                if (pxl6.blue() == 0) {vb=vb+32; vb5 = 'X';} else vb5 = '-';
                QColor pxl7(image.pixel(x-1,y));
                if (pxl7.red() == 0) {v=v+64; v6 ='X';} else v6 ='-';            //if V6 black
                if (pxl7.blue() == 0) {vb=vb+64; vb6 = 'X';} else vb6 = '-';
                QColor pxl8(image.pixel(x-1,y-1));
                if (pxl8.red() == 0) {v=v+128; v7 ='X';} else v7 ='-';           //if V7 black
                if (pxl8.blue() == 0) {vb=vb+128; vb7 = 'X';} else vb7 = '-';

                if (v==2 or v==8 or v==32 or v==128 or v==1 or v==4 or v==16 or v==64){
                    cout << "Point v = " << v << "   x = " << x << "   y = " << y << endl;
                    points_remarquables << "v = " << v << "   x = " << x << "   y = " << y << endl;
                }
            }
        }   //Fin de ligne
    }       //Fin d'image
    points_remarquables.close();
    return image;
}



QImage Ouvrir()
{
    QImage image;
    QString fichier = QFileDialog::getOpenFileName(NULL,"Ouvrir le fichier image",QString(),"(*.jpg *.jpeg)");
    image.load(fichier);
    cout << image.width() << "   " << image.height() << "\n";
    return image;
}


int alea(int min, int max)
{
/*    srand(time(NULL));   */

    return rand()%(max-min)+min;
}

QImage Random(QImage image, int NB)
{
    int xR, xV, xB;
    int yR, yV, yB;
    int n=0;

    while (n<NB)
    {
        xR = alea(0,image.width());
        yR = alea(0,image.height());
        image.setPixel(xR, yR,qRgb(255,255,255));
        xV = alea(0,image.width());
        yV = alea(0,image.height());
        image.setPixel(xV, yV,qRgb(255,255,255));
        xB = alea(0,image.width());
        yB = alea(0,image.height());
        image.setPixel(xB, yB,qRgb(255,255,255));
        ++n;
    }
    return image;
}


QImage NoirBlanc(QImage image)
{

    for (int x = 0; x < image.width(); ++x)
        {
          for (int y = 0; y < image.height(); ++y)
            {
                int r,g,b;
                QColor pxl(image.pixel(x,y));
                r = pxl.red();
                g = pxl.green();
                b = pxl.blue();
                int gris = (r+g+b)/3;
                image.setPixel(x, y,qRgb(gris,gris,gris));
            }
        }
    return image;
}

QImage Division(QImage image, int D)
{

    for (int x = 0; x < image.width(); ++x)
        {
          for (int y = 0; y < image.height(); ++y)
            {
                QColor c;
                int r,g,b;
                QColor pxl(image.pixel(x,y));
                r = pxl.red();
                g = pxl.green();
                b = pxl.blue();
                image.setPixel(x, y,qRgb(r/D,g/D,b/D));
            }
        }
    return image;
}

QImage SeuilRVB(QImage image, int R, int V, int B)
{
//    QColor CN, CB;
//    CB = QColorDialog::getColor();
//    CN = QColorDialog::getColor();

    for (int x = 0; x < image.width(); ++x)
        {
          for (int y = 0; y < image.height(); ++y)
            {
                QColor c;
                int r,g,b;
                QColor pxl(image.pixel(x,y));
                r = pxl.red();
                g = pxl.green();
                b = pxl.blue();

                if (r>R) r = 255; else r = 0;
                if (g>V) g = 255; else g = 0;
                if (b>B) b = 255; else b = 0;

                if (r+g+b > 0) image.setPixel(x, y,qRgb(255,255,255));
                else image.setPixel(x, y,qRgb(0,0,0));
            }
        }
    return image;
}

QImage Uniforme(QImage image, int R, int V, int B)
{

    for (int x = 0; x < image.width(); ++x)
        for (int y = 0; y < image.height(); ++y) image.setPixel(x, y,qRgb(R,V,B));
    return image;
}

QImage FourmiR(QImage image, int dx, int dy)
{
    int x = image.width()/2 + dx;
    int y = image.height()/2 + dy;
    int dir = 0;
    int D;

    while (x>0 and x<image.width() and y>0 and y<image.height())
    {
        QColor c;
        int r;
        QColor pxl(image.pixel(x,y));
        r = pxl.red();
        if (r==0) image.setPixel(x, y,qRgb(255,0,0)); else image.setPixel(x, y,qRgb(0,0,0));
        if (r==0 and dir==0) {--x; D=3;}
        if (r==0 and dir==1) {y++; D=0;}
        if (r==0 and dir==2) {x++; D=1;}
        if (r==0 and dir==3) {y--; D=2;}

        if (r==255 and dir==0) {x++; D=1;}
        if (r==255 and dir==1) {y--; D=2;}
        if (r==255 and dir==2) {x--; D=3;}
        if (r==255 and dir==3) {y++; D=0;}
        dir = D;
    }
    return image;
}

QImage FourmiV(QImage image, int dx, int dy)
{
    int x = image.width()/2 + dx;
    int y = image.height()/2 + dy;
    int dir = 0;
    int D;

    while (x>0 and x<image.width() and y>0 and y<image.height())
    {
        QColor c;
        int g;
        QColor pxl(image.pixel(x,y));
        g = pxl.green();
        if (g==0) image.setPixel(x, y,qRgb(0,255,0)); else image.setPixel(x, y,qRgb(0,0,0));
        if (g==0 and dir==0) {--x; D=3;}
        if (g==0 and dir==1) {y++; D=0;}
        if (g==0 and dir==2) {x++; D=1;}
        if (g==0 and dir==3) {y--; D=2;}

        if (g==255 and dir==0) {x++; D=1;}
        if (g==255 and dir==1) {y--; D=2;}
        if (g==255 and dir==2) {x--; D=3;}
        if (g==255 and dir==3) {y++; D=0;}
        dir = D;
    }
    return image;
}

QImage FourmiB(QImage image, int dx, int dy)
{
    int x = image.width()/2 + dx;
    int y = image.height()/2 + dy;
    int dir = 0;
    int D;

    while (x>0 and x<image.width() and y>0 and y<image.height())
    {
        QColor c;
        int b;
        QColor pxl(image.pixel(x,y));
        b = pxl.blue();
        if (b==0) image.setPixel(x, y,qRgb(0,0,255)); else image.setPixel(x, y,qRgb(0,0,0));
        if (b==0 and dir==0) {--x; D=3;}
        if (b==0 and dir==1) {y++; D=0;}
        if (b==0 and dir==2) {x++; D=1;}
        if (b==0 and dir==3) {y--; D=2;}

        if (b==255 and dir==0) {x++; D=1;}
        if (b==255 and dir==1) {y--; D=2;}
        if (b==255 and dir==2) {x--; D=3;}
        if (b==255 and dir==3) {y++; D=0;}
        dir = D;
    }
    return image;
}


QImage ColorBoule(QImage image)
{
    int xR = image.width()/2;
    int yR = image.height()/2;
    int xV = image.width()/2;
    int yV = image.height()/2;
    int xB = image.width()/2;
    int yB = image.height()/2;
    int R, V, B, DR, DV, DB;

    for (int x = 0; x < image.width(); ++x)
        for (int y = 0; y < image.height(); ++y)
        {
            DR = sqrt((xR - x)*(xR - x) + (yR - y)*(yR - y))/4;
            DV = sqrt((xV - x)*(xV - x) + (yV - y)*(yV - y))/4;
            DB = sqrt((xB - x)*(xB - x) + (yB - y)*(yB - y))/4;
            R = DR; if (R<0) R=0;
            V = sin(DV/1024)*255; if (V<0) V=0;
            B = 1024-DB; if (B<0) B=0;
            image.setPixel(x, y,qRgb(R,V,B));
        }
    return image;
}


QImage Color(QImage image)
{
    int R = 0, V = 0, B = 0;

    for (int x = 0; x < image.width(); ++x)
        for (int y = 0; y < image.height(); ++y)
        {
            //++R;
            //if (R == 256) { R = 0; ++V;}
            //if (V == 256) { V = 0; ++B;}
            //if (B == 256) { B = 0;}
            R=x/5;
            V=y/5;
            B=(x+y)/5;
            image.setPixel(x, y,qRgb(R,V,B));

        }
    return image;
}


QImage Brown(QImage image, int dx, int dy)
{
    int x = image.width()/2 + dx;
    int y = image.height()/2 + dy;
    int R = 255;
    int V = 255;
    int B = 255;

    while (x>0 and x<image.width() and y>0 and y<image.height())
    {
        QColor c;
        int r = alea(0,9);
        image.setPixel(x, y,qRgb(R,V,B));
        if (r==1) {--x; R = 0; V = 0; B = 0;}
        if (r==2) {--x; ++y; R = 0; V = 0; B = 255;}
        if (r==3) {++y; R = 0; V = 255; B = 0;}
        if (r==4) {++x; ++y; R = 0; V = 255; B = 255;}
        if (r==5) {++x; R = 255; V = 0; B = 0;}
        if (r==6) {++x; --y; R = 255; V = 0; B = 255;}
        if (r==7) {--y; R = 255; V = 255; B = 0;}
        if (r==8) {--x; --y; R = 255; V = 255; B = 255;}

    }
    return image;
}

QImage Histogramme(QImage image, int Egalisation)
{
    double HistoR[256];
    double HistoV[256];
    double HistoB[256];
    double CumulR[256];
    double CumulV[256];
    double CumulB[256];

    QColor c;
    int r,v,b;
    double maxR = 0;
    double maxV = 0;
    double maxB = 0;
    double minR = 24000000;
    double minV = 24000000;
    double minB = 24000000;
    double max = 0;

    int X0 = 200;
    int Y0R = 200;
    int Y0V = 350;
    int Y0B = 500;
    int H = 100;


    for (int i = 0; i <256; ++i)
    {
        HistoR[i] = 0;
        HistoV[i] = 0;
        HistoB[i] = 0;
    }

    for (int x = 0; x < image.width(); ++x)
        for (int y = 0; y < image.height(); ++y)
        {
            QColor pxl(image.pixel(x,y));
            r = pxl.red();
            v = pxl.green();
            b = pxl.blue();
            ++HistoR[pxl.red()];
            if (HistoR[pxl.red()] > max) max = HistoR[pxl.red()];
            ++HistoV[pxl.green()];
            if (HistoV[pxl.green()] > max) max = HistoV[pxl.green()];
            ++HistoB[pxl.blue()];
            if (HistoB[pxl.blue()] > max) max = HistoB[pxl.blue()];
        }
    float a = H/max;
    cout << "Histogramme de l'image" "\n" << flush;
    cout << "Max = " << max << "   a = " << a <<"\n";

    for ( int i = 0; i < 256; ++i)
    {
        if (i == 0)
        {
            CumulR[0] = HistoR[0];
            if (HistoR[i] > max) max = HistoR[i];
            CumulV[0] = HistoV[0];
            if (HistoV[i] > max) max = HistoV[i];
            CumulB[0] = HistoB[0];
            if (HistoB[i] > max) max = HistoB[i];
        }
        else
        {
            CumulR[i] = CumulR[i-1] + HistoR[i];
            if (HistoR[i] > maxR) maxR = HistoR[i];
            if (HistoR[i] < minR) minR = HistoR[i];
            CumulV[i] = CumulV[i-1] + HistoV[i];
            if (HistoV[i] > maxV) maxV = HistoV[i];
            if (HistoV[i] < minV) minV = HistoR[i];
            CumulB[i] = CumulB[i-1] + HistoB[i];
            if (HistoB[i] > maxB) maxB = HistoB[i];
            if (HistoB[i] < minB) minB = HistoR[i];
        }
        for ( int j = Y0R; j > Y0R-HistoR[i]*a; --j) image.setPixel(i+X0, j,qRgb(255,0,0));
        for ( int j = Y0V; j > Y0V-HistoV[i]*a; --j) image.setPixel(i+X0, j,qRgb(0,255,0));
        for ( int j = Y0B; j > Y0B-HistoB[i]*a; --j) image.setPixel(i+X0, j,qRgb(0,0,255));

/*        cout << i << "  " << flush;
        cout << HistoR[i] << ";" << HistoV[i] << ";" << HistoB[i] << flush;
        cout << ";" << CumulR[i] << ";" << CumulV[i] << ";" << CumulB[i] << "\n" << flush;
*/
    }

    double MX = 24000000;

    if (Egalisation)

    for (int x = 0; x < image.width(); ++x)
        for (int y = 0; y < image.height(); ++y)
        {
            QColor pxl(image.pixel(x,y));
            r = pxl.red();
            v = pxl.green();
            b = pxl.blue();
            image.setPixel(x, y,qRgb(CumulR[r]*255.0/MX,CumulV[v]*255.0/MX,CumulB[b]*255.0/MX));
        }
    return image;
}

