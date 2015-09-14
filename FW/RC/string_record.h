#ifndef STRINGRECORD_H
#define STRINGRECORD_H

#include "FW/RC/record.h"
#include "FW/RC/html_action.h"

class TypeStateWriter;
class TypeStateReader;

class TypeStringRecord : public TypeRecord
{
public:

    explicit TypeStringRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    TypeStringRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    ~TypeStringRecord() override;

    void                                    Html(TypeHtmlBlockStream& block_stream) override;
    void                                    Script(TypeHtmlBlockStream& block_stream) override;
    QWidget*                                PropertyWidget(TypeController& controller) override;
    bool                                    SetState(TypeStateWriter& state, TypeStruct*) override;
    bool                                    GetState(TypeStateReader& state) override;

    M_VALUE                                 ( HtmlAction, int )

private:

    friend class                            TypeStringRecordFactory;
};

class TypeStringRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS                         ( TypeStringRecordFactory )

    TypeStringRecordFactory();

    TypeRecord*                             NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
    TypeRecord*                             NewInstance(TypeStateWriter& state, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
};

#endif // StringRECORD_H
