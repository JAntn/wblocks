#include "FW/RC/record.h"
#include "FW/htmlbuilder.h"
#include "FW/RC/record_struct.h"

TypeHtmlBuilder::TypeHtmlBuilder( TypeVariant* parent ):
    TypeVariant( parent )
{
    // void
}

TypeHtmlBuilder::~TypeHtmlBuilder()
{
    // void
}

void TypeHtmlBuilder::Build( TypeRecordStruct& root )
{
    m_Html.clear();

    m_Html
    << "\n<!DOCTYPE html>"
    << "\n<html>\n"
    << "\n<script>\n";

    for( TypeVariant* variant : root )
    {
        TypeRecord* record = static_cast<TypeRecord*>( variant );
        m_Html << record->Script();
    }
    m_Html << "\n</script>\n";

    for( TypeVariant* variant : root )
    {
        TypeRecord* record = static_cast<TypeRecord*>( variant );
        m_Html << record->Html();
    }

    m_Html << "\n</html>";
}

