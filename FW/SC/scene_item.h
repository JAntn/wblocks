#ifndef C_SCENE_ITEM_H
#define C_SCENE_ITEM_H

#include "FW/macro.h"
#include "FW/variant.h"
#include <QGraphicsItem>

class C_Record;
class C_Scene;
class C_StateReader;
class C_StateWriter;

class C_SceneItem : public C_Variant, public QGraphicsItem
{
public:

    C_SceneItem(C_Scene& scene, C_StateWriter &state);
    C_SceneItem(C_Scene& scene, C_Record& record, qreal x_val, qreal y_val, qreal z_val = -1);
    ~C_SceneItem() override;

    QRectF              boundingRect() const override;
    void                paint(QPainter* painter,
                              const QStyleOptionGraphicsItem* option,
                              QWidget* widget) override;
    void                mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    void                contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;
    void                mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    QString             HeaderText() const;
    virtual void        GetState(C_StateReader& state);
    virtual void        SetState(C_StateWriter& state);

    ATR_POINTER         (Record, C_Record)
    ATR_POINTER         (Scene,  C_Scene)
    ATR_CONST_VALUE     (Id,     QString)

private:

    friend class        C_Scene;
};

#endif // C_SCENE_ITEM_H


