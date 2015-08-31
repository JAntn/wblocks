#include "FW/SC/scene.h"
#include "FW/RC/record.h"
#include "FW/document.h"
#include "FW/UI/ui_scene_item_context_menu.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QPainter>
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"

#define GFX_THICK 1
#define GFX_THIN 1
#define GFX_BLACK_BRUSH                     QBrush(QColor(0,0,0))
#define GFX_WHITE_BRUSH                     QBrush(QColor(255,255,255))
#define GFX_OUTER_RECT(__WIDTH)             QRectF(0,0,__WIDTH+10+2*GFX_THICK,50+5+2*GFX_THICK)
#define GFX_TEXT_RECT(__WIDTH)              QRectF(GFX_THICK+5,GFX_THICK+5,__WIDTH,20)
#define GFX_VALUE_RECT(__WIDTH)             QRectF(GFX_THICK+5,GFX_THICK+5+20,__WIDTH,20)
#define GFX_SEPARATOR_LINE(__WIDTH)         QLine(GFX_THICK,GFX_THICK+5+19,__WIDTH+10+GFX_THICK,GFX_THICK+5+19)

TypeSceneItem::TypeSceneItem( TypeScene& scene, TypeStateWriter& state ) :
    TypeVariant( 0 ),
    m_Scene( &scene )
{
    SetState( state );
    SetParent( &Record() );
    Scene().Items().append( this );
    Scene().Graphics().addItem( this );
    setFlag( QGraphicsItem::ItemIsMovable );
}

TypeSceneItem::TypeSceneItem( TypeScene& scene, TypeRecord& record, qreal x_val, qreal y_val, qreal z_val ):
    TypeVariant( 0 ),
    m_Record( &record ),
    m_Scene( &scene )

{
    m_Id = Scene().GenerateId();
    SetParent( &Record() );
    Scene().Items().append( this );
    Scene().Graphics().addItem( this );
    setFlag( QGraphicsItem::ItemIsMovable );
    setPos( x_val, y_val );

    if( z_val < 0 )
        Scene().BringFront( *this );
    else
        setZValue( z_val );
}

TypeSceneItem::~TypeSceneItem()
{
    Scene().Items().removeOne( this );
}


QString TypeSceneItem::HeaderText() const
{
    return Record().FullName() + " : " + Record().Class();
}

QRectF TypeSceneItem::boundingRect() const
{
    QFontMetrics fm( scene()->font() );
    int header_width = fm.width( HeaderText() );

    if( header_width < 200 )
        header_width = 200;

    return GFX_OUTER_RECT( header_width );
}

void TypeSceneItem::paint( QPainter* painter, const QStyleOptionGraphicsItem*, QWidget* )
{

    QFontMetrics fm( this->scene()->font() );
    int header_width = fm.width( HeaderText() );

    if( header_width < 200 )
        header_width = 200;

    painter->fillRect( GFX_OUTER_RECT( header_width ), GFX_WHITE_BRUSH );
    painter->setPen( QPen( GFX_BLACK_BRUSH, GFX_THICK ) );
    painter->drawRect( GFX_OUTER_RECT( header_width ) );
    painter->drawText( GFX_TEXT_RECT( header_width ), HeaderText() );
    painter->drawText( GFX_VALUE_RECT( header_width ), Record().Value() );
    painter->drawLine( GFX_SEPARATOR_LINE( header_width ) );
}

void TypeSceneItem::mousePressEvent( QGraphicsSceneMouseEvent* )
{
    Scene().BringFront( *this );
}

bool TypeSceneItem::GetState( TypeStateReader& state )
{
    QStringList row;
    row << Id();
    row << Record().Id();
    row << QString::number( x() );
    row << QString::number( y() );
    row << QString::number( zValue() );
    state.Read( row );

    return true;
}

bool TypeSceneItem::SetState( TypeStateWriter& state )
{
    QStringList row;
    state.Write( row );
    m_Id = row[0];
    m_Record = Scene().Document().Root().FromId( row[1], true );
    setPos( row[2].toFloat(), row[3].toFloat() );
    setZValue( row[4].toFloat() );

    return true;
}

void TypeSceneItem::mouseDoubleClickEvent( QGraphicsSceneMouseEvent* )
{
    Record().PropertyWidget( Scene().Document().Controller() );
}

void TypeSceneItem::contextMenuEvent( QGraphicsSceneContextMenuEvent* event )
{
    TypeUiSceneItemContextMenu context_menu( *this, event );
}




