#include "FW/RC/struct_record.h"
#include "FW/RC/integer_record.h"
#include "FW/RC/record_struct.h"
#include "FW/RC/reference_record.h"
#include "FW/RC/real_record.h"
#include "FW/RC/script_file_record.h"
#include "FW/RC/script_record.h"
#include "FW/RC/string_record.h"
#include "FW/RC/bool_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/RC/file_record.h"
#include "FW/RC/html_record.h"

///////////////////////////////////////////////////////////////////////
/// STATIC

QList<C_RecordFactory*> C_RecordStruct::m_FactoryList;

void C_RecordStruct::InitFactoryList()
{
    if( m_FactoryList.empty() )
    {
        m_FactoryList.append( &C_BoolRecordFactory::Instance() );
        m_FactoryList.append( &C_IntegerRecordFactory::Instance() );
        m_FactoryList.append( &C_RealRecordFactory::Instance() );
        m_FactoryList.append( &C_StringRecordFactory::Instance() );
        m_FactoryList.append( &C_ScriptRecordFactory::Instance() );
        m_FactoryList.append( &C_ScriptFileRecordFactory::Instance() );
        m_FactoryList.append( &C_StructRecordFactory::Instance() );
        m_FactoryList.append( &C_ReferenceRecordFactory::Instance() );
        m_FactoryList.append( &C_FileRecordFactory::Instance() );
        m_FactoryList.append( &C_HtmlRecordFactory::Instance() );

        // Add more classes here or later
    }
}

QString C_RecordStruct::FullName()
{
    if( Name() == "root" )
        return "";

    auto parent = this->Parent() ;
    return static_cast<C_Record*>( parent )->FullName();
}

const QList<C_RecordFactory*>& C_RecordStruct::FactoryList()
{
    return m_FactoryList;
}

C_RecordFactory* C_RecordStruct::FactoryFromName( QString class_name )
{
    for( C_RecordFactory* record_factory : FactoryList() )
    {
        if( record_factory->RecordClass() == class_name )
            return record_factory;
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////
/// NON STATIC

C_RecordStruct::C_RecordStruct( QString name, C_Variant* parent ):
    C_VariantStruct( parent ),
    m_Name( name ),
    m_Flags( FLAG_ACTION_ALL )
{
    //void
}

C_RecordStruct::~C_RecordStruct()
{
    Clear();
}

C_Record* C_RecordStruct::CreateRecord( C_StateWriter& state, iterator position, C_RecordStruct* root )
{
    C_Record*           record = 0;
    QString             class_name = state.Data().at( 3 );
    C_RecordFactory*    record_factory = C_RecordStruct::FactoryFromName( class_name );

    if( record_factory != 0 )
    {
        record = record_factory->CreateInstance( state, 0, root );
        Insert( position, *record );
    }

    return record;
}

C_Record* C_RecordStruct::CreateRecord( C_StateWriter& state, int position, C_RecordStruct* root )
{
    C_Record*           record = 0;
    QString             class_name = state.Data().at( 3 );
    C_RecordFactory*    record_factory = C_RecordStruct::FactoryFromName( class_name );

    if( record_factory != 0 )
    {
        record = record_factory->CreateInstance( state, 0, root );

        if( position > 0 )
            Insert( position, *record );
        else
            Append( *record );
    }

    return record;
}

C_Record* C_RecordStruct::CreateRecord(
    QString name,
    QString value,
    QString class_name,
    int position,
    C_RecordStruct* root )
{
    C_Record* record = 0;
    C_RecordFactory* record_factory = C_RecordStruct::FactoryFromName( class_name );

    if( record_factory != 0 )
    {
        record = record_factory->CreateInstance( name, value, 0, root );

        if( position > 0 )
            Insert( position, *record );
        else
            Append( *record );
    }

    return record;
}

C_Record* C_RecordStruct::CreateRecord(
    QString name,
    QString value,
    QString class_name,
    iterator position,
    C_RecordStruct* root )
{
    C_Record* record = 0;
    C_RecordFactory* record_factory = C_RecordStruct::FactoryFromName( class_name );

    if( record_factory != 0 )
    {
        record = record_factory->CreateInstance( name, value, 0, root );
        Insert( position, *record );
    }

    return record;
}

int C_RecordStruct::GetIndex( C_Record* record_value ) const
{
    int count = 0;

    for( C_Variant* variant : *this )
    {
        C_Record* record = static_cast<C_Record*>( variant );

        if( record == record_value )
            return count;

        ++count;
    }

    return -1;
}

C_Record* C_RecordStruct::FromIndex( int index ) const
{
    auto iter = begin();

    for( int count = 0; count < index; ++count )
        ++iter;

    return static_cast<C_Record*>( *iter );
}

C_Record* C_RecordStruct::FromName( QString name, bool deep ) const
{
    for( C_Variant* variant : *this )
    {
        C_Record* record = static_cast<C_Record*>( variant );

        if( record->Name() == name )
            return record;

        if( deep )
        {
            auto record_struct = record->Struct();

            if( record_struct != 0 )
            {
                record = record_struct->FromName( name, deep );

                if( record != 0 )
                    return record;
            }
        }
    }

    return 0;
}

C_Record* C_RecordStruct::FromId( QString record_id , bool deep ) const
{
    for( C_Variant* variant : *this )
    {
        C_Record* record = static_cast<C_Record*>( variant );

        if( record->Id() == record_id )
            return record;

        if( deep )
        {
            auto record_struct = record->Struct();

            if( record_struct != 0 )
            {
                record = record_struct->FromId( record_id, deep );

                if( record != 0 )
                    return record;
            }
        }
    }

    return 0;
}

C_Record* C_RecordStruct::FromFullName( QString full_name ) const
{
    QStringList tokens = full_name.split( "." );
    QString token_end = tokens.back();
    tokens.pop_back();
    C_Record* record;
    const C_RecordStruct* record_struct = this;

    for( QString token : tokens )
    {
        record = record_struct->FromName( token );

        if( record == 0 )
            return 0;

        record_struct = record->Struct();

        if( record_struct == 0 )
            return 0;
    }

    return record_struct->FromName( token_end );
}




