#include "FW/controller.h"
#include "FW/RC/record.h"
#include "FW/RC/struct.h"
#include "FW/SC/scene.h"
#include "FW/UI/ED/ui_text_editor.h"
#include "FW/UI/SH/ui_syntax_highlighter.h"
#include "FW/UI/SH/ui_syntax_highlighter_factory.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ED/ui_html_text_view.h"
#include "FW/UI/ui_record_explorer.h"
#include "FW/UI/ui_add_record.h"
#include "FW/UI/ui_editor_container.h"
#include "FW/htmlbuilder.h"
#include "FW/database.h"
#include "FW/clipboard.h"
#include "FW/config.h"
#include "FW/clipboard.h"
#include "FW/document.h"
#include "FW/tools.h"
#include "FW/context.h"
#include <QWebFrame>
#include "ui_mainwindow.h"

///////////////////////////////////////////////////////////////////////////////////////////////
/// STATIC

QString TypeController::LoadTextFile( QString file_name )
{
    QFile file( file_name );

    if( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        file.close();
        return QString();
    }

    QString text = file.readAll();
    file.close();
    return text;
}

void TypeController::SaveTextFile( QString file_name, QString text )
{
    QFile file( file_name );

    if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        file.close();
        return;
    }

    QTextStream out( &file );
    out << text;
    file.close();
}

bool TypeController::AcceptMessage( QString msg )
{
    QMessageBox msgBox;
    msgBox.setText( msg );
    msgBox.setStandardButtons( QMessageBox::Ok | QMessageBox::Cancel );
    msgBox.setDefaultButton( QMessageBox::Cancel );
    msgBox.exec();

    if( msgBox.result() == QMessageBox::Cancel )
        return false;

    return true;
}

void TypeController::Message( QString msg )
{
    QMessageBox msgBox;
    msgBox.setText( msg );
    msgBox.exec();
}

///////////////////////////////////////////////////////////////////////////////////////////////
/// NON STATIC

TypeController::TypeController(): TypeVariant()
{
    m_BinPath           = QDir().canonicalPath();
    m_HtmlBuilder       = new TypeHtmlBuilder( this );
    m_Database          = new TypeDatabase( this );
    m_Clipboard         = new TypeClipboard( this );

    m_SyntaxHighlighterFactory = new TypeUiSyntaxHighlighterFactory( this );
    SyntaxHighlighterFactory().AppendFormat( "C++", ":/SyntaxHighlight/rcc/cpp.txt" );
    SyntaxHighlighterFactory().AppendFormat( "HTML", ":/SyntaxHighlight/rcc/html.txt" );
    SyntaxHighlighterFactory().AppendFormat( "JS", ":/SyntaxHighlight/rcc/js.txt" );
    SyntaxHighlighterFactory().AppendFormat( "PHP", ":/SyntaxHighlight/rcc/php.txt" );
}

TypeController::~TypeController()
{
    // void
}

void TypeController::ConnectSlots()
{
    connect(
        this,
        TypeController::DirectoryChanged,
        this,
        TypeController::OnDirectoryChanged );

    connect(
        this,
        TypeController::RecordsChanged,
        this,
        TypeController::OnRecordsChanged );

    connect(
        this,
        TypeController::SceneChanged,
        this,
        TypeController::OnSceneChanged );

    connect(
        this,
        TypeController::HtmlTextChanged,
        this,
        TypeController::OnHtmlTextChanged );

    connect(
        this,
        TypeController::RecordExplorerChanged,
        this,
        TypeController::OnRecordExplorerChanged );

    connect(
        this,
        TypeController::FileExplorerChanged,
        this,
        TypeController::OnFileExplorerChanged );

    connect(
        this,
        TypeController::EditorContainerChanged,
        this,
        TypeController::OnEditorContainerChanged );
}

void TypeController::OpenRecordEditorWidget( TypeRecord& record )
{
    QString id = "RECORD:" + record.Id();

    if( MainWindow().EditorContainer().HasId( id ) )
    {
        if( TypeController::AcceptMessage( QCoreApplication::translate( "TypeController", "Record already opened.\n\nLoad again?" ) ) )
        {
            MainWindow().EditorContainer().Close( id );
            MainWindow().OpenEditorWidget( record.EditorWidget( id, *this ) );
        }

        return;
    }

    MainWindow().OpenEditorWidget( record.EditorWidget( id, *this ) );
}

