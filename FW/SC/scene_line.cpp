#include "FW/SC/scene_line.h"
#include "FW/SC/scene.h"
#include <QGraphicsItem>

C_SceneLine::C_SceneLine( C_SceneItem& from, C_SceneItem& target , Qt::GlobalColor color )
    : QGraphicsLineItem( &from )
{
    SetFrom( from );
    SetTarget( target );
    SetColor( color );
}

C_SceneLine::~C_SceneLine()
{
    From().Scene().Lines().removeOne( this );
}

void C_SceneLine::paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget )
{
    qreal x1, y1, x2, y2;
    x1 = From().scenePos().x();
    y1 = From().scenePos().y();
    x2 = Target().scenePos().x();
    y2 = Target().scenePos().y();

    if( abs( y2 - y1 ) < From().boundingRect().height() )
    {
        if( x1 > x2 )
            setLine( 0, From().boundingRect().height() / 2, x2 + Target().boundingRect().width() - x1 , y2 + ( Target().boundingRect().height() / 2 ) - y1 );
        else
            setLine( From().boundingRect().width(), Target().boundingRect().height() / 2, x2 - x1, y2 + ( Target().boundingRect().height() / 2 ) - y1 );
    }
    else
    {
        if( y1 > y2 )
            setLine( 100, 0, x2 - x1 + 100, y2 + Target().boundingRect().height() - y1 );
        else
            setLine( 100, From().boundingRect().height(), x2 - x1 + 100, y2 - y1 );
    }

    setPen( QPen( Color(), 1 ) );
    this->QGraphicsLineItem::paint( painter, option, widget );
}

