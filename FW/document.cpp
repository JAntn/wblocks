#include "FW/RC/struct_record.h"
#include "FW/RC/record.h"
#include "FW/SC/scene.h"
#include "FW/database.h"
#include "FW/document.h"
#include "FW/htmlbuilder.h"
#include "FW/clipboard.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_file_explorer.h"
#include "FW/RC/script_file_record.h"
#include "FW/config.h"
#include <QMessageBox>
#include <QStack>
#include <QDebug>
#include <QFileInfo>
#include <QDir>

///////////////////////////////////////////////////////////////////////////////////////////////
/// STATIC

QString C_Document::LoadTextFile( QString file_name )
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

///////////////////////////////////////////////////////////////////////////////////////////////
/// NON STATIC

C_Document::C_Document( QString file_name, QString path, C_UiMainWindow& main_window, C_Variant* parent ):
    C_Variant( parent ),
    m_MainWindow( &main_window )
{
    C_RecordStruct::InitFactoryList();

    m_FileName          = file_name;
    m_Path              = path;
    m_Root              = new C_RecordStruct( "root", this );
    m_Scene             = new C_Scene( *this, this );
    m_Context           = new C_Context( Root(), Scene(), this );
    m_HtmlBuilder       = new C_HtmlBuilder( this );
    m_Database          = new C_Database( this );
    m_Clipboard         = new C_Clipboard( this );
    m_Events            = new C_Events( *this, main_window );
}

C_Document::~C_Document()
{
    // void
}


void C_Document::UpdateHtml()
{
    HtmlBuilder().Build( Root() );
    m_Html = HtmlBuilder().Html().join( "" );

    emit Events().HtmlCodeChanged();
}

void C_Document::Clear()
{
    Context().SetRecords( Root() );
    Root().Clear();
    Scene().Clear();
    Clipboard().Clear();
    Html().clear();

    emit Events().RecordsChanged();

    // UPDATE CONFIG FILE

    SetFileName( "" );
    SetPath( "" );
    MainWindow().Config().SetProjectFileName( "" );
    MainWindow().Config().SetProjectPath( "" );
    QDir().setCurrent( "" );

    emit Events().DirectoryChanged();

    MainWindow().SetTitle( MainWindow().Config().ProjectFileName() );
}

void C_Document::SaveFile( QFile& file )
{
    file.open( QIODevice::WriteOnly );
    QDataStream out( &file );
    out << C_RecordFactory::IdCount();
    out << C_Scene::IdCount();

    // GET RECORDS

    C_StateReaderStream record_state( out );

    for( C_Variant* variant : Root() )
    {
        C_Record* record = static_cast<C_Record*>( variant );
        record->GetState( record_state );
    }

    record_state.Stop();

    // GET SCENE ITEMS

    C_StateReaderStream scene_state( out );

    for( C_SceneItem* item : Scene().Items() )
        item->GetState( scene_state );

    scene_state.Stop();
    file.close();

    // UPDATE CONFIG FILE

    SetFileName( QFileInfo( file ).fileName() );
    SetPath( QFileInfo( file ).canonicalPath() );
    MainWindow().Config().SetProjectFileName( FileName() );
    MainWindow().Config().SetProjectPath( Path() );
    QDir().setCurrent( MainWindow().Config().ProjectPath() );

    emit Events().DirectoryChanged();

    MainWindow().SetTitle( MainWindow().Config().ProjectFileName() );
}

void C_Document::LoadFile( QFile& file )
{
    Clear();

    file.open( QIODevice::ReadOnly );
    QDataStream in( &file );
    QString value;
    in >> value;
    C_RecordFactory::m_IdCount = value.toLong();
    in >> value;
    C_Scene::m_IdCount = value.toLong();

    // SET RECORDS

    C_StateWriterStream record_state( in );

    while( !record_state.AtEnd() )
        Root().CreateRecord( record_state, -1, &Root() );

    // SET SCENE ITEMS

    C_StateWriterStream scene_state( in );

    while( !scene_state.AtEnd() )
        Scene().CreateItem( scene_state );

    emit Events().RecordsChanged();

    file.close();

    // UPDATE CONFIG FILE

    SetFileName( QFileInfo( file ).fileName() );
    SetPath( QFileInfo( file ).canonicalPath() );
    MainWindow().Config().SetProjectFileName( FileName() );
    MainWindow().Config().SetProjectPath( Path() );
    QDir().setCurrent( MainWindow().Config().ProjectPath() );

    emit Events().DirectoryChanged();

    MainWindow().SetTitle( MainWindow().Config().ProjectFileName() );
}

