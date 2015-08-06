#include "FW/RC/struct_record.h"
#include "FW/RC/record.h"
#include "FW/SC/scene.h"
#include "FW/database.h"
#include "FW/document.h"
#include "data_state.h"

#include "FW/UI/ui_main_window.h"
#include <QMessageBox>
#include <QStack>
#include <QDebug>

QString C_Document::LoadTextFile(QString file_name)
{
    QFile file(file_name);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString();
    }

    return file.readAll();
}

void C_Document::SaveTextFile(QString file_name,QString text)
{
    QFile file(file_name);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    out << text;
}

C_Document::C_Document(C_UiMainWindow& main_window, C_Variant* parent):
    C_Variant(parent),
    m_MainWindow(&main_window)
{
    C_RecordStruct::InitFactoryList();

    m_Records           = new C_RecordStruct("root",this);
    m_Scene             = new C_Scene(*this,this);
    m_Context           = new C_Context(Records(),Scene(),this);
    m_Script            = new C_Script(*this,this);
    m_Database          = new C_Database(this);
    m_Signals           = new C_Signals(*this,main_window,&main_window);

    // Sample document

    C_Record* record = Records().CreateRecord("SampleRecord","Monday Thursday Wednesday Tuesday Friday Saturday Sunday","String");

    Scene().CreateItem(*record);
    Script().Generate(Records());

    emit Signals().RecordsChanged();
    emit Signals().SceneChanged();
    emit Signals().ScriptChanged();
}


void C_Document::UpdateScript()
{
    Script().Generate(Records());
}

void C_Document::UpdateScene()
{
    emit Signals().SceneChanged();
}

C_Record* C_Document::RecordAtId(QString id)
{
    auto iter = Records().begin();
    auto iter_end = Records().end();
    list<decltype(iter)> stack, stack_end;

    stack.push_back(iter);
    stack_end.push_back(iter_end);

    while(!stack.empty())
    {
        while(iter != iter_end)
        {
            auto record = static_cast<C_Record*>(*iter);

            if(record->Id() == id) {
                return record;
            }

            if(record->Struct() != 0)
            {
                stack.push_back(iter);
                stack_end.push_back(iter_end);

                auto record_struct = record->Struct();

                iter = record_struct->begin();
                iter_end = record_struct->end();
            }
            else {
                ++iter;
            }
        }

        iter = stack.back();
        stack.pop_back();

        iter_end = stack_end.back();
        stack_end.pop_back();
    }

    return 0;
}

C_Record* C_Document::RecordAtName(QString name)
{
    auto iter = Records().begin();
    auto iter_end = Records().end();
    list<decltype(iter)> stack, stack_end;


    stack.push_back(iter);
    stack_end.push_back(iter_end);

    while(!stack.empty())
    {
        while(iter != iter_end)
        {
            auto record = static_cast<C_Record*>(*iter);

            if(record->Name() == name) {
                return record;
            }

            if( record->Struct() != 0 )
            {
                stack.push_back(iter);
                stack_end.push_back(iter_end);

                auto record_struct = record->Struct();

                iter = record_struct->begin();
                iter_end = record_struct->end();
            }
            else {
                ++iter;
            }
        }

        iter = stack.back();
        stack.pop_back();

        iter_end = stack_end.back();
        stack_end.pop_back();
    }

    return 0;
}


void C_Document::Clear()
{
    Context().SetRecords(Records());
    Scene().Clear();
    Records().Clear();

    emit Signals().RecordsChanged();
    emit Signals().SceneChanged();
}

bool C_Document::AcceptMessage(QString msg)
{
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.exec();

    if( msgBox.result() == QMessageBox::Cancel )
        return false;

    return true;
}

void C_Document::Message(QString msg)
{
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.exec();
}

void C_Document::FileSave(QFile &file)
{
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    out << C_RecordFactory::IdCount();
    out << C_Scene::IdCount();
    out << QString::number(Records().Size());
    out << QString::number(Scene().Size());

    /////////////////////////////////////////////////////////////////////////

    C_DataStateStream record_state(out,C_DataState::stream_type::out);
    record_state.Next();

    for(C_Variant* node : Records())
    {
        auto
        record = static_cast<C_Record*>(node);
        record->GetState(record_state);
    }
    record_state.Stop();

    /////////////////////////////////////////////////////////////////////////

    C_DataStateStream scene_state(out,C_DataState::stream_type::out);
    scene_state.Next();

    for(C_SceneItem* item : Scene().Items())
    {
        item->GetState(scene_state);
    }
    scene_state.Stop();

}

void C_Document::FileLoad(QFile &file)
{

    Clear();

    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);

    // head

    QString val;

    in >> val;
    C_RecordFactory::m_IdCount = val.toLong();

    in >> val;
    C_Scene::m_IdCount = val.toLong();

    in >> val;
    long record_max = val.toLong();

    in >> val;
    long scene_item_max = val.toLong();

    /////////////////////////////////////////////////////////////////////////

    C_DataStateStream record_state(in,C_DataState::stream_type::in);
    record_state.Next();

    while(!record_state.AtEnd()) {
        Records().CreateRecord(record_state);
    }

    /////////////////////////////////////////////////////////////////////////

    C_DataStateStream scene_state(in,C_DataState::stream_type::in);
    scene_state.Next();

    while(!scene_state.AtEnd()) {
        Scene().CreateItem(scene_state);
    }

    emit Signals().RecordsChanged();    
}

