#ifndef SCRIPTRECORD_H
#define SCRIPTRECORD_H

#include "FW/RC/record.h"

class TypeStateReader;
class TypeStateWriter;

class TypeJsScriptRecord : public TypeRecord
{

public:

    explicit TypeJsScriptRecord( TypeStateWriter& state, TypeVariant* Parent, TypeStruct* root = 0 );
    TypeJsScriptRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    ~TypeJsScriptRecord() override;

    void                                    Script( TypeHtmlBlockStream& block_stream )  override;
    QWidget*                                PropertyWidget( TypeController& controller ) override;
    TypeUiEditor*                           EditorWidget( QString id, TypeController& document ) override;

private:

    friend class                            TypeJsScriptRecordFactory;
};

class TypeJsScriptRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS                         ( TypeJsScriptRecordFactory )

    TypeJsScriptRecordFactory();

    TypeRecord*                             NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
    TypeRecord*                             NewInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
};

#endif // SCRIPTRECORD_H