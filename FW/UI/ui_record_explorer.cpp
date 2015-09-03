#include "FW/RC/record.h"
#include "FW/UI/ui_record_contextmenu.h"
#include "FW/UI/ui_record_tablemodel.h"
#include "FW/UI/ui_record_explorer.h"
#include "FW/RC/struct_record.h"
#include "FW/UI/ui_main_window.h"
#include "FW/document.h"
#include "FW/context.h"
#include "FW/clipboard.h"
#include "ui_main_window.h"
#include "ui_recordexplorer.h"

TypeUiRecordExplorer::TypeUiRecordExplorer( TypeContext& context, TypeController& controller, QWidget* parent ) :
    QWidget( parent ),
    TypeVariant(0),
    m_Context( &context ),
    m_Controller( &controller ),
    ui( new Ui::TypeUiRecordExplorer )
{
    ui->setupUi( this );
    m_RecordTableModel = new TypeUiRecordTableModel( Controller().Document(), this );
    ui->TableView->setModel( m_RecordTableModel );

    connect(
        ui->TableView,
        QTableView::doubleClicked,
        this,
        TypeUiRecordExplorer::OnDoubleClicked
    );

    connect(
        ui->RootButton,
        QPushButton::clicked,
        this,
        TypeUiRecordExplorer::OnRootButtonClicked
    );

    connect(
        ui->UpButton,
        QPushButton::clicked,
        this,
        TypeUiRecordExplorer::OnUpButtonClicked
    );

    connect(
        ui->TableView,
        QTableView::customContextMenuRequested,
        this,
        TypeUiRecordExplorer::OnCustomContextMenuRequested
    );

    connect(
        ui->TableView->selectionModel(),
        QItemSelectionModel::selectionChanged,
        this,
        TypeUiRecordExplorer::OnSelectionChanged
    );

    connect(
        ui->LineEdit,
        QLineEdit::returnPressed,
        this,
        TypeUiRecordExplorer::OnLineEditReturnPressed
    );
}

TypeUiRecordExplorer::~TypeUiRecordExplorer()
{
    delete ui;
}

void TypeUiRecordExplorer::Update()
{
    ui->LineEdit->setText( Context().Records().FullName() );
    m_RecordTableModel->layoutChanged();
    emit Controller().RecordExplorerChanged();
}


QList<TypeRecord*> TypeUiRecordExplorer::Selection()
{
    QModelIndexList index_list = ui->TableView->selectionModel()->selectedRows();
    QList<TypeRecord*> record_list;

    for( auto index : index_list )
    {
        TypeRecord* record = Context().Records().FromIndex( index.row() );

        record_list.append( record );
    }

    return record_list;
}

void TypeUiRecordExplorer::ClearSelection()
{
    ui->TableView->selectionModel()->clearSelection();
}

bool TypeUiRecordExplorer::HasSelection()
{
    return ui->TableView->selectionModel()->hasSelection();
}

void TypeUiRecordExplorer::Activate( TypeRecord* record )
{
    if( record == 0 )
        return;

    if( record->Struct() != 0 )
    {
        Context().SetRecords( *( record->Struct() ) );
        Update();
        return;
    }

    Context().SetRecords( *static_cast<TypeRecordStruct*>( record->Parent() ) );
    Update();
    Controller().SetPropertyWidgetRecord( *record );
}

void TypeUiRecordExplorer::OnCustomContextMenuRequested( const QPoint& point )
{
    QPoint global_point = ui->TableView->viewport()->mapToGlobal( point );
    QModelIndex index = ui->TableView->indexAt( point );

    if( index.row() >= 0 )
        ui->TableView->selectionModel()->setCurrentIndex( index, QItemSelectionModel::Select );

    TypeUiRecordContextMenu context_menu( Controller(), global_point );
}

void TypeUiRecordExplorer::OnDoubleClicked( const QModelIndex& index )
{
    Activate( Context().Records().FromIndex( index.row() ) );
}

void TypeUiRecordExplorer::OnRootButtonClicked()
{
    Context().SetRecords( Controller().Document().Root() );
    Update();
}

void TypeUiRecordExplorer::OnUpButtonClicked()
{
    if( ( & Context().Records() ) != ( & Controller().Document().Root() ) )
    {
        TypeRecord* record = static_cast<TypeRecord*>( Context().Records().Parent() );
        TypeRecordStruct* parent = static_cast<TypeRecordStruct*>( record->Parent() );
        Context().SetRecords( *parent );
        Update();
    }
}

void TypeUiRecordExplorer::OnSelectionChanged( const QItemSelection&, const QItemSelection&  )
{
    Controller().MainWindow().UpdateMenubar();
}

void TypeUiRecordExplorer::OnLineEditReturnPressed()
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
