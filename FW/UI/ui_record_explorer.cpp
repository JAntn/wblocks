#include "FW/RC/record.h"
#include "FW/UI/ui_record_context_menu.h"
#include "FW/document.h"
#include "FW/UI/ui_record_table_model.h"
#include "FW/UI/ui_record_explorer.h"
#include "FW/RC/struct_record.h"
#include "FW/clipboard.h"
#include "FW/UI/ui_main_window.h"
#include "ui_mainwindow.h"
#include "ui_recordexplorer.h"

C_UiRecordExplorer::C_UiRecordExplorer( C_Document& document, QWidget* parent ) :
    QWidget( parent ),
    m_Document( &document ),
    ui( new Ui::C_UiRecordExplorer )
{
    ui->setupUi( this );
    m_RecordTableModel = new C_UiRecordTableModel( Document(), this );
    ui->TableView->setModel( m_RecordTableModel );

    connect(
        ui->TableView,
        QTableView::doubleClicked,
        this,
        C_UiRecordExplorer::OnDoubleClicked
    );

    connect(
        ui->RootButton,
        QPushButton::clicked,
        this,
        C_UiRecordExplorer::OnRootButtonClicked
    );

    connect(
        ui->UpButton,
        QPushButton::clicked,
        this,
        C_UiRecordExplorer::OnUpButtonClicked
    );

    connect(
        ui->TableView,
        QTableView::customContextMenuRequested,
        this,
        C_UiRecordExplorer::OnCustomContextMenuRequested
    );

    connect(
        ui->TableView->selectionModel(),
        QItemSelectionModel::selectionChanged,
        this,
        C_UiRecordExplorer::OnSelectionChanged
    );

    connect(
        ui->LineEdit,
        QLineEdit::returnPressed,
        this,
        C_UiRecordExplorer::OnLineEditReturnPressed
    );
}

C_UiRecordExplorer::~C_UiRecordExplorer()
{
    delete ui;
}

void C_UiRecordExplorer::Update()
{
    ui->LineEdit->setText( Document().Context().Records().FullName() );
    m_RecordTableModel->layoutChanged();
    emit Document().Events().RecordExplorerChanged();
}

C_RecordStruct& C_UiRecordExplorer::Records()
{
    return Document().Context().Records();
}

QList<C_Record*> C_UiRecordExplorer::Selection()
{
    QModelIndexList index_list =
        ui->TableView
        ->selectionModel()
        ->selectedRows();

    QList<C_Record*> record_list;

    for( auto index : index_list )
    {
        C_Record* record =
            Document()
            .Context()
            .Records()
            .FromIndex( index.row() );

        record_list.append( record );
    }

    return record_list;
}

void C_UiRecordExplorer::ClearSelection()
{
    ui->TableView->selectionModel()->clearSelection();
}

bool C_UiRecordExplorer::HasSelection()
{
    return ui->TableView->selectionModel()->hasSelection();
}

void C_UiRecordExplorer::Activate( C_Record* record )
{
    if( record == 0 )
        return;

    if( record->Struct() != 0 )
    {
        Document().Context().SetRecords( *( record->Struct() ) );
        Update();
        return;
    }

    record->EditProperties( Document() );
}

void C_UiRecordExplorer::OnCustomContextMenuRequested( const QPoint& point )
{
    QPoint global_point = ui->TableView->viewport()->mapToGlobal( point );
    QModelIndex index = ui->TableView->indexAt( point );

    if( index.row() >= 0 )
        ui->TableView->selectionModel()->setCurrentIndex( index, QItemSelectionModel::Select );

    C_UiRecordContextMenu context_menu( Document(), global_point );
}

void C_UiRecordExplorer::OnDoubleClicked( const QModelIndex& index )
{
    Activate( Records().FromIndex( index.row() ) );
}

void C_UiRecordExplorer::OnRootButtonClicked()
{
    Document().Context().SetRecords( Document().Root() );
    Update();
}

void C_UiRecordExplorer::OnUpButtonClicked()
{
    if( ( & Records() ) != ( & Document().Root() ) )
    {
        C_Record* record = static_cast<C_Record*>( Document().Context().Records().Parent() );
        auto parent = static_cast<C_RecordStruct*>( record->Parent() );
        Document().Context().SetRecords( *parent );
        Update();
    }
}

void C_UiRecordExplorer::OnSelectionChanged( const QItemSelection&, const QItemSelection&  )
{
    Document().MainWindow().UpdateMenubar();
}

void C_UiRecordExplorer::OnLineEditReturnPressed()
{
    QString full_name = ui->LineEdit->text();

    if( full_name == "" )
    {
        Document().Context().SetRecords( Document().Root() );
        Update();
        return;
    }

    Activate( Document().Root().FromFullName( full_name ) );
}
