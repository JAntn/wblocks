#ifndef C_SCRIPT_FILE_RECORD_H
#define C_SCRIPT_FILE_RECORD_H

#include "FW/RC/record.h"
#include "FW/macro.h"

class C_RecordStruct;
class C_StringRecord;
class C_BoolRecord;

class C_StateWriter;
class C_StateReader;
class C_FileRecord;

class C_ScriptFileRecord: public C_Record
{

public:

    explicit C_ScriptFileRecord( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    C_ScriptFileRecord( QString id, QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    ~C_ScriptFileRecord() override;

    QString             Class() const override;
    QString             Script() override;
    C_RecordStruct*     Struct() override;

    void 			    GetState( C_StateReader& state ) override;
    void                SetState( C_StateWriter& state, C_RecordStruct* root = 0 ) override;
    void                EditProperties( C_Document& document ) override;
    void                OpenInEditor(C_Document& document) override;

    QString             Value() override;
    void                SetValue( QString ) override;

    M_POINTER           ( Records,    C_RecordStruct )
    M_POINTER           ( File,       C_FileRecord )
    M_VALUE             ( Code,       QString )

private:

    friend class        C_UiScriptFileRecordProperties;
    friend class        C_ScriptFileRecordFactory;
};

class C_ScriptFileRecordFactory : public C_RecordFactory
{
public:

    SINGLETON_CLASS   ( C_ScriptFileRecordFactory )

    QString             RecordClass() const override;

    C_Record*           CreateInstance( QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
    C_Record*           CreateInstance( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
};

#endif // C_SCRIPT_RECORD_H
