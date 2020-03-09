#ifndef TRAITIMAGE_H
#define TRAITIMAGE_H
QImage Ouvrir();
void Afficher(QImage image);
int alea(int min, int max);
QImage Random(QImage image, int NB);
QImage NoirBlanc(QImage image);
QImage Division(QImage image, int D);
QImage SeuilRVB(QImage image, int R, int V, int B);
QImage Uniforme(QImage image, int R, int V, int B);
QImage FourmiR(QImage image,int dx,int dy);
QImage FourmiV(QImage image,int dx,int dy);
QImage FourmiB(QImage image,int dx,int dy);
QImage ColorBoule(QImage image);
QImage Color(QImage image);
QImage Brown(QImage image, int dx, int dy);
QImage Histogramme(QImage image, int squelette);
QImage Squelette(QImage image);

#endif // TRAITIMAGE_H
