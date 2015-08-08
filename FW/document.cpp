#include "FW/RC/struct_record.h"
#include "FW/RC/record.h"
#include "FW/SC/scene.h"
#include "FW/database.h"
#include "FW/document.h"
#include "data_state.h"

#include "FW/UI/ui_main_window.h"
#include <QMessageBox>
#include <QStack>
#include <QDebug>
#include <FW/RC/script_record.h>

QString C_Document::LoadTextFile( QString file_name )
{
    QFile file( file_name );

    if( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        file.close();
        return QString();
    }

    auto text = file.readAll();
    file.close();
    return text;
}

void C_Document::SaveTextFile( QString file_name, QString text )
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

C_Document::C_Document( C_UiMainWindow& main_window, C_Variant* parent ):
    C_Variant( parent ),
    m_MainWindow( &main_window )
{
    C_RecordStruct::InitFactoryList();
    m_Records           = new C_RecordStruct( "root", this );
    m_Scene             = new C_Scene( *this, this );
    m_Context           = new C_Context( Records(), Scene(), this );
    m_Script            = new C_Script( *this, this );
    m_Database          = new C_Database( this );
    m_Signals           = new C_Signals( *this, main_window, &main_window );

    auto record1 = Records().CreateRecord( "SampleString", "Monday", "String" );
    Scene().CreateItem( *record1 );

    auto record2 = Records().CreateRecord( "SampleScript", "", "Script" );
    Scene().CreateItem( *record2 );
    static_cast<C_ScriptRecord*> (record2)
            ->Struct()
            ->FromName("Code")
            ->SetValue(
                "document.write(SampleString)"
                );


    Script().Generate( Records() );
    SetPaintFlag( true );
    emit Signals().RecordsChanged();
    emit Signals().SceneChanged();
    emit Signals().ScriptChanged();
}

C_Document::~C_Document()
{
    // void
}

void C_Document::UpdateScript()
{
    Script().Generate( Records() );
}

void C_Document::UpdateScene()
{
    emit Signals().SceneChanged();
}

C_Record* RECORD_AT_ID( C_RecordStruct* record_struct, QString* id )
{
    for( auto val : *record_struct )
    {
        auto record = static_cast<C_Record*> ( val );

        if( record->Id() == *id )
            return record;

        if( record->Struct() != 0 )
        {
            record = RECORD_AT_ID( record->Struct(), id );

            if( record != 0 )
                return record;
        }
    }

    return 0;
}

C_Record* C_Document::RecordAtId( QString id )
{
    return RECORD_AT_ID( &Records(), &id );
}

C_Record* RECORD_AT_NAME( C_RecordStruct* record_struct, QString* name )
{
    for( auto val : *record_struct )
    {
        auto record = static_cast<C_Record*> ( val );

        if( record->Name() == *name )
            return record;

        if( record->Struct() != 0 )
        {
            record = RECORD_AT_ID( record->Struct(), name );

            if( record != 0 )
                return record;
        }
    }

    return 0;
}

C_Record* C_Document::RecordAtName( QString name )
{
    return RECORD_AT_NAME( &Records(), &name );
}

void C_Document::Clear()
{
    Context().SetRecords( Records() );
    Records().Clear();
    Scene().Clear();

    emit Signals().RecordsChanged();
}

bool C_Document::AcceptMessage( QString msg )
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

void C_Document::Message( QString msg )
{
    QMessageBox msgBox;
    msgBox.setText( msg );
    msgBox.exec();
}

void C_Document::FileSave( QFile& file )
{
    file.open( QIODevice::WriteOnly );
    QDataStream out( &file );
    out << C_RecordFactory::IdCount();
    out << C_Scene::IdCount();

    // GET RECORDS

    C_DataStateStream record_state( C_DataState::StreamTypeEnum::OUT, out );
    record_state.Next();

    for( C_Variant* node : Records() )
    {
        auto record = static_cast<C_Record*>( node );
        record->GetState( record_state );
    }

    record_state.Stop();

    // GET SCENE ITEMS

    C_DataStateStream scene_state( C_DataState::StreamTypeEnum::OUT, out );
    scene_state.Next();

    for( C_SceneItem* item : Scene().Items() )
        item->GetState( scene_state );

    scene_state.Stop();

    file.close();
}

void C_Document::FileLoad( QFile& file )
{
    Clear();
    file.open( QIODevice::ReadOnly );
    QDataStream in( &file );
    QString val;
    in >> val;
    C_RecordFactory::m_IdCount = val.toLong();
    in >> val;
    C_Scene::m_IdCount = val.toLong();

    // SET RECORDS

    C_DataStateStream record_state( C_DataState::StreamTypeEnum::IN, in );
    record_state.Next();

    while( !record_state.AtEnd() )
        Records().CreateRecord( record_state );

    // SET SCENE ITEMS

    C_DataStateStream scene_state( C_DataState::StreamTypeEnum::IN, in );
    scene_state.Next();

    while( !scene_state.AtEnd() )
        Scene().CreateItem( scene_state );

    emit Signals().RecordsChanged();
    file.close();
}

