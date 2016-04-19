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

#include "synthesiswindow.h"
#include "ui_synthesiswindow.h"
#include <QDir>
#include <QVBoxLayout>
#include "activityitem.h"
#include <QFormLayout>
#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QDesktopWidget>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

SynthesisWindow::SynthesisWindow(QString travelTitle, QMainWindow * parentWindow, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SynthesisWindow)
{
    QDesktopWidget screen;
    int screen_width = screen.screen()->width();
    int screen_height = screen.screen()->height();

    ui->setupUi(this);
    this->parentWindow = parentWindow;
    this->title = travelTitle;
    this->isArchived = false;
    this->setupTabs();
    this->currentTab = GENERAL;
    this->total = 0;
    this->setMinimumSize(QSize(540, 758));
    this->setMaximumSize(QSize(540, 758));
    this->move(screen_width/2 - this->width()/2, screen_height/2 - this->height()/2);

    QPixmap background(":/synthesisImages/travel.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);
    //this->ui->travelTitle->setStyleSheet("background-color: rgba(0,0,0,0%)");

    QFont totalFont ("Arial", 15, QFont::Bold);
    this->ui->totalLabel->setFont(totalFont);
    this->ui->totalLabel->setText(" Total = ");
    this->ui->totalLabel->setFixedWidth(125);
    this->ui->totalLabel->setFixedHeight(50);
    this->ui->totalLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    this->ui->totalLabel->setStyleSheet("QLabel { background-color : #3257a3; border-radius : 6px;  }");
    this->ui->totalValueLabel->setFont(totalFont);
    this->ui->totalValueLabel->setFixedHeight(50);
    this->ui->totalValueLabel->setStyleSheet("QLabel { background-color : #3257a3; border-radius : 6px;  }");//{ background-color : transparent; }");
    this->ui->totalValueLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    QObject::connect(this->ui->generalButton, SIGNAL(clicked()), this, SLOT(onGeneralButtonClick()));
    QObject::connect(this->ui->transportButton, SIGNAL(clicked()), this, SLOT(onTransportButtonClick()));
    QObject::connect(this->ui->housingButton, SIGNAL(clicked()), this, SLOT(onHousingButtonClick()));
    QObject::connect(this->ui->restaurantButton, SIGNAL(clicked()), this, SLOT(onRestaurantButtonClick()));
    QObject::connect(this->ui->othersButton, SIGNAL(clicked()), this, SLOT(onOthersButtonClick()));
    QObject::connect(this, SIGNAL(changeTab()), this, SLOT(updateSelectedTab()));

    QFont titleFont("Arial", 22, QFont::Black);
    this->ui->travelTitle->setFont(titleFont);
    this->ui->travelTitle->setText(this->title);
    this->setMinimumSize(parentWindow->minimumWidth(), parentWindow->minimumHeight());
    this->ui->activityList->show();

    //this->ui->generalButton->setIcon(*(this->generateIcon(GENERAL)));

    this->updateSelectedTab();
    this->updateActivityList();


}

void SynthesisWindow::open() {
    this->parentWindow->hide();
    this->show();
}

void SynthesisWindow::close() {
    this->hide();
    this->parentWindow->show();
}

void SynthesisWindow::readFromFile(const char * fileName) {

    string typeline, nameline, valueline;
    activity_type type;
    float value = 0;

    ifstream file(fileName);

    if(file.is_open()) {
        QString name;
        QString buffer;

        while(getline(file, typeline) && getline(file, nameline) && getline(file, valueline)) {

            std::istringstream typeinput(typeline);
            std::istringstream valueinput(valueline);

            int tab;
            typeinput >> tab;

            switch(tab) {
            case GENERAL:
                type = GENERAL;
                break;
            case TRANSPORT:
                type = TRANSPORT;
                break;
            case HOUSING:
                type = HOUSING;
                break;
            case RESTAURANT:
                type = RESTAURANT;
                break;
            case OTHERS:
                type = OTHERS;
                break;
            default:
                type = GENERAL;
                break;
            }

            name = QString::fromStdString(nameline);
            valueinput >> value;

            switch(type) {
            case GENERAL:
                this->others->addItem(name, value);
                break;
            case TRANSPORT:
                this->transport->addItem(name, value);
                break;
            case HOUSING:
                this->housing->addItem(name, value);
                break;
            case RESTAURANT:
                this->restaurant->addItem(name, value);
                break;
            case OTHERS:
                this->others->addItem(name, value);
                break;
            }

            this->general->addItem(name, value);

            buffer.clear();


        }

        this->updateActivityList();
        this->ui->activityList->setFocus();
    } else {
        qDebug("Error reading file.");
    }

}

void SynthesisWindow::setTitle(QString title) {
    this->title = title;
}

QString SynthesisWindow::getTitle() {
    return this->title;
}

void SynthesisWindow::setupTabs() {

    this->general = new SynthesisTab(QString ("General"), this->generateIcon(GENERAL, false));
    this->transport = new SynthesisTab(QString ("Transport"), this->generateIcon(TRANSPORT, false));
    this->housing = new SynthesisTab(QString ("Housing"), this->generateIcon(HOUSING, false));
    this->restaurant = new SynthesisTab(QString ("Restaurant"), this->generateIcon(RESTAURANT, false));
    this->others = new SynthesisTab(QString ("Others"), this->generateIcon(OTHERS, false));

    this->updateTabIcons();
}

QIcon * SynthesisWindow::generateIcon(activity_type type, bool isSelected) {

    QString resourcePath;

    switch(type) {
        case GENERAL:
            resourcePath = ":/appIcons/all" ;
            break;
        case TRANSPORT:
            resourcePath = ":/appIcons/transport";
            break;
        case HOUSING:
            resourcePath = ":/appIcons/sleeping";
            break;
        case RESTAURANT:
            resourcePath = ":/appIcons/restaurant";
            break;
        case OTHERS:
            resourcePath = ":/appIcons/others";
            break;
    }

    if(isSelected) {
        resourcePath += "_select.png";
    } else {
        resourcePath += ".png";
    }

    qDebug(resourcePath.toStdString().c_str());

    QPixmap tab_pixmap (resourcePath);
    QIcon * tabIcon = new QIcon();
    tabIcon->addPixmap(tab_pixmap);

    return tabIcon;
}

void SynthesisWindow::addActivity(activity_type type, QString name, float value) {

    if(!this->isArchived) {
        switch(type) {
            case GENERAL:
                this->general->addItem(name, value);
                break;
            case TRANSPORT:
                this->transport->addItem(name, value);
                break;
            case HOUSING:
                this->housing->addItem(name, value);
                break;
            case RESTAURANT:
                this->restaurant->addItem(name, value);
                break;
            case OTHERS:
                this->others->addItem(name, value);
                break;
        }
    }
}

void SynthesisWindow::removeActivity(activity_type type, QString name) {

    if(!this->isArchived) {
        switch(type) {
            case GENERAL:
                this->general->removeItem(name);
                break;
            case TRANSPORT:
                this->transport->removeItem(name);
                break;
            case HOUSING:
                this->housing->removeItem(name);
                break;
            case RESTAURANT:
                this->restaurant->removeItem(name);
                break;
            case OTHERS:
                this->others->removeItem(name);
                break;
        }
    }
}

void SynthesisWindow::onGeneralButtonClick() {
    this->currentTab = GENERAL;
    emit changeTab();
    this->updateActivityList();
}

void SynthesisWindow::onTransportButtonClick() {
    this->currentTab = TRANSPORT;
    emit changeTab();
    this->updateActivityList();
}

void SynthesisWindow::onHousingButtonClick() {
    this->currentTab = HOUSING;
    emit changeTab();
    this->updateActivityList();
}

void SynthesisWindow::onRestaurantButtonClick() {
    this->currentTab = RESTAURANT;
    emit changeTab();
    this->updateActivityList();
}

void SynthesisWindow::onOthersButtonClick() {
    this->currentTab = OTHERS;
    emit changeTab();
    this->updateActivityList();
}

void SynthesisWindow::updateTabIcons() {

    this->general->setIcon(*(this->generateIcon(GENERAL, false)));
    this->transport->setIcon(*(this->generateIcon(TRANSPORT, false)));
    this->restaurant->setIcon(*(this->generateIcon(RESTAURANT, false)));
    this->housing->setIcon(*(this->generateIcon(HOUSING, false)));
    this->others->setIcon(*(this->generateIcon(OTHERS, false)));

    switch(this->currentTab) {
        case GENERAL:
            this->ui->generalButton->setStyleSheet("QPush {background-color: #cecece; color: #ffffff}");
            this->general->setIcon(*(this->generateIcon(GENERAL, true)));
            this->transport->setIcon(*(this->generateIcon(TRANSPORT, false)));
            this->restaurant->setIcon(*(this->generateIcon(RESTAURANT, false)));
            this->housing->setIcon(*(this->generateIcon(HOUSING, false)));
            this->others->setIcon(*(this->generateIcon(OTHERS, false)));
            break;
        case TRANSPORT:
            this->ui->transportButton->setStyleSheet("QPush {background-color: #cecece; color: #ffffff}");
            this->general->setIcon(*(this->generateIcon(GENERAL, false)));
            this->transport->setIcon(*(this->generateIcon(TRANSPORT, true)));
            this->restaurant->setIcon(*(this->generateIcon(RESTAURANT, false)));
            this->housing->setIcon(*(this->generateIcon(HOUSING, false)));
            this->others->setIcon(*(this->generateIcon(OTHERS, false)));
            break;
        case HOUSING:
            this->ui->housingButton->setStyleSheet("QPush {background-color: #cecece; color: #ffffff}");
            this->general->setIcon(*(this->generateIcon(GENERAL, false)));
            this->transport->setIcon(*(this->generateIcon(TRANSPORT, false)));
            this->restaurant->setIcon(*(this->generateIcon(RESTAURANT, false)));
            this->housing->setIcon(*(this->generateIcon(HOUSING, true)));
            this->others->setIcon(*(this->generateIcon(OTHERS, false)));
            break;
        case RESTAURANT:
            this->ui->restaurantButton->setStyleSheet("QPush {background-color: #cecece; color: #ffffff}");
            this->general->setIcon(*(this->generateIcon(GENERAL, false)));
            this->transport->setIcon(*(this->generateIcon(TRANSPORT, false)));
            this->restaurant->setIcon(*(this->generateIcon(RESTAURANT, true)));
            this->housing->setIcon(*(this->generateIcon(HOUSING, false)));
            this->others->setIcon(*(this->generateIcon(OTHERS, false)));
            break;
        case OTHERS:
            this->ui->othersButton->setStyleSheet("QPush {background-color: #cecece; color: #ffffff}");
            this->general->setIcon(*(this->generateIcon(GENERAL, false)));
            this->transport->setIcon(*(this->generateIcon(TRANSPORT, false)));
            this->restaurant->setIcon(*(this->generateIcon(RESTAURANT, false)));
            this->housing->setIcon(*(this->generateIcon(HOUSING, false)));
            this->others->setIcon(*(this->generateIcon(OTHERS, true)));
            break;
    }

    this->ui->generalButton->setIcon(this->general->getIcon());
    this->ui->generalButton->setIconSize( QSize(55, 55));
    this->ui->transportButton->setIcon(this->transport->getIcon());
    this->ui->transportButton->setIconSize( QSize(55, 55));
    this->ui->housingButton->setIcon(this->housing->getIcon());
    this->ui->housingButton->setIconSize( QSize(55, 55));
    this->ui->restaurantButton->setIcon(this->restaurant->getIcon());
    this->ui->restaurantButton->setIconSize( QSize(55, 55));
    this->ui->othersButton->setIcon(this->others->getIcon());
    this->ui->othersButton->setIconSize( QSize(55, 55));

}

void SynthesisWindow::updateSelectedTab() {

    this->ui->generalButton->setStyleSheet("QPushButton {background-color: #ffffff; color: #000000}");
    this->ui->housingButton->setStyleSheet("QPushButton {background-color: #ffffff; color: #000000}");
    this->ui->transportButton->setStyleSheet("QPushButton {background-color: #ffffff; color: #000000}");
    this->ui->restaurantButton->setStyleSheet("QPushButton {background-color: #ffffff; color: #000000}");
    this->ui->othersButton->setStyleSheet("QPushButton {background-color: #ffffff; color: #000000}");

    this->ui->activityList->setFocus();

    switch(this->currentTab) {
        case GENERAL:
            this->ui->generalButton->setStyleSheet("QPushButton {background-color: #cecece; color: #ffffff}");
            break;
        case TRANSPORT:
            this->ui->transportButton->setStyleSheet("QPushButton {background-color: #cecece; color: #ffffff}");
            break;
        case HOUSING:
            this->ui->housingButton->setStyleSheet("QPushButton {background-color: #cecece; color: #ffffff}");
            break;
        case RESTAURANT:
            this->ui->restaurantButton->setStyleSheet("QPushButton {background-color: #cecece; color: #ffffff}");
            break;
        case OTHERS:
            this->ui->othersButton->setStyleSheet("QPushButton {background-color: #cecece; color: #ffffff}");
            break;
    }

    this->updateTabIcons();
}

void SynthesisWindow::onAddButtonClick() {

    QDialog dialog (this);

    QFormLayout demandForm (&dialog);

    QLineEdit * title = new QLineEdit(&dialog);
    title->setMaxLength((SYNTHESIS_WINDOW_WIDTH * 0.6)/11);
    demandForm.addRow(new QLabel("Activity Title: "), title);

    QDoubleSpinBox * cost = new QDoubleSpinBox(&dialog);
    cost->setMinimum(0);
    cost->setMaximum((double)100000);
    cost->setSingleStep(true);
    cost->setValue((double)0);
    demandForm.addRow(new QLabel("How much will it cost? "), cost);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    demandForm.addRow(&buttonBox);

    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted) {

            QString recoveredTitle;
            recoveredTitle = title->text();

            float value = (float)cost->value();

            switch(this->currentTab) {
                    case GENERAL:
                        this->others->addItem(recoveredTitle, value);
                        break;
                    case TRANSPORT:
                        this->transport->addItem(recoveredTitle, value);
                        break;
                    case HOUSING:
                        this->housing->addItem(recoveredTitle, value);
                        break;
                    case RESTAURANT:
                        this->restaurant->addItem(recoveredTitle, value);
                        break;
                    case OTHERS:
                        this->others->addItem(recoveredTitle, value);
                        break;
            }

            this->general->addItem(recoveredTitle, value);

            this->updateActivityList();
            this->ui->activityList->setFocus();
    }

}

