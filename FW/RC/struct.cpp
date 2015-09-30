#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/RC/record.h"
#include "FW/tools.h"


///////////////////////////////////////////////////////////////////////
/// NON STATIC

TypeStruct::TypeStruct(  TypeVariant* parent ):
    TypeVariantStruct( parent ),
    m_Flags( FLAG_ACTION_ALL )
{
    // void
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

TypeRecord* TypeStruct::NewRecord( TypeStateWriter& state, iterator position )
{
    TypeRecord*           record = 0;
    QString               class_name = state.Data().at( 3 );
    TypeRecordFactory*    record_factory = TypeController::FactoryFromName( class_name );

    if( record_factory != 0 )
    {
        record = record_factory->NewInstance( state, 0 );
        Insert( position, *record );
    }

    return record;
}

TypeRecord* TypeStruct::NewRecord( TypeStateWriter& state, int position )
{
    TypeRecord*           record = 0;
    QString               class_name = state.Data()[3];
    TypeRecordFactory*    record_factory = TypeController::FactoryFromName( class_name );

    if( record_factory != 0 )
    {
        record = record_factory->NewInstance( state, 0 );

        if( position >= 0 )
            Insert( position, *record );
        else
            Append( *record );
    }

    return record;
}

TypeRecord* TypeStruct::NewRecord( QString name, QString value, QString class_name, int position )
{
    TypeRecord* record = 0;
    TypeRecordFactory* record_factory = TypeController::FactoryFromName( class_name );

    if( record_factory != 0 )
    {
        record = record_factory->NewInstance( name, value, 0 );

        if( position >= 0 )
            Insert( position, *record );
        else
            Append( *record );
    }

    return record;
}

TypeRecord* TypeStruct::NewRecord( QString name, QString value, QString class_name, iterator position )
{
    TypeRecord* record = 0;
    TypeRecordFactory* record_factory = TypeController::FactoryFromName( class_name );

    if( record_factory != 0 )
    {
        record = record_factory->NewInstance( name, value, 0 );
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

    QStringList token_sequence = record_name.split( "_" );
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




