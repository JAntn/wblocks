#ifndef C_RCSTRING_H
#define C_RCSTRING_H

#include "FW/macro.h"
#include "FW/RC/record.h"

class C_Document;

class C_StringRecord : public C_Record{

public:


    explicit            C_StringRecord(QString name, QString value, C_Variant* parent=0);

    QString             Id()        const override;
    QString             Name()      const override;
    QString             Class() const override;
    QString             Script()    const override;
    C_RecordStruct*     Struct()    const override;

    void 			    GetState(C_DataState& state) override;
    void                SetState(C_DataState& value_list) override;

    void                ShowEditor(C_Document& document) override;

private:

    friend class        C_UiStringEditor;
    friend class        C_StringRecordFactory;
};

class C_StringRecordFactory : public C_RecordFactory {
public:

    C_SINGLETON_CLASS(C_StringRecordFactory)

    QString             RecordClass() const override;

    C_Record*           CreateInstance(QString name, QString value, C_Variant* parent=0) override;
    C_Record*           CreateInstance(C_DataState& state, C_Variant* parent=0) override;

};

#endif // C_RCSTRING_H