void SynthesisWindow::loadList(SynthesisTab * tab) {
    QList<QString> titles;
    int titleCount = tab->getItemNames(&titles);

    AddNewItem * addNewItem = new AddNewItem();

    QObject::connect(addNewItem, SIGNAL(newItemClicked()), this, SLOT(onAddButtonClick()));

    QListWidgetItem * item = new QListWidgetItem();

    item->setSizeHint(addNewItem->sizeHint());

    this->ui->activityList->addItem(item);
    this->ui->activityList->setItemWidget(item, addNewItem);

    this->total = 0;

    for(int index = 0; index < titleCount; index++) {
        qDebug("In 1");
        QString * currentTitle = new QString();
        *currentTitle = titles.at(index);
        qDebug("In 2");
        this->total += tab->getItemValue(*currentTitle);
        ActivityItem * activity = new ActivityItem(currentTitle, (float)tab->getItemValue(*currentTitle));

        QObject::connect(activity, SIGNAL(deleteActivity(QString)), this, SLOT(onDeleteActivityClick(QString)));
        QObject::connect(activity, SIGNAL(modifyActivity(QString)), this, SLOT(onModifyActivityClick(QString)));

        QListWidgetItem * item = new QListWidgetItem();
        item->setSizeHint(activity->sizeHint());
        this->ui->activityList->addItem(item);
        this->ui->activityList->setItemWidget(item, activity);
    }

    qDebug("%s=%f", "string", this->total);
    this->ui->totalValueLabel->setText(QString::number((double)this->total) + QString(" €    "));
}

