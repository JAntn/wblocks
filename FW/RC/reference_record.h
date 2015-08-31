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

    explicit C_ReferenceRecord( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    C_ReferenceRecord( QString id, QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    ~C_ReferenceRecord() override;

    bool                GetState( C_StateReader& state ) override;
    bool                SetState( C_StateWriter& state, C_RecordStruct* root = 0) override;
    QWidget*            PropertyWidget(C_Controller& controller ) override;

    QString             Value() override;
    void                SetValue(QString full_name) override;

    C_Record*           Referencee();

    M_POINTER           ( Root,  C_RecordStruct )

private:

    friend class        C_UiReferenceEditor;
    friend class        C_ReferenceRecordFactory;
};

class C_ReferenceRecordFactory : public C_RecordFactory
{
public:

    SINGLETON_CLASS( C_ReferenceRecordFactory )

    C_ReferenceRecordFactory();

    C_Record*           CreateInstance( QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
    C_Record*           CreateInstance( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
};

#endif // C_REFERENCE_RECORD_H
