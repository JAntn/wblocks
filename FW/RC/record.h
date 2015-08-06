#ifndef C_RECORD_H
#define C_RECORD_H

#include "FW/macro.h"
#include "FW/variant.h"

#include <QString>
#include <QWidget>

class C_Document;
class C_RecordStruct;
class C_DataState;

class C_Record : public C_Variant {
public:

    explicit                      C_Record(QString name, QString value, C_Variant* parent=0);

    virtual QString               Id()        const = 0;
    virtual QString               Name()      const = 0;
    virtual QString               Class()     const = 0;
    virtual QString               Script()    const = 0;
    virtual C_RecordStruct*       Struct()    const = 0;

    virtual void                  GetState(C_DataState&) = 0;
    virtual void                  SetState(C_DataState&) = 0;

    virtual void                  ShowEditor(C_Document&) = 0;

    QString                       FullName() const;

    virtual void                  SetValue(QString value) { m_Value = value; }
    virtual QString               Value() const { return m_Value; }

protected:

    QString                       m_Id;
    QString                       m_Name;
    QString                       m_Value;
};

class C_RecordFactory {
public:

    virtual C_Record*             CreateInstance(QString name, QString value, C_Variant* parent=0) = 0;
    virtual C_Record*             CreateInstance(C_DataState& state, C_Variant* parent=0) = 0;

    virtual QString               RecordClass() const = 0;

    static QString                GenerateId();
    static QString                IdCount();

private:

    static long                   m_IdCount;
    friend class                  C_Document;
};

#include "FW/RC/record_struct.h"


#endif // C_RECORD_H
