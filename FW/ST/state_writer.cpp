#include "FW/ST/state_writer.h"


TypeStateWriter::TypeStateWriter( long flags, TypeVariant* parent )
    : TypeVariant( parent )
{
    m_Flags = flags;
    m_Count = 0;
}

TypeStateWriter::~TypeStateWriter()
{
    // void
}

void TypeStateWriter::Stop()
{
    m_Flags |= FLAG_STATE_ATEND;
}


void TypeStateWriter::TypeStateWriter::Write( QStringList& data, bool next )
{
    if( AtEnd() )
        return;

    data = m_Data;

    if( next )
        this->Next();
}

bool TypeStateWriter::AtEnd()
{
    return Flags() & FLAG_STATE_ATEND;
}
