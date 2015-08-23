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

    C_Record( QString id, QString name, QString value, C_Variant* parent = 0 );
    ~C_Record() override;

    virtual QString               Class() const = 0;
    virtual QString               Script() const = 0;
    virtual C_RecordStruct*       Struct() const = 0;
    virtual void                  SetValue( QString value );
    virtual QString               Value() const;
    virtual void                  GetState( C_StateReader& ) = 0;
    virtual void                  SetState( C_StateWriter& ) = 0;
    virtual void                  ShowEditor( C_Document& ) = 0;
    QString                       FullName() const;

    M_VALUE                       ( Name,  QString)
    M_VALUE                       ( Flags, long )
    M_CONST_VALUE                 ( Id,    QString )

protected:

    QString                       m_Value;
};

class C_RecordFactory
{
public:

    virtual C_Record*             CreateInstance( QString name, QString value, C_Variant* parent = 0 ) = 0;
    virtual C_Record*             CreateInstance( C_StateWriter& state, C_Variant* parent = 0 ) = 0;
    virtual QString               RecordClass() const = 0;

    static QString                GenerateId();
    static QString                IdCount();

private:

    static long                   m_IdCount;
    friend class                  C_Document;
};

#endif // C_RECORD_H

#include "FW/RC/record_struct.h"
