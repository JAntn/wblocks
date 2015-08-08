#ifndef C_STRING_RECORD_H
#define C_STRING_RECORD_H

#include "FW/macro.h"
#include "FW/RC/record.h"

class C_StringRecord : public C_Record
{

public:

    explicit C_StringRecord( C_DataState& state, C_Variant* parent );
    C_StringRecord( QString id, QString name, QString value, C_Variant* parent = 0 );

    ~C_StringRecord() override;

    QString             Class() const override;
    QString             Script()    const override;
    C_RecordStruct*     Struct()    const override;

    void 			    GetState( C_DataState& state ) override;
    void                SetState( C_DataState& value_list ) override;

    void                ShowEditor( C_Document& document ) override;

private:

    friend class        C_UiStringEditor;
    friend class        C_StringRecordFactory;
};

class C_StringRecordFactory : public C_RecordFactory
{
public:

    C_SINGLETON_CLASS( C_StringRecordFactory )

    QString             RecordClass() const override;

    C_Record*           CreateInstance( QString name, QString value, C_Variant* parent = 0 ) override;
    C_Record*           CreateInstance( C_DataState& state, C_Variant* parent = 0 ) override;

};

#endif // C_STRING_RECORD_H
