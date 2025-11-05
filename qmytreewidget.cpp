#include "qmytreewidget.h"
#include <QHeaderView>
#include <QDebug>
#include <QSettings>
#include "cstrres.h"
#include "qmtwoptdialog.h"

QMyTreeWidget::QMyTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    m_pvecColumnsDef = new vector<Column>;
    m_pvecColumnsUsr = new vector<Column>;
    m_pmapColumns = new map<quint8, int>;
    m_pSubMenu = new QMenu( this );
    m_nCurColumn = -1;
    m_pqaOptions = 0;
}

QMyTreeWidget::~QMyTreeWidget()
{
    vector<Column> *pvecColumns = 0;

    if( m_pvecColumnsUsr->size() > 0 )
        pvecColumns  = m_pvecColumnsUsr;
    else
        pvecColumns  = m_pvecColumnsDef;

    // Keep column width
    if( m_qsID.length() > 0 && m_qsCompany.length() > 0 )
    {
        // Maintain column widths
        QSettings Settings(m_qsCompany, m_qsID);

        Settings.beginGroup("Settings");

        int nCol = 0, nCols = columnCount();
        for( nCol = 0; nCol < nCols; nCol++ )
        {
            QString qsWidth;
            int     nWidth = -1;
            qsWidth = QString::asprintf("%s_col#%d", m_qsID.toStdString().data(), nCol );

            nWidth = header()->sectionSize( nCol );
            Settings.setValue( qsWidth, nWidth );                       // Column width, if hidden, then 0

            qsWidth = QString::asprintf("%s_col#%d_id", m_qsID.toStdString().data(), nCol );

            Settings.setValue( qsWidth, (*pvecColumns)[nCol].m_nID );   //Column ID
        }

        Settings.endGroup();
    }

    if( m_pvecColumnsDef ) delete m_pvecColumnsDef;
    if( m_pvecColumnsUsr ) delete m_pvecColumnsUsr;
    if( m_pmapColumns ) delete m_pmapColumns;
    if( m_pSubMenu) delete m_pSubMenu;
    if( m_pqaOptions ) delete m_pqaOptions;
}

// Initializing columns
void QMyTreeWidget::InitColumns( bool bResize )
{
    vector<Column> *pvecColumns = 0;

    if( m_pvecColumnsUsr->size() > 0 )
        pvecColumns  = m_pvecColumnsUsr;
    else
        pvecColumns  = m_pvecColumnsDef;

    int nCols = (int)pvecColumns->size(), nCol = 0;
    // Create columns
    setColumnCount( nCols );

    QTreeWidgetItem *pHdrItem =  headerItem();
    if( !pHdrItem ) return;

    m_pmapColumns->clear();

    QHeaderView::ResizeMode oldResizeMode = header()->sectionResizeMode( 0 );

    if( bResize )
        header()->setSectionResizeMode( QHeaderView::ResizeToContents );

    for( nCol = 0; nCol < nCols; nCol++ )
    {
        pHdrItem->setText( nCol, (*pvecColumns)[nCol].m_qsName );
        m_pmapColumns->insert( map<quint8, int>::value_type( (*pvecColumns)[nCol].m_nID, nCol ) );
        if( !((*pvecColumns)[nCol].m_bVisible) )
            header()->hideSection( nCol );
        else
        {
            header()->showSection( nCol );
            if( header()->sectionSize( nCol ) == 0 )
            {
                // Set width to fit title text
                header()->setSectionResizeMode( QHeaderView::ResizeToContents );
                pHdrItem->setText( nCol, (*pvecColumns)[nCol].m_qsName );
                header()->setSectionResizeMode( oldResizeMode );
            }
        }
    }

    if( bResize )
    {
        header()->setSectionResizeMode( oldResizeMode );

        setAlternatingRowColors(1);
        QPalette p = palette();
        p.setColor( QPalette::AlternateBase, QColor(226, 237, 253) );
        setPalette(p);

        header()->setSectionsMovable( false );
    }
}

