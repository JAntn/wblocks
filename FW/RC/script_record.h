#ifndef C_SCRIPT_RECORD_H
#define C_SCRIPT_RECORD_H

#include "FW/macro.h"
#include "FW/RC/record.h"

class C_StateReader;
class C_StateWriter;

class C_ScriptRecord : public C_Record
{

public:

    explicit C_ScriptRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root = 0 );
    C_ScriptRecord( QString id, QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    ~C_ScriptRecord() override;

    QString             Class() const override;
    QString             Script()  override;

    void                GetState( C_StateReader& state ) override;
    void                SetState( C_StateWriter& state , C_RecordStruct* root = 0 ) override;
    void                EditProperties( C_Document& document ) override;
    void                OpenInEditor( C_Document& document ) override;

private:

    friend class        C_UiScriptRecordProperties;
    friend class        C_ScriptRecordFactory;
};

class C_ScriptRecordFactory : public C_RecordFactory
{
public:

    SINGLETON_CLASS     ( C_ScriptRecordFactory )

    QString             RecordClass() const override;

    C_Record*           CreateInstance( QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
    C_Record*           CreateInstance( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;

};

#endif // C_SCRIPT_RECORD_H
