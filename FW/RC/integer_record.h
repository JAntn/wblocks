#ifndef INTEGERRECORD_H
#define INTEGERRECORD_H

#include "FW/RC/record.h"
#include "FW/RC/html_action.h"

class TypeStateWriter;
class TypeStateReader;

class TypeIntegerRecord : public TypeRecord
{
public:

    explicit TypeIntegerRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    TypeIntegerRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    ~TypeIntegerRecord() override;

    void                                    Html(TypeHtmlBlockStream& block_stream) override;
    void                                    Script(TypeHtmlBlockStream& block_stream) override;
    QWidget*                                PropertyWidget(TypeController& controller) override;
    bool                                    SetState(TypeStateWriter& state, TypeStruct*) override;
    bool                                    GetState(TypeStateReader& state) override;

    M_VALUE                                 ( HtmlAction, int )

private:

    friend class                            TypeIntegerRecordFactory;
};

class TypeIntegerRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS                         ( TypeIntegerRecordFactory )

    TypeIntegerRecordFactory();

    TypeRecord*                             NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
    TypeRecord*                             NewInstance(TypeStateWriter& state, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
};

#endif // IntegerRECORD_H
