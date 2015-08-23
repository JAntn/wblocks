#include "FW/RC/record.h"
#include "FW/document.h"

C_Script::C_Script( C_Variant* parent ):
    C_Variant( parent )
{
    // void
}

C_Script::~C_Script()
{
    // void
}

void C_Script::Parse( C_RecordStruct& records )
{
    m_StringList.clear();

    for( C_Variant* variant : records )
    {
        C_Record* record = static_cast<C_Record*>( variant );
        m_StringList.append( record->Script() );
    }
}

