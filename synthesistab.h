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

#ifndef SYNTHESISTAB_H
#define SYNTHESISTAB_H

#include <QMap>
#include <QIcon>
#include <QTabBar>
#include <activityitem.h>

class SynthesisTab : public QHash<QString, float>
{
    public:
        SynthesisTab();
        SynthesisTab(QString title, QIcon * icon);
        void addItem(QString itemTitle, float value);
        void removeItem(QString itemTitle);
        void lock();
        QIcon getIcon();
        void unlock();
        float getItemValue(QString itemTitle);
        void setItemValue(QString activity_name, float value);
        int getItemNames(QList<QString> * listItemTitles);
        void setIcon(QIcon icon);

    private:
        QString title;
        QIcon * icon;
        int counter;
        bool isLocked;
};

#endif // VOYAGETAB_H
