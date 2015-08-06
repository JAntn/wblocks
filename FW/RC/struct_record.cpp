#include "FW/RC/struct_record.h"
#include "FW/document.h"
#include "FW/data_state.h"
#include "FW/UI/ui_main_window.h"
#include <FW/UI/ui_struct_editor.h>

#define CLASS_NAME "Struct"

C_StructRecord::C_StructRecord(QString name, C_Variant* parent)
    :C_Record(name,QString(),parent)
{
    m_Records = new C_RecordStruct(name,this);
}

C_StructRecord::~C_StructRecord()
{
    delete m_Records;
}

QString C_StructRecord::Id() const
{
    return m_Id;
}

QString C_StructRecord::Name() const
{
    return m_Name;
}

QString C_StructRecord::Value() const
{
    return QString::number(Records().Size());
}

void C_StructRecord::SetValue(QString)
{
    // void
}

QString C_StructRecord::Class() const
{
    return CLASS_NAME;
}

C_RecordStruct* C_StructRecord::Struct() const
{
    return m_Records;
}

QString C_StructRecord::Script() const
{   

    QStringList script;
    script << FullName() << " = {} ;";

    for( C_Variant* node: Records() )
    {
        script << "\n" << static_cast<C_Record*>(node)->Script() ;
    }

    return script.join("");
}

void C_StructRecord::GetState(C_DataState& state)
{
    QStringList row;

    row.append(Id());
    row.append(Name());
    row.append(Value());
    row.append(Class());

    state.Insert(row);

    for(C_Variant* node : Records())
    {
        C_Record* record = static_cast<C_Record*>(node);
        record->GetState(state);
    }
}

void C_StructRecord::SetState(C_DataState& state)
{
    Records().Clear();

    QStringList row;

    state.Extract(row);

    m_Id    = row.at(0);
    m_Name  = row.at(1);    
    m_Value = row.at(2);

    int size = m_Value.toInt();

    for(int count = 0; count < size; ++count)
    {
        Records().CreateRecord(state);
    }
}

void C_StructRecord::ShowEditor(C_Document& document)
{
    QWidget* dialog = new C_UiStructEditor(*this,document,&document.MainWindow());
    dialog->show();
}

C_Record* C_StructRecordFactory::CreateInstance(QString name, QString, C_Variant* parent)
{
    C_StructRecord *record = new C_StructRecord(name,parent);

    record->m_Id = C_RecordFactory::GenerateId();


    return record;
}

C_Record* C_StructRecordFactory::CreateInstance(C_DataState& state, C_Variant* parent)
{    
    C_StructRecord *record = new C_StructRecord(state.Data().at(1),parent);

    record->SetState(state);

    return record;
}

QString C_StructRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}
