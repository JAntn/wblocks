#include "FW/RC/record.h"
#include "FW/UI/ui_record_context_menu.h"
#include "FW/document.h"
#include "FW/UI/ui_record_table_model.h"
#include "FW/UI/ui_record_struct_view.h"
#include "ui_recordstructview.h"
#include "FW/RC/struct_record.h"
#include "FW/clipboard.h"
#include "FW/UI/ui_main_window.h"
#include "ui_mainwindow.h"

C_UiRecordStructView::C_UiRecordStructView( C_Document& document, QWidget* parent ) :
    QWidget( parent ),
    m_Document( &document ),
    ui( new Ui::C_UiRecordStructView )
{
    ui->setupUi( this );
    m_RecordTableModel = new C_UiRecordTableModel( Document(), this );
    ui->TableView->setModel( m_RecordTableModel );

    connect(
        ui->TableView,
        QTableView::doubleClicked,
        this,
        C_UiRecordStructView::OnDoubleClicked
    );

    connect(
        ui->RootButton,
        QPushButton::clicked,
        this,
        C_UiRecordStructView::OnRootButtonClicked
    );

    connect(
        ui->UpButton,
        QPushButton::clicked,
        this,
        C_UiRecordStructView::OnUpButtonClicked
    );

    connect(
        ui->TableView,
        QTableView::customContextMenuRequested,
        this,
        C_UiRecordStructView::OnCustomContextMenuRequested
    );

    connect(
        ui->TableView->selectionModel(),
        QItemSelectionModel::selectionChanged,
        this,
        C_UiRecordStructView::OnSelectionChanged
    );

    connect(
        ui->LineEdit,
        QLineEdit::returnPressed,
        this,
        C_UiRecordStructView::OnLineEditReturnPressed
    );
}

C_UiRecordStructView::~C_UiRecordStructView()
{
    delete ui;
}

void C_UiRecordStructView::Update()
{
    ui->LineEdit->setText(Document().Context().Records().FullName());
    m_RecordTableModel->layoutChanged();
}


C_RecordStruct& C_UiRecordStructView::Records()
{
    return Document().Context().Records();
}

list<C_Record*> C_UiRecordStructView::Selection()
{
    QModelIndexList indexes = ui->TableView
                              ->selectionModel()
                              ->selectedRows();
    list<C_Record*> record_list;


    for( auto index : indexes )
    {
        auto record = Document()
                      .Context()
                      .Records()
                      .FromIndex( index.row() );

        record_list.push_back( record );
    }

    return record_list;
}

void C_UiRecordStructView::ClearSelection()
{
    ui->TableView->selectionModel()->clearSelection();
}

bool C_UiRecordStructView::HasSelection()
{
    return ui->TableView->selectionModel()->hasSelection();
}

void C_UiRecordStructView::OnCustomContextMenuRequested( const QPoint& point )
{
    QPoint global_point = ui->TableView->viewport()->mapToGlobal( point );
    QModelIndex index = ui->TableView->indexAt( point );

    if( index.row() >= 0 )
        ui->TableView->selectionModel()->setCurrentIndex( index, QItemSelectionModel::Select );

    C_UiRecordContextMenu context_menu( Document(), global_point );
}

void C_UiRecordStructView::OnDoubleClicked( const QModelIndex& index )
{
    C_Record* record = Records().FromIndex( index.row() );

    if( record->Struct() != 0 )
    {
        Document().Context().SetRecords( *( record->Struct() ) );
        emit Document().Events().RecordsChanged();
        return;
    }

    record->ShowEditor( Document() );
}

void C_UiRecordStructView::OnRootButtonClicked()
{
    Document().Context().SetRecords( Document().Records() );
    emit Document().Events().RecordsChanged();
}

void C_UiRecordStructView::OnUpButtonClicked()
{
    if( ( & Records() ) != ( & Document().Records() ) )
    {
        auto record = static_cast<C_Record*>( Document().Context().Records().Parent() );
        auto parent = static_cast<C_RecordStruct*>( record->Parent() );
        Document().Context().SetRecords( *parent );
        emit Document().Events().RecordsChanged();
    }
}

void C_UiRecordStructView::OnSelectionChanged( const QItemSelection& selected, const QItemSelection& deselected )
{
    Document()
    .MainWindow()
    .UpdateMenubar();
}


void C_UiRecordStructView::OnLineEditReturnPressed()
{

    QString full_name = ui->LineEdit->text();
    QStringList string_list = full_name.split( "." );
    auto* parent = &Document().Records();

    if( *string_list.begin() == "")
    {

        Document()
        .Context()
        .SetRecords(*parent);
        emit Document()
        .Events()
        .RecordsChanged();
        return;
    }

    auto iter = string_list.begin();
    auto record = parent->FromName( *iter );

    if( record == 0 )
        return;

    parent = record->Struct();

    if( parent == 0 )
        return;

    for( ; iter != string_list.end(); )
    {
        auto tmp = iter;
        ++tmp;

        if( tmp == string_list.end() )
        {
            Document()
            .Context()
            .SetRecords( *parent );
            emit Document()
            .Events()
            .RecordsChanged();
            return;
        }

        ++iter;
        auto record = parent->FromName( *iter );

        if( record == 0 )
            return;

        parent = record->Struct();

        if( parent == 0 )
            return;
    }

}
