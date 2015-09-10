#ifndef HTMLBLOCKSTREAM_H
#define HTMLBLOCKSTREAM_H

#include "FW/tools.h"
#include "FW/BK/html_block.h"

class TypeHtmlBlockStream : protected TypeVariantStruct
{
public:

    using TypeVariantStruct::Size;
    using TypeVariantStruct::Clear;
    using TypeVariantStruct::begin;
    using TypeVariantStruct::end;

    TypeHtmlBlockStream( TypeVariant* Parent = 0 );

    void                                    Append( QString text, QString record_id = "" );
    TypeHtmlBlock*                          BlockFromCursorPosition( int cursor_position );

    M_VALUE                                 ( Count, int )
};

#endif // BLOCKSTREAM_H
