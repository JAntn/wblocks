#include "FW/ST/state_reader.h"

C_StateReader::C_StateReader( long flags, C_Variant* parent ):
    C_Variant( parent )
{
    m_Flags = flags;
    m_Count = 0;
}


C_StateReader::~C_StateReader()
{
    // void
}

void C_StateReader::Stop()
{
    m_Flags |= FLAG_STATE_ATEND;
}

bool C_StateReader::AtEnd()
{
    return m_Flags & FLAG_STATE_ATEND;
}

