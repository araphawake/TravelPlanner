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

#ifndef ADDNEWITEM_H
#define ADDNEWITEM_H

#include <QWidget>
#include <QPushButton>

class AddNewItem : public QWidget
{
    Q_OBJECT
public:
    explicit AddNewItem(QWidget *parent = 0);

signals:
    void newItemClicked();

public slots:

private:
    QPushButton * newItemButton;
};

#endif // ADDNEWITEM_H
