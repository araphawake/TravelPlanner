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

#include "addnewitem.h"
#include <QHBoxLayout>
#include <QLabel>

AddNewItem::AddNewItem(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout * container = new QHBoxLayout(this);

    QFont valueFont("Arial", 14, QFont::Bold);

    QPixmap newitem_pixmap (":/appIcons/sign.png");
    QIcon * newItemIcon = new QIcon();
    newItemIcon->addPixmap(newitem_pixmap);

    this->newItemButton = new QPushButton(*newItemIcon, "Write here your new activity...", this);
    this->newItemButton->setIconSize(QSize(25, 25));
    this->newItemButton->setMinimumWidth(20);
    this->newItemButton->setMinimumHeight(40);
    this->newItemButton->setStyleSheet("QPushButton { background-color : #87ff4b; border-radius : 6px;  }");
    container->addWidget(this->newItemButton);

    QObject::connect(this->newItemButton, SIGNAL(clicked()), this, SIGNAL(newItemClicked()));

    this->setLayout(container);

}

