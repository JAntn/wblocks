#ifndef TypeRECORD_H
#define TypeRECORD_H

#include "FW/macro.h"
#include "FW/variant.h"

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

    explicit TypeRecord( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    TypeRecord( QString id, QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    ~TypeRecord() override;

    virtual bool                  GetState( TypeStateReader& state );
    virtual bool                  SetState( TypeStateWriter& state, TypeRecordStruct* root = 0 );
    virtual QWidget*              PropertyWidget( TypeController& controller );
    virtual TypeUiEditor*           EditorWidget( QString id, TypeController& controller );

    virtual TypeRecordStruct*       Struct();
    virtual QStringList           Script();
    virtual QStringList           Html();

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

    virtual TypeRecord*             CreateInstance( QString name, QString value, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );
    virtual TypeRecord*             CreateInstance( TypeStateWriter& state, TypeVariant* parent = 0, TypeRecordStruct* root = 0 );

    static QString                GenerateId();
    static QString                IdCount();

    M_CONST_VALUE                 ( RecordClass, QString )

private:

    static long                   m_IdCount;
    friend class                  TypeDocument;
};

#endif // TypeRECORD_H

#include "FW/RC/record_struct.h"

#include <FW/controller.h>
