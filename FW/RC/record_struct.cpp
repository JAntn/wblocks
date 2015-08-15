#include "FW/RC/struct_record.h"
#include "FW/RC/integer_record.h"
#include "FW/RC/record_struct.h"
#include "FW/RC/reference_record.h"
#include "FW/RC/real_record.h"
#include "FW/RC/script_record.h"
#include "FW/RC/string_record.h"
#include "FW/RC/bool_record.h"
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"

///////////////////////////////////////////////////////////////////////
/// STATIC

list<C_RecordFactory*> C_RecordStruct::m_FactoryList;

void C_RecordStruct::InitFactoryList()
{
    if( m_FactoryList.empty() )
    {
        m_FactoryList.push_back( &C_BoolRecordFactory::Instance() );
        m_FactoryList.push_back( &C_IntegerRecordFactory::Instance() );
        m_FactoryList.push_back( &C_RealRecordFactory::Instance() );
        m_FactoryList.push_back( &C_StringRecordFactory::Instance() );
        m_FactoryList.push_back( &C_ScriptRecordFactory::Instance() );
        m_FactoryList.push_back( &C_StructRecordFactory::Instance() );
        m_FactoryList.push_back( &C_ReferenceRecordFactory::Instance() );
        // Add more classes here or later
    }
}

const list<C_RecordFactory*>& C_RecordStruct::FactoryList()
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
    m_Name( name ), m_Flags( FLAG_ACTION_ALL )
{
    //void
}

C_RecordStruct::~C_RecordStruct()
{
    Clear();
}

C_Record* C_RecordStruct::CreateRecord(C_StateWriter &state, const_iterator position )
{
    C_Record*           record = 0;
    QString             class_name = state.Data().at( 3 );
    C_RecordFactory*    record_factory = C_RecordStruct::FactoryFromName( class_name );

    if( record_factory != 0 )
    {
        record = record_factory->CreateInstance( state );
        Insert( position, *record );
    }

    return record;
}

C_Record* C_RecordStruct::CreateRecord( C_StateWriter& state, int position )
{
    C_Record*           record = 0;
    QString             class_name = state.Data().at( 3 );
    C_RecordFactory*    record_factory = C_RecordStruct::FactoryFromName( class_name );

    if( record_factory != 0 )
    {
        record = record_factory->CreateInstance( state );

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
    int position )
{
    C_Record* record = 0;
    C_RecordFactory* record_factory = C_RecordStruct::FactoryFromName( class_name );

    if( record_factory != 0 )
    {
        record = record_factory->CreateInstance( name, value );

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
    const_iterator position )
{
    C_Record* record = 0;
    C_RecordFactory* record_factory = C_RecordStruct::FactoryFromName( class_name );

    if( record_factory != 0 )
    {
        record = record_factory->CreateInstance( name, value );
        Insert( position, *record );
    }

    return record;
}

int C_RecordStruct::GetIndex( C_Record* record_value ) const
{
    int count = 0;

    for( C_Variant* node : *this )
    {
        auto record = static_cast<C_Record*>( node );

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
    for( C_Variant* node : *this )
    {
        auto record = static_cast<C_Record*>( node );

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
    for( C_Variant* node : *this )
    {
        auto record = static_cast<C_Record*>( node );

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