#define FIELD(__NAME)   "[?#"+QString(__NAME)+"]"

void C_Document::DatabaseSave(QString file_name)
{
    QFile::remove(file_name);
    Database().OpenDatabase(file_name);

    //
    // Setup table

    QStringList row;
    row << FIELD("ROW") << FIELD("VALUE");
    Database().CreateTable(FIELD("SETUP_TABLE"),row);

    //
    // Fill setup table

    row.clear();
    row << FIELD("RECORD_ID_COUNT") << C_RecordFactory::IdCount();
    Database().AppendRecord(FIELD("SETUP_TABLE"),row);

    row.clear();
    row << FIELD("SCENE_ID_COUNT") << C_Scene::IdCount();
    Database().AppendRecord(FIELD("SETUP_TABLE"),row);

    /////////////////////////////////////////////////////////////////////////

    //
    // Record item stack table

    QStringList record_fields;
    record_fields.append(FIELD("ROW"));
    record_fields.append(FIELD("ID"));
    record_fields.append(FIELD("NAME"));
    record_fields.append(FIELD("VALUE"));
    record_fields.append(FIELD("CLASS_NAME"));

    Database().CreateTable(FIELD("RECORD_TABLE"),record_fields);

    // Fill table

    C_DataStateDatabase record_state(Database(),FIELD("RECORD_TABLE"),FIELD("ROW"),-1,C_DataState::stream_type::out);
    record_state.Next();

    for(C_Variant* node : Records())
    {
        C_Record* record = static_cast<C_Record*>(node);
        record->GetState(record_state);
    }
    record_state.Stop();

    row.clear();
    row << FIELD("RECORD_NUM") << QString::number(record_state.RowMax());
    Database().AppendRecord(FIELD("SETUP_TABLE"),row);

    /////////////////////////////////////////////////////////////////////////

    //
    // Scene item stack table

    QStringList scene_fields;
    scene_fields.append(FIELD("ROW"));
    scene_fields.append(FIELD("ID"));
    scene_fields.append(FIELD("RECORD_ID"));
    scene_fields.append(FIELD("X"));
    scene_fields.append(FIELD("Y"));
    scene_fields.append(FIELD("Z"));

    Database().CreateTable(FIELD("SCENE_TABLE"),scene_fields);

    C_DataStateDatabase scene_state(Database(),FIELD("SCENE_TABLE"),FIELD("ROW"),-1,C_DataState::stream_type::out);
    scene_state.Next();

    for(C_SceneItem* item : Scene().Items())
    {
        item->GetState(scene_state);
    }
    scene_state.Stop();

    row.clear();
    row << FIELD("SCENEITEM_NUM") << QString::number(scene_state.RowMax());
    Database().AppendRecord(FIELD("SETUP_TABLE"),row);

    /////////////////////////////////////////////////////////////////////////

    Database().CloseDatabase();
}

void C_Document::DatabaseLoad(QString file_name)
{
    Clear();
    Database().OpenDatabase(file_name);

    QStringList row;

    row = Database().GetRecord(FIELD("SETUP_TABLE"), FIELD("ROW"), FIELD("RECORD_ID_COUNT"));
    C_RecordFactory::m_IdCount = row.at(1).toInt();

    row = Database().GetRecord(FIELD("SETUP_TABLE"), FIELD("ROW"), FIELD("SCENE_ID_COUNT"));
    C_Scene::m_IdCount = row.at(1).toInt();

    row = Database().GetRecord(FIELD("SETUP_TABLE"), FIELD("ROW"), FIELD("RECORD_NUM"));
    int record_num = row.at(1).toInt();

    row = Database().GetRecord(FIELD("SETUP_TABLE"), FIELD("ROW"), FIELD("SCENEITEM_NUM"));
    int sceneitem_num = row.at(1).toInt();

    /////////////////////////////////////////////////////////////////////////

    C_DataStateDatabase record_state(Database(),FIELD("RECORD_TABLE"),FIELD("ROW"),record_num,C_DataState::stream_type::in);
    record_state.Next();

    while(!record_state.AtEnd()) {
        Records().CreateRecord(record_state);
    }

    /////////////////////////////////////////////////////////////////////////

    C_DataStateDatabase scene_state(Database(),FIELD("SCENE_TABLE"),FIELD("ROW"),sceneitem_num,C_DataState::stream_type::in);
    scene_state.Next();

    while(!scene_state.AtEnd()) {
        Scene().CreateItem(scene_state);
    }

    /////////////////////////////////////////////////////////////////////////

    Database().CloseDatabase();

    emit Signals().RecordsChanged();
    emit Signals().SceneChanged();
}

