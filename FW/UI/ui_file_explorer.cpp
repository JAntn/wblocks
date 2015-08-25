#include "FW/document.h"
#include "FW/UI/ui_file_explorer.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_text_editor_container.h"
#include "ui_fileexplorer.h"
#include "FW/UI/ui_file_text_editor.h"
#include <QDir>
#include <QStringListModel>

C_UiFileExplorer::C_UiFileExplorer( C_Document& document, QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::C_UiFileExplorer )
{
    m_Document = &document;
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
        C_UiFileExplorer::OnDoubleClicked
    );

    connect(
        ui->RootButton,
        QPushButton::clicked,
        this,
        C_UiFileExplorer::OnRootButtonClicked
    );

    connect(
        ui->UpButton,
        QPushButton::clicked,
        this,
        C_UiFileExplorer::OnUpButtonClicked
    );

    connect(
        ui->LineEdit,
        QLineEdit::returnPressed,
        this,
        C_UiFileExplorer::OnLineEditReturnPressed
    );
}

C_UiFileExplorer::~C_UiFileExplorer()
{
    delete ui;
}

QString C_UiFileExplorer::FullPath()
{
    if( !Path().isEmpty() )
        return Document().Path() + "/" + Path();

    return Document().Path();
}

void C_UiFileExplorer::Update()
{
    ui->LineEdit->setText( Path() );
    m_ModelData = QDir( FullPath() ).entryList();
    m_ModelData.pop_front();
    m_ModelData.pop_front();
    m_Model->setStringList( m_ModelData );
    m_Model->layoutChanged();
    emit Document().Events().FileExplorerChanged();
}

void C_UiFileExplorer::Activate( QString file_name )
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
        C_Document::Message( tr( "File doesn't exists" ) );
        Update();
        return;
    }

    QString editor_id = "FILE:TEXT:" + file_name;

    if( Document().MainWindow().TextEditorContainer().HasId( editor_id ) )
    {
        if( C_Document::AcceptMessage( tr( "File already opened. Do you want to load again?" ) ) )
        {
            Document().MainWindow().TextEditorContainer().Close( editor_id );
            Document().MainWindow().TextEditorContainer().Append( new C_UiFileTextEditor( editor_id, file_name ) );
            Document().MainWindow().TextEditorContainer().SetCurrent( editor_id );
            Document().MainWindow().SetCurrentTab( MAINWINDOW_TAB_EDITOR );

            Update();
        }

        return;
    }

    Document().MainWindow().TextEditorContainer().Append( new C_UiFileTextEditor( editor_id, file_name ) );
    Document().MainWindow().TextEditorContainer().SetCurrent( editor_id );
    Document().MainWindow().SetCurrentTab( MAINWINDOW_TAB_EDITOR );

    Update();
}

void C_UiFileExplorer::OnDoubleClicked( const QModelIndex& index )
{
    QString file_name = m_ModelData[index.row()];

    if( !Path().isEmpty() )
        file_name.prepend( Path() + "/" );

    Activate( file_name );
}

void C_UiFileExplorer::OnLineEditReturnPressed()
{
    Activate( ui->LineEdit->text() );
}

void C_UiFileExplorer::OnRootButtonClicked()
{
    m_Path = "";
    Update();
}

void C_UiFileExplorer::OnUpButtonClicked()
{
    if( !m_Path.isEmpty() )
    {
        QStringList path_list = m_Path.split( "/" );
        path_list.pop_back();
        m_Path = path_list.join( "/" );
        Update();
    }
}
