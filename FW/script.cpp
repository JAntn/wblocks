#include "FW/RC/record.h"
#include "FW/document.h"

C_Script::C_Script(C_Document& document, C_Variant* parent):
      C_Variant(parent),
      m_Document(&document)
{
    // void
}

void C_Script::Generate(C_RecordStruct& record_container)
{
    m_StringList.clear();

    for( C_Variant* node : record_container )
    {
        C_Record* record = static_cast<C_Record*>(node);

        m_StringList.push_back(record->Script());
    }

    emit Document().Signals().ScriptChanged();
}

