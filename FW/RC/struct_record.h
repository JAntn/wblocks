#ifndef TypeSTRUCT_RECORD_H
#define TypeSTRUCT_RECORD_H

#include "FW/RC/record.h"
#include "FW/macro.h"

class TypeRecordStruct;

class TypeStateWriter;
class TypeStateReader;
class TypeController;
class TypeStructRecord : public TypeRecord
{
public:

    explicit TypeStructRecord( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    TypeStructRecord( QString id, QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    ~TypeStructRecord() override;

    TypeRecordStruct*     Struct() override;
    QStringList         Script() override;
    QStringList         Html() override;

    bool                GetState( TypeStateReader& state ) override;
    bool                SetState( TypeStateWriter& state , TypeRecordStruct* root = 0 ) override;
    QWidget*            PropertyWidget( TypeController& controller ) override;

    M_POINTER           ( Records, TypeRecordStruct )

    QString             Value() override;
    void                SetValue( QString ) override;

private:

    friend class        TypeUiStructEditor;
    friend class        TypeStructRecordFactory;
};

class TypeStructRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS   ( TypeStructRecordFactory )

    TypeStructRecordFactory();

    TypeRecord*           CreateInstance( QString name, QString value, TypeVariant* parent = 0 , TypeRecordStruct* root = 0 ) override;
    TypeRecord*           CreateInstance( TypeStateWriter& table, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;

};

#endif // TypeSTRUCT_RECORD_H
