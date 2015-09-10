#include "FW/RC/record.h"
#include "FW/UI/ui_record_contextmenu.h"
#include "FW/UI/ui_record_tablemodel.h"
#include "FW/UI/ui_record_explorer.h"
#include "FW/RC/struct_record.h"
#include "FW/RC/root_struct.h"
#include "FW/UI/ui_main_window.h"
#include "FW/document.h"
#include "FW/context.h"
#include "FW/clipboard.h"
#include "ui_main_window.h"
#include "ui_recordexplorer.h"

TypeUiRecordExplorer::TypeUiRecordExplorer( TypeContext& context, TypeController& controller, QWidget* parent ) :
    QWidget( parent ),
    TypeVariant( 0 ),
    m_Context( &context ),
    m_Controller( &controller ),
    m_ActiveRecord( 0 ),
    ui( new Ui::TypeUiRecordExplorer )
{
    ui->setupUi( this );
    m_RecordTableModel = new TypeUiRecordTableModel( Controller().Document().Context().Struct(), this );
    ui->TableView->setModel( m_RecordTableModel );

    connect(
        &controller,
        TypeController::SetActiveRecord,
        this,
        TypeUiRecordExplorer::ActivateRecord
    );

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
    if( &Context().Struct() != &Context().Root() )
        ui->LineEdit->setText( Context().Struct().ParentRecord()->FullName() );
    else
        ui->LineEdit->setText( "" );

    m_RecordTableModel->SetStruct( Context().Struct() );
    m_RecordTableModel->layoutChanged();

    emit Controller().RecordExplorerChanged();
}


QList<TypeRecord*> TypeUiRecordExplorer::Selection()
{
    QModelIndexList index_list = ui->TableView->selectionModel()->selectedRows();
    QList<TypeRecord*> record_list;

    for( auto index : index_list )
    {
        TypeRecord* record = Context().Struct().FromIndex( index.row() );

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

void TypeUiRecordExplorer::OpenRecord( TypeRecord* record )
{
    SetActiveRecord( record );

    if( record == 0 )
        return;

    if( record->Struct() != 0 )
    {
        Context().SetStruct( *( record->Struct() ) );
        Update();
        return;
    }

    Context().SetStruct( *record->ParentStruct() );
    Update();

    // Select the row
    int row = record->ParentStruct()->GetIndex( record );
    ui->TableView->selectRow( row );
}

void TypeUiRecordExplorer::ActivateRecord( TypeRecord* record )
{
    if( ActiveRecord() == record )
        return;

    SetActiveRecord( record );

    if( ActiveRecord() == 0 )
        return;

    Context().SetStruct( *ActiveRecord()->ParentStruct() );
    Update();

    // Select the row
    int row = ActiveRecord()->ParentStruct()->GetIndex( ActiveRecord() );
    ui->TableView->selectRow( row );
}

void TypeUiRecordExplorer::OnCustomContextMenuRequested( const QPoint& point )
{
    QPoint global_point = ui->TableView->viewport()->mapToGlobal( point );
    QModelIndex index = ui->TableView->indexAt( point );
    TypeRecord* record = 0;

    if( index.row() >= 0 )
    {
        //ui->TableView->selectionModel()->setCurrentIndex( index, QItemSelectionModel::Select );
        record = Context().Struct().FromIndex( index.row() );
    }

    ActivateRecord( record );
    long action_flags = Context().Struct().Flags();
    bool has_selection = false;

    if( record != 0 )
        has_selection = true;

    TypeUiRecordContextMenu context_menu( Controller(), action_flags, has_selection, global_point, this );
}

void TypeUiRecordExplorer::OnDoubleClicked( const QModelIndex& index )
{
    TypeRecord* record = Context().Struct().FromIndex( index.row() );
    OpenRecord( record );

    emit Controller().SetActiveRecord( record );
}

void TypeUiRecordExplorer::OnRootButtonClicked()
{
    Context().SetStruct( Controller().Document().Root() );
    Update();

    emit Controller().SetActiveRecord( 0 );
}

void TypeUiRecordExplorer::OnUpButtonClicked()
{
    if( &Context().Struct() != ( & Controller().Document().Root() ) )
    {
        Context().SetStruct( *Context().Struct().ParentStruct() );
        Update();

        emit Controller().SetActiveRecord( 0 );
    }
}

void TypeUiRecordExplorer::OnSelectionChanged( const QItemSelection&, const QItemSelection&  )
{
    Controller().MainWindow().UpdateActions();

    if( HasSelection() )
    {
        TypeVariantPtr<TypeRecord> record = *Selection().begin();

        emit Controller().SetActiveRecord( record );

        return;
    }

    emit Controller().SetActiveRecord( 0 );
}

void TypeUiRecordExplorer::OnLineEditReturnPressed()
{
    QString record_name = ui->LineEdit->text();

    if( record_name == "" )
    {
        Context().SetStruct( Controller().Document().Root() );
        Update();

        emit Controller().SetActiveRecord( 0 );
        return;
    }

    TypeRootStruct& root = Controller().Document().Root();
    TypeRecord* record = root.FromName( record_name, true );
    OpenRecord( record );

    emit Controller().SetActiveRecord( record );
}
