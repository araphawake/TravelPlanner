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

#ifndef ACTIVITYITEM_H
#define ACTIVITYITEM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

const unsigned int SYNTHESIS_WINDOW_WIDTH     = 475;

class ActivityItem : public QWidget
{
    Q_OBJECT
public:
    explicit ActivityItem(QString * name, float value, QWidget *parent = 0);

signals:
    void deleteActivity(QString string);
    void modifyActivity(QString string);

public slots:
    void deleteClicked();
    void modifyClicked();

private:
    QPushButton * deleteButton;
    QPushButton * modifyButton;
    QLabel * nameLabel;
    QLabel * valueLabel;
    QString *name, *value;
};

#endif // ACTIVITYITEM_H
