#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qmytreewidget.h"

namespace Ui {
class MainWindow;
}

// Tree column identifiers for displaying device information
#define ID_COL_MAC_SRC      1
#define ID_COL_MAC_DST      2
#define ID_COL_TIME         3
#define ID_COL_CHANNEL      4
#define ID_COL_SIGNAL       5
#define ID_COL_NOISE        6
#define ID_COL_TYPE         7
#define ID_COL_SCRYPT       8
#define ID_COL_PACKETS      9
#define ID_COL_ESSID        10
#define ID_COL_MAC_SRC_ZONE 11

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    QString GetColNameByID(int nID);

private:
    Ui::MainWindow *ui;
    QMyTreeWidget   *m_pTreeWgt;
};

#endif // MAINWINDOW_H