QString TypeController::NewFileNameId( QString file_name )
{
    QString file_ext = file_name.split( "." ).back();

    for( QString ext : QVector<QString> { "h", "hpp", "c", "cpp"} )
    {
        if( file_ext == ext )
            return "FILE:C++:" + file_name;
    }

    if( file_ext == "js" )
        return "FILE:JS:" + file_name;

    if( file_ext == "html" )
        return "FILE:HTML:" + file_name;

    if( file_ext == "php" )
        return"FILE:PHP:" + file_name;

    return "FILE:TEXT:" + file_name;
}

QString TypeController::NewHtmlTextViewId( QString file_name )
{
    QString file_ext = file_name.split( "." ).back();

    if( file_ext == "prj" )
        return "STRUCT:PRJ:" + file_name;

    if( file_ext == "sql" )
        return "STRUCT:SQL:" + file_name;

    return "STRUCT:UNKNOWN:" + file_name;
}

void TypeController::OpenFileUiEditor( QString file_name )
{
    QString id = NewFileNameId( file_name );

    if( MainWindow().EditorContainer().HasId( id ) )
    {
        if( !TypeController::AcceptMessage( tr( "File already open. Load again?" ) ) )
            return;

        MainWindow().EditorContainer().Close( id );
    }

    TypeUiEditor::TypeSaveCallback save_callback = [file_name]( TypeUiEditor & editor_base )
    {
        TypeVariantPtr<TypeUiTextEditor> editor = &editor_base;
        SaveTextFile( file_name, editor->Text() );
        return true;
    };

    TypeUiSyntaxHighlighter* syntax_highlighter = SyntaxHighlighterFactory().NewInstance( id.split( ":" )[1] );

    TypeUiTextEditor* text_editor = new TypeUiTextEditor(
        id, file_name, file_name.split( "/" ).back(), 0/*parent widget*/,
        save_callback/*editor save callback*/,
        syntax_highlighter/*syntax highlighter*/ );

    text_editor->SetText( LoadTextFile( file_name ) );
    text_editor->SetHasChanged( false );
    text_editor->UpdateTitle();

    MainWindow().EditorContainer().Append( text_editor );
    MainWindow().EditorContainer().SetCurrent( id );
    MainWindow().SetCurrentTab( MAINWINDOW_TAB_EDITOR );
}


void TypeController::OnDirectoryChanged()
{
    MainWindow().UpdateFileExplorer();
}

void TypeController::OnRecordExplorerChanged()
{
    MainWindow().UpdateActions();
}

void TypeController::OnFileExplorerChanged()
{
    MainWindow().UpdateActions();
}

void TypeController::OnRecordsChanged()
{
    MainWindow().UpdateRecordExplorer();
    MainWindow().UpdateSceneView();

    Document().UpdateHtml();
}

void TypeController::OnHtmlTextChanged()
{
    MainWindow().UpdateHtmlTextView();
}

void TypeController::OnEditorContainerChanged()
{
    MainWindow().UpdateActions();
}

void TypeController::OnSceneChanged()
{
    MainWindow().UpdateSceneView();
}

void TypeController::OnActionNewProjectFile()
{
    Document().Clear();
    MainWindow().SetTitle( "" );

    MainWindow().HtmlTextView().SetName( "" );
    MainWindow().HtmlTextView().SetHasChanged( false );
    MainWindow().HtmlTextView().UpdateTitle();
}


void TypeController::OnActionLoadProjectFile()
{
    QString file_name =
        QFileDialog::getOpenFileName(
            &MainWindow(),
            tr( "Load File" ),
            Document().FileName(),
            tr( "Project Files (*.prj)" )
        );

    if( file_name.isEmpty() )
    {
        qDebug() << "File selection cancelled";
        return;
    }

    int error = Document().LoadFile( file_name );

    if( !error )
    {
        qDebug() << "Load project successfull";

        MainWindow().HtmlTextView().SetName( Document().FileName() );
        MainWindow().HtmlTextView().OnActionSave();

        Config().SetProjectFileName( Document().FileName() );
        Config().SetProjectPath( Document().Path() );
        QDir().setCurrent( Config().ProjectPath() );
        emit DirectoryChanged();

        return;
    }

    qDebug() << "Load project error. Code " << error;
}

