#include "FW/RC/struct_record.h"
#include "FW/RC/record.h"
#include "FW/SC/scene.h"
#include "FW/database.h"
#include "FW/document.h"
#include "FW/context.h"
#include "FW/BK/html_builder.h"
#include "FW/clipboard.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/UI/ui_file_explorer.h"
#include "FW/config.h"
#include "FW/tools.h"
#include "FW/RC/root_struct.h"

#include "FW/UI/SH/ui_syntax_highlighter_factory.h"
#include "FW/UI/ED/ui_html_text_view.h"
#include "FW/UI/ui_editor_container.h"
#include "ui_texteditor.h"

///////////////////////////////////////////////////////////////////////////////////////////////
/// NON STATIC

TypeDocument::TypeDocument( TypeController& controller, QString file_name, QString path, TypeVariant* parent ):
    TypeVariant( parent ), m_Controller( &controller )
{
    qDebug() << "Creating document..";

    m_FileName          = file_name;
    m_Path              = path;
    m_Root              = new TypeRootStruct( this );
    m_Scene             = new TypeScene( controller, this );
    m_Context           = new TypeContext( Root(), Scene(), Root(), this );
    m_HtmlBuilder       = new TypeHtmlBuilder( this );

    qDebug() << "Document created";
}

TypeDocument::~TypeDocument()
{
    delete m_Root;
}

