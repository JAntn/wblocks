#ifndef C_HTML_RECORD_H
#define C_HTML_RECORD_H

#include "FW/RC/record.h"
#include "FW/macro.h"

class C_RecordStruct;
class C_StringRecord;
class C_StructRecord;

class C_StateWriter;
class C_StateReader;

class C_HtmlRecord: public C_Record
{

public:

    explicit C_HtmlRecord( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    C_HtmlRecord( QString id, QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    ~C_HtmlRecord() override;

    QString             Class() const override;
    C_RecordStruct*     Struct() override;
    QString             Html() override;

    void                GetState( C_StateReader& state ) override;
    void                SetState( C_StateWriter& state, C_RecordStruct* root = 0 ) override;
    //void              EditProperties( C_Document& document );
    //void              OpenInEditor( C_Document& document );

    QString             Value();
    void                SetValue(QString);

    M_POINTER           ( Records,        C_RecordStruct )
    M_POINTER           ( HtmlAtributes,  C_StructRecord )
    M_POINTER           ( HtmlTag,        C_StringRecord )
    M_POINTER           ( HtmlContent,    C_StringRecord )
    M_VALUE             ( Code,           QString )


private:

    friend class        C_UiScriptEditor;
    friend class        C_ScriptRecordFactory;
};

class C_HtmlRecordFactory : public C_RecordFactory
{
public:

    SINGLETON_CLASS   ( C_HtmlRecordFactory )

    QString             RecordClass() const override;

    C_Record*           CreateInstance( QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
    C_Record*           CreateInstance( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
};

#endif // C_HTML_RECORD_H
