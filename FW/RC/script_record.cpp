#include "FW/RC/script_record.h"
#include "FW/RC/string_record.h"

#include "FW/document.h"
#include "FW/data_state.h"

#include "bool_record.h"

#include "FW/UI/ui_main_window.h"
#include "FW/RC/string_record.h"
#include <FW/UI/ui_script_editor.h>
#include "FW/RC/record_struct.h"

#define CLASS_NAME "Script"

C_ScriptRecord::C_ScriptRecord(QString name, C_Variant* parent)
    : C_Record(name,"0",parent)
{
    m_Records = new C_RecordStruct(name,this);

    m_IsFromFile = static_cast<C_BoolRecord*>   ( Records().CreateRecord("IsFromFile", "False", "Bool") );
    m_Code       = static_cast<C_StringRecord*> ( Records().CreateRecord("Code", "//Script: \n", "String") );
    m_FileName   = static_cast<C_StringRecord*> ( Records().CreateRecord("FileName", "", "String") );
}

QString C_ScriptRecord::Script() const
{
    // TODO load file
    return Code().Value();
}

C_RecordStruct* C_ScriptRecord::Struct() const
{
    return m_Records;
}

QString C_ScriptRecord::Name() const
{
    return m_Name;
}

QString C_ScriptRecord::Value() const
{
    return QString::number(Records().Size());
}

void C_ScriptRecord::SetValue(QString)
{
    // void
}

QString C_ScriptRecord::Id() const
{
    return m_Id;
}

QString C_ScriptRecord::Class() const
{
    return CLASS_NAME;
}

void C_ScriptRecord::ShowEditor(C_Document& document)
{
    QWidget* dialog = new C_UiScriptEditor(*this,document,&document.MainWindow());
    dialog->show();
}

void C_ScriptRecord::GetState(C_DataState& state)
{
    QStringList row;

    row.append(Id());
    row.append(Name());
    row.append(Value());
    row.append(Class());

    state.Insert(row);

    m_IsFromFile ->GetState(state);
    m_Code       ->GetState(state);
    m_FileName   ->GetState(state);
}

void C_ScriptRecord::SetState(C_DataState& state)
{
    QStringList row;

    state.Extract(row);

    m_Id    = row.at(0);
    m_Name  = row.at(1);
    m_Value = row.at(2);

    m_IsFromFile ->SetState(state);
    m_Code       ->SetState(state);
    m_FileName   ->SetState(state);

    if( m_IsFromFile->Value() == "True" ) {
        m_Code->SetValue(C_Document::LoadTextFile(m_FileName->Value()));
    }
}


C_Record* C_ScriptRecordFactory::CreateInstance(QString name, QString, C_Variant* parent)
{
    C_ScriptRecord *record = new C_ScriptRecord(name,parent);

    record->m_Id = C_RecordFactory::GenerateId();

    return record;
}

C_Record* C_ScriptRecordFactory::CreateInstance(C_DataState& state, C_Variant* parent)
{
    C_ScriptRecord *record = new C_ScriptRecord(state.Data().at(1),parent);

    record->SetState(state);

    return record;
}

QString C_ScriptRecordFactory::RecordClass() const
{
    return CLASS_NAME;
}

