#ifndef QMYTREEWIDGET_H
#define QMYTREEWIDGET_H

#include <QTreeWidget>
#include <QContextMenuEvent>
#include <QMenu>
#include "cl_types.h"

using namespace std;

#define SORT_BY_NUMBER 7
#define SORT_BY_STRING 77

class QMyTreeWidgetItem : public QTreeWidgetItem {
  public:
  QMyTreeWidgetItem(QTreeWidget* parent):QTreeWidgetItem(parent){}
  QMyTreeWidgetItem(QTreeWidgetItem *parent, int type = Type):QTreeWidgetItem(parent,type){}
  private:
  bool operator<(const QTreeWidgetItem &other)const
  {
     if( isHidden() || other.isHidden() ) return false;

     int column = treeWidget()->sortColumn();

     QTreeWidgetItem *pHdrItem = treeWidget()->headerItem();
     int nSort = pHdrItem->data( column, Qt::UserRole ).toInt();

     if( nSort == SORT_BY_NUMBER )
     {
        int nSrc = atoi( text(column).toStdString().data() );
        int nOther = atoi( other.text(column).toStdString().data() );
        return nSrc < nOther;
     }
     else
        return text(column).toLower() < other.text(column).toLower();
  }
};

class QMyTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit QMyTreeWidget(QWidget *parent = 0);
    ~QMyTreeWidget();

    vector<Column>* GetColumns() { return m_pvecColumnsDef; };
    vector<Column>* GetUsrColumns() { return m_pvecColumnsUsr; };
    // Initialization of columns, internal indexes
    void Init(QString qsID, QString qsCompany = "TestCompany", bool bDisableOpt = true);
    // Return column number by ID
    int GetIdxByID( quint8 nID );
    QMenu* GetSubMenu() { return m_pSubMenu; };
    int GetCurColumn() { return m_nCurColumn; };
    void SetCurColumn( int nCurColumn ) { m_nCurColumn = nCurColumn; };

signals:

protected slots:
    void onOptions();

protected:
    vector<Column>      *m_pvecColumnsDef;
    vector<Column>      *m_pvecColumnsUsr;
    map<quint8, int>    *m_pmapColumns;
    QMenu               *m_pSubMenu;
    int                 m_nCurColumn;
    QString             m_qsID, m_qsCompany;
    QAction             *m_pqaOptions;                              // Column customization
    bool                m_bDisableOpt;

    virtual void contextMenuEvent( QContextMenuEvent *pe );
    void InitColumns( bool bResize = true );
};

#endif // QMYTREEWIDGET_H
