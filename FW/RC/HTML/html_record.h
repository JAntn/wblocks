#ifndef C_HTML_RECORD_H
#define C_HTML_RECORD_H

#include "FW/macro.h"
#include "FW/RC/record.h"

class C_StateReader;
class C_StateWriter;

class C_HtmlRecord : public C_Record
{

public:

    explicit C_HtmlRecord( C_StateWriter& state, C_Variant* parent, C_RecordStruct* root = 0 );
    C_HtmlRecord( QString id, QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    ~C_HtmlRecord() override;

    QStringList         Html()  override;
    void                EditProperties( C_Document& document ) override;
    void                OpenInEditor( C_Document& document ) override;

private:

    friend class        C_UiScriptRecordProperties;
    friend class        C_HtmlRecordFactory;
};

class C_HtmlRecordFactory : public C_RecordFactory
{
public:

    SINGLETON_CLASS     ( C_HtmlRecordFactory )

    C_HtmlRecordFactory();

    C_Record*           CreateInstance( QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
    C_Record*           CreateInstance( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
};


#endif // C_HTML_RECORD_H
