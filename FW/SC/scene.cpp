#include "FW/SC/scene.h"
#include "FW/macro.h"
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

TypeScene::TypeScene( TypeDocument& document, TypeVariant* parent ) :
    TypeVariant( parent ),
    m_Document( &document ),
    m_TopZ( 0 )
{
    m_Graphics = new QGraphicsScene();
}

TypeScene::~TypeScene()
{
    delete m_Graphics;
}

TypeSceneItem* TypeScene::CreateItem( TypeStateWriter& state )
{
    return new TypeSceneItem( *this, state );
}

TypeSceneItem* TypeScene::CreateItem( TypeRecord& record )
{
    return new TypeSceneItem( *this, record, 100 + ( qrand() % 40 - 80 ), 100 + ( qrand() % 40 - 80 ) );
}

TypeSceneItem* TypeScene::CreateItem( TypeRecord& record, qreal x, qreal y, qreal z )
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

void TypeScene::UpdateLines()
{
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
                    m_Lines.append( new TypeSceneLine( *from, *target, Qt::green) );
            }
        }
        else if( from->Record().Struct() != 0 )
        {
            QList<TypeReferenceRecord*> reference_list;

            for( TypeVariant* variant : *from->Record().Struct() )
            {
                TypeRecord* reference = static_cast<TypeRecord*> ( variant );

                if( reference->Class() == "Reference" )
                    reference_list.append( static_cast<TypeReferenceRecord*> ( reference ) );
            }

            for( TypeReferenceRecord* record : reference_list )
            {
                for( TypeSceneItem* target : Items() )
                {
                    TypeRecord* record_target = &target->Record();

                    if( record->Referencee() == record_target )
                        m_Lines.append( new TypeSceneLine( *from, *target, Qt::blue) );
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
