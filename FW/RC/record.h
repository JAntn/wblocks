#ifndef C_RECORD_H
#define C_RECORD_H

#include "FW/macro.h"
#include "FW/variant.h"

#include <QString>
#include <QWidget>

class C_Document;
class C_RecordStruct;
class C_StateReader;
class C_StateWriter;

class C_Record : public C_Variant
{
public:

    explicit C_Record( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    C_Record( QString id, QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    ~C_Record() override;

    virtual void                  GetState( C_StateReader& state );
    virtual void                  SetState( C_StateWriter& state, C_RecordStruct* root = 0 );
    virtual void                  EditProperties( C_Document& document );
    virtual void                  OpenInEditor( C_Document& document );

    virtual C_RecordStruct*       Struct();
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

class C_RecordFactory
{
public:

    C_RecordFactory();

    virtual C_Record*             CreateInstance( QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    virtual C_Record*             CreateInstance( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 );

    static QString                GenerateId();
    static QString                IdCount();

    M_CONST_VALUE                 ( RecordClass, QString )

private:

    static long                   m_IdCount;
    friend class                  C_Document;
};

#endif // C_RECORD_H

#include "FW/RC/record_struct.h"