void TypeController::OnActionSaveProjectFile()
{
    QString file_name =
        QFileDialog::getSaveFileName(
            &MainWindow(),
            tr( "Save File" ),
            Document().FileName(),
            tr( "Project Files (*.prj)" )
        );

    if( file_name.isEmpty() )
    {
        qDebug() << "File selection cancelled";
        return;
    }

    int error = Document().SaveFile( file_name );
    MainWindow().UpdateFileExplorer();

    if( !error )
    {
        qDebug() << "Save project successfull";

        MainWindow().HtmlTextView().SetName( Document().FileName() );
        MainWindow().HtmlTextView().OnActionSave();

        Config().SetProjectFileName( Document().FileName() );
        Config().SetProjectPath( Document().Path() );
        QDir().setCurrent( Config().ProjectPath() );
        emit DirectoryChanged();

        return;
    }

    qDebug() << "Save project error. Code " << error;
}

void TypeController::OnActionLoadProjectSQL()
{
    QString file_name =
        QFileDialog::getOpenFileName(
            &MainWindow(),
            tr( "Load SQL Database File" ),
            "",
            tr( "SQL Files (*.sql)" )
        );

    if( file_name.isEmpty() )
    {
        qDebug() << "File selection canceled";
        return;
    }

    int error = Document().LoadSQL( file_name );

    if( !error )
    {
        qDebug() << "Load project SQL successfull";

        MainWindow().HtmlTextView().SetName( Document().FileName() );
        MainWindow().HtmlTextView().OnActionSave();

        Config().SetProjectFileName( Document().FileName() );
        Config().SetProjectPath( Document().Path() );
        QDir().setCurrent( Config().ProjectPath() );
        emit DirectoryChanged();

        return;
    }

    qDebug() << "Load project SQL error. Code " << error;
}

void TypeController::OnActionSaveProjectSQL()
{
    QString file_name =
        QFileDialog::getSaveFileName(
            &MainWindow(),
            tr( "Save SQL Database File" ),
            tr( "untitled.sql" ),
            tr( "SQL Files (*.sql)" )
        );

    if( file_name.isEmpty() )
    {
        qDebug() << "File selection canceled";
        return;
    }

    int error = Document().SaveSQL( file_name );
    MainWindow().UpdateFileExplorer();

    if( !error )
    {
        qDebug() << "Load project SQL successfull";

        MainWindow().HtmlTextView().SetName( Document().FileName() );
        MainWindow().HtmlTextView().OnActionSave();

        Config().SetProjectFileName( Document().FileName() );
        Config().SetProjectPath( Document().Path() );
        QDir().setCurrent( Config().ProjectPath() );
        emit DirectoryChanged();

        return;
    }

    qDebug() << "Load project SQL error. Code " << error;
}

void TypeController::OnActionSaveHtmlFile()
{
    QString file_name =
        QFileDialog::getSaveFileName(
            &MainWindow(),
            tr( "Save Html File" ),
            tr( "untitled.html" ),
            tr( "Html Files (*.html)" )
        );

    if( file_name.isEmpty() )
    {
        qDebug() << "File Selection failed";
        return;
    }

    Document().UpdateHtml();

    TypeController::SaveTextFile(
        file_name,
        HtmlBuilder().Text()
    );

    MainWindow().UpdateFileExplorer();
}

void TypeController::OnActionChangePropertyWidget()
{
    long action_flags = Document().Context().Struct().Flags() ;
    bool has_selection = MainWindow().RecordExplorer().HasSelection();

    if( ( action_flags & FLAG_ACTION_ACTIVATE ) && has_selection )
    {
        TypeVariantPtr<TypeRecord> record =
            *MainWindow().RecordExplorer().Selection().begin();

        if( !( record->Flags() & FLAG_ACTION_ACTIVATE ) )
        {
            qDebug() << "FLAG_ACTION_ACTIVATE is disabled on record"
                     << record->Name();
            return;
        }

        emit SetActiveRecord( record );

    }
    else
    {
        if( has_selection )
            qDebug() << "FLAG_ACTION_ACTIVATE is disabled on parent struct";
        else
            qDebug() << "Change record properties: nothing selected";
    }
}

