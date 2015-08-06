#include "FW/data_state.h"
#include <QStringList>
#include <QDataStream>

/////////////////////////////////////////////////////////////////////////////////

C_DataState::C_DataState(stream_type stype, C_Variant* parent)
: C_Variant(parent), m_StreamType(stype)
{
    // void
}

/////////////////////////////////////////////////////////////////////////////////

C_DataStateStream::C_DataStateStream(QDataStream& stream, stream_type stype, C_Variant* parent)
    : C_DataState(stype,parent)
{
    m_DataStream = &stream;

    QStringList val;
    val << "ID_BEGIN";

    SetData(val);
}

void C_DataStateStream::Next()
{
    if( StreamType() == stream_type::in )
    {
        if( !AtEnd() )
        {
            DataStream() >> Data();
        }
    }
}

void C_DataStateStream::Extract(QStringList& row)
{
    if( StreamType()== stream_type::in )
    {
        row = Data();

        if( !AtEnd() )
        {
            DataStream() >> Data();
        }
    }
}

void C_DataStateStream::Insert(QStringList& row)
{
    if( StreamType()== stream_type::out )
    {
        DataStream() << row;
    }
}


bool C_DataStateStream::AtEnd()
{
    return (Data().at(0) == "ID_END");
}

void C_DataStateStream::Stop()
{
    if( StreamType()== stream_type::out )
    {
        DataStream() << (QStringList() << "ID_END");
    }
}


/////////////////////////////////////////////////////////////////////////////////

C_DataStateTable::C_DataStateTable(QList<QStringList>& table, stream_type stype, C_Variant* parent)
    : C_DataState(stype, parent)
{
    m_Table = &table;
    m_Iter = m_Table->begin();
}

void C_DataStateTable::Next()
{
    if( StreamType() == stream_type::in )
    {
        if( !AtEnd() ) {
            SetData(*m_Iter);
            ++m_Iter;
        }
    }
}

void C_DataStateTable::Extract(QStringList& row)
{
    if( StreamType() == stream_type::in )
    {
        row = Data();

        if( !AtEnd() ) {
            SetData(*m_Iter);
            ++m_Iter;
        }else{
            Data().clear();
        }
    }
}

bool C_DataStateTable::AtEnd()
{
    return m_Iter != m_Table->end();
}

void C_DataStateTable::Insert(QStringList& row)
{
    if( StreamType() == stream_type::out )
    {
        if( !AtEnd() ) {
            *m_Iter = row;
            ++m_Iter;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////

C_DataStateDatabase::C_DataStateDatabase(
        C_Database& database,
        QString table_name,
        QString row_name,
        long row_max,
        C_DataState::stream_type stype,
        C_Variant* parent):
    C_DataState(stype,parent)
{
    SetDatabase(database);
    SetTableName(table_name);
    SetRowName(row_name);
    SetRowCount(0);
    SetRowMax(row_max);
}

void C_DataStateDatabase::Next()
{
    if( StreamType() == stream_type::in )
    {
        if( !AtEnd() )
        {
            QStringList tmp =
                    Database()
                    .GetRecord(TableName(),RowName(),QString::number(RowCount()));

            tmp.pop_front();

            SetData(tmp);
            ++m_RowCount;
        }
    }
}

void C_DataStateDatabase::Insert(QStringList& row)
{
    if( StreamType() == stream_type::out )
    {
        if( !AtEnd() )
        {
            QStringList tmp = row;
            tmp.push_front(QString::number(m_RowCount));

            Database().AppendRecord(TableName(),tmp);
            ++m_RowCount;
        }
    }
}

void C_DataStateDatabase::Extract(QStringList& row)
{
    if( StreamType() == stream_type::in )
    {
        row = Data();
        if( !AtEnd() )
        {
            QStringList tmp =
                    Database()
                    .GetRecord(TableName(),RowName(),QString::number(RowCount()));

            tmp.pop_front();

            SetData(tmp);
            ++m_RowCount;
        }
    }
}

bool C_DataStateDatabase::AtEnd()
{
    return RowCount() == RowMax();
}

void C_DataStateDatabase::Stop()
{
    SetRowMax(RowCount());
}
