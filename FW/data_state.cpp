#include "FW/data_state.h"
#include <QStringList>
#include <QDataStream>


C_DataState::C_DataState( StreamTypeEnum  stream_type, C_Variant* parent )
    : C_Variant( parent ), m_StreamType(  stream_type )
{
    // void
}

C_DataState::~C_DataState()
{
    // void
}

C_DataStateStream::C_DataStateStream( StreamTypeEnum  stream_type, QDataStream& stream, long size, C_Variant* parent )
    : C_DataState(  stream_type, parent )
{
    SetDataStream( stream );
    SetSize( size );
    SetCount( 0 );
    SetByteFlag( false );
}

bool C_DataStateStream::AtEnd()
{
    return ByteFlag() || !( Count() < Size() || Size() < 0 );
}


void C_DataStateStream::Next()
{
    if( StreamType() == StreamTypeEnum::IN )
    {
        if( !AtEnd() )
            DataStream() >> ByteFlag();

        if( !AtEnd() )
        {
            DataStream() >> Data();
            ++Count();
        }
        else
            Data().clear();
    }
}

void C_DataStateStream::Read( QStringList& row )
{
    if( StreamType() == StreamTypeEnum::IN )
    {
        row = Data();

        if( !AtEnd() )
            DataStream() >> ByteFlag();

        if( !AtEnd() )
        {
            DataStream() >> Data();
            ++Count();
        }
        else
            Data().clear();
    }
}

void C_DataStateStream::Append( QStringList& row )
{
    if( StreamType() == StreamTypeEnum::OUT )
    {
        if( !AtEnd() )
        {
            DataStream() << ByteFlag();
            DataStream() << row;
            ++Count();
        }
    }
}

void C_DataStateStream::Stop()
{
    if( StreamType() == StreamTypeEnum::OUT )
    {
        SetByteFlag( true );
        DataStream() << ByteFlag();
    }
}

C_DataStateTable::C_DataStateTable( StreamTypeEnum  stream_type, QList<QStringList>& table, long size, long start, C_Variant* parent )
    : C_DataState(  stream_type, parent )
{
    SetTable( table );
    SetCount( 0 );
    SetSize( size );

    if( StreamType() == StreamTypeEnum::IN )
    {
        SetIter( table.begin() );

        for( long n = 0; n < start; ++n )
            ++Iter();

        if( Size() < 0 )
            SetSize( table.size() - start );
    }
    else
    {
        SetIter( table.begin() );

        for( long n = 0; n < start; ++n )
            ++Iter();
    }
}

void C_DataStateTable::Next()
{
    if( StreamType() == StreamTypeEnum::IN )
    {
        if( !AtEnd() )
        {
            SetData( *Iter() );
            ++Iter();
            ++Count();
        }
        else
            Data().clear();
    }
}

void C_DataStateTable::Read( QStringList& row )
{
    if( StreamType() == StreamTypeEnum::IN )
    {
        row = Data();

        if( !AtEnd() )
        {
            SetData( *Iter() );
            ++Iter();
            ++Count();
        }
        else
            Data().clear();
    }
}

bool C_DataStateTable::AtEnd()
{
    return !( Count() < Size() || Size() < 0 ) ;
}

void C_DataStateTable::Append( QStringList& row )
{
    if( StreamType() == StreamTypeEnum::OUT )
    {
        if( !AtEnd() )
        {
            Table().insert( Iter(), row );
            ++Count();
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////

C_DataStateDatabase::C_DataStateDatabase(
    C_DataState::StreamTypeEnum  stream_type,
    C_Database& database,
    QString table_name,
    QString field,
    long size, long start,
    C_Variant* parent ):
    C_DataState(  stream_type, parent )
{
    SetDatabase( database );
    SetTableName( table_name );
    SetField( field );
    SetCount( 0 );
    SetSize( size );
    SetStart( 0 );
}

void C_DataStateDatabase::Next()
{
    if( StreamType() == StreamTypeEnum::IN )
    {
        if( !AtEnd() )
        {
            QStringList tmp = Database().GetRecord( TableName(), Field(), QString::number( Count() + Start() ) );
            tmp.pop_front();
            SetData( tmp );
            ++Count();
        }
        else
            Data().clear();
    }
}

void C_DataStateDatabase::Append( QStringList& row )
{
    if( StreamType() == StreamTypeEnum::OUT )
    {
        if( !AtEnd() )
        {
            QStringList tmp = row;
            tmp.push_front( QString::number( Count() + Start() ) );
            Database().AppendRecord( TableName(), tmp );
            ++Count();
        }
    }
}

void C_DataStateDatabase::Read( QStringList& row )
{
    if( StreamType() == StreamTypeEnum::IN )
    {
        row = Data();

        if( !AtEnd() )
        {
            QStringList tmp = Database().GetRecord( TableName(), Field(), QString::number( Count() + Start() ) );
            tmp.pop_front();
            SetData( tmp );
            ++Count();
        }
        else
            Data().clear();
    }
}

bool C_DataStateDatabase::AtEnd()
{
    return !( Count() < Size() || Size() < 0 ) ;
}