#define FIELD(__NAME)   "[$$$"+QString(__NAME)+"]"

void C_Document::DatabaseSave( QString file_name )
{
    QFile::remove( file_name );
    Database().OpenDatabase( file_name );

    // SETUP TABLE

    QStringList row;
    row << FIELD( "ROW" ) << FIELD( "VALUE" );
    Database().CreateTable( FIELD( "SETUP_TABLE" ), row );
    row.clear();

    // FILL SETUP TABLE

    row << FIELD( "RECORD_ID_COUNT" ) << C_RecordFactory::IdCount();
    Database().AppendRecord( FIELD( "SETUP_TABLE" ), row );
    row.clear();
    row << FIELD( "SCENE_ID_COUNT" ) << C_Scene::IdCount();
    Database().AppendRecord( FIELD( "SETUP_TABLE" ), row );
    row.clear();

    // RECORD TABLE

    QStringList record_fields;
    record_fields.append( FIELD( "ROW" ) );
    record_fields.append( FIELD( "ID" ) );
    record_fields.append( FIELD( "NAME" ) );
    record_fields.append( FIELD( "VALUE" ) );
    record_fields.append( FIELD( "CLASS_NAME" ) );
    Database().CreateTable( FIELD( "RECORD_TABLE" ), record_fields );

    // FILL TABLE

    C_DataStateDatabase record_state( C_DataState::StreamTypeEnum::OUT, Database(), FIELD( "RECORD_TABLE" ), FIELD( "ROW" ) );
    record_state.Next();

    for( C_Variant* node : Records() )
    {
        C_Record* record = static_cast<C_Record*>( node );
        record->GetState( record_state );
    }

    row << FIELD( "RECORD_NUM" ) << QString::number( record_state.Size() );
    Database().AppendRecord( FIELD( "SETUP_TABLE" ), row );
    row.clear();

    // SCENE ITEMS TABLE

    QStringList scene_fields;
    scene_fields.append( FIELD( "ROW" ) );
    scene_fields.append( FIELD( "ID" ) );
    scene_fields.append( FIELD( "RECORD_ID" ) );
    scene_fields.append( FIELD( "X" ) );
    scene_fields.append( FIELD( "Y" ) );
    scene_fields.append( FIELD( "Z" ) );
    Database().CreateTable( FIELD( "SCENE_TABLE" ), scene_fields );
    C_DataStateDatabase scene_state( C_DataState::StreamTypeEnum::OUT, Database(), FIELD( "SCENE_TABLE" ), FIELD( "ROW" ) );
    scene_state.Next();

    for( C_SceneItem* item : Scene().Items() )
        item->GetState( scene_state );

    row.clear();
    row << FIELD( "SCENEITEM_NUM" ) << QString::number( scene_state.Size()  );
    Database().AppendRecord( FIELD( "SETUP_TABLE" ), row );
    Database().CloseDatabase();
}

void C_Document::DatabaseLoad( QString file_name )
{
    Clear();
    Database().OpenDatabase( file_name );
    QStringList row;
    row = Database().GetRecord( FIELD( "SETUP_TABLE" ), FIELD( "ROW" ), FIELD( "RECORD_ID_COUNT" ) );
    C_RecordFactory::m_IdCount = row.at( 1 ).toLong();
    row = Database().GetRecord( FIELD( "SETUP_TABLE" ), FIELD( "ROW" ), FIELD( "SCENE_ID_COUNT" ) );
    C_Scene::m_IdCount = row.at( 1 ).toLong();
    row = Database().GetRecord( FIELD( "SETUP_TABLE" ), FIELD( "ROW" ), FIELD( "RECORD_NUM" ) );
    long record_size = row.at( 1 ).toLong();
    row = Database().GetRecord( FIELD( "SETUP_TABLE" ), FIELD( "ROW" ), FIELD( "SCENEITEM_NUM" ) );
    long scene_size = row.at( 1 ).toLong();

    // RECORDS TABLE

    C_DataStateDatabase record_state( C_DataState::StreamTypeEnum::IN, Database(), FIELD( "RECORD_TABLE" ), FIELD( "ROW" ), record_size );
    record_state.Next();

    while( !record_state.AtEnd() )
        Records().CreateRecord( record_state );

    // SCENE ITEMS TABLE

    C_DataStateDatabase scene_state( C_DataState::StreamTypeEnum::IN, Database(), FIELD( "SCENE_TABLE" ), FIELD( "ROW" ), scene_size );
    scene_state.Next();

    while( !scene_state.AtEnd() )
        Scene().CreateItem( scene_state );

    Database().CloseDatabase();
    emit Signals().RecordsChanged();
    emit Signals().SceneChanged();
}

