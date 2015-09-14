#ifndef JSSCRIPTFILERECORD_H
#define JSSCRIPTFILERECORD_H

#include "FW/RC/text_file_record.h"

class TypeStruct;
class TypeUiEditor;
class TypeController;

class TypeStateWriter;
class TypeStateReader;

class TypeJsScriptFileRecord: public TypeTextFileRecord
{

public:

    explicit TypeJsScriptFileRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    TypeJsScriptFileRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    ~TypeJsScriptFileRecord() override;

    void                                    Script(TypeHtmlBlockStream& block_stream) override;
    void                                    Html(TypeHtmlBlockStream& block_stream) override;

    QString                                 FileFormatTitle() override;
    QString                                 FileFormat() override;
    QString                                 FileExtension() override;

    QWidget*                                PropertyWidget(TypeController& controller);

private:

    friend class                            TypeJsScriptFileRecordFactory;
};

class TypeJsScriptFileRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS                         ( TypeJsScriptFileRecordFactory )

    TypeJsScriptFileRecordFactory();

    TypeRecord*                             NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
    TypeRecord*                             NewInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
};

#endif // JSSCRIPTFILERECORD_H
