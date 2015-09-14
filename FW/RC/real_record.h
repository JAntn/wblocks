#ifndef REALRECORD_H
#define REALRECORD_H

#include "FW/RC/record.h"
#include "FW/RC/html_action.h"

class TypeStateWriter;
class TypeStateReader;

class TypeRealRecord : public TypeRecord
{
public:

    explicit TypeRealRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    TypeRealRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    ~TypeRealRecord() override;

    void                                    Html(TypeHtmlBlockStream& block_stream) override;
    void                                    Script(TypeHtmlBlockStream& block_stream) override;
    QWidget*                                PropertyWidget(TypeController& controller) override;
    bool                                    SetState(TypeStateWriter& state, TypeStruct*) override;
    bool                                    GetState(TypeStateReader& state) override;

    M_VALUE                                 ( HtmlAction, int )

private:

    friend class                            TypeRealRecordFactory;
};

class TypeRealRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS                         ( TypeRealRecordFactory )

    TypeRealRecordFactory();

    TypeRecord*                             NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
    TypeRecord*                             NewInstance(TypeStateWriter& state, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
};

#endif // REALRECORD_H
