#include "FW/document.h"
#include "FW/UI/ui_file_explorer.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_editor_container.h"
#include "ui_fileexplorer.h"
#include <QDir>
#include <QStringListModel>
#include <FW/UI/ED/ui_text_editor.h>
#include "FW/controller.h"

TypeUiFileExplorer::TypeUiFileExplorer( TypeController& controller, QWidget* parent ) :
    QWidget( parent ),
    m_Controller( &controller ),
    ui( new Ui::TypeUiFileExplorer )
{
    m_Path = ""; // RELATIVE TO DOCUMENT PATH
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
}

TypeUiFileExplorer::~TypeUiFileExplorer()
{
    delete ui;
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

void TypeUiFileExplorer::Open( QString file_name )
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
        // IT SHALL NOT ENTER HERE NEVER
        TypeController::Message( tr( "File doesn't exists" ) );
        Update();
        return;
    }

    QStringList string_list = file_name.split( "/" );
    string_list.pop_back();
    m_Path = string_list.join( "/" );
    Update();
    Controller().OpenFileEditorWidget( file_name );
}

void TypeUiFileExplorer::OnDoubleClicked( const QModelIndex& index )
{
    QString file_name = m_ModelData[index.row()];

    if( !Path().isEmpty() )
        file_name.prepend( Path() + "/" );

    Open( file_name );
}

void TypeUiFileExplorer::OnLineEditReturnPressed()
{
    Open( ui->LineEdit->text() );
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