void TypeController::OnActionRemoveRecord()
{
    long action_flags = Document().Context().Struct().Flags() ;
    bool has_selection = MainWindow().RecordExplorer().HasSelection();

    if( ( action_flags & FLAG_ACTION_REMOVE ) && has_selection )
    {
        auto selection_list = MainWindow().RecordExplorer().Selection();

        if( selection_list.size() == 1 )
        {
            if( !TypeController::AcceptMessage( tr( "Remove Record?" ) ) )
                return;
        }
        else
        {
            if( !TypeController::AcceptMessage( tr( "Do you want to remove these records?" ) ) )
                return;
        }

        for( TypeRecord* record : selection_list )
        {
            if( !( record->Flags() & FLAG_ACTION_REMOVE ) )
            {
                qDebug() << "FLAG_ACTION_REMOVE is disabled on record" << record->Name();
                return;
            }
        }

        emit SetActiveRecord(0);

        for( TypeRecord* record : selection_list )
            delete record;

        emit RecordsChanged();
    }
    else
        qDebug() << "FLAG_ACTION_REMOVE is disabled on parent struct.";
}

void TypeController::OnActionAddRecord()
{
    long action_flags = Document().Context().Struct().Flags() ;

    if( !( action_flags & FLAG_ACTION_ADD ) )
    {
        qDebug() << "FLAG_ACTION_ADD is disabled on parent struct.";
        return;
    }

    int position = -1;

    if ( MainWindow().RecordExplorer().HasSelection() )
    {
        TypeRecord* front = MainWindow().RecordExplorer().Selection().front();
        position = Document().Context().Struct().GetIndex( front );
    }

    QWidget* dialog;

    if( position >= 0 )
    {
        dialog = new TypeUiAddRecord( *this, Document().Context(), position, &MainWindow() );
        dialog->show();
        return;
    }

    dialog = new TypeUiAddRecord( *this, Document().Context(), -1, &MainWindow() );
    dialog->show();
}

void TypeController::OnActionAddSceneItem()
{
    long action_flags = Document().Context().Struct().Flags();

    if( ( action_flags & FLAG_ACTION_ADD_SCENE ) &&
            MainWindow().RecordExplorer().HasSelection() )
    {
        auto selection_list = MainWindow().RecordExplorer().Selection();

        for( TypeRecord* record : selection_list )
        {
            if( !( record->Flags() & FLAG_ACTION_ADD_SCENE ) )
            {
                qDebug() << "FLAG_ACTION_ADD_SCENE is disabled on record"
                         << record->Name();
                return;
            }
        }

        for( TypeRecord* record : selection_list )
            Document().Context().Scene().NewItem( *record );

        MainWindow().SetCurrentTab( MAINWINDOW_TAB_SCENE );
        emit SceneChanged();
    }
    else
    {
        qDebug() << "FLAG_ACTION_ADD_SCENE is disabled on parent struct.";
        return;
    }
}

void TypeController::OnActionCopyRecord()
{
    long action_flags = Document().Context().Struct().Flags();
    bool has_selection = MainWindow().RecordExplorer().HasSelection();

    if( ( action_flags & FLAG_ACTION_COPY ) && has_selection )
    {
        auto selection_list = MainWindow().RecordExplorer().Selection();

        for( TypeRecord* record : selection_list )
        {
            if( !( record->Flags() & FLAG_ACTION_CUT ) )
            {
                qDebug() << "FLAG_ACTION_CUT is disabled on record"
                         << record->Name();
                return;
            }
        }

        Clipboard().Copy( selection_list );
        MainWindow().UpdateActions();
    }
    else
    {
        qDebug() << "FLAG_ACTION_COPY is disabled on parent struct";
        return;
    }
}

void TypeController::OnActionPasteRecord()
{
    long action_flags = Document().Context().Struct().Flags();
    bool has_selection = MainWindow().RecordExplorer().HasSelection(); //This function lies ('la lia?=
    int position = -1;

    if( action_flags & FLAG_ACTION_PASTE )
    {
        if( has_selection )
        {
            QList<TypeRecord*> selection_list = MainWindow().RecordExplorer().Selection();

            if( !selection_list.empty() )
                position = Document().Context().Struct().GetIndex( selection_list.front() );
        }

        Clipboard().Paste(
            Document().Context().Struct(),
            position
        );

        Clipboard().Clear();
        emit RecordsChanged();
    }
    else
    {
        qDebug() << "FLAG_ACTION_PASTE is disabled on parent struct";
        return;
    }
}

