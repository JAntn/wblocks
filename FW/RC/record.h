#ifndef RECORD_H
#define RECORD_H

#include "FW/macro.h"
#include "FW/variant.h"
#include "FW/htmlbuilder.h"
#include <QString>
#include <QWidget>

class TypeUiEditor;
class TypeRecordStruct;
class TypeStateReader;
class TypeStateWriter;
class TypeController;

class TypeRecord : public TypeVariant
{
public:

    explicit TypeRecord( TypeStateWriter& state, TypeVariant* Parent = 0, TypeRecordStruct* root = 0 );
    TypeRecord( QString id, QString name, QString value, TypeVariant* Parent = 0, TypeRecordStruct* root = 0 );
    ~TypeRecord() override;

    virtual bool                  GetState( TypeStateReader& state );
    virtual bool                  SetState( TypeStateWriter& state, TypeRecordStruct* root = 0 );
    virtual QWidget*              PropertyWidget( TypeController& controller );
    virtual TypeUiEditor*         EditorWidget( QString id, TypeController& controller );

    virtual TypeRecordStruct*     Struct();
    virtual void                  Script( TypeBlockStream& block_stream );
    virtual void                  Html( TypeBlockStream& block_stream );

    virtual void                  SetValue( QString value );
    virtual QString               Value();

    QString                       FullName() const;


    M_CONST_VALUE                 ( Id,    QString )
    M_VALUE                       ( Name,  QString )
    M_CONST_VALUE                 ( Class, QString )
    M_VALUE                       ( Flags, long )

protected:

    QString                       m_Value;
};

class TypeRecordFactory
{
public:

    TypeRecordFactory();

    virtual TypeRecord*             NewInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    virtual TypeRecord*             NewInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );

    static QString                GenerateId();
    static QString                IdCount();

    M_CONST_VALUE                 ( RecordClass, QString )

private:

    static long                   m_IdCount;
    friend class                  TypeDocument;
};

#endif // RECORD_H

#include "FW/RC/record_struct.h"

#include <FW/controller.h>
