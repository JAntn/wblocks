#ifndef C_SCENELINE_H
#define C_SCENELINE_H

#include "FW/SC/scene_item.h"
#include "FW/macro.h"


class C_SceneLine : public QGraphicsLineItem
{
public:

    C_SceneLine(C_SceneItem& from, C_SceneItem& target);
    ~C_SceneLine() override;

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0) override;

    ATR_POINTER              (From, C_SceneItem)
    ATR_POINTER              (Target, C_SceneItem)

};

#endif // C_SCENELINE_H