void SynthesisWindow::updateActivityList() {

    this->ui->activityList->clear();

    switch(this->currentTab) {
            case GENERAL:
                this->loadList(this->general);
                break;
            case TRANSPORT:
                this->loadList(this->transport);
                break;
            case HOUSING:
                this->loadList(this->housing);
                break;
            case RESTAURANT:
                this->loadList(this->restaurant);
                break;
            case OTHERS:
                this->loadList(this->others);
                break;
    }

    return;

}

void SynthesisWindow::archiveTravel() {
    this->isArchived = true;
}

void SynthesisWindow::startTravel() {
    this->isArchived = false;
}

void SynthesisWindow::onDeleteActivityClick(QString activity_name) {
    switch(this->currentTab) {
            case GENERAL:
                if(this->others->contains(activity_name)) {
                    this->others->removeItem(activity_name);
                } else if(this->transport->contains(activity_name)) {
                    this->transport->removeItem(activity_name);
                } else if(this->housing->contains(activity_name)) {
                    this->housing->removeItem(activity_name);
                } else if(this->restaurant->contains(activity_name)) {
                    this->restaurant->removeItem(activity_name);
                }
                break;
            case TRANSPORT:
                this->transport->removeItem(activity_name);
                break;
            case HOUSING:
                this->housing->removeItem(activity_name);
                break;
            case RESTAURANT:
                this->restaurant->removeItem(activity_name);
                break;
            case OTHERS:
                this->others->removeItem(activity_name);
                break;
    }

    this->general->removeItem(activity_name);

    this->updateActivityList();

}

void SynthesisWindow::onModifyActivityClick(QString activity_name) {


    QDialog dialog (this);
    dialog.setWindowTitle(activity_name);

    QFormLayout demandForm (&dialog);

    QDoubleSpinBox * cost = new QDoubleSpinBox(&dialog);
    cost->setMinimum(0);
    cost->setMaximum((double)100000);
    cost->setSingleStep(true);

    cost->setValue((double)this->general->getItemValue(activity_name));
    demandForm.addRow(new QLabel("How much will it cost? "), cost);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    demandForm.addRow(&buttonBox);

    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted) {

            float value = (float)cost->value();

            switch(this->currentTab) {
                    case GENERAL:
                        break;
                    case TRANSPORT:
                        this->transport->setItemValue(activity_name, value);
                        break;
                    case HOUSING:
                        this->housing->setItemValue(activity_name, value);
                        break;
                    case RESTAURANT:
                        this->restaurant->setItemValue(activity_name, value);
                        break;
                    case OTHERS:
                        this->others->setItemValue(activity_name, value);
                        break;
            }

            this->general->setItemValue(activity_name, value);

            this->updateActivityList();
    }

}

SynthesisWindow::~SynthesisWindow()
{
    delete ui;
}
