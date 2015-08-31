#ifndef C_FILE_RECORD_H
#define C_FILE_RECORD_H

#include "FW/macro.h"
#include "FW/RC/record.h"

class C_StateReader;
class C_StateWriter;

class C_FileRecord : public C_Record
{

public:

    explicit C_FileRecord( C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    C_FileRecord( QString id, QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 );
    ~C_FileRecord() override;

    QWidget*            PropertyWidget( C_Controller& controller ) override;

    QString             FilePath();
    QString             FileName();
    QString             FileFullName();

private:

    friend class        C_FileRecordFactory;
};

class C_FileRecordFactory : public C_RecordFactory
{
public:

    SINGLETON_CLASS     ( C_FileRecordFactory )

    C_FileRecordFactory();

    C_Record*           CreateInstance( QString name, QString value, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
    C_Record*           CreateInstance(C_StateWriter& state, C_Variant* parent = 0, C_RecordStruct* root = 0 ) override;
};

#endif // C_FILE_RECORD_H
