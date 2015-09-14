#ifndef HTMLFILERECORD_H
#define HTMLFILERECORD_H

#include "FW/RC/text_file_record.h"

class TypeStruct;
class TypeUiEditor;
class TypeController;

class TypeStateWriter;
class TypeStateReader;

class TypeHtmlFileRecord: public TypeTextFileRecord
{

public:

    explicit TypeHtmlFileRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    TypeHtmlFileRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    ~TypeHtmlFileRecord() override;

    QString                                 FileExtension();
    QString                                 FileFormat();
    QString                                 FileFormatTitle();

private:

    friend class                            TypeHtmlFileRecordFactory;
};

class TypeHtmlFileRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS                         ( TypeHtmlFileRecordFactory )

    TypeHtmlFileRecordFactory();

    TypeRecord*                             NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
    TypeRecord*                             NewInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
};

#endif // HTMLFILERECORD_H
