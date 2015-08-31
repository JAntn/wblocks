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
#include "FW/RC/HTML/html_record.h"

#include "FW/RC/JS/js_bool_record.h"
#include "FW/RC/JS/js_integer_record.h"
#include "FW/RC/JS/js_real_record.h"
#include "FW/RC/JS/js_reference_record.h"
#include "FW/RC/JS/js_string_record.h"

///////////////////////////////////////////////////////////////////////
/// STATIC

QList<TypeRecordFactory*> TypeRecordStruct::m_FactoryList;

void TypeRecordStruct::InitFactoryList()
{
    if( m_FactoryList.empty() )
    {
        m_FactoryList.append( &TypeBoolRecordFactory::Instance() );
        m_FactoryList.append( &TypeIntegerRecordFactory::Instance() );
        m_FactoryList.append( &TypeRealRecordFactory::Instance() );
        m_FactoryList.append( &TypeStringRecordFactory::Instance() );
        m_FactoryList.append( &TypeScriptRecordFactory::Instance() );
        m_FactoryList.append( &TypeScriptFileRecordFactory::Instance() );
        m_FactoryList.append( &TypeStructRecordFactory::Instance() );
        m_FactoryList.append( &TypeReferenceRecordFactory::Instance() );
        m_FactoryList.append( &TypeFileRecordFactory::Instance() );
        m_FactoryList.append( &TypeHtmlRecordFactory::Instance() );

        m_FactoryList.append( &TypeJsBoolRecordFactory::Instance() );
        m_FactoryList.append( &TypeJsIntegerRecordFactory::Instance() );
        m_FactoryList.append( &TypeJsRealRecordFactory::Instance() );
        m_FactoryList.append( &TypeJsStringRecordFactory::Instance() );
        m_FactoryList.append( &TypeJsReferenceRecordFactory::Instance() );

        // Add more classes here or later
    }
}

const QList<TypeRecordFactory*>& TypeRecordStruct::FactoryList()
{
    return m_FactoryList;
}

TypeRecordFactory* TypeRecordStruct::FactoryFromName( QString class_name )
{
    for( TypeRecordFactory* record_factory : FactoryList() )
    {
        if( record_factory->RecordClass() == class_name )
            return record_factory;
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////
/// NON STATIC

TypeRecordStruct::TypeRecordStruct( QString name, TypeVariant* parent ):
    TypeVariantStruct( parent ),
    m_Name( name ),
    m_Flags( FLAG_ACTION_ALL )
{
    //void
}

TypeRecordStruct::~TypeRecordStruct()
{
    Clear();
}

QString TypeRecordStruct::FullName()
{
    if( Name() == "root" )
        return "";

    auto parent = this->Parent() ;
    return static_cast<TypeRecord*>( parent )->FullName();
}

TypeRecord* TypeRecordStruct::CreateRecord( TypeStateWriter& state, iterator position, TypeRecordStruct* root )
{
    TypeRecord*           record = 0;
    QString             class_name = state.Data().at( 3 );
    TypeRecordFactory*    record_factory = TypeRecordStruct::FactoryFromName( class_name );

    if( record_factory != 0 )
    {
        record = record_factory->CreateInstance( state, 0, root );
        Insert( position, *record );
    }

    return record;
}

TypeRecord* TypeRecordStruct::CreateRecord( TypeStateWriter& state, int position, TypeRecordStruct* root )
{
    TypeRecord*           record = 0;
    QString             class_name = state.Data()[3];
    TypeRecordFactory*    record_factory = TypeRecordStruct::FactoryFromName( class_name );

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

TypeRecord* TypeRecordStruct::CreateRecord( QString name, QString value, QString class_name, int position,
                                        TypeRecordStruct* root )
{
    TypeRecord* record = 0;
    TypeRecordFactory* record_factory = TypeRecordStruct::FactoryFromName( class_name );

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

TypeRecord* TypeRecordStruct::CreateRecord( QString name, QString value, QString class_name, iterator position,
                                        TypeRecordStruct* root )
{
    TypeRecord* record = 0;
    TypeRecordFactory* record_factory = TypeRecordStruct::FactoryFromName( class_name );

    if( record_factory != 0 )
    {
        record = record_factory->CreateInstance( name, value, 0, root );
        Insert( position, *record );
    }

    return record;
}

int TypeRecordStruct::GetIndex( TypeRecord* record_value ) const
{
    int count = 0;

    for( TypeVariant* variant : *this )
    {
        TypeRecord* record = static_cast<TypeRecord*>( variant );

        if( record == record_value )
            return count;

        ++count;
    }

    return -1;
}

TypeRecord* TypeRecordStruct::FromIndex( int index ) const
{
    auto iter = begin();

    for( int count = 0; count < index; ++count )
        ++iter;

    return static_cast<TypeRecord*>( *iter );
}

TypeRecord* TypeRecordStruct::FromName( QString name, bool deep ) const
{
    for( TypeVariant* variant : *this )
    {
        TypeRecord* record = static_cast<TypeRecord*>( variant );

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

TypeRecord* TypeRecordStruct::FromId( QString record_id , bool deep ) const
{
    for( TypeVariant* variant : *this )
    {
        TypeRecord* record = static_cast<TypeRecord*>( variant );

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

TypeRecord* TypeRecordStruct::FromFullName( QString full_name ) const
{
    QStringList tokens = full_name.split( "." );
    QString token_end = tokens.back();
    tokens.pop_back();
    TypeRecord* record;
    const TypeRecordStruct* record_struct = this;

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




