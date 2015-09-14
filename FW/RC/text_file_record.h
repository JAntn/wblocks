#ifndef TEXTFILERECORD_H
#define TEXTFILERECORD_H

#include "FW/RC/file_record.h"
#include "FW/RC/html_action.h"

class TypeStruct;
class TypeUiEditor;
class TypeController;
class TypeStateWriter;
class TypeStateReader;

class TypeTextFileRecord: public TypeFileRecord
{
public:

    explicit TypeTextFileRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    TypeTextFileRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    ~TypeTextFileRecord() override;

    TypeUiEditor*                           EditorWidget( QString id, TypeController& controller ) override;
    QWidget*                                PropertyWidget( TypeController& controller ) override;
    bool                                    SetState( TypeStateWriter& state, TypeStruct* ) override;
    bool                                    GetState( TypeStateReader& state ) override;
    void                                    Html( TypeHtmlBlockStream& block_stream ) override;

    M_VALUE                                 ( HtmlAction, int )

    virtual QString                         FileFormatTitle();
    virtual QString                         FileFormat();
    virtual QString                         FileExtension();

private:

    friend class                            TypeTextFileRecordFactory;
};

class TypeTextFileRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS                         ( TypeTextFileRecordFactory )

    TypeTextFileRecordFactory();

    TypeRecord*                             NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
    TypeRecord*                             NewInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;


};

#endif // PHPFILERECORD_H
