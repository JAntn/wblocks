#ifndef C_INTEGER_RECORD_H
#define C_INTEGER_RECORD_H

#include "FW/RC/record.h"
#include "FW/macro.h"

class C_StateWriter;
class C_StateReader;

class C_IntegerRecord : public C_Record
{
public:

    explicit C_IntegerRecord( C_StateWriter& state, C_Variant* parent = 0 );
    C_IntegerRecord( QString id, QString name, QString value, C_Variant* parent = 0 );
    ~C_IntegerRecord() override;

    QString             Class() const override;
    QString             Script() const override;
    C_RecordStruct*     Struct() const override;
    void                GetState( C_StateReader& state ) override;
    void                SetState( C_StateWriter& state ) override;
    void                ShowEditor( C_Document& document ) override;

private:

    friend class        C_UiIntegerEditor;
    friend class        C_IntegerRecordFactory;
};

class C_IntegerRecordFactory : public C_RecordFactory
{
public:

    SINGLETON_CLASS   ( C_IntegerRecordFactory )

    C_Record*           CreateInstance( QString name, QString value, C_Variant* parent = 0 ) override;
    C_Record*           CreateInstance( C_StateWriter& state, C_Variant* parent = 0 ) override;
    QString             RecordClass() const override;
};

#endif // C_INTEGER_RECORD_H
