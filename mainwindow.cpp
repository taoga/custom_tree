#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cstrres.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Initialize the tree
    m_pTreeWgt = 0;
    m_pTreeWgt = new QMyTreeWidget( this );

    if( m_pTreeWgt )
    {
        m_pTreeWgt->setToolTipDuration( 10000 );

        // Initialize display tree columns, if necessary, load from file
        vector<Column> *pvecColumns = m_pTreeWgt->GetColumns();

        pvecColumns->push_back( Column( ID_COL_MAC_SRC, GetColNameByID(ID_COL_MAC_SRC) ) );
        pvecColumns->push_back( Column( ID_COL_MAC_DST, GetColNameByID(ID_COL_MAC_DST) ) );
        pvecColumns->push_back( Column( ID_COL_TIME, GetColNameByID(ID_COL_TIME) ) );
        pvecColumns->push_back( Column( ID_COL_CHANNEL, GetColNameByID(ID_COL_CHANNEL) ) );
        pvecColumns->push_back( Column( ID_COL_SIGNAL, GetColNameByID(ID_COL_SIGNAL) ) );
        pvecColumns->push_back( Column( ID_COL_NOISE, GetColNameByID(ID_COL_NOISE) ) );
        pvecColumns->push_back( Column( ID_COL_TYPE, GetColNameByID(ID_COL_TYPE) ) );
        pvecColumns->push_back( Column( ID_COL_SCRYPT, GetColNameByID(ID_COL_SCRYPT) ) );
        pvecColumns->push_back( Column( ID_COL_PACKETS, GetColNameByID(ID_COL_PACKETS) ) );
        pvecColumns->push_back( Column( ID_COL_ESSID, GetColNameByID(ID_COL_ESSID) ) );

        m_pTreeWgt->Init( "TestTreeWgt", "TestCompany", false );

        setCentralWidget( m_pTreeWgt );

        QString qsStyle =  m_pTreeWgt->styleSheet();

        qDebug() << "Tree stylesheet: " << qsStyle;

        qsStyle = " QTreeView::branch:has-children:!has-siblings:closed,\
                QTreeView::branch:closed:has-children:has-siblings\
                {\
                        border-image: none;\
                        image: url(:/images/r_arrow_80.png);\
                }\
                QTreeView::branch:open:has-children:!has-siblings,\
                QTreeView::branch:open:has-children:has-siblings\
                {\
                        border-image: none;\
                        image: url(:/images/45_arrow_80.png);\
                }";
        m_pTreeWgt->setStyleSheet( qsStyle );

        QMyTreeWidgetItem *ptwgRootItem = new QMyTreeWidgetItem( m_pTreeWgt );

        ptwgRootItem->setText( 0, "Root" );

        QMyTreeWidgetItem *ptwgChildItem = new QMyTreeWidgetItem( ptwgRootItem );

        ptwgChildItem->setText( 0, "Child" );
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::GetColNameByID( int nID )
{
    QString qsName = "---";

    switch( nID )
    {
    case ID_COL_MAC_SRC:
        qsName = CStrRes::IDS_COL_TWSENSORS_MAC_SRC;
        break;
    case ID_COL_MAC_DST:
        qsName = CStrRes::IDS_COL_TWSENSORS_MAC_DST;
        break;
    case ID_COL_TIME:
        qsName = CStrRes::IDS_COL_TWSENSORS_TIME;
        break;
    case ID_COL_CHANNEL:
        qsName = CStrRes::IDS_COL_TWSENSORS_CHANNEL;
        break;
    case ID_COL_SIGNAL:
        qsName = CStrRes::IDS_COL_TWSENSORS_SIGNAL;
        break;
    case ID_COL_NOISE:
        qsName = CStrRes::IDS_COL_TWSENSORS_NOISE;
        break;
    case ID_COL_TYPE:
        qsName = CStrRes::IDS_COL_TWSENSORS_TYPE;
        break;
    case ID_COL_SCRYPT:
        qsName = CStrRes::IDS_COL_TWSENSORS_SCRYPT;
        break;
    case ID_COL_PACKETS:
        qsName = CStrRes::IDS_COL_TWSENSORS_PACKETS;
        break;
    case ID_COL_ESSID:
        qsName = CStrRes::IDS_COL_TWSENSORS_ESSID;
        break;
    case ID_COL_MAC_SRC_ZONE:
        qsName = CStrRes::IDS_COL_TWZONES_MAC_SRC;
        break;
    }

    return qsName;
}
