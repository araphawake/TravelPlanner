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

#include "synthesistab.h"

SynthesisTab::SynthesisTab(QString title, QIcon * icon) : QHash<QString, float>()
{
    this->title = title;
    this->icon = icon;
    this->isLocked = false;
    this->counter = 0;
}

void SynthesisTab::addItem(QString itemTitle, float value) {
    if(!this->isLocked) {
        if(!this->contains(itemTitle)) {
            this->insert(itemTitle, value);
            this->counter++;
        } else {
            qDebug("This item already exists");
        }
    } else {
        qDebug("This tab is locked.");
    }
}

QIcon SynthesisTab::getIcon() {
    return *(this->icon);
}

void SynthesisTab::setIcon(QIcon icon) {
    *(this->icon) = icon;
}

void SynthesisTab::removeItem(QString itemTitle) {
    if(!this->isLocked) {
        this->remove(itemTitle);
        this->counter--;
    } else {
        qDebug("This tab is locked.");
    }
}

void SynthesisTab::setItemValue(QString itemTitle, float value) {
    (*this)[itemTitle] = value;
}

void SynthesisTab::lock() {
    this->isLocked = true;
}

void SynthesisTab::unlock() {
    this->isLocked = false;
}

float SynthesisTab::getItemValue(QString itemTitle) {
    if(this->contains(itemTitle)) {
        return this->value(itemTitle);
    } else {
        return -1;
    }
}

int SynthesisTab::getItemNames(QList<QString> * listItemTitles) {
    *listItemTitles = this->keys();;
    return this->counter;
}
