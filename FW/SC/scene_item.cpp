#include "FW/SC/scene.h"
#include "FW/RC/record.h"
#include "FW/document.h"
#include "FW/UI/ui_sceneitem_contextmenu.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QPainter>
#include "FW/ST/state_reader.h"
#include "FW/ST/state_writer.h"
#include "FW/RC/root_struct.h"

#define GFX_THICK 1
#define GFX_THIN 1
#define GFX_BLACK_BRUSH                     QBrush(QColor(100,100,100))
#define GFX_WHITE_BRUSH                     QBrush(QColor(255,255,255))
#define GFX_GREY_BRUSH1                     QBrush(QColor(250,250,250))
#define GFX_GREY_BRUSH2                     QBrush(QColor(200,200,200))

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
    return Record().Name() + " : " + Record().Class();
}

void TypeSceneItem::GetInfo( int* line_height, int* line_num, QString* text, QString* header_text ) const
{
    QFontMetrics fm( this->scene()->font() );

    *line_num = 1;
    *header_text = HeaderText();
    *line_height = fm.height();

    if( Record().Struct() != 0 )
    {
        *line_num = Record().Struct()->Size();

        for( TypeVariantPtr<TypeRecord> record : *Record().Struct() )
        {
            QString line_text =
                record->Name() +
                " : " +
                record->Class() +
                " = " +
                record->Value().split( "\n" ).front()  +
                "\n";

            ( *text ).append( line_text );
        }
    }
    else
        *text = Record().Value().split( "\n" ).front();
}

QRectF TypeSceneItem::boundingRect() const
{
    int line_num, line_height;
    QString text;
    QString header_text;
    GetInfo( &line_height, &line_num, &text, &header_text );

    return QRect( 0, 0, 320 + 18, line_height * ( line_num + 1 ) + 36 );
}


void TypeSceneItem::paint( QPainter* painter, const QStyleOptionGraphicsItem*, QWidget* )
{
    int line_num, line_height;
    QString text;
    QString header_text;
    GetInfo( &line_height, &line_num, &text, &header_text );

    painter->fillRect( 1, 1, 320 + 18 - 2, line_height * ( line_num + 1 ) + 36 - 2, GFX_GREY_BRUSH1 );

    QPen pen = QPen( QColor( 200, 200, 200 ), 1, Qt::SolidLine );
    painter->setPen( pen );
    painter->drawRect( 0, 0, 320 + 18, line_height * ( line_num + 1 ) + 36 );

    pen = QPen( QColor( 0, 0, 230 ), 1, Qt::SolidLine );
    painter->setPen( pen );

    painter->drawText( 9, 9, 320, line_height, Qt::AlignLeft, header_text );
    painter->drawText( 9, 27 + line_height, 320, 27 + line_height + ( line_height * line_num ), Qt::AlignLeft, text );

    pen = QPen( QColor( 200, 200, 200 ), 1, Qt::SolidLine );
    painter->setPen( pen );
    painter->drawLine( 1, 18 + line_height, 320 + 18 - 1 , 18 + line_height );

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

    TypeRootStruct& root = Scene().Controller().Document().Root();
    m_Record = root.FromId( row[1], true );

    setPos( row[2].toFloat(), row[3].toFloat() );
    setZValue( row[4].toFloat() );

    return true;
}

void TypeSceneItem::mouseDoubleClickEvent( QGraphicsSceneMouseEvent* )
{
    emit Scene().Controller().SetActiveRecord( &Record() );
}

void TypeSceneItem::contextMenuEvent( QGraphicsSceneContextMenuEvent* event )
{
    TypeUiSceneItemContextMenu context_menu( Scene().Controller(), *this, event );
}




