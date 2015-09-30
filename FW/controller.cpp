//
// Include all records:

#include "FW/RC/struct_record.h"

#include "FW/controller.h"
#include "FW/RC/record.h"
#include "FW/RC/struct.h"
#include "FW/SC/scene.h"
#include "FW/UI/ED/ui_text_editor.h"
#include "FW/UI/SH/ui_syntax_highlighter.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ED/ui_html_text_view.h"
#include "FW/UI/ui_record_explorer.h"
#include "FW/UI/ui_add_record.h"
#include "FW/UI/ui_editor_container.h"
#include "FW/BK/html_builder.h"
#include "FW/database.h"
#include "FW/clipboard.h"
#include "FW/config.h"
#include "FW/clipboard.h"
#include "FW/document.h"
#include "FW/tools.h"
#include "FW/context.h"
#include <QWebFrame>
#include "ui_mainwindow.h"
#include "FW/UI/ui_file_explorer.h"

///////////////////////////////////////////////////////////////////////////////////////////////
/// STATIC

QList<TypeRecordFactory*>        TypeController::m_FactoryList;
TypeUiSyntaxHighlighterFactory   TypeController::m_SyntaxHighlighterFactory;


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

    qDebug() << "File " + file_name + " loaded";
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

    qDebug() << "File " + file_name + " saved";
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
    qDebug() << "Starting Controller..";

    m_BinPath           = QDir().canonicalPath();
    m_Database          = new TypeDatabase( this );
    m_Clipboard         = new TypeClipboard( this );

    if( SyntaxHighlighterFactory().Empty() )
    {
        SyntaxHighlighterFactory().AppendFormat( "C++", ":/SyntaxHighlight/rcc/cpp.txt" );
        SyntaxHighlighterFactory().AppendFormat( "HTML", ":/SyntaxHighlight/rcc/html.txt" );
        SyntaxHighlighterFactory().AppendFormat( "JAVASCRIPT", ":/SyntaxHighlight/rcc/js.txt" );
        SyntaxHighlighterFactory().AppendFormat( "PHP", ":/SyntaxHighlight/rcc/php.txt" );
        SyntaxHighlighterFactory().AppendFormat( "CSS", ":/SyntaxHighlight/rcc/css.txt" );
    }

    if( FactoryList().empty() )
    {
        m_FactoryList.append( &TypeRecordFactory::Instance() );
        m_FactoryList.append( &TypeStructRecordFactory::Instance() );

        // Add more classes here or later
    }

    qDebug() << "Controller loaded succesfull";
}

TypeController::~TypeController()
{
    qDebug() << "Controller deleted";
}

const QList<TypeRecordFactory*>& TypeController::FactoryList()
{
    return m_FactoryList;
}

TypeRecordFactory* TypeController::FactoryFromName( QString class_name )
{
    for( TypeRecordFactory* record_factory : FactoryList() )
    {
        if( record_factory->RecordClass() == class_name )
            return record_factory;
    }

    return 0;
}

