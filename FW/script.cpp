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

void C_Script::Generate( C_RecordStruct& record_container )
{
    m_StringList.clear();

    for( auto node : record_container )
    {
        auto record = static_cast<C_Record*>( node );
        m_StringList.append( record->Script() );
    }
}

