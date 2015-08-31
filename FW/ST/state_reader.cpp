#include "FW/ST/state_reader.h"

TypeStateReader::TypeStateReader( long flags, TypeVariant* parent ):
    TypeVariant( parent )
{
    m_Flags = flags;
    m_Count = 0;
}


TypeStateReader::~TypeStateReader()
{
    // void
}

void TypeStateReader::Stop()
{
    m_Flags |= FLAG_STATE_ATEND;
}

bool TypeStateReader::AtEnd()
{
    return m_Flags & FLAG_STATE_ATEND;
}

