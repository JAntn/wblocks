#ifndef SCENE_H
#define SCENE_H

#include "FW/tools.h"
#include <QGraphicsScene>

class TypeSceneItem;
class TypeRecord;
class TypeController;
class TypeStateWriter;
class TypeSceneLine;

class TypeScene : public TypeVariant
{
public:

    explicit TypeScene( TypeController& controller, TypeVariant* Parent = 0 );
    ~TypeScene() override;

    static QString                          GenerateId();
    static QString                          IdCount();

    void                                    Clear();
    int                                     Size();
    TypeSceneItem*                          NewItem( TypeStateWriter& state );
    TypeSceneItem*                          NewItem( TypeRecord& record );
    TypeSceneItem*                          NewItem( TypeRecord& record, qreal x, qreal y, qreal z = -1 );
    QList<TypeSceneItem*>                   FromRecord( TypeRecord& record ) const;

    void                                    BringFront( TypeSceneItem& sc );

    void                                    UpdateView();
    void                                    ClearLines();

    M_REFERENCE                             ( Controller,     TypeController )
    M_REFERENCE                             ( Graphics,       QGraphicsScene )
    M_VALUE                                 ( TopZ,           double )
    M_VALUE                                 ( Items,          QList<TypeSceneItem*> )
    M_VALUE                                 ( Lines,          QList<TypeSceneLine*> )

private:

    static long                             m_IdCount;

    friend class                            TypeSceneItem;
    friend class                            TypeSceneLine;
    friend class                            TypeDocument;
};



#endif // SCENE_H

#include "scene_item.h"

