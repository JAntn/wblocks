#ifndef REFERENCERECORD_H
#define REFERENCERECORD_H

#include "FW/RC/record.h"

class TypeStateWriter;
class TypeStateReader;

class TypeReferenceRecord : public TypeRecord
{

public:

    explicit TypeReferenceRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    TypeReferenceRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeStruct* root = 0 );
    ~TypeReferenceRecord() override;

    bool                GetState( TypeStateReader& state ) override;
    bool                SetState( TypeStateWriter& state, TypeStruct* root = 0 ) override;
    QWidget*            PropertyWidget( TypeController& controller ) override;

    QString             Value() override;
    void                SetValue( QString record_name ) override;

    TypeRecord*         Referencee();

    M_REFERENCE         ( Root,  TypeStruct )

private:

    friend class        TypeUiReferenceEditor;
    friend class        TypeReferenceRecordFactory;
};

class TypeReferenceRecordFactory : public TypeRecordFactory
{
public:

    SINGLETON_CLASS( TypeReferenceRecordFactory )

    TypeReferenceRecordFactory();

    TypeRecord*           NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
    TypeRecord*           NewInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeStruct* root = 0 ) override;
};

#endif // REFERENCERECORD_H
