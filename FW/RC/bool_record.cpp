
#include "FW/RC/bool_record.h"

#include "FW/UI/ui_bool_editor.h"
#include "FW/UI/ui_main_window.h"

#include "ui_booleditor.h"

#include <FW/data_state.h>

#include <FW/document.h>

#define CLASS_NAME "Bool"

C_BoolRecord::C_BoolRecord(QString name, QString value, C_Variant* parent)
    : C_Record(name,value,parent)
{
    // void
}

QString C_BoolRecord::Script() const
{
    return  FullName() + " = " + Value() + ";";
}

C_RecordStruct* C_BoolRecord::Struct() const
{
    return 0;
}

QString C_BoolRecord::Name() const
{
    return m_Name;
}


QString C_BoolRecord::Id() const
{
    return m_Id;
}

QString C_BoolRecord::Class() const
{
    return CLASS_NAME;
}

void C_BoolRecord::ShowEditor(C_Document& document)
{
    QWidget* dialog = new C_UiBoolEditor(*this,document,&document.MainWindow());
    dialog->show();
}

void C_BoolRecord::GetState(C_DataState& state)
{
    QStringList row;

    row.append(m_Id);
    row.append(m_Name);
    row.append(m_Value);
    row.append(Class());

    state.Insert(row);
}

void C_BoolRecord::SetState(C_DataState& state)
{
    QStringList row;

    state.Extract(row);

    m_Id    = row.at(0);
    m_Name  = row.at(1);
    m_Value = row.at(2);
}


C_Record* C_BoolRecordFactory::CreateInstance(QString name, QString value, C_Variant* parent)
{
    C_BoolRecord* record = new C_BoolRecord(name,value,parent);

    record->m_Id = C_RecordFactory::GenerateId();

    return record;
}

C_Record* C_BoolRecordFactory::CreateInstance(C_DataState& state, C_Variant* parent)
{
    C_BoolRecord* record = new C_BoolRecord(QString(),QString(),parent);

    record->SetState(state);

    return record;
}

QString C_BoolRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}



