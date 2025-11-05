#include "qmtwoptdialog.h"
#include "ui_qmtwoptdialog.h"

QMTWOptDialog::QMTWOptDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QMTWOptDialog)
{
    m_pvecColumns = 0;
    ui->setupUi(this);
}

QMTWOptDialog::~QMTWOptDialog()
{
    delete ui;
}

int QMTWOptDialog::Init()
{
    if( !m_pvecColumns ) return -1;

    ui->listWidget->setAcceptDrops( true );
    ui->listWidget->setDragEnabled( true );

    ui->listWidget->setSelectionMode( QAbstractItemView::SingleSelection );
    ui->listWidget->setDropIndicatorShown( true );
    ui->listWidget->setDragDropMode( QAbstractItemView::InternalMove );

    // Initialize the column list
    int nCol = 0, nCols = 0;

    nCols = m_pvecColumns->size();
    for( nCol = 0; nCol < nCols; nCol++ )
    {
        QListWidgetItem *plwgItem = new QListWidgetItem( ui->listWidget );

        plwgItem->setText( (*m_pvecColumns)[nCol].m_qsName );
        plwgItem->setData( Qt::UserRole, (*m_pvecColumns)[nCol].m_nID );
        plwgItem->setFlags( plwgItem->flags() | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | /*Qt::ItemIsDropEnabled | */Qt::ItemIsDragEnabled );
        plwgItem->setCheckState( (*m_pvecColumns)[nCol].m_bVisible ? Qt::Checked : Qt::Unchecked );
    }

    return 0;
}

void QMTWOptDialog::on_buttonBox_accepted()
{
    // New column order
    m_pvecColumns->clear();

    int nRow = 0, nRows = ui->listWidget->count();
    for( nRow = 0; nRow < nRows; nRow++ )
    {
        QListWidgetItem *pItem = 0;

        pItem = ui->listWidget->item( nRow );
        if( pItem )
        {
            Column tmpColumn( (pItem->data( Qt::UserRole )).toInt(), pItem->text(), (pItem->checkState() == Qt::Checked) ? true : false );
            m_pvecColumns->push_back( tmpColumn );
        }
    }
}
