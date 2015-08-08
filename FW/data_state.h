#ifndef C_DATA_STATE_H
#define C_DATA_STATE_H

#include <QString>
#include <QStringList>

#include "FW/macro.h"
#include "FW/variant.h"

#include "database.h"


/////////////////////////////////////////////////////////////////////////////////

class C_DataState : public C_Variant
{
public:

    enum class StreamTypeEnum {IN, OUT};

    C_DataState( StreamTypeEnum stream_type, C_Variant* parent = 0 );
    ~C_DataState() override;

    virtual void        Next() = 0;
    virtual void        Append( QStringList& ) = 0;
    virtual void        Read( QStringList& ) = 0;
    virtual bool        AtEnd() = 0;

    C_VALUE             ( Data,       QStringList )
    C_VALUE             ( StreamType, StreamTypeEnum )

};

/////////////////////////////////////////////////////////////////////////////////

class C_DataStateTable : public C_DataState
{
public:

    C_DataStateTable(StreamTypeEnum stream_type, QList<QStringList>& table, long size = -1, long start = 0, C_Variant* parent = 0 );

    void                Next() override;
    void                Append( QStringList& row ) override;
    void                Read( QStringList& row ) override;
    bool                AtEnd() override;

    C_POINTER           ( Table, QList<QStringList> )
    C_VALUE             ( Iter,  QList<QStringList>::iterator )
    C_VALUE             ( Count, long )
    C_VALUE             ( Size, long )
};


/////////////////////////////////////////////////////////////////////////////////

class C_DataStateStream : public C_DataState
{
public:
    C_DataStateStream(StreamTypeEnum stream_type, QDataStream& stream, long size = -1, C_Variant* parent = 0 );

    void                Next() override;
    void                Append( QStringList& row ) override;
    void                Read( QStringList& row ) override;
    bool                AtEnd() override;

    C_POINTER           ( DataStream, QDataStream )
    C_VALUE             ( ByteFlag, bool )
    C_VALUE             ( Count, long )
    C_VALUE             ( Size, long )

    void                Stop();
};

/////////////////////////////////////////////////////////////////////////////////

class C_DataStateDatabase : public C_DataState
{
public:

    C_DataStateDatabase(StreamTypeEnum stream_type,
        C_Database& database,
        QString table_name,
        QString field,
        long size = -1, long start = 0,
        C_Variant* parent = 0 );

    void                Next() override;
    void                Append( QStringList& row ) override;
    void                Read( QStringList& row ) override;
    bool                AtEnd() override;

    C_POINTER           ( Database, C_Database )
    C_VALUE             ( TableName, QString )
    C_VALUE             ( Field, QString )
    C_VALUE             ( Count, long )
    C_VALUE             ( Size, long )
    C_VALUE             ( Start, long )

};

#endif // C_DATA_STATE_H

