#ifndef C_SCENE_H
#define C_SCENE_H

#include "FW/variant.h"
#include "FW/macro.h"

#include <QObject>
#include <QGraphicsScene.h>


class C_SceneItem;
class C_Record;
class C_Document;
class C_DataState;

class C_Scene : public C_Variant
{
public:

    explicit                      C_Scene(C_Document& document, C_Variant *parent = 0);
                                  ~C_Scene();

    C_SceneItem*                  CreateItem(C_DataState& state);
    C_SceneItem*                  CreateItem(C_Record& record);
    C_SceneItem*                  CreateItem(C_Record& record, qreal x, qreal y, qreal z = -1);

    list<C_SceneItem*>            FromRecord(C_Record& record) const;

    void                          Clear();
    int                           Size();
    void                          BringFront(C_SceneItem& sc);

    C_POINTER                     (Document,      C_Document)
    C_POINTER                     (GraphicsScene, QGraphicsScene)

    C_VALUE                       (TopZ,  double)
    C_VALUE                       (Items, list<C_SceneItem*>)

    static QString                GenerateId();
    static QString                IdCount();

private:

    static long                   m_IdCount;

    friend class                  C_Document;
    friend class                  C_SceneItem;
};

#include "scene_item.h"

#endif // C_SCENE_H