#define FIELD(__NAME)   "[$$$"+QString(__NAME)+"]"

void C_Document::SaveSQL( QString file_name )
{
    QFile::remove( file_name );
    Database().OpenDatabase( file_name );

    // SETUP TABLE

    QStringList row;
    row << FIELD( "ROW" ) << FIELD( "valueUE" );
    Database().CreateTable( FIELD( "SETUP_TABLE" ), row );

    // FILL SETUP TABLE

    row.clear();
    row << FIELD( "RECORD_ID_COUNT" ) << C_RecordFactory::IdCount();
    Database().AppendRecord( FIELD( "SETUP_TABLE" ), row );
    row.clear();
    row << FIELD( "SCENE_ID_COUNT" ) << C_Scene::IdCount();
    Database().AppendRecord( FIELD( "SETUP_TABLE" ), row );

    // RECORD TABLE

    QStringList record_fields;
    record_fields.append( FIELD( "ROW" ) );
    record_fields.append( FIELD( "ID" ) );
    record_fields.append( FIELD( "NAME" ) );
    record_fields.append( FIELD( "valueUE" ) );
    record_fields.append( FIELD( "CLASS_NAME" ) );
    Database().CreateTable( FIELD( "RECORD_TABLE" ), record_fields );

    // FILL TABLE

    C_StateReaderDatabase record_state( Database(), FIELD( "RECORD_TABLE" ), FIELD( "ROW" ) );

    for( C_Variant* variant : Root() )
    {
        C_Record* record = static_cast<C_Record*>( variant );
        record->GetState( record_state );
    }

    row.clear();
    row << FIELD( "RECORD_NUM" ) << QString::number( record_state.Count() );
    Database().AppendRecord( FIELD( "SETUP_TABLE" ), row );

    // SCENE ITEMS TABLE

    QStringList scene_fields;
    scene_fields.append( FIELD( "ROW" ) );
    scene_fields.append( FIELD( "ID" ) );
    scene_fields.append( FIELD( "RECORD_ID" ) );
    scene_fields.append( FIELD( "X" ) );
    scene_fields.append( FIELD( "Y" ) );
    scene_fields.append( FIELD( "Z" ) );
    Database().CreateTable( FIELD( "SCENE_TABLE" ), scene_fields );
    C_StateReaderDatabase scene_state( Database(), FIELD( "SCENE_TABLE" ), FIELD( "ROW" ) );

    for( C_SceneItem* item : Scene().Items() )
        item->GetState( scene_state );

    row.clear();
    row << FIELD( "SCENEITEM_NUM" ) << QString::number( scene_state.Count()  );
    Database().AppendRecord( FIELD( "SETUP_TABLE" ), row );
    Database().CloseDatabase();
}

void C_Document::LoadSQL( QString file_name )
{
    Clear();
    Database().OpenDatabase( file_name );
    QStringList row;
    row = Database().GetRecord( FIELD( "SETUP_TABLE" ), FIELD( "ROW" ), FIELD( "RECORD_ID_COUNT" ) );
    C_RecordFactory::m_IdCount = row[1].toLong();
    row = Database().GetRecord( FIELD( "SETUP_TABLE" ), FIELD( "ROW" ), FIELD( "SCENE_ID_COUNT" ) );
    C_Scene::m_IdCount = row[1].toLong();
    row = Database().GetRecord( FIELD( "SETUP_TABLE" ), FIELD( "ROW" ), FIELD( "RECORD_NUM" ) );
    long record_size = row[1].toLong();
    row = Database().GetRecord( FIELD( "SETUP_TABLE" ), FIELD( "ROW" ), FIELD( "SCENEITEM_NUM" ) );
    long scene_size = row[1].toLong();

    // RECORDS TABLE

    C_StateWriterDatabase record_state( Database(), FIELD( "RECORD_TABLE" ), FIELD( "ROW" ), record_size );

    while( !record_state.AtEnd() )
        Root().CreateRecord( record_state, -1, &Root() );

    // SCENE ITEMS TABLE

    C_StateWriterDatabase scene_state( Database(), FIELD( "SCENE_TABLE" ), FIELD( "ROW" ), scene_size );

    while( !scene_state.AtEnd() )
        Scene().CreateItem( scene_state );

    Database().CloseDatabase();
    emit Events().RecordsChanged();
}

