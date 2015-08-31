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

C_UiRecordExplorer::C_UiRecordExplorer( C_Context& context, C_Controller& controller, QWidget* parent ) :
    QWidget( parent ),
    m_Context( &context ),
    m_Controller( &controller ),
    ui( new Ui::C_UiRecordExplorer )
{
    ui->setupUi( this );
    m_RecordTableModel = new C_UiRecordTableModel( Controller().Document(), this );
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
    ui->LineEdit->setText( Context().Records().FullName() );
    m_RecordTableModel->layoutChanged();
    emit Controller().RecordExplorerChanged();
}


QList<C_Record*> C_UiRecordExplorer::Selection()
{
    QModelIndexList index_list = ui->TableView->selectionModel()->selectedRows();
    QList<C_Record*> record_list;

    for( auto index : index_list )
    {
        C_Record* record = Context().Records().FromIndex( index.row() );

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
        Context().SetRecords( *( record->Struct() ) );
        Update();
        return;
    }

    Context().SetRecords( *static_cast<C_RecordStruct*>( record->Parent() ) );
    Update();
    Controller().SetPropertyWidgetRecord( *record );
}

void C_UiRecordExplorer::OnCustomContextMenuRequested( const QPoint& point )
{
    QPoint global_point = ui->TableView->viewport()->mapToGlobal( point );
    QModelIndex index = ui->TableView->indexAt( point );

    if( index.row() >= 0 )
        ui->TableView->selectionModel()->setCurrentIndex( index, QItemSelectionModel::Select );

    C_UiRecordContextMenu context_menu( Controller(), global_point );
}

void C_UiRecordExplorer::OnDoubleClicked( const QModelIndex& index )
{
    Activate( Context().Records().FromIndex( index.row() ) );
}

void C_UiRecordExplorer::OnRootButtonClicked()
{
    Context().SetRecords( Controller().Document().Root() );
    Update();
}

void C_UiRecordExplorer::OnUpButtonClicked()
{
    if( ( & Context().Records() ) != ( & Controller().Document().Root() ) )
    {
        C_Record* record = static_cast<C_Record*>( Context().Records().Parent() );
        C_RecordStruct* parent = static_cast<C_RecordStruct*>( record->Parent() );
        Context().SetRecords( *parent );
        Update();
    }
}

void C_UiRecordExplorer::OnSelectionChanged( const QItemSelection&, const QItemSelection&  )
{
    Controller().MainWindow().UpdateMenubar();
}

void C_UiRecordExplorer::OnLineEditReturnPressed()
{
    QString full_name = ui->LineEdit->text();

    if( full_name == "" )
    {
        Context().SetRecords( Controller().Document().Root() );
        Update();
        return;
    }

    Activate( Controller().Document().Root().FromFullName( full_name ) );
}