// Initializing a tree
void QMyTreeWidget::Init(QString qsID, QString qsCompany, bool bDisableOpt )
{
    // Identifier for saving/loading settings
    m_qsID = qsID;
    m_qsCompany = qsCompany;
    m_bDisableOpt = bDisableOpt;

    // Load a custom column set
    if( !m_bDisableOpt && m_qsID.length() > 0 && m_pvecColumnsDef && m_pvecColumnsDef->size() > 0 )
    {
        // Try to restore the column widths
        QSettings Settings(m_qsCompany, m_qsID);

        Settings.beginGroup("Settings");

        int nCol = 0, nCols = m_pvecColumnsDef->size();

        for( nCol = 0; nCol < nCols; nCol++ )
        {
            QString qsWidth;
            int     nId = -1, nWidth = 0;
            // Name of the parameter in the registry/settings file
            qsWidth = QString::asprintf("%s_col#%d", m_qsID.toStdString().data(), nCol );
            nWidth = Settings.value( qsWidth, -1 ).toInt();
            // Name of the parameter in the registry/settings file
            qsWidth = QString::asprintf("%s_col#%d_id", m_qsID.toStdString().data(), nCol );
            nId = Settings.value( qsWidth, -1 ).toInt();
            if( nWidth >= 0 )
            {
                for( int nColDef = 0; nColDef < nCols; nColDef++ )
                {
                    if( (*m_pvecColumnsDef)[nColDef].m_nID == nId )
                    {
                        if( nWidth > 0 )
                            (*m_pvecColumnsDef)[nColDef].m_bVisible = true;
                        else
                            (*m_pvecColumnsDef)[nColDef].m_bVisible = false;

                        m_pvecColumnsUsr->push_back( (*m_pvecColumnsDef)[nColDef] );

                        break;
                    }
                }
            }
        }

        Settings.endGroup();
    }

    InitColumns();

    // Restore column widths
    if( m_qsID.length() > 0 )
    {
        // Try to restore the column widths
        QSettings Settings(m_qsCompany, m_qsID);

        Settings.beginGroup("Settings");

        int nCol = 0, nCols = header()->count();

        for( nCol = 0; nCol < nCols; nCol++ )
        {
            QString qsWidth;
            int     nWidth = -1;
            // Name of the parameter in the registry/settings file
            qsWidth = QString::asprintf("%s_col#%d", m_qsID.toStdString().data(), nCol );
            nWidth = Settings.value( qsWidth, -1 ).toInt();
            if( nWidth > 0 )
                header()->resizeSection( nCol, nWidth );
        }

        Settings.endGroup();
    }
}
// Return column number by ID
int QMyTreeWidget::GetIdxByID( quint8 nID )
{
    map<quint8, int>::iterator itCol;

    itCol = m_pmapColumns->find( nID );

    if( itCol != m_pmapColumns->end() )
        return itCol->second;

    return -1;
}
//
void QMyTreeWidget::contextMenuEvent( QContextMenuEvent *pe )
{
    QPoint tmpPoint = pe->globalPos(), localPoint;

    localPoint = mapFromGlobal( tmpPoint );

    m_nCurColumn = -1;
    m_nCurColumn = columnAt( localPoint.x() );

    // Add a column settings command to the menu
    if( !m_bDisableOpt && m_pSubMenu && !m_pqaOptions )
    {
        // Program parameters
        m_pqaOptions = new QAction( CStrRes::IDS_MTWG_OPTIONS, 0 );
        if( m_pqaOptions )
        {
            m_pqaOptions->setText(CStrRes::IDS_MTWG_OPTIONS);
            m_pqaOptions->setToolTip(CStrRes::IDS_MTWG_OPTIONS);
            m_pqaOptions->setStatusTip(CStrRes::IDS_MTWG_OPTIONS_MSG);
            m_pqaOptions->setWhatsThis(CStrRes::IDS_MTWG_OPTIONS_MSG);
            m_pqaOptions->setIcon( QIcon(":/images/options.png") );
            m_pqaOptions->setEnabled( true );

            connect( m_pqaOptions, SIGNAL(triggered()), this, SLOT( onOptions() ) );
            // Add separators
            m_pSubMenu->addAction( m_pqaOptions );
        }
    }

    m_pSubMenu->exec( tmpPoint );
}
//////////////////////////////////////////////////////////////////////////////////////////
// Customizing tree/list columns
void QMyTreeWidget::onOptions()
{
    QMTWOptDialog tmpDlg;

    vector<Column>  *pvecColumns = 0, tmpColumns;
    int             nCols = 0, nCol = 0;

    if( m_pvecColumnsUsr->size() > 0 )
        pvecColumns  = m_pvecColumnsUsr;
    else
        pvecColumns  = m_pvecColumnsDef;

    nCols = (int)pvecColumns->size();
    // Prepare a temporary list of columns for user modification
    for( nCol = 0; nCol < nCols; nCol++ )
        tmpColumns.push_back( pvecColumns->at(nCol) );

    tmpDlg.setUsrColumns( &tmpColumns );

    if( tmpDlg.Init() >= 0 && tmpDlg.exec() == QDialog::Accepted )
    {
        m_pvecColumnsUsr->clear();
        nCols = tmpColumns.size();
        for( nCol = 0; nCol < nCols; nCol++ )
            m_pvecColumnsUsr->push_back( tmpColumns.at(nCol) );

        // Reinitialize
        InitColumns( false );
    }
}

