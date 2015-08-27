#include "FW/SC/scene.h"
#include "FW/macro.h"
#include "FW/ST/state_writer.h"
#include "FW/RC/record.h"
#include "FW/SC/scene_line.h"
#include <FW/RC/reference_record.h>

////////////////////////////////////////////////////////////////////////
/// Static

long C_Scene::m_IdCount = 0;

QString C_Scene::GenerateId()
{
    return QString().setNum( m_IdCount++ );
}

QString C_Scene::IdCount()
{
    return QString().setNum( m_IdCount );
}

////////////////////////////////////////////////////////////////////////

C_Scene::C_Scene( C_Document& document, C_Variant* parent ) :
    C_Variant( parent ),
    m_Document( &document ),
    m_TopZ( 0 )
{
    m_Graphics = new QGraphicsScene();
}

C_Scene::~C_Scene()
{
    delete m_Graphics;
}

C_SceneItem* C_Scene::CreateItem( C_StateWriter& state )
{
    return new C_SceneItem( *this, state );
}

C_SceneItem* C_Scene::CreateItem( C_Record& record )
{
    return new C_SceneItem( *this, record, 100 + ( qrand() % 40 - 80 ), 100 + ( qrand() % 40 - 80 ) );
}

C_SceneItem* C_Scene::CreateItem( C_Record& record, qreal x, qreal y, qreal z )
{
    return new C_SceneItem( *this, record, x, y, z );
}

QList<C_SceneItem*> C_Scene::FromRecord( C_Record& record ) const
{
    QList<C_SceneItem*> result;

    for( C_SceneItem* item : Items() )
    {
        if( & item->Record() == & record )
            result.append( item );
    }

    return result;
}

void C_Scene::Clear()
{
    Graphics().clear();
}

int C_Scene::Size()
{
    return Items().size();
}

void C_Scene::BringFront( C_SceneItem& item )
{
    m_TopZ += 0.01;
    item.setZValue( m_TopZ );
}

void C_Scene::UpdateLines()
{
    ClearLines();

    for( C_SceneItem* from : Items() )
    {
        if( from->Record().Class() == "Reference" )
        {
            C_ReferenceRecord* record_from = static_cast<C_ReferenceRecord*>( &from->Record() );

            for( C_SceneItem* target : Items() )
            {
                C_Record* record_target = &target->Record();

                if( record_from->Referencee() == record_target )
                    m_Lines.append( new C_SceneLine( *from, *target, Qt::green) );
            }
        }
        else if( from->Record().Struct() != 0 )
        {
            QList<C_ReferenceRecord*> reference_list;

            for( C_Variant* variant : *from->Record().Struct() )
            {
                C_Record* reference = static_cast<C_Record*> ( variant );

                if( reference->Class() == "Reference" )
                    reference_list.append( static_cast<C_ReferenceRecord*> ( reference ) );
            }

            for( C_ReferenceRecord* record : reference_list )
            {
                for( C_SceneItem* target : Items() )
                {
                    C_Record* record_target = &target->Record();

                    if( record->Referencee() == record_target )
                        m_Lines.append( new C_SceneLine( *from, *target, Qt::blue) );
                }
            }
        }
    }
}

void C_Scene::ClearLines()
{
    for( C_SceneLine* line : Lines() )
        delete line;
}
