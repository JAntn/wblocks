
#include "FW/RC/string_record.h"
#include "FW/UI/ui_string_editor.h"
#include "FW/UI/ui_main_window.h"
#include <FW/data_state.h>
#include <FW/document.h>

#define CLASS_NAME "String"

C_StringRecord::C_StringRecord(QString name, QString value, C_Variant* parent)
    : C_Record(name,value,parent)
{
    //void
}

QString C_StringRecord::Script() const
{           
    return FullName() + " = \"" + Value() + "\""  + ";";
}

C_RecordStruct* C_StringRecord::Struct() const
{
    return 0;
}

QString C_StringRecord::Name() const
{
    return m_Name;
}


QString C_StringRecord::Id() const
{
    return m_Id;
}

QString C_StringRecord::Class() const
{
    return CLASS_NAME;
}

void C_StringRecord::ShowEditor(C_Document& document)
{
    QWidget* dialog = new C_UiStringEditor(*this,document,&document.MainWindow());
    dialog->show();
}

void C_StringRecord::GetState(C_DataState& state)
{
    QStringList row;

    row.append(m_Id);
    row.append(m_Name);
    row.append(m_Value);
    row.append(Class());

    state.Insert(row);
}

void C_StringRecord::SetState(C_DataState& state)
{

    QStringList row;

    state.Extract(row);

    m_Id    = row.at(0);
    m_Name  = row.at(1);
    m_Value = row.at(2);
}

C_Record* C_StringRecordFactory::CreateInstance(QString name, QString value, C_Variant* parent)
{
    C_StringRecord* record = new C_StringRecord(name,value,parent);

    record->m_Id = C_RecordFactory::GenerateId();

    return record;
}

C_Record* C_StringRecordFactory::CreateInstance(C_DataState& state, C_Variant* parent)
{
    C_StringRecord* record = new C_StringRecord(QString(),QString(),parent);

    record->SetState(state);

    return record;
}

QString C_StringRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}


