#ifndef TypeSCENE_ITEM_H
#define TypeSCENE_ITEM_H

#include "FW/macro.h"
#include "FW/variant.h"
#include <QGraphicsItem>

class TypeRecord;
class TypeScene;
class TypeStateReader;
class TypeStateWriter;

class TypeSceneItem : public TypeVariant, public QGraphicsItem
{
public:

    TypeSceneItem(TypeScene& scene, TypeStateWriter &state);
    TypeSceneItem(TypeScene& scene, TypeRecord& record, qreal x_val, qreal y_val, qreal z_val = -1);
    ~TypeSceneItem() override;

    QRectF              boundingRect() const override;
    void                paint(QPainter* painter,
                              const QStyleOptionGraphicsItem* option,
                              QWidget* widget) override;
    void                mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    void                contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;
    void                mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    QString             HeaderText() const;
    virtual bool        GetState(TypeStateReader& state);
    virtual bool        SetState(TypeStateWriter& state);

    M_POINTER           (Record,    TypeRecord)
    M_POINTER           (Scene,     TypeScene)
    M_CONST_VALUE       (Id,        QString)

private:

    friend class        TypeScene;
};

#endif // TypeSCENE_ITEM_H


