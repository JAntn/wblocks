#ifndef C_REAL_RECORD_H
#define C_REAL_RECORD_H

#include "FW/macro.h"
#include "FW/RC/record.h"

class C_RealRecord : public C_Record
{

public:

    explicit C_RealRecord( C_DataState& state, C_Variant* parent = 0 );
    C_RealRecord( QString id, QString name, QString value, C_Variant* parent = 0 );

    ~C_RealRecord() override;

    QString             Class()     const override;
    QString             Script()    const override;
    C_RecordStruct*     Struct()    const override;

    void                GetState( C_DataState& state ) override;
    void                SetState( C_DataState& state ) override;

    void                ShowEditor( C_Document& document ) override;

private:

    friend class        C_UiRealEditor;
    friend class        C_RealRecordFactory;
};

class C_RealRecordFactory : public C_RecordFactory
{
public:

    C_SINGLETON_CLASS( C_RealRecordFactory )

    C_Record*           CreateInstance( QString name, QString value, C_Variant* parent = 0 ) override;
    C_Record*           CreateInstance( C_DataState& state, C_Variant* parent = 0 ) override;

    QString             RecordClass() const override;
};

#endif // C_REAL_RECORD_H
