#include "FW/RC/record.h"
#include "FW/UI/ui_record_context_menu.h"

#include "FW/document.h"

#include "FW/UI/ui_record_table_model.h"
#include "FW/UI/ui_record_struct_view.h"
#include "ui_recordstructview.h"

#include <FW/RC/struct_record.h>

C_UiRecordStructView::C_UiRecordStructView( C_Document& document, QWidget* parent ) :
    QWidget( parent ),
    m_Document( &document ),
    ui( new Ui::C_UiRecordStructView )
{
    ui->setupUi( this );
    m_RecordTableModel = new C_UiRecordTableModel( Document(), this );
    ui->TableView->setModel( m_RecordTableModel );

    QObject::connect(
        ui->TableView,
        QTableView::doubleClicked,
        this,
        C_UiRecordStructView::OnDoubleClicked
    );

    QObject::connect(
        ui->TableView,
        QTableView::customContextMenuRequested,
        this,
        C_UiRecordStructView::OnCustomContextMenuRequested
    );
}

C_UiRecordStructView::~C_UiRecordStructView()
{
    delete ui;
}

void C_UiRecordStructView::Update()
{
    m_RecordTableModel->layoutChanged();
}

void C_UiRecordStructView::OnDoubleClicked( const QModelIndex& index )
{
    C_Record* record = Records().FromIndex( index.row() );

    if( record->Struct() != 0 )
    {
        Document().Context().SetRecords( *( record->Struct() ) );
        emit Document().Signals().RecordsChanged();
        return;
    }

    record->ShowEditor( Document() );
}


C_RecordStruct& C_UiRecordStructView::Records()
{
    return Document().Context().Records();
}


void C_UiRecordStructView::OnCustomContextMenuRequested( const QPoint& point )
{
    C_Record* record = 0;
    QPoint global_point = ui->TableView->viewport()->mapToGlobal( point );
    int index = ui->TableView->rowAt( point.y() );

    if( index >= 0 )
        record = Records().FromIndex( index );

    C_UiRecordContextMenu context_menu( Document(), global_point, index, record );
}

void C_UiRecordStructView::on_RootButton_clicked()
{
    Document().Context().SetRecords( Document().Records() );
    emit Document().Signals().RecordsChanged();
}

void C_UiRecordStructView::on_UpButton_clicked()
{
    if( ( & Records() ) != ( & Document().Records() ) )
    {
        auto record = static_cast<C_Record*>( Document().Context().Records().Parent() );
        auto parent = static_cast<C_RecordStruct*>( record->Parent() );
        Document().Context().SetRecords( *parent );
        emit Document().Signals().RecordsChanged();
    }
}
