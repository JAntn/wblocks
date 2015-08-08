#include "FW/RC/record.h"


long C_RecordFactory::m_IdCount = 0;

QString C_RecordFactory::GenerateId()
{
    return QString::number( m_IdCount++ );
}

QString C_RecordFactory::IdCount()
{
    return QString::number( m_IdCount );
}

C_Record::C_Record( QString id, QString name, QString value, C_Variant* parent ) :
    C_Variant( parent ), m_Id( id ), m_Name( name ), m_Value( value )
{
    SetFlags(FLAG_ALL);
}

C_Record::~C_Record()
{
    // void
}

QString C_Record::Id() const
{
    return m_Id;
}

QString C_Record::Name() const
{
    return m_Name;
}

void C_Record::SetName( QString name )
{
     m_Name = name;
}

QString C_Record::FullName() const
{
    auto record_struct = static_cast<C_RecordStruct*>( Parent() );

    if( record_struct->Name() != "root" )
    {
        auto record = static_cast<C_Record*>( record_struct->Parent() );
        return record->FullName() + "." + Name();
    }

    return Name();
}

void C_Record::SetValue(QString value)
{
    m_Value = value;
}

QString C_Record::Value() const
{
    return m_Value;
}





