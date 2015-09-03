#ifndef SCENELINE_H
#define SCENELINE_H

#include "FW/SC/scene_item.h"
#include "FW/variant.h"
#include "FW/macro.h"


class TypeSceneLine : public QGraphicsLineItem, public TypeVariant
{
public:

    TypeSceneLine( TypeSceneItem& from, TypeSceneItem& target, Qt::GlobalColor color );
    ~TypeSceneLine() override;

    void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0 ) override;

    M_POINTER                ( From, TypeSceneItem )
    M_POINTER                ( Target, TypeSceneItem )
    M_VALUE                  ( Color, Qt::GlobalColor )
};

#endif // SCENELINE_H
