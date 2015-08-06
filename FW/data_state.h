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

    enum class stream_type {in, out};

                        C_DataState(stream_type stype, C_Variant* parent=0);

    virtual void        Next() = 0;
    virtual void        Insert(QStringList&)=0;
    virtual void        Extract(QStringList&)=0;
    virtual bool        AtEnd()=0;

    C_VALUE             (Data,       QStringList)
    C_VALUE             (StreamType, stream_type)

};

/////////////////////////////////////////////////////////////////////////////////

class C_DataStateTable : public C_DataState
{
public:

                        C_DataStateTable(QList<QStringList>& table, stream_type stype, C_Variant* parent=0);

    void                Next() override;
    void                Insert(QStringList& row) override;
    void                Extract(QStringList& row) override;
    bool                AtEnd() override;

    C_POINTER           (Table, QList<QStringList>)
    C_VALUE             (Iter,  QList<QStringList>::iterator)
};


/////////////////////////////////////////////////////////////////////////////////

class C_DataStateStream : public C_DataState
{
public:

                        C_DataStateStream(QDataStream& stream, stream_type stype, C_Variant* parent=0);

    void                Next() override;
    void                Insert(QStringList& row) override;
    void                Extract(QStringList& row) override;
    bool                AtEnd() override;
    void                Stop();

    C_POINTER           (DataStream, QDataStream)
};

/////////////////////////////////////////////////////////////////////////////////

class C_DataStateDatabase : public C_DataState
{
public:

                        C_DataStateDatabase(
                                C_Database& database,
                                QString table_name,
                                QString row_name,
                                long row_max,
                                stream_type stype,
                                C_Variant* parent=0);

    void                Next() override;
    void                Insert(QStringList& row) override;
    void                Extract(QStringList& row) override;
    bool                AtEnd() override;
    void                Stop();

    C_POINTER           (Database, C_Database)
    C_VALUE             (TableName, QString)
    C_VALUE             (RowName, QString)
    C_VALUE             (RowCount, long)
    C_VALUE             (RowMax, long)

};

#endif // C_DATA_STATE_H

