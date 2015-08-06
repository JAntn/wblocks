
#include "FW/RC/real_record.h"

#include "FW/UI/ui_real_editor.h"
#include "FW/UI/ui_main_window.h"

#include "ui_realeditor.h"

#include <FW/data_state.h>

#include <FW/document.h>

#define CLASS_NAME "Real"

C_RealRecord::C_RealRecord(QString name, QString value, C_Variant* parent)
    : C_Record(name,value,parent)
{
    // void
}

QString C_RealRecord::Script() const
{
    return  FullName() + " = " + Value() + ";";
}

C_RecordStruct* C_RealRecord::Struct() const
{
    return 0;
}

QString C_RealRecord::Name() const
{
    return m_Name;
}

QString C_RealRecord::Id() const
{
    return m_Id;
}

QString C_RealRecord::Class() const
{
    return CLASS_NAME;
}

void C_RealRecord::ShowEditor(C_Document& document)
{
    QWidget* dialog = new C_UiRealEditor(*this,document,&document.MainWindow());
    dialog->show();
}

void C_RealRecord::GetState(C_DataState& state)
{
    QStringList row;

    row.append(m_Id);
    row.append(m_Name);
    row.append(m_Value);
    row.append(Class());

    state.Insert(row);
}

void C_RealRecord::SetState(C_DataState& state)
{
    QStringList row;

    state.Extract(row);

    m_Id    = row.at(0);
    m_Name  = row.at(1);
    m_Value = row.at(2);
}


C_Record* C_RealRecordFactory::CreateInstance(QString name, QString value, C_Variant* parent)
{
    C_RealRecord* record = new C_RealRecord(name,value,parent);

    record->m_Id = C_RecordFactory::GenerateId();

    return record;
}

C_Record* C_RealRecordFactory::CreateInstance(C_DataState& state, C_Variant* parent)
{
    C_RealRecord* record = new C_RealRecord(QString(),QString(),parent);

    record->SetState(state);

    return record;
}

QString C_RealRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}



