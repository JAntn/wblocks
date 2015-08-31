#include "FW/RC/record.h"
#include "FW/htmlbuilder.h"
#include "FW/RC/record_struct.h"

C_HtmlBuilder::C_HtmlBuilder( C_Variant* parent ):
    C_Variant( parent )
{
    // void
}

C_HtmlBuilder::~C_HtmlBuilder()
{
    // void
}

void C_HtmlBuilder::Build( C_RecordStruct& root )
{
    m_Html.clear();

    m_Html
    << "\n<!DOCTYPE html>"
    << "\n<html>\n"
    << "\n<script>\n";

    for( C_Variant* variant : root )
    {
        C_Record* record = static_cast<C_Record*>( variant );
        m_Html << record->Script();
    }
    m_Html << "\n</script>\n";

    for( C_Variant* variant : root )
    {
        C_Record* record = static_cast<C_Record*>( variant );
        m_Html << record->Html();
    }

    m_Html << "\n</html>";
}

