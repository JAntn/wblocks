#ifndef PHPFILERECORD_H
#define PHPFILERECORD_H

#include "FW/RC/text_file_record.h"

class TypeStruct;

class TypePhpFileRecord: public TypeTextFileRecord
{

public:

    explicit TypePhpFileRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    TypePhpFileRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    ~TypePhpFileRecord() override;

    void                                    Html( TypeHtmlBlockStream& block_stream );
    QWidget*                                PropertyWidget( TypeController& controller );

    QString                                 FileFormatTitle() override;
    QString                                 FileFormat() override;
    QString                                 FileExtension() override;


private:

    friend class                            TypePhpFileRecordFactory;
};

class TypePhpFileRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS                         ( TypePhpFileRecordFactory )

    TypePhpFileRecordFactory();

    TypeRecord*                             NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
    TypeRecord*                             NewInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
};

#endif // PHPFILERECORD_H
