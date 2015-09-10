#ifndef SCRIPTFILERECORD_H
#define SCRIPTFILERECORD_H

#include "FW/RC/file_record.h"

class TypeStruct;
class TypeUiEditor;
class TypeController;

class TypeStateWriter;
class TypeStateReader;

class TypeJsScriptFileRecord: public TypeFileRecord
{

public:

    explicit TypeJsScriptFileRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    TypeJsScriptFileRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    ~TypeJsScriptFileRecord() override;

    void                Html(TypeHtmlBlockStream& block_stream) override;
    TypeUiEditor*       EditorWidget( QString id, TypeController& controller ) override;


private:

    friend class        TypeJsScriptFileRecordFactory;
};

class TypeJsScriptFileRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS   ( TypeJsScriptFileRecordFactory )

    TypeJsScriptFileRecordFactory();

    TypeRecord*           NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
    TypeRecord*           NewInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
};

#endif // SCRIPTFILERECORD_H
