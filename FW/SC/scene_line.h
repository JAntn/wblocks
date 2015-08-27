#ifndef C_SCENELINE_H
#define C_SCENELINE_H

#include "FW/SC/scene_item.h"
#include "FW/macro.h"


class C_SceneLine : public QGraphicsLineItem
{
public:

    C_SceneLine( C_SceneItem& from, C_SceneItem& target, Qt::GlobalColor color );
    ~C_SceneLine() override;

    void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0 ) override;

    M_POINTER                ( From, C_SceneItem )
    M_POINTER                ( Target, C_SceneItem )
    M_VALUE                  ( Color, Qt::GlobalColor )
};

#endif // C_SCENELINE_H
