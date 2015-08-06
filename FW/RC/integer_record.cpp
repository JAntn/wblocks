#include "FW/RC/integer_record.h"
#include "FW/UI/ui_integer_editor.h"
#include "FW/UI/ui_main_window.h"

#include <QString>

#include <FW/data_state.h>
#include <FW/document.h>

#define CLASS_NAME "Integer"

QString C_IntegerRecord::Script() const
{
    return FullName() + " = " + Value() + ";";
}

C_RecordStruct* C_IntegerRecord::Struct() const
{
    return 0;
}

QString C_IntegerRecord::Name() const
{
    return m_Name;
}

C_IntegerRecord::C_IntegerRecord(QString name, QString value, C_Variant* parent)
    : C_Record(name,value,parent)
{
    //void
}

QString C_IntegerRecord::Id() const
{
    return m_Id;
}

QString C_IntegerRecord::Class() const
{
    return CLASS_NAME;
}

void C_IntegerRecord::ShowEditor(C_Document& document)
{
    QWidget* dialog = new C_UiIntegerEditor(*this,document,&document.MainWindow());
    dialog->show();
}

void C_IntegerRecord::GetState(C_DataState& state)
{
    QStringList row;

    row.append(m_Id);
    row.append(m_Name);
    row.append(m_Value);
    row.append(Class());

    state.Insert(row);
}

void C_IntegerRecord::SetState(C_DataState& state)
{

    QStringList row;

    state.Extract(row);

    m_Id    = row.at(0);
    m_Name  = row.at(1);
    m_Value = row.at(2);
}

QString C_IntegerRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}

C_Record* C_IntegerRecordFactory::CreateInstance(QString name, QString value, C_Variant* parent)
{
    C_IntegerRecord* record = new C_IntegerRecord(name,value,parent);

    record->m_Id = C_RecordFactory::GenerateId();

    return record;
}

C_Record* C_IntegerRecordFactory::CreateInstance(C_DataState& state, C_Variant* parent)
{
    C_IntegerRecord* record = new C_IntegerRecord(QString(),QString(),parent);

    record->SetState(state);

    return record;
}





