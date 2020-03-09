/*Patrick GUEBEY traitement d'images commencé en décembre 2016
Squelettisation février 2020*/

#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <iostream>
#include "traitimage.h"
#include <QString>
#include <QInputDialog>
#include <QFileDialog>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QImage image1;
    QImage image2;
    QImage image3;
    QLabel label1;
    QLabel label2;
    QLabel label3;
    cout << "Chargement image couleur \n" << flush;
    image1.load("C:/Users/patri/Documents/PATRICK/ETUDES/Squelettisation/TRISKEL.jpg");
    image1 = image1.scaled(1366, 768, Qt::KeepAspectRatio);
    label1.setPixmap(QPixmap::fromImage(image1));
    label1.show();
    cout << "Convertion en noir et blanc\n"  << flush;
    image2 = NoirBlanc(image1);
    image2 = image2.scaled(1366, 768, Qt::KeepAspectRatio);
    label2.setPixmap(QPixmap::fromImage(image2));
    label2.show();
    image2.save("C:/Users/patri/Documents/PATRICK/ETUDES/Squelettisation/I_nb.jpg");
    cout << "Binarisation\n" << flush;
    image2 = SeuilRVB(image2, 70, 70, 70);
    image2 = image2.scaled(1366, 768, Qt::KeepAspectRatio);
    label2.setPixmap(QPixmap::fromImage(image2));
    label2.show();
    image2.save("C:/Users/patri/Documents/PATRICK/ETUDES/Squelettisation/I_binaire.jpg");
    cout << "Squelettisation\n" << flush;
    image3 = Squelette(image2);
    image3 = image3.scaled(1366, 768, Qt::KeepAspectRatio);
    label3.setPixmap(QPixmap::fromImage(image3));
    label3.show();
    image3.save("C:/Users/patri/Documents/PATRICK/ETUDES/Squelettisation/TRISQUEL_squelette.jpg");
//    image1.save("C:/Users/patri/Documents/PATRICK/ETUDES/Squelettisation/origine_et_squelette.jpg");
//    image1 = FourmiR(image1, -1000, 0);
//    image1 = FourmiV(image1, 0, 0);
//    image1 = FourmiB(image1, 1000, 0);*/

//    image1.save("C:/Users/patri/Pictures/Paimboeuf 2016-2017/Derniere.jpg");
    return app.exec();
}
