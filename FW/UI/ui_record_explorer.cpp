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

TypeUiRecordExplorer::TypeUiRecordExplorer( TypeController& controller, TypeDocument& document, QWidget* parent ) :
    QWidget( parent ),
    TypeVariant( 0 ),
    m_Controller( &controller ),
    m_Document( &document ),
    m_ActiveRecord( 0 ),
    ui( new Ui::TypeUiRecordExplorer )
{
    ui->setupUi( this );
    m_RecordTableModel = new TypeUiRecordTableModel( Document().Context().Struct(), this );
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
    //
    // Update record search widget contents:

    if( &Document().Context().Struct() != &Document().Context().Root() )
        ui->LineEdit->setText( Document().Context().Struct().ParentRecord()->FullName() );
    else
        ui->LineEdit->setText( "" );

    m_RecordTableModel->SetStruct( Document().Context().Struct() );
    m_RecordTableModel->layoutChanged();

    emit Controller().RecordExplorerChanged();
}


QList<TypeRecord*> TypeUiRecordExplorer::Selection()
{
    QModelIndexList index_list = ui->TableView->selectionModel()->selectedRows();
    QList<TypeRecord*> record_list;

    for( auto index : index_list )
    {
        TypeRecord* record = Document().Context().Struct().FromIndex( index.row() );
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
        Document().Context().SetStruct( *( record->Struct() ) );
        Update();
        return;
    }

    //
    // Open record value in editor:

    Controller().OpenRecordEditorWidget( *record );

    //
    // Set current struct in record explorer:

    Document().Context().SetStruct( *record->ParentStruct() );
    Update();

    //
    // Select the row in record explorer:

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

    Document().Context().SetStruct( *ActiveRecord()->ParentStruct() );
    Update();

    //
    // Select the row in view:

    int row = ActiveRecord()->ParentStruct()->GetIndex( ActiveRecord() );
    ui->TableView->selectRow( row );
}

void TypeUiRecordExplorer::OnCustomContextMenuRequested( const QPoint& point )
{
    QPoint global_point = ui->TableView->viewport()->mapToGlobal( point );
    QModelIndex index = ui->TableView->indexAt( point );
    TypeRecord* record = 0;

    if( index.row() >= 0 )
        record = Document().Context().Struct().FromIndex( index.row() );

    ActivateRecord( record );
    long action_flags = Document().Context().Struct().Flags();
    bool has_selection = false;

    if( record != 0 )
        has_selection = true;

    TypeUiRecordContextMenu context_menu( Controller(), action_flags, has_selection, global_point, this );
}

void TypeUiRecordExplorer::OnDoubleClicked( const QModelIndex& index )
{
    TypeRecord* record = Document().Context().Struct().FromIndex( index.row() );
    OpenRecord( record );

    emit Controller().SetActiveRecord( record );
}

void TypeUiRecordExplorer::OnRootButtonClicked()
{
    Document().Context().SetStruct( Document().Root() );
    Update();

    emit Controller().SetActiveRecord( 0 );
}

void TypeUiRecordExplorer::OnUpButtonClicked()
{
    if( &Document().Context().Struct() != ( & Document().Root() ) )
    {
        Document().Context().SetStruct( *Document().Context().Struct().ParentStruct() );
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
        Document().Context().SetStruct( Document().Root() );
        Update();
        emit Controller().SetActiveRecord( 0 );

        return;
    }

    TypeRootStruct& root = Document().Root();
    TypeRecord* record = root.FromName( record_name, true );
    OpenRecord( record );

    emit Controller().SetActiveRecord( record );
}