QWidget* TypeDocument::EditorWidget()
{

    qDebug() << "Editor widget request to Document";

    TypeUiEditor::TypeUpdateCallback update_callback = [this]( TypeUiEditor & editor_base )
    {
        TypeVariantPtr<TypeUiHtmlTextView> editor = &editor_base;

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

    //
    // Create widget:

    QWidget* widget = new TypeUiHtmlTextView(
        Controller(),
        Controller().Document(),
        Controller().NewHtmlTextViewId( FileName() ),
        FileName(),
        FileName().split( "/" ).back(),
        0/*parent widget*/,
        &TypeUiEditor::empty_save_callback,
        &TypeUiEditor::empty_save_callback,
        update_callback,
        Controller().SyntaxHighlighterFactory().NewInstance( "HTML" ) );

    return widget;
}

void TypeDocument::UpdateHtml()
{
    HtmlBuilder().Build( Root() );

    emit Controller().HtmlTextChanged();
}

void TypeDocument::Clear()
{
    Context().SetStruct( Root() );
    Root().Clear();
    Scene().Clear();

    emit Controller().RecordChanged(/*generic slot*/);

    SetFileName( "" );
    SetPath( "" );

    emit Controller().DirectoryChanged();
}

int TypeDocument::SaveFile( QString file_name )
{
    QFile file( file_name );

    if( !file.open( QIODevice::WriteOnly ) )
    {
        qDebug() << "Failed to open file to write" << file_name;
        return 1;
    }

    QDataStream out( &file );
    out << TypeRecordFactory::IdCount();
    out << TypeScene::IdCount();

    // GET RECORDS

    TypeStateReaderStream record_state( out );

    for( TypeVariantPtr<TypeRecord> record : Root() )
    {
        if( !record->GetState( record_state ) )
        {
            qDebug() << "Failed at reading record state" << file_name;
            return 2;
        }
    }

    record_state.Stop();

    // GET SCENE ITEMS

    TypeStateReaderStream scene_state( out );

    for( TypeSceneItem* item : Scene().Items() )
    {
        if( !item->GetState( scene_state ) )
        {
            qDebug() << "Failed at reading scene state" << file_name;
            return 3;
        }
    }

    scene_state.Stop();

    SetFileName( file_name );
    SetPath( QFileInfo( file_name ).canonicalPath() );

    return 0;
}

int TypeDocument::LoadFile( QString file_name )
{
    QFile file( file_name );

    if( !file.open( QIODevice::ReadOnly ) )
    {
        qDebug() << "Failed to open file to read"
                 << file_name;

        return 1;
    }

    Clear();
    QDataStream in( &file );
    QString value;
    in >> value;
    TypeRecordFactory::m_IdCount = value.toLong();
    in >> value;
    TypeScene::m_IdCount = value.toLong();

    // SET RECORDS

    TypeStateWriterStream record_state( in );

    while( !record_state.AtEnd() )
    {
        if( Root().NewRecord( record_state, -1 ) == 0 )
        {
            qDebug() << "Failed at writing record state" << file_name;
            return 2;
        }
    }

    // SET SCENE ITEMS

    TypeStateWriterStream scene_state( in );

    while( !scene_state.AtEnd() )
    {
        if( Scene().NewItem( scene_state ) == 0 )
        {
            qDebug() << "Failed at writing scene state" << file_name;
            return 3;
        }
    }

    emit Controller().RecordChanged(/*generic slot*/);

    SetFileName( file_name );
    SetPath( QFileInfo( file_name ).canonicalPath() );

    qDebug() << "Document loaded";

    return 0;
}

#define FIELD(__NAME)   "[$$$"+QString(__NAME)+"]"

int TypeDocument::SaveSQL( QString file_name )
{
    QFile::remove( file_name );

    if( !Controller().Database().OpenDatabase( file_name ) )
    {
        qDebug() << "Failed to open file to read" << file_name;
        return 1;
    }

    // SETUP TABLE

    QStringList row;
    row << FIELD( "ROW" ) << FIELD( "VALUE" );
    Controller().Database().CreateTable( FIELD( "SETUP_TABLE" ), row );

    // FILL SETUP TABLE

    row.clear();
    row << FIELD( "RECORD_ID_COUNT" ) << TypeRecordFactory::IdCount();
    Controller().Database().AppendRecord( FIELD( "SETUP_TABLE" ), row );
    row.clear();
    row << FIELD( "SCENE_ID_COUNT" ) << TypeScene::IdCount();
    Controller().Database().AppendRecord( FIELD( "SETUP_TABLE" ), row );

    // RECORD TABLE

    QStringList record_fields;
    record_fields.append( FIELD( "ROW" ) );
    record_fields.append( FIELD( "ID" ) );
    record_fields.append( FIELD( "NAME" ) );
    record_fields.append( FIELD( "VALUE" ) );
    record_fields.append( FIELD( "CLASS" ) );
    record_fields.append( FIELD( "FLAGS" ) );
    Controller().Database().CreateTable( FIELD( "RECORD_TABLE" ), record_fields );

    // FILL TABLE

    TypeStateReaderDatabase record_state( Controller().Database(), FIELD( "RECORD_TABLE" ), FIELD( "ROW" ) );

    for( TypeVariantPtr<TypeRecord> record : Root() )
    {
        if( !record->GetState( record_state ) )
        {
            qDebug() << "Failed at reading record state" << file_name;
            return 2;
        }
    }

    row.clear();
    row << FIELD( "RECORD_NUM" ) << QString::number( record_state.Count() );
    Controller().Database().AppendRecord( FIELD( "SETUP_TABLE" ), row );

    // SCENE ITEMS TABLE

    QStringList scene_fields;
    scene_fields.append( FIELD( "ROW" ) );
    scene_fields.append( FIELD( "ID" ) );
    scene_fields.append( FIELD( "RECORD_ID" ) );
    scene_fields.append( FIELD( "X" ) );
    scene_fields.append( FIELD( "Y" ) );
    scene_fields.append( FIELD( "Z" ) );
    Controller().Database().CreateTable( FIELD( "SCENE_TABLE" ), scene_fields );
    TypeStateReaderDatabase scene_state( Controller().Database(), FIELD( "SCENE_TABLE" ), FIELD( "ROW" ) );

    for( TypeSceneItem* item : Scene().Items() )
    {
        if( !item->GetState( scene_state ) )
        {
            qDebug() << "Failed at reading scene state" << file_name;
            return 3;
        }

    }

    row.clear();
    row << FIELD( "SCENEITEM_NUM" ) << QString::number( scene_state.Count()  );
    Controller().Database().AppendRecord( FIELD( "SETUP_TABLE" ), row );
    Controller().Database().CloseDatabase();

    SetFileName( file_name );
    SetPath( QFileInfo( file_name ).canonicalPath() );

    return 0;
}

int TypeDocument::LoadSQL( QString file_name )
{
    Clear();

    if( !Controller().Database().OpenDatabase( file_name ) )
    {
        qDebug() << "Failed to open file to read" << file_name;
        return 1;
    }

    QStringList row;
    row = Controller().Database().GetRecord( FIELD( "SETUP_TABLE" ), FIELD( "ROW" ), FIELD( "RECORD_ID_COUNT" ) );
    TypeRecordFactory::m_IdCount = row[1].toLong();
    row = Controller().Database().GetRecord( FIELD( "SETUP_TABLE" ), FIELD( "ROW" ), FIELD( "SCENE_ID_COUNT" ) );
    TypeScene::m_IdCount = row[1].toLong();
    row = Controller().Database().GetRecord( FIELD( "SETUP_TABLE" ), FIELD( "ROW" ), FIELD( "RECORD_NUM" ) );
    long record_size = row[1].toLong();
    row = Controller().Database().GetRecord( FIELD( "SETUP_TABLE" ), FIELD( "ROW" ), FIELD( "SCENEITEM_NUM" ) );
    long scene_size = row[1].toLong();

    // RECORDS TABLE

    TypeStateWriterDatabase record_state( Controller().Database(), FIELD( "RECORD_TABLE" ), FIELD( "ROW" ), record_size );

    while( !record_state.AtEnd() )
    {
        if( Root().NewRecord( record_state, -1 ) == 0 )
        {
            qDebug() << "Failed at writing record state" << file_name;
            return 2;
        }
    }

    // SCENE ITEMS TABLE

    TypeStateWriterDatabase scene_state( Controller().Database(), FIELD( "SCENE_TABLE" ), FIELD( "ROW" ), scene_size );

    while( !scene_state.AtEnd() )
    {
        if( Scene().NewItem( scene_state ) == 0 )
        {
            qDebug() << "Failed at writing scene state" << file_name;
            return 3;
        }
    }

    Controller().Database().CloseDatabase();
    emit Controller().RecordChanged(/*generic slot*/);

    SetFileName( file_name );
    SetPath( QFileInfo( file_name ).canonicalPath() );

    qDebug() << "Document loaded";

    return 0;
}

