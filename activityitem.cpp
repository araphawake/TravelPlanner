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

#include "activityitem.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

ActivityItem::ActivityItem(QString * name, float value, QWidget *parent) :
    QWidget(parent)
{

    QHBoxLayout * container = new QHBoxLayout(this);

    this->name = new QString();
    *this->name = *name;

    this->value = new QString();
    *this->value = QString::number(value);

    QLabel * euroSymbol = new QLabel(" € ");

    this->nameLabel = new QLabel(*this->name);
    this->nameLabel->setFixedWidth(SYNTHESIS_WINDOW_WIDTH * 0.45);
    QFont font("Arial", 10, QFont::Normal);
    this->nameLabel->setFont(font);

    this->valueLabel = new QLabel(*this->value);
    QFont valueFont("Arial", 10, QFont::Bold);
    this->valueLabel->setFont(valueFont);
    euroSymbol->setFont(valueFont);
    this->valueLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    this->valueLabel->setFixedWidth(70);

    QPixmap delete_pixmap (":/appIcons/delete.png");
    QIcon * deleteIcon = new QIcon();
    deleteIcon->addPixmap(delete_pixmap);

    QPixmap modify_pixmap (":/appIcons/editing.png");
    QIcon * modifyIcon = new QIcon();
    modifyIcon->addPixmap(modify_pixmap);

    this->deleteButton = new QPushButton(*deleteIcon, "", this);
    this->deleteButton->setIconSize(QSize(15, 15));
    this->modifyButton = new QPushButton(*modifyIcon, "", this);
    this->modifyButton->setIconSize(QSize(15, 15));

    container->addWidget(this->nameLabel);
    container->addSpacing(1);
    container->addWidget(this->valueLabel);
    container->addWidget(euroSymbol);
    container->addSpacing(1);
    container->addWidget(this->modifyButton);
    container->addSpacing(1);
    container->addWidget(this->deleteButton);
    container->addStretch();

    QObject::connect(this->deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    QObject::connect(this->modifyButton, SIGNAL(clicked()), this, SLOT(modifyClicked()));

    this->setLayout(container);

}

void ActivityItem::deleteClicked() {

    emit deleteActivity(*this->name);

}

void ActivityItem::modifyClicked() {

    emit modifyActivity(*this->name);

}