TypeUiSyntaxHighlighterFactory& TypeController::SyntaxHighlighterFactory()
{
    return m_SyntaxHighlighterFactory;
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



QString TypeController::NewFileNameId( QString file_name )
{
    QString file_ext = file_name.split( "." ).back();

    for( QString ext : QVector<QString> { "h", "hpp", "c", "cpp"} )
    {
        if( file_ext == ext )
            return "FILE:C++:" + file_name;
    }

    if( file_ext == "js" )
        return "FILE:JAVASCRIPT:" + file_name;

    if( file_ext == "html" )
        return "FILE:HTML:" + file_name;

    if( file_ext == "php" )
        return"FILE:PHP:" + file_name;

    if( file_ext == "css" )
        return"FILE:CSS:" + file_name;

    if( file_ext == "txt" )
        return"FILE:PLAINTEXT:" + file_name;

    return "FILE:PLAINTEXT:" + file_name;
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

void TypeController::OpenRecordEditorWidget( TypeRecord& record )
{
    QString id = "RECORD:" + record.Id();

    if( MainWindow().EditorContainer().HasId( id ) )
    {
        MainWindow().EditorContainer().Close( id );
        MainWindow().OpenEditorWidget( record.EditorWidget( id, *this ) );

        return;
    }

    MainWindow().OpenEditorWidget( record.EditorWidget( id, *this ) );
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

    TypeUiEditor::TypeSaveCallback save_callback = [file_name, this]( TypeUiEditor & editor_base )
    {
        TypeVariantPtr<TypeUiTextEditor> editor = &editor_base;
        SaveTextFile( file_name, editor->Text() );
        MainWindow().UpdateFileExplorer();
        return true;
    };

    TypeUiEditor::TypeSaveCallback save_as_callback = [file_name, this]( TypeUiEditor & editor_base )
    {
        TypeVariantPtr<TypeUiTextEditor> editor = &editor_base;

        QString file_name_out =
            QFileDialog::getSaveFileName(
                &MainWindow(),
                tr( "Select File Name" ),
                editor->Name(),
                tr( "All files (*.*)" )
            );

        if( file_name_out.isEmpty() )
        {
            qDebug() << "File selection cancelled";
            return false;
        }

        QString new_id = NewFileNameId( file_name_out );

        if( new_id != editor->Id() )
        {
            if( MainWindow().EditorContainer().HasId( new_id ) )
            {
                if( !TypeController::AcceptMessage( tr( "File already open. Replace file?" ) ) )
                    return false;

                MainWindow().EditorContainer().Close( new_id );
            }

            editor->SetId( new_id );
        }

        editor->SetName( file_name_out );
        editor->SetTabName( file_name_out.split( "/" ).back() );
        editor->OnActionUpdate();

        SaveTextFile( file_name_out, editor->Text() );
        MainWindow().UpdateFileExplorer();
        return true;
    };

    TypeUiEditor::TypeUpdateCallback update_callback = []( TypeUiEditor & editor_base )
    {
        TypeVariantPtr<TypeUiTextEditor> editor = &editor_base;

        //
        // Update editor title:

        QString changed_mark = "";

        if( editor->HasChanged() )
            changed_mark = "*";

        editor->SetTitle( editor->Name() + changed_mark );

        //
        // Update editor container data:

        if( editor->EditorContainer() != 0 )
        {
            editor->EditorContainer()->SetTabName( editor->Id(), editor->TabName() + changed_mark );
            editor->EditorContainer()->SetTabToolTip( editor->Id(), editor->Name() + changed_mark );
        }

        return true;
    };

    TypeUiSyntaxHighlighter* syntax_highlighter = SyntaxHighlighterFactory().NewInstance( id.split( ":" )[1] );

    TypeUiTextEditor* text_editor = new TypeUiTextEditor(
        id,
        file_name,
        file_name.split( "/" ).back(),
        0 /*parent widget*/,
        save_callback,
        save_as_callback,
        update_callback,
        syntax_highlighter );

    text_editor->SetText( LoadTextFile( file_name ) );
    text_editor->SetHasChanged( false );

    MainWindow().EditorContainer().Append( text_editor );
    MainWindow().EditorContainer().SetCurrent( id );
    MainWindow().SetCurrentTab( MAINWINDOW_TAB_EDITOR );
}

void TypeController::NewFileUiEditor( QString file_name )
{
    QString id = NewFileNameId( file_name );

    if( MainWindow().EditorContainer().HasId( id ) )
    {
        if( !TypeController::AcceptMessage( tr( "File already open. Replace file?" ) ) )
            return;

        MainWindow().EditorContainer().Close( id );
    }

    TypeUiEditor::TypeSaveCallback save_callback = [file_name, this]( TypeUiEditor & editor_base )
    {
        TypeVariantPtr<TypeUiTextEditor> editor = &editor_base;
        SaveTextFile( file_name, editor->Text() );
        MainWindow().UpdateFileExplorer();
        return true;
    };

    TypeUiEditor::TypeSaveCallback save_as_callback = [file_name, this]( TypeUiEditor & editor_base )
    {
        TypeVariantPtr<TypeUiTextEditor> editor = &editor_base;

        QString file_name_out =
            QFileDialog::getSaveFileName(
                &MainWindow(),
                tr( "Select File Name" ),
                editor->Name(),
                tr( "Text files (*.txt);;Html files (*.html);;Css files (*.css);;Java Script Files (*.js);;Php files (*.php)" )
            );

        if( file_name_out.isEmpty() )
        {
            qDebug() << "File selection cancelled";
            return false;
        }

        QString new_id = NewFileNameId( file_name_out );

        if( new_id != editor->Id() )
        {

            if( MainWindow().EditorContainer().HasId( new_id ) )
            {
                if( !TypeController::AcceptMessage( tr( "File already open. Replace file?" ) ) )
                    return false;

                MainWindow().EditorContainer().Close( new_id );
            }

            editor->SetId( new_id );
        }

        editor->SetName( file_name_out );
        editor->SetTabName( file_name_out.split( "/" ).back() );
        editor->OnActionUpdate();

        SaveTextFile( file_name_out, editor->Text() );
        MainWindow().UpdateFileExplorer();
        return true;
    };

    TypeUiEditor::TypeUpdateCallback update_callback = []( TypeUiEditor & editor_base )
    {
        TypeVariantPtr<TypeUiTextEditor> editor = &editor_base;

        //
        // Update editor title:

        QString changed_mark = "";

        if( editor->HasChanged() )
            changed_mark = "*";

        editor->SetTitle( editor->Name() + changed_mark );

        //
        // Update editor container data:

        if( editor->EditorContainer() != 0 )
        {
            editor->EditorContainer()->SetTabName( editor->Id(), editor->TabName() + changed_mark );
            editor->EditorContainer()->SetTabToolTip( editor->Id(), editor->Name() + changed_mark );
        }

        return true;
    };

    TypeUiSyntaxHighlighter* syntax_highlighter =
        SyntaxHighlighterFactory().NewInstance( id.split( ":" )[1] );

    TypeUiTextEditor* text_editor = new TypeUiTextEditor(
        id,
        file_name,
        file_name.split( "/" ).back(),
        0/*parent widget*/,
        save_callback,
        save_as_callback,
        update_callback,
        syntax_highlighter );

    text_editor->SetText( "" );
    text_editor->SetHasChanged( false );

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

void TypeController::OnActionProjectNew()
{
    if( TypeController::AcceptMessage( "Save project changes?" ) )
    {
        MainWindow().EditorContainer().SaveAll();

        QString file_name = Document().FileName();

        if( file_name.isEmpty() )
        {
            file_name =
                QFileDialog::getSaveFileName(
                    &MainWindow(),
                    tr( "Save Project File" ),
                    tr( "untitled" ),
                    tr( "Project Files (*.prj *.sql)" )
                );
        }

        if( file_name.isEmpty() )
        {
            qDebug() << "File name is empty";
            return;
        }

        MainWindow().EditorContainer().SaveAll();
        MainWindow().UpdateFileExplorer();
        MainWindow().EditorContainer().CloseAll();

        int error;

        if( file_name.split( "." ).back() == "sql" )
            error = Document().SaveSQL( file_name );
        else
            error = Document().SaveFile( file_name );

        if( !error )
        {
            qDebug() << "Save project successfull";

            Config().SetProjectFileName( Document().FileName() );
            Config().SetProjectPath( Document().Path() );
        }
        else
            qDebug() << "Save project error. Code " << error;
    }

    Document().Clear();

    MainWindow().SetTitle( "" );

    MainWindow().HtmlTextView().SetName( "" );
    MainWindow().HtmlTextView().SetTabName( "" );
    MainWindow().HtmlTextView().SetTitle( "" );
    MainWindow().HtmlTextView().SetHasChanged( false );
    MainWindow().HtmlTextView().OnActionUpdate();

    MainWindow().SetPropertyWidget( 0 );

    Config().SetProjectFileName( "" );
    Config().SetProjectPath( "" );

    QDir().setCurrent( Config().ProjectPath() );
    emit DirectoryChanged();
}


void TypeController::OnActionProjectOpen()
{
    QString file_name =
        QFileDialog::getOpenFileName(
            &MainWindow(),
            tr( "Load File" ),
            Document().FileName(),
            tr( "Project Files (*.prj *.sql)" )
        );

    if( file_name.isEmpty() )
    {
        qDebug() << "File selection cancelled";
        return;
    }

    int error;

    if( file_name.split( "." ).back() == "prj" )
        error = Document().LoadFile( file_name );
    else
        error = Document().LoadSQL( file_name );

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

void TypeController::OnActionProjectSaveAs()
{
    QString file_name =
        QFileDialog::getSaveFileName(
            &MainWindow(),
            tr( "Save File" ),
            Document().FileName(),
            tr( "Project Files (*.prj *.sql)" )
        );

    if( file_name.isEmpty() )
    {
        qDebug() << "File selection cancelled";
        return;
    }

    int error;

    if( file_name.split( "." ).back() == "prj" )
        error = Document().SaveFile( file_name );
    else
        error = Document().SaveSQL( file_name );

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

void TypeController::OnActionProjectSave()
{
    int error;

    if( Document().FileName().split( "." ).back() == "prj" )
        error = Document().SaveFile( Document().FileName() );
    else
        error = Document().SaveSQL( Document().FileName() );

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

void TypeController::OnActionHtmlSaveAs()
{
    QStringList token_list = Document().FileName().split( "." );
    token_list.pop_back();

    QString file_name =
        QFileDialog::getSaveFileName(
            &MainWindow(),
            tr( "Save Html File" ),
            token_list.join( "" ) + ".html",
            tr( "Html Files (*.html)" )
        );

    if( file_name.isEmpty() )
    {
        qDebug() << "File Selection failed";
        return;
    }

    Document().UpdateHtml();

    TypeController::SaveTextFile( file_name, Document().HtmlBuilder().Text() );
    MainWindow().UpdateFileExplorer();
}

void TypeController::OnActionHtmlSave()
{
    QStringList token_list = Document().FileName().split( "." );
    token_list.pop_back();
    QString file_name = token_list.join( "" ) + ".html";

    Document().UpdateHtml();

    TypeController::SaveTextFile( file_name, Document().HtmlBuilder().Text() );
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

void TypeController::OnActionRecordRemove()
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

        emit SetActiveRecord( 0 );

        for( TypeRecord* record : selection_list )
            delete record;

        emit RecordsChanged();
    }
    else
        qDebug() << "FLAG_ACTION_REMOVE is disabled on parent struct.";
}

void TypeController::OnActionRecordAdd()
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

void TypeController::OnActionRecordAddSceneItem()
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

void TypeController::OnActionRecordCopy()
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

void TypeController::OnActionRecordPaste()
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

void TypeController::OnActionRecordCut()
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

void TypeController::OnActionRecordOpenInEditor()
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


void TypeController::OnActionFileNew()
{
    QString file_name =
        QFileDialog::getSaveFileName(
            &MainWindow(),
            tr( "New File" ),
            tr( "untitled" ),
            tr( "Text files (*.txt);;Html files (*.html);;Php files (*.php);;Css files (*.css);;Java Script Files (*.js)" )
        );

    if( file_name.isEmpty() )
        return;

    NewFileUiEditor( file_name );
}

void TypeController::OnActionFileClose()
{
    if( TypeController::AcceptMessage( tr( "Save changes?" ) ) )
    {
        MainWindow().EditorContainer().SaveCurrent();
        MainWindow().FileExplorer().Update();
    }

    MainWindow().EditorContainer().CloseCurrent();
    emit EditorContainerChanged();
}

void TypeController::OnActionFileCloseAll()
{
    if( TypeController::AcceptMessage( tr( "Save changes?" ) ) )
    {
        MainWindow().EditorContainer().SaveAll();
        emit FileExplorerChanged();
    }

    MainWindow().EditorContainer().CloseAll();
    emit EditorContainerChanged();
}

void TypeController::OnActionFileSaveAs()
{
    MainWindow().EditorContainer().SaveAsCurrent();
}

void TypeController::OnActionFileSave()
{
    MainWindow().EditorContainer().SaveCurrent();
}

void TypeController::OnActionFileSaveAll()
{
    MainWindow().EditorContainer().SaveAll();
}

void TypeController::OnActionFileNew_FileExplorer()
{
    MainWindow().FileExplorer().FileNew();
}

void TypeController::OnActionFileOpen_FileExplorer()
{
    MainWindow().FileExplorer().FileOpen();
}

void TypeController::OnActionFileRemove_FileExplorer()
{
    MainWindow().FileExplorer().FileRemove();
}

void TypeController::OnActionFileMkDir_FileExplorer()
{
    MainWindow().FileExplorer().FileMkDir();
}

void TypeController::OnActionFileOpen()
{
    QString file_name =
        QFileDialog::getOpenFileName(
            &MainWindow(),
            tr( "New File" ),
            tr( "untitled.js" ),
            tr( "Text files (*.txt);;Html files (*.txt);;PHP files (*.php);;CSS files (*.css);;Java Script Files (*.js)" )
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

    if( TypeController::AcceptMessage( "Save project changes?" ) )
    {
        MainWindow().EditorContainer().SaveAll();

        QString file_name = Document().FileName();

        if( file_name.isEmpty() )
        {
            file_name =
                QFileDialog::getSaveFileName(
                    &MainWindow(),
                    tr( "Save Project File" ),
                    tr( "untitled" ),
                    tr( "Project Files (*.prj *.sql)" )
                );
        }

        if( file_name.isEmpty() )
        {
            qDebug() << "File is empty";
            return;
        }

        MainWindow().EditorContainer().SaveAll();

        int error;

        if( file_name.split( "." ).back() == "sql" )
            error = Document().SaveSQL( file_name );
        else
            error = Document().SaveFile( file_name );

        if( !error )
        {
            qDebug() << "Save project successfull";

            Config().SetProjectFileName( Document().FileName() );
            Config().SetProjectPath( Document().Path() );
            Config().Save();
            return;
        }

        qDebug() << "Save project error. Code " << error;
        Config().SetProjectFileName( "" );
        Config().SetProjectPath( "" );
        Config().Save();
    }

}

void TypeController::OnActionHtmlUpdateWeb()
{
    Document().UpdateHtml();

    MainWindow().UpdateHtmlWebView();
    MainWindow().SetCurrentTab( MAINWINDOW_TAB_OUTPUT );
}

void TypeController::OnActionHtmlUpdateText()
{
    Document().UpdateHtml();
    MainWindow().SetCurrentTab( MAINWINDOW_TAB_HTML );
}

