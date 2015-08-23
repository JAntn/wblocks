#ifndef C_FILE_RECORD_H
#define C_FILE_RECORD_H

#include "FW/macro.h"
#include "FW/RC/record.h"

class C_StateReader;
class C_StateWriter;

class C_FileRecord : public C_Record
{

public:

    explicit C_FileRecord( C_StateWriter& state, C_Variant* parent );
    C_FileRecord( QString id, QString name, QString value, C_Variant* parent = 0 );
    ~C_FileRecord() override;

    QString             Class() const override;
    QString             Script() const override;
    C_RecordStruct*     Struct() const override;
    void 		        GetState( C_StateReader& state ) override;
    void                SetState( C_StateWriter& value_list ) override;
    void                ShowEditor( C_Document& document ) override;
    QString             FileDir();
    QString             FileName();
    QString             FileFullName();

private:

    friend class        C_UiStringEditor;
    friend class        C_FileRecordFactory;
};

class C_FileRecordFactory : public C_RecordFactory
{
public:

    SINGLETON_CLASS     ( C_FileRecordFactory )

    QString             RecordClass() const override;
    C_Record*           CreateInstance( QString name, QString value, C_Variant* parent = 0 ) override;
    C_Record*           CreateInstance( C_StateWriter& state, C_Variant* parent = 0 ) override;
};

#endif // C_FILE_RECORD_H
