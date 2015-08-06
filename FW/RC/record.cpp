#include "FW/RC/record.h"


long C_RecordFactory::m_IdCount = 0;

QString C_RecordFactory::GenerateId()
{
    return QString::number(m_IdCount++);
}

QString C_RecordFactory::IdCount()
{
    return QString::number(m_IdCount);
}

C_Record::C_Record(QString name, QString value, C_Variant* parent) :
    C_Variant(parent), m_Name(name), m_Value(value)
{
    //void;
}

QString C_Record::FullName() const
{
    C_RecordStruct* record_struct
            = static_cast<C_RecordStruct*>(Parent());

    if(record_struct->Name() != "root")
    {
        auto record
                = static_cast<C_Record*>(record_struct->Parent());

        return record->FullName() + "." + Name();
    }

    return Name();
}


