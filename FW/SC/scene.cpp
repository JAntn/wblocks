#include "FW/SC/scene.h"
#include "FW/macro.h"

#include <FW/ST/state_writer.h>

////////////////////////////////////////////////////////////////////////
/// Static

long C_Scene::m_IdCount = 0;

QString C_Scene::GenerateId()
{
    return QString().setNum(m_IdCount++);
}

QString C_Scene::IdCount()
{
    return QString().setNum(m_IdCount);
}

////////////////////////////////////////////////////////////////////////

C_Scene::C_Scene(C_Document& document, C_Variant* parent) :
    C_Variant(parent),
    m_Document(&document),
    m_TopZ(0)
{
    m_GraphicsScene = new QGraphicsScene();
}

C_Scene::~C_Scene(){
    delete m_GraphicsScene;
}

C_SceneItem* C_Scene::CreateItem(C_StateWriter& state)
{
    return new C_SceneItem(*this,state);
}

C_SceneItem* C_Scene::CreateItem(C_Record& record)
{
    return new C_SceneItem(*this,record,100 + (qrand()%40-80),100 + (qrand()%40-80));
}

C_SceneItem* C_Scene::CreateItem(C_Record& record, qreal x, qreal y, qreal z)
{
    return new C_SceneItem(*this,record,x,y,z);
}

list<C_SceneItem*> C_Scene::FromRecord(C_Record& record) const
{
    list<C_SceneItem*> result;

    for(C_SceneItem* item : Items())
    {
        if( & item->Record() == & record )
        {
            result.push_back(item);
        }
    }
    return result;
}

void C_Scene::Clear()
{
    GraphicsScene().clear();
}

int C_Scene::Size()
{
    return Items().size();
}

void C_Scene::BringFront(C_SceneItem& item)
{
    m_TopZ += 0.01;
    item.setZValue(m_TopZ);
}

