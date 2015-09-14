#include "FW/document.h"
#include "FW/UI/ui_file_explorer.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_editor_container.h"
#include "ui_fileexplorer.h"
#include <QDir>
#include <QStringListModel>
#include <FW/UI/ED/ui_text_editor.h>
#include "FW/controller.h"
#include "FW/UI/ui_file_contextmenu.h"

TypeUiFileExplorer::TypeUiFileExplorer( TypeController& controller, QWidget* parent ) :
    QWidget( parent ),
    TypeVariant( 0 ),
    m_Controller( &controller ),
    ui( new Ui::TypeUiFileExplorer )
{
    m_Path = "";
    m_Model = new QStringListModel( this );
    ui->setupUi( this );
    ui->ListView->setModel( m_Model );
    ui->ListView->setEditTriggers( QAbstractItemView::DoubleClicked );
    Update();

    connect(
        ui->ListView,
        QListView::doubleClicked,
        this,
        TypeUiFileExplorer::OnDoubleClicked
    );

    connect(
        ui->RootButton,
        QPushButton::clicked,
        this,
        TypeUiFileExplorer::OnRootButtonClicked
    );

    connect(
        ui->UpButton,
        QPushButton::clicked,
        this,
        TypeUiFileExplorer::OnUpButtonClicked
    );

    connect(
        ui->LineEdit,
        QLineEdit::returnPressed,
        this,
        TypeUiFileExplorer::OnLineEditReturnPressed
    );

    connect(
        ui->ListView,
        QListView::customContextMenuRequested,
        this,
        TypeUiFileExplorer::OnCustomContextMenuRequested
    );
}

TypeUiFileExplorer::~TypeUiFileExplorer()
{
    delete ui;
}

void TypeUiFileExplorer::FileOpen()
{
    QModelIndexList index_list = ui->ListView->selectionModel()->selectedIndexes();

    if( index_list.empty() )
        return;

    QModelIndex index = *index_list.begin();
    QString file_name = m_ModelData[index.row()];

    if( !Path().isEmpty() )
        file_name.prepend( Path() + "/" );

    FileOpen( file_name );
}

QString TypeUiFileExplorer::FullPath()
{
    if( !Path().isEmpty() )
        return Controller().Document().Path() + "/" + Path();

    return Controller().Document().Path();
}

void TypeUiFileExplorer::Update()
{
    ui->LineEdit->setText( Path() );
    m_ModelData = QDir( FullPath() ).entryList();
    m_ModelData.pop_front();
    m_ModelData.pop_front();
    m_Model->setStringList( m_ModelData );
    m_Model->layoutChanged();
    emit Controller().FileExplorerChanged();
}

void TypeUiFileExplorer::FileNew()
{
    QString path = Path();

    if( !path.isEmpty() )
        path = path + "/";

    QString file_name =
        QFileDialog::getSaveFileName(
            &Controller().MainWindow(),
            tr( "New File" ),
            path + tr( "untitled" ),
            tr( "Text files (*.txt);;Html files (*.html);;Php files (*.php);;Css files (*.css);;Java Script Files (*.js)" )
        );

    if( file_name.isEmpty() )
        return;

    Controller().NewFileUiEditor( file_name );
}

void TypeUiFileExplorer::FileMkDir()
{
    QString path = Path();

    if( !path.isEmpty() )
        path = path + "/";

    QString file_name =
        QFileDialog::getSaveFileName(
            &Controller().MainWindow(),
            tr( "New File" ),
            path + tr( "untitled" ),
            tr( "" )
        );

    if( file_name.isEmpty() )
        return;

    QDir( path ).mkdir( file_name );
    Update();
}

void TypeUiFileExplorer::FileOpen( QString file_name )
{
    if( file_name.isEmpty() )
    {
        m_Path = "";
        Update();
        return;
    }

    if( QFileInfo( file_name ).isDir() )
    {
        m_Path = file_name;
        Update();
        return;
    }

    if( !QFileInfo( file_name ).exists() )
    {
        TypeController::Message( tr( "File doesn't exists" ) );
        Update();
        return;
    }

    QStringList string_list = file_name.split( "/" );
    string_list.pop_back();
    m_Path = string_list.join( "/" );
    Update();
    Controller().OpenFileUiEditor( file_name );
}

void TypeUiFileExplorer::FileRemove()
{
    QModelIndexList index_list = ui->ListView->selectionModel()->selectedIndexes();

    if( index_list.empty() )
        return;

    QModelIndex index = *index_list.begin();
    QString file_name = m_ModelData[index.row()];

    if( !Path().isEmpty() )
        file_name.prepend( Path() + "/" );

    FileRemove( file_name );
}

void TypeUiFileExplorer::FileRemove( QString file_name )
{
    if( file_name.isEmpty() )
        return;

    if( !QFileInfo( file_name ).exists() )
    {
        TypeController::Message( tr( "File doesn't exists" ) );
        Update();
        return;
    }

    if( QFileInfo( file_name ).isDir() )
    {
        if( !QDir( file_name ).removeRecursively() )
            qDebug() << "Failed removing dir" << file_name;

        Update();
        return;
    }

    if( !QFile( file_name ).remove() )
        qDebug() << "Failed removing file" << file_name;

    Update();
}

void TypeUiFileExplorer::OnDoubleClicked( const QModelIndex& index )
{
    QString file_name = m_ModelData[index.row()];

    if( !Path().isEmpty() )
        file_name.prepend( Path() + "/" );

    FileOpen( file_name );
}

void TypeUiFileExplorer::OnLineEditReturnPressed()
{
    FileOpen( ui->LineEdit->text() );
}

void TypeUiFileExplorer::OnCustomContextMenuRequested( const QPoint& point )
{
    QPoint global_point = ui->ListView->viewport()->mapToGlobal( point );
    QModelIndex index = ui->ListView->indexAt( point );

    bool has_selection = false;

    if( index.row() >= 0 )
        has_selection = true;

    TypeUiFileContextMenu context_menu( Controller(), has_selection, global_point, this );
}

void TypeUiFileExplorer::OnRootButtonClicked()
{
    m_Path = "";
    Update();
}

void TypeUiFileExplorer::OnUpButtonClicked()
{
    if( !m_Path.isEmpty() )
    {
        QStringList path_list = m_Path.split( "/" );
        path_list.pop_back();
        m_Path = path_list.join( "/" );
        Update();
    }
}
