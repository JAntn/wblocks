#include "FW/RC/record.h"
#include "FW/html.h"
#include "FW/RC/record_struct.h"

C_Html::C_Html( C_Variant* parent ):
    C_Variant( parent )
{
    // void
}

C_Html::~C_Html()
{
    // void
}

void C_Html::Parse( C_RecordStruct& root )
{
    m_StringList.clear();

    for( C_Variant* variant : root )
    {
        C_Record* record = static_cast<C_Record*>( variant );
        m_StringList.append( record->Html() );
    }
}

