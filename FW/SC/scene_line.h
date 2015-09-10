#ifndef SCENELINE_H
#define SCENELINE_H

#include "FW/SC/scene_item.h"
#include "FW/tools.h"


class TypeSceneLine : public QGraphicsLineItem, public TypeVariant
{
public:

    TypeSceneLine( TypeSceneItem& from, TypeSceneItem& target, Qt::GlobalColor color );
    ~TypeSceneLine() override;

    void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0 ) override;

    M_REFERENCE              ( From, TypeSceneItem )
    M_REFERENCE              ( Target, TypeSceneItem )
    M_VALUE                  ( Color, Qt::GlobalColor )
};

#endif // SCENELINE_H
