#ifndef SCENEITEM_H
#define SCENEITEM_H

#include "FW/tools.h"
#include <QGraphicsItem>

class TypeRecord;
class TypeScene;
class TypeStateReader;
class TypeStateWriter;

class TypeSceneItem : public TypeVariant, public QGraphicsItem
{
public:

    TypeSceneItem( TypeScene& scene, TypeStateWriter& state );
    TypeSceneItem( TypeScene& scene, TypeRecord& record, qreal x_val, qreal y_val, qreal z_val = -1 );
    ~TypeSceneItem() override;

    QRectF                                  boundingRect() const override;
    void                                    paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget ) override;

    void                                    mouseDoubleClickEvent( QGraphicsSceneMouseEvent* event ) override;
    void                                    contextMenuEvent( QGraphicsSceneContextMenuEvent* event ) override;
    void                                    mousePressEvent( QGraphicsSceneMouseEvent* event ) override;

    QString                                 HeaderText() const;
    virtual bool                            GetState( TypeStateReader& state );
    virtual bool                            SetState( TypeStateWriter& state );

    M_REFERENCE                             ( Record,    TypeRecord )
    M_REFERENCE                             ( Scene,     TypeScene )
    M_VALUE_READONLY                        ( Id,        QString )

private:

    friend class        TypeScene;
    void                                    GetInfo(int* line_height, int* line_num, QString* text, QString* header_text ) const;
};

#endif // SCENEITEM_H


