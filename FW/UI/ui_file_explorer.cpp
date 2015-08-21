#include "FW/UI/ui_file_explorer.h"
#include "ui_fileexplorer.h"
#include "FW/document.h"
#include <QDir>
#include <QStringListModel>
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_code_editor_container.h"

C_UiFileExplorer::C_UiFileExplorer( C_Document& document, QString path, QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::C_UiFileExplorer )
{
    m_Document = &document;
    m_Path = path;
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

void C_UiFileExplorer::Update()
{
    ui->LineEdit->setText( Path() );
    m_ModelData = QDir( Path() ).entryList();
    m_ModelData.pop_front();
    m_ModelData.pop_front();
    m_Model->setStringList( m_ModelData );
    m_Model->layoutChanged();
    emit Document().Events().FileExplorerChanged();
}

void C_UiFileExplorer::Activate( QString file_name )
{
    if( !m_Path.isEmpty() )
        file_name = ( QStringList() << m_Path << file_name ).join( "/" );


    if( QFileInfo( file_name ).isDir() )
    {
        m_Path = file_name;
        Update();
        return;
    }

    if( !QFile( file_name ).exists() )
    {
        C_Document::Message( tr( "File doesn't exists" ) );
        Update();
        return;
    }

    if( Document().MainWindow().CodeEditorContainer().HasFile( file_name ) )
    {
        if( C_Document::AcceptMessage( tr( "File already opened. Do you want to load again?" ) ) )
        {
            Document().MainWindow().CodeEditorContainer().Clear( file_name );
            Document().MainWindow().CodeEditorContainer().Append( file_name );
            Update();
        }

        return;
    }

    Document().MainWindow().CodeEditorContainer().Append( file_name );
    Update();
}

void C_UiFileExplorer::OnDoubleClicked( const QModelIndex& index )
{
    Activate(m_ModelData[index.row()]);
}

void C_UiFileExplorer::OnLineEditReturnPressed()
{
    Activate(ui->LineEdit->text());
}

void C_UiFileExplorer::OnRootButtonClicked()
{
    m_Path = "";
    Update();
}

void C_UiFileExplorer::OnUpButtonClicked()
{
    QStringList path_list = m_Path.split( "/" );
    path_list.pop_back();
    m_Path = path_list.join( "/" );
    Update();
}
