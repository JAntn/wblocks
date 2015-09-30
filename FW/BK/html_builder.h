#ifndef HTMLBUILDER_H
#define HTMLBUILDER_H

#include "FW/tools.h"

class TypeHtmlBlockStream;
class TypeStruct;

class TypeHtmlBuilder : public TypeVariant
{
public:

    explicit TypeHtmlBuilder( TypeVariant* parent = 0 );
    ~TypeHtmlBuilder() override;

    void                                    Build( TypeStruct& root );
    QString                                 Text();
    QString                                 FormattedText();

    M_REFERENCE                             ( BlockStream,  TypeHtmlBlockStream )
};

#endif // HTMLBUILDER_H