void TypeController::OnActionCutRecord()
{
    long action_flags = Document().Context().Struct().Flags();
    bool has_selection = MainWindow().RecordExplorer().HasSelection();

    if( ( action_flags & FLAG_ACTION_CUT ) && has_selection )
    {
        QList<TypeRecord*> selection_list = MainWindow().RecordExplorer().Selection();

        for( TypeRecord* record : selection_list )
        {
            if( !( record->Flags() & FLAG_ACTION_CUT ) )
            {
                qDebug() << "FLAG_ACTION_CUT is disabled on record"
                         << record->Name();
                return;
            }
        }

        for( TypeRecord* record : selection_list )
        {
            record->SetParent( 0 );

            auto items = Document().Scene().FromRecord( *record );

            for( auto item : items )
                delete item;
        }

        Clipboard().Copy( selection_list );
        emit RecordsChanged();
    }
    else
    {
        qDebug() << "FLAG_ACTION_CUT is disabled on parent struct";
        return;
    }
}

void TypeController::OnActionOpenRecordInEditor()
{
    long action_flags = Document().Context().Struct().Flags() ;
    bool has_selection = MainWindow().RecordExplorer().HasSelection();

    if( ( action_flags & FLAG_ACTION_OPEN ) && has_selection )
    {
        TypeVariantPtr<TypeRecord> record =
            *MainWindow().RecordExplorer().Selection().begin();

        if( !( record->Flags() & FLAG_ACTION_OPEN ) )
        {
            qDebug() << "FLAG_ACTION_OPEN is disabled on record" << record->Name();
            return;
        }

        OpenRecordEditorWidget( *record );
    }
    else
        qDebug() << "FLAG_ACTION_OPEN is disabled on parent struct.";
}


void TypeController::OnActionNewFile()
{
    QString file_name =
        QFileDialog::getSaveFileName(
            &MainWindow(),
            tr( "New File" ),
            tr( "untitled.js" ),
            tr( "JS Files (*.js); PHP files (*.php); CSS files (*.css)" )
        );

    if( file_name.isEmpty() )
        return;

// *  QFileDialog has showed a message like the following example:
// *
//
//    if( QFileInfo( file_name ).exists() )
//    {
//        if( !TypeController::AcceptMessage( tr( "File already exists. Overwrite?" ) ) )
//            return;
//    }


    TypeController::SaveTextFile( file_name, "//FILE: " + file_name.split( "/" ).back() );
    emit FileExplorerChanged();

    OpenFileUiEditor( file_name );
}

void TypeController::OnActionCloseFile()
{
    if( TypeController::AcceptMessage( tr( "Save changes?" ) ) )
    {
        MainWindow().EditorContainer().SaveCurrent();
        emit FileExplorerChanged();
    }

    MainWindow().EditorContainer().CloseCurrent();
    emit EditorContainerChanged();
}

void TypeController::OnActionCloseAllFiles()
{
    if( TypeController::AcceptMessage( tr( "Save changes?" ) ) )
    {
        MainWindow().EditorContainer().SaveAll();
        emit FileExplorerChanged();
    }

    MainWindow().EditorContainer().CloseAll();
    emit EditorContainerChanged();
}

void TypeController::OnActionSaveFile()
{
    MainWindow().EditorContainer().SaveCurrent();
}

void TypeController::OnActionSaveAllFiles()
{
    MainWindow().EditorContainer().SaveAll();
}

void TypeController::OnActionLoadFile()
{
    QString file_name =
        QFileDialog::getOpenFileName(
            &MainWindow(),
            tr( "New File" ),
            tr( "untitled.js" ),
            tr( "JS Files (*.js)" )
        );

    if( file_name.isEmpty() )
        return;

    if( !QFileInfo( file_name ).exists() )
    {
        TypeController::Message( tr( "File not found" ) );
        return;
    }

    OpenFileUiEditor( file_name );
}

void TypeController::OnLeftTabCurrentChanged( int )
{
    MainWindow().UpdateActions();
}

void TypeController::OnRightTabCurrentChanged( int )
{
    //void
}

void TypeController::OnActionExit()
{
    MainWindow().close();
}

void TypeController::OnActionUpdateHtmlWeb()
{
    Document().UpdateHtml();

    MainWindow().UpdateHtmlWebView();
    MainWindow().SetCurrentTab( MAINWINDOW_TAB_OUTPUT );
}

void TypeController::OnActionUpdateHtmlText()
{
    Document().UpdateHtml();
    MainWindow().SetCurrentTab( MAINWINDOW_TAB_HTML );
}

