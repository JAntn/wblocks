#ifndef C_SCENE_H
#define C_SCENE_H

#include "FW/variant.h"
#include "FW/macro.h"
#include <QObject>
#include <QGraphicsScene>

class C_SceneItem;
class C_Record;
class C_Document;
class C_StateWriter;
class C_SceneLine;

class C_Scene : public C_Variant
{
public:

    explicit C_Scene( C_Document& document, C_Variant* parent = 0 );
    ~C_Scene() override;

    static QString                GenerateId();
    static QString                IdCount();

    C_SceneItem*                  CreateItem( C_StateWriter& state );
    C_SceneItem*                  CreateItem( C_Record& record );
    C_SceneItem*                  CreateItem( C_Record& record, qreal x, qreal y, qreal z = -1 );

    QList<C_SceneItem*>           FromRecord( C_Record& record ) const;

    void                          Clear();
    int                           Size();

    void                          BringFront( C_SceneItem& sc );

    void                          UpdateLines();
    void                          ClearLines();

    M_POINTER                     ( Graphics,       QGraphicsScene )
    M_POINTER                     ( Document,       C_Document )
    M_VALUE                       ( TopZ,           double )
    M_VALUE                       ( Items,          QList<C_SceneItem*> )
    M_VALUE                       ( Lines,          QList<C_SceneLine*> )

private:

    static long                   m_IdCount;

    friend class                  C_Document;
    friend class                  C_SceneItem;
    friend class                  C_SceneLine;

};



#endif // C_SCENE_H

#include "scene_item.h"

