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

    QStringList         Script()  override;
    QWidget*            PropertyWidget( C_Controller& controller ) override;
    C_UiEditor*         EditorWidget( QString id, C_Controller& document ) override;

private:

    friend class        C_ScriptRecordFactory;
};

class C_ScriptRecordFactory : public C_RecordFactory
{
public:

    SINGLETON_CLASS     ( C_ScriptRecordFactory )

    C_ScriptRecordFactory();

    C_Record*           CreateInstance( QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
    C_Record*           CreateInstance( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
};

#endif // C_SCRIPT_RECORD_H
