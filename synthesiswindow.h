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

#ifndef SYNTHESISWINDOW_H
#define SYNTHESISWINDOW_H

#include <QMainWindow>
#include <synthesistab.h>
#include <QTimer>
#include "activityitem.h"
#include <addnewitem.h>

typedef enum {
    GENERAL,
    HOUSING,
    TRANSPORT,
    RESTAURANT,
    OTHERS
} activity_type;

namespace Ui {
class SynthesisWindow;
}

class SynthesisWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SynthesisWindow(QString travelTitle, QMainWindow * parentWindow, QWidget *parent = 0);
    void open();
    void close();
    void setTitle(QString title);
    QString getTitle();
    void addActivity(activity_type type, QString name, float value);
    void removeActivity(activity_type type, QString name);
    void archiveTravel();
    void startTravel();
    void readFromFile(const char * fileName);
    ~SynthesisWindow();

signals:
    void changeTab();

public slots:
    void onGeneralButtonClick();
    void onTransportButtonClick();
    void onHousingButtonClick();
    void onRestaurantButtonClick();
    void onOthersButtonClick();
    void onAddButtonClick();
    void updateActivityList();
    void onDeleteActivityClick(QString activity_name);
    void onModifyActivityClick(QString activity_name);
    void updateSelectedTab();

private:
    Ui::SynthesisWindow *ui;
    QMainWindow * parentWindow;
    SynthesisTab * general, * housing, * transport, * restaurant, * others;
    QString title;
    QString targetActivity;
    double total;
    bool isArchived;
    activity_type currentTab;
    QIcon * generateIcon(activity_type type, bool isSelected);
    void setupTabs();
    void loadList(SynthesisTab * tab);
    void updateTabIcons();

};

#endif // SYNTHESISWINDOW_H
