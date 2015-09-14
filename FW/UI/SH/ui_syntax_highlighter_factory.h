#ifndef UISYNTAXHIGHLIGHTERFACTORY_H
#define UISYNTAXHIGHLIGHTERFACTORY_H

#include "FW/variant.h"
#include "FW/UI/SH/ui_syntax_highlighter.h"
#include "FW/tools.h"


class TypeUiSyntaxHighlighterFactory : public TypeVariant
{
public:

    TypeUiSyntaxHighlighterFactory( TypeVariant* parent = 0 );

    TypeUiSyntaxHighlighter*           NewInstance( QString format );
    void                               AppendFormat( QString format, QString file_name );
    bool                               Empty();

private:

    QMap<QString, QString>             m_FormatMap;
};

#endif // UISYNTAXHIGHLIGHTERFACTORY_H
