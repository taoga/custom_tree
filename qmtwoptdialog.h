#ifndef QMTWOPTDIALOG_H
#define QMTWOPTDIALOG_H

#include <QDialog>
#include "cl_types.h"

namespace Ui {
class QMTWOptDialog;
}

class QMTWOptDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QMTWOptDialog(QWidget *parent = 0);
    ~QMTWOptDialog();

    void setUsrColumns( vector<Column>  *pvecColumns ) { m_pvecColumns = pvecColumns; }
    int Init();

private slots:
    void on_buttonBox_accepted();

private:

    Ui::QMTWOptDialog *ui;
    vector<Column>  *m_pvecColumns;
};

#endif // QMTWOPTDIALOG_H
