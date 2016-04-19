/*
 * COPYRIGHT NOTICE. THIS NOTICE CANNOT BE REMOVED.
 *
 * Author: Azevedo Moscoso Silva Cruz, Rafael.
 * The author of this file studies at Pontificia Universidade Catolica do Rio de Janeiro; Télécom ParisTech.
 * 18/04/2015
 *
 * This code is protected.
 * The name of the author must be always mentioned on any project using this code.
 *
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    SynthesisWindow * synthesisWindow = new SynthesisWindow(QString("Rio de Janeiro GIGANTE"), (QMainWindow*)&w);
    synthesisWindow->readFromFile("/home/araphawake/CompagnonDeVoyage/data.txt");
    synthesisWindow->open();

    return a.exec();
}
