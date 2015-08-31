#ifndef C_SCRIPT_FILE_RECORD_H
#define C_SCRIPT_FILE_RECORD_H

#include "FW/RC/file_record.h"
#include "FW/macro.h"

class C_RecordStruct;
class C_UiEditor;
class C_Controller;

class C_StateWriter;
class C_StateReader;

class C_ScriptFileRecord: public C_FileRecord
{

public:

    explicit C_ScriptFileRecord( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    C_ScriptFileRecord( QString id, QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    ~C_ScriptFileRecord() override;

    QStringList         Script() override;
    C_UiEditor*         EditorWidget( QString id, C_Controller& controller ) override;

private:

    friend class        C_ScriptFileRecordFactory;
};

class C_ScriptFileRecordFactory : public C_RecordFactory
{
public:

    SINGLETON_CLASS   ( C_ScriptFileRecordFactory )

    C_ScriptFileRecordFactory();

    C_Record*           CreateInstance( QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
    C_Record*           CreateInstance( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
};

#endif // C_SCRIPT_RECORD_H
