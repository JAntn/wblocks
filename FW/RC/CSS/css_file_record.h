#ifndef CSSFILERECORD_H
#define CSSFILERECORD_H

#include "FW/RC/text_file_record.h"

class TypeStruct;

class TypeCssFileRecord: public TypeTextFileRecord
{

public:

    explicit TypeCssFileRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    TypeCssFileRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    ~TypeCssFileRecord() override;

    QString                                 FileExtension();
    QString                                 FileFormat();
    QString                                 FileFormatTitle();

    void                                    Html(TypeHtmlBlockStream& block_stream);
    QWidget*                                PropertyWidget(TypeController& controller);

private:

    friend class                            TypeCssFileRecordFactory;
};

class TypeCssFileRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS                         ( TypeCssFileRecordFactory )

    TypeCssFileRecordFactory();

    TypeRecord*                             NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
    TypeRecord*                             NewInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
};

#endif // CSSFILERECORD_H
