#ifndef HTMLRECORD_H
#define HTMLRECORD_H

#include "FW/RC/record.h"
#include "FW/RC/html_action.h"

class TypeStateWriter;
class TypeStateReader;

class TypeHtmlRecord : public TypeRecord
{
public:

    explicit TypeHtmlRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    TypeHtmlRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    ~TypeHtmlRecord() override;

    void                                    Html(TypeHtmlBlockStream& block_stream) override;
    QWidget*                                PropertyWidget(TypeController& controller) override;
    bool                                    SetState(TypeStateWriter& state, TypeStruct*) override;
    bool                                    GetState(TypeStateReader& state) override;

    M_VALUE                                 ( HtmlAction, int )

private:

    friend class                            TypeHtmlRecordFactory;
};

class TypeHtmlRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS                         ( TypeHtmlRecordFactory )

    TypeHtmlRecordFactory();

    TypeRecord*                             NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
    TypeRecord*                             NewInstance(TypeStateWriter& state, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
};

#endif // HtmlRECORD_H
