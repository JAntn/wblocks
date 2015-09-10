#include "FW/SC/scene.h"
#include "FW/tools.h"
#include "FW/ST/state_writer.h"
#include "FW/RC/record.h"
#include "FW/SC/scene_line.h"
#include <FW/RC/reference_record.h>

////////////////////////////////////////////////////////////////////////
/// Static

long TypeScene::m_IdCount = 0;

QString TypeScene::GenerateId()
{
    return QString().setNum( m_IdCount++ );
}

QString TypeScene::IdCount()
{
    return QString().setNum( m_IdCount );
}

////////////////////////////////////////////////////////////////////////

TypeScene::TypeScene( TypeController& controller, TypeVariant* parent ) :
    TypeVariant( parent ),
    m_Controller( &controller ),
    m_TopZ( 0 )
{
    m_Graphics = new QGraphicsScene();
}

TypeScene::~TypeScene()
{
    delete m_Graphics;
}

TypeSceneItem* TypeScene::NewItem( TypeStateWriter& state )
{
    return new TypeSceneItem( *this, state );
}

TypeSceneItem* TypeScene::NewItem( TypeRecord& record )
{
    return new TypeSceneItem( *this, record, 100 + ( qrand() % 40 - 80 ), 100 + ( qrand() % 40 - 80 ) );
}

TypeSceneItem* TypeScene::NewItem( TypeRecord& record, qreal x, qreal y, qreal z )
{
    return new TypeSceneItem( *this, record, x, y, z );
}

QList<TypeSceneItem*> TypeScene::FromRecord( TypeRecord& record ) const
{
    QList<TypeSceneItem*> result;

    for( TypeSceneItem* item : Items() )
    {
        if( & item->Record() == & record )
            result.append( item );
    }

    return result;
}

void TypeScene::Clear()
{
    Graphics().clear();
}

int TypeScene::Size()
{
    return Items().size();
}

void TypeScene::BringFront( TypeSceneItem& item )
{
    m_TopZ += 0.01;
    item.setZValue( m_TopZ );
}

void TypeScene::UpdateView()
{

    // Update lines

    ClearLines();

    for( TypeSceneItem* from : Items() )
    {
        if( from->Record().Class() == "Reference" )
        {
            TypeReferenceRecord* record_from = static_cast<TypeReferenceRecord*>( &from->Record() );

            for( TypeSceneItem* target : Items() )
            {
                TypeRecord* record_target = &target->Record();

                if( record_from->Referencee() == record_target )
                    m_Lines.append( new TypeSceneLine( *from, *target, Qt::green ) );
            }
        }
        else if( from->Record().Struct() != 0 )
        {
            QList<TypeReferenceRecord*> reference_list;

            for( TypeVariantPtr<TypeRecord> record : *from->Record().Struct() )
            {
                if( record->Class() == "Reference" )
                {
                    TypeVariantPtr<TypeReferenceRecord> reference( record );
                    reference_list.append( reference );
                }
            }

            for( TypeReferenceRecord* record : reference_list )
            {
                for( TypeSceneItem* target : Items() )
                {
                    TypeRecord* record_target = &target->Record();

                    if( record->Referencee() == record_target )
                        m_Lines.append( new TypeSceneLine( *from, *target, Qt::blue ) );
                }
            }
        }
    }
}

void TypeScene::ClearLines()
{
    for( TypeSceneLine* line : Lines() )
        delete line;
}
