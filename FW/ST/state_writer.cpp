#include "FW/ST/state_writer.h"


C_StateWriter::C_StateWriter( long flags, C_Variant* parent )
    : C_Variant( parent )
{
    m_Flags = flags;
    m_Count = 0;
}

C_StateWriter::~C_StateWriter()
{
    // void
}

void C_StateWriter::Stop()
{
    m_Flags |= FLAG_STATE_ATEND;
}


void C_StateWriter::C_StateWriter::Write(QStringList &data, bool next)
{
    if( AtEnd() )
        return;

    data = m_Data;

    if( next )
        this->Next();
}

bool C_StateWriter::AtEnd()
{
    return Flags() & FLAG_STATE_ATEND;
}