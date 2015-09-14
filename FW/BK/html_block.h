#ifndef HTMLBLOCK_H
#define HTMLBLOCK_H

#include "FW/tools.h"
#include "FW/controller.h"

class TypeHtmlBlock : public TypeVariant
{
public:

    TypeHtmlBlock( int position, QString text, QString record_id, TypeVariant* Parent = 0 );

    M_VALUE                                 ( Position, int )
    M_VALUE                                 ( Text,     QString )
    M_VALUE                                 ( RecordId, QString )
    M_VALUE                                 ( Selected, bool )

};

#endif // BLOCK_H
