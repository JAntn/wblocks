#include "FW/RC/struct_record.h"
#include "FW/RC/record.h"
#include "FW/SC/scene.h"
#include "FW/database.h"
#include "FW/document.h"
#include "FW/htmlbuilder.h"
#include "FW/clipboard.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/UI/ui_file_explorer.h"
#include "FW/RC/script_file_record.h"
#include "FW/config.h"
#include <QMessageBox>
#include <QStack>
#include <QDebug>
#include <QFileInfo>
#include <QDir>

///////////////////////////////////////////////////////////////////////////////////////////////
/// NON STATIC

TypeDocument::TypeDocument( TypeController& controller, QString file_name, QString path, TypeVariant* parent ):
    TypeVariant( parent ), m_Controller( &controller )
{
    TypeRecordStruct::InitFactoryList();

    m_FileName          = file_name;
    m_Path              = path;
    m_Root              = new TypeRecordStruct( "root", this );
    m_Scene             = new TypeScene( *this, this );
    m_Context           = new TypeContext( Root(), Scene(), &Root(), this );
}

TypeDocument::~TypeDocument()
{
    // void
}

void TypeDocument::UpdateHtml()
{
    Controller().HtmlBuilder().Build( Root() );
    m_Html = Controller().HtmlBuilder().Html().join( "" );

    emit Controller().HtmlCodeChanged();
}

void TypeDocument::Clear()
{
    Context().SetRecords( Root() );
    Root().Clear();
    Scene().Clear();
    Html().clear();

    //
    // Controller().Clipboard().Clear();

    emit Controller().RecordsChanged();

    // UPDATE CONFIG FILE

    SetFileName( "" );
    SetPath( "" );

    emit Controller().DirectoryChanged();
}

int TypeDocument::SaveFile( QString file_name )
{
    QFile file( file_name );

    if( !file.open( QIODevice::WriteOnly ) )
    {
        qDebug() << "Failed to open file to write"
                 << file_name;
        // code
        return 1;
    }

    QDataStream out( &file );
    out << TypeRecordFactory::IdCount();
    out << TypeScene::IdCount();

    // GET RECORDS

    TypeStateReaderStream record_state( out );

    for( TypeVariant* variant : Root() )
    {
        TypeRecord* record = static_cast<TypeRecord*>( variant );

        if( !record->GetState( record_state ) )
        {
            qDebug() << "Failed at reading record state"
                     << file_name;
            // code
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
            qDebug() << "Failed at reading scene state"
                     << file_name;
            // code
            return 3;
        }

    }

    scene_state.Stop();

    SetFileName( QFileInfo( file_name ).fileName() );
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
        // code
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
        if( Root().CreateRecord( record_state, -1, &Root() ) == 0 )
        {
            qDebug() << "Failed at writing record state"
                     << file_name;
            // code
            return 2;
        }
    }

    // SET SCENE ITEMS

    TypeStateWriterStream scene_state( in );

    while( !scene_state.AtEnd() )
    {
        if( Scene().CreateItem( scene_state ) == 0 )
        {
            qDebug() << "Failed at writing scene state"
                     << file_name;
            // code
            return 3;
        }
    }

    emit Controller().RecordsChanged();

    SetFileName( QFileInfo( file_name ).fileName() );
    SetPath( QFileInfo( file_name ).canonicalPath() );

    return 0;
}

#define FIELD(__NAME)   "[$$$"+QString(__NAME)+"]"

int TypeDocument::SaveSQL( QString file_name )
{
    QFile::remove( file_name );
    Controller().Database().OpenDatabase( file_name );

    // SETUP TABLE

    QStringList row;
    row << FIELD( "ROW" ) << FIELD( "valueUE" );
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
    record_fields.append( FIELD( "valueUE" ) );
    record_fields.append( FIELD( "CLASS_NAME" ) );
    Controller().Database().CreateTable( FIELD( "RECORD_TABLE" ), record_fields );

    // FILL TABLE

    TypeStateReaderDatabase record_state( Controller().Database(), FIELD( "RECORD_TABLE" ), FIELD( "ROW" ) );

    for( TypeVariant* variant : Root() )
    {
        TypeRecord* record = static_cast<TypeRecord*>( variant );
        record->GetState( record_state );
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
        item->GetState( scene_state );

    row.clear();
    row << FIELD( "SCENEITEM_NUM" ) << QString::number( scene_state.Count()  );
    Controller().Database().AppendRecord( FIELD( "SETUP_TABLE" ), row );
    Controller().Database().CloseDatabase();

    SetFileName( QFileInfo( file_name ).fileName() );
    SetPath( QFileInfo( file_name ).canonicalPath() );

    return 0;
}

int TypeDocument::LoadSQL( QString file_name )
{
    Clear();
    Controller().Database().OpenDatabase( file_name );
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
        Root().CreateRecord( record_state, -1, &Root() );

    // SCENE ITEMS TABLE

    TypeStateWriterDatabase scene_state( Controller().Database(), FIELD( "SCENE_TABLE" ), FIELD( "ROW" ), scene_size );

    while( !scene_state.AtEnd() )
        Scene().CreateItem( scene_state );

    Controller().Database().CloseDatabase();
    emit Controller().RecordsChanged();

    SetFileName( QFileInfo( file_name ).fileName() );
    SetPath( QFileInfo( file_name ).canonicalPath() );

    return 0;
}

