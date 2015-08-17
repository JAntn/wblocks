#ifndef C_REFERENCE_RECORD_H
#define C_REFERENCE_RECORD_H

#include "FW/macro.h"
#include "FW/RC/record.h"
#include "QString"
#include "FW/document.h"

class C_StateWriter;
class C_StateReader;

class C_ReferenceRecord : public C_Record
{

public:

    explicit C_ReferenceRecord( C_StateWriter& state, C_Variant* parent = 0 );
    C_ReferenceRecord( QString id, QString name, QString value, C_Variant* parent = 0 );

    ~C_ReferenceRecord() override;

    QString             Class()     const override;
    QString             Script()    const override;
    C_RecordStruct*     Struct()    const override;

    void                GetState( C_StateReader& state )   override;
    void                SetState( C_StateWriter& state )   override;
    void                ShowEditor( C_Document& document ) override;

    QString             Value() const override;
    void                SetValue(QString full_name) override;

    ATR_POINTER         ( Document,  C_Document )

    C_Record*           Referencee();

private:

    friend class        C_UiReferenceEditor;
    friend class        C_ReferenceRecordFactory;
};

class C_ReferenceRecordFactory : public C_RecordFactory
{
public:

    SINGLETON_CLASS( C_ReferenceRecordFactory )

    C_Record*           CreateInstance( QString name, QString value, C_Variant* parent = 0 ) override;
    C_Record*           CreateInstance( C_StateWriter& state, C_Variant* parent = 0 ) override;
    QString             RecordClass() const override;
};

#endif // C_REFERENCE_RECORD_H
