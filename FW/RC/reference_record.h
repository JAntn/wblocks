#ifndef REFERENCERECORD_H
#define REFERENCERECORD_H

#include "FW/macro.h"
#include "FW/RC/record.h"
#include "QString"
#include "FW/document.h"

class TypeStateWriter;
class TypeStateReader;

class TypeReferenceRecord : public TypeRecord
{

public:

    explicit TypeReferenceRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeRecordStruct* root = 0 );
    TypeReferenceRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeRecordStruct* root = 0 );
    ~TypeReferenceRecord() override;

    bool                GetState( TypeStateReader& state ) override;
    bool                SetState( TypeStateWriter& state, TypeRecordStruct* root = 0 ) override;
    QWidget*            PropertyWidget( TypeController& controller ) override;

    QString             Value() override;
    void                SetValue( QString full_name ) override;

    TypeRecord*         Referencee();

    M_POINTER           ( Root,  TypeRecordStruct )

private:

    friend class        TypeUiReferenceEditor;
    friend class        TypeReferenceRecordFactory;
};

class TypeReferenceRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS( TypeReferenceRecordFactory )

    TypeReferenceRecordFactory();

    TypeRecord*           NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
    TypeRecord*           NewInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 ) override;
};

#endif // REFERENCERECORD_H
