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
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
