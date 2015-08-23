#include "FW/document.h"
#include "FW/UI/ui_file_explorer.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_code_editor_container.h"
#include "ui_fileexplorer.h"
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

QString C_UiFileExplorer::AbsolutePath()
{
    if( !Path().isEmpty() )
        return Document().Path() + "/" + Path();

    return Document().Path();
}

void C_UiFileExplorer::Update()
{
    ui->LineEdit->setText( Path() );
    m_ModelData = QDir( AbsolutePath() ).entryList();
    m_ModelData.pop_front();
    m_ModelData.pop_front();
    m_Model->setStringList( m_ModelData );
    m_Model->layoutChanged();
    emit Document().Events().FileExplorerChanged();
}

void C_UiFileExplorer::Activate( QString file_name )
{
    QString file_name_abs = Document().Path();

    if( !file_name.isEmpty() )
        file_name_abs = file_name_abs + "/" + file_name;

    if( QFileInfo( file_name_abs ).isDir() )
    {
        m_Path = file_name;
        Update();
        return;
    }

    if( !QFileInfo( file_name_abs ).exists() )
    {
        C_Document::Message( tr( "File doesn't exists" ) );
        Update();
        return;
    }

    if( Document().MainWindow().CodeEditorContainer().HasFile( file_name ) )
    {
        if( C_Document::AcceptMessage( tr( "File already opened. Do you want to load again?" ) ) )
        {
            Document().MainWindow().CodeEditorContainer().Clear( file_name_abs );
            Document().MainWindow().CodeEditorContainer().Append( file_name_abs );
            Update();
        }

        return;
    }

    Document().MainWindow().CodeEditorContainer().Append( file_name );
    Update();
}

void C_UiFileExplorer::OnDoubleClicked( const QModelIndex& index )
{
    Activate( m_ModelData[index.row()] );
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
