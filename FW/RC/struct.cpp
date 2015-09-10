#include "FW/RC/struct_record.h"
#include "FW/RC/integer_record.h"
#include "FW/RC/struct.h"
#include "FW/RC/reference_record.h"
#include "FW/RC/real_record.h"
#include "FW/RC/JS/js_script_file_record.h"
#include "FW/RC/JS/js_script_record.h"
#include "FW/RC/PHP/php_file_record.h"
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

#include "FW/tools.h"

///////////////////////////////////////////////////////////////////////
/// STATIC

QList<TypeRecordFactory*> TypeStruct::m_FactoryList;

void TypeStruct::InitFactoryList()
{
    if( m_FactoryList.empty() )
    {
        m_FactoryList.append( &TypeBoolRecordFactory::Instance() );
        m_FactoryList.append( &TypeIntegerRecordFactory::Instance() );
        m_FactoryList.append( &TypeRealRecordFactory::Instance() );
        m_FactoryList.append( &TypeStringRecordFactory::Instance() );
        m_FactoryList.append( &TypeStructRecordFactory::Instance() );
        m_FactoryList.append( &TypeReferenceRecordFactory::Instance() );
        m_FactoryList.append( &TypeFileRecordFactory::Instance() );
        m_FactoryList.append( &TypeHtmlRecordFactory::Instance() );
        m_FactoryList.append( &TypePhpFileRecordFactory::Instance() );
        m_FactoryList.append( &TypeJsScriptRecordFactory::Instance() );
        m_FactoryList.append( &TypeJsScriptFileRecordFactory::Instance() );
        m_FactoryList.append( &TypeJsBoolRecordFactory::Instance() );
        m_FactoryList.append( &TypeJsIntegerRecordFactory::Instance() );
        m_FactoryList.append( &TypeJsRealRecordFactory::Instance() );
        m_FactoryList.append( &TypeJsStringRecordFactory::Instance() );
        m_FactoryList.append( &TypeJsReferenceRecordFactory::Instance() );

        // Add more classes here or later
    }
}

const QList<TypeRecordFactory*>& TypeStruct::FactoryList()
{
    return m_FactoryList;
}

TypeRecordFactory* TypeStruct::FactoryFromName( QString class_name )
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

TypeStruct::TypeStruct(  TypeVariant* parent ):
    TypeVariantStruct( parent ),
    m_Flags( FLAG_ACTION_ALL )
{
    //void
}

TypeStruct::~TypeStruct()
{
    Clear();
}

TypeRecord* TypeStruct::ParentRecord()
{
    return TypeVariantPtr<TypeRecord>( this->Parent() );
}

TypeStruct* TypeStruct::ParentStruct()
{
    TypeRecord* parent_record = this->ParentRecord();

    if( parent_record != 0 )
        return parent_record->ParentStruct();

    return 0;
}

TypeRecord* TypeStruct::NewRecord( TypeStateWriter& state, iterator position, TypeStruct* root )
{
    TypeRecord*           record = 0;
    QString               class_name = state.Data().at( 3 );
    TypeRecordFactory*    record_factory = TypeStruct::FactoryFromName( class_name );

    if( record_factory != 0 )
    {
        record = record_factory->NewInstance( state, 0, root );
        Insert( position, *record );
    }

    return record;
}

TypeRecord* TypeStruct::NewRecord( TypeStateWriter& state, int position, TypeStruct* root )
{
    TypeRecord*           record = 0;
    QString               class_name = state.Data()[3];
    TypeRecordFactory*    record_factory = TypeStruct::FactoryFromName( class_name );

    if( record_factory != 0 )
    {
        record = record_factory->NewInstance( state, 0, root );

        if( position >= 0 )
            Insert( position, *record );
        else
            Append( *record );
    }

    return record;
}

TypeRecord* TypeStruct::NewRecord( QString name, QString value, QString class_name, int position,
                                   TypeStruct* root )
{
    TypeRecord* record = 0;
    TypeRecordFactory* record_factory = TypeStruct::FactoryFromName( class_name );

    if( record_factory != 0 )
    {
        record = record_factory->NewInstance( name, value, 0, root );

        if( position >= 0 )
            Insert( position, *record );
        else
            Append( *record );
    }

    return record;
}

TypeRecord* TypeStruct::NewRecord( QString name, QString value, QString class_name, iterator position,
                                   TypeStruct* root )
{
    TypeRecord* record = 0;
    TypeRecordFactory* record_factory = TypeStruct::FactoryFromName( class_name );

    if( record_factory != 0 )
    {
        record = record_factory->NewInstance( name, value, 0, root );
        Insert( position, *record );
    }

    return record;
}

int TypeStruct::GetIndex( TypeRecord* record_value ) const
{
    int count = 0;

    for( TypeVariantPtr<TypeRecord> record : *this )
    {
        if( record == record_value )
            return count;

        ++count;
    }

    return -1;
}

TypeRecord* TypeStruct::FromIndex( int index ) const
{
    auto iter = begin();

    for( int count = 0; count < index; ++count )
        ++iter;

    return static_cast<TypeRecord*>( *iter );
}

TypeRecord* TypeStruct::FromId( QString record_id , bool deep ) const
{
    for( TypeVariantPtr<TypeRecord> record : *this )
    {
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

TypeRecord* TypeStruct::FromName( QString record_name, bool deep ) const
{
    if( !deep )
    {
        for( TypeVariantPtr<TypeRecord> record : *this )
        {
            if( record_name == record->Name() )
                return record;
        }

        return 0;
    }

    QStringList token_sequence = record_name.split( "." );
    const QString token_end = token_sequence.back();
    token_sequence.pop_back();
    TypeRecord* record = 0;
    const TypeStruct* record_struct = this;

    for( QString token : token_sequence )
    {
        record = record_struct->FromName( token, false );

        if( record == 0 )
            return 0;

        record_struct = record->Struct();

        if( record_struct == 0 )
            return 0;
    }

    return record_struct->FromName( token_end, false );
}




