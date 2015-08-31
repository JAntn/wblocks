#ifndef TypeSCENE_H
#define TypeSCENE_H

#include "FW/variant.h"
#include "FW/macro.h"
#include <QObject>
#include <QGraphicsScene>

class TypeSceneItem;
class TypeRecord;
class TypeDocument;
class TypeStateWriter;
class TypeSceneLine;

class TypeScene : public TypeVariant
{
public:

    explicit TypeScene( TypeDocument& document, TypeVariant* parent = 0 );
    ~TypeScene() override;

    static QString                GenerateId();
    static QString                IdCount();

    TypeSceneItem*                  CreateItem( TypeStateWriter& state );
    TypeSceneItem*                  CreateItem( TypeRecord& record );
    TypeSceneItem*                  CreateItem( TypeRecord& record, qreal x, qreal y, qreal z = -1 );

    QList<TypeSceneItem*>           FromRecord( TypeRecord& record ) const;

    void                          Clear();
    int                           Size();

    void                          BringFront( TypeSceneItem& sc );

    void                          UpdateLines();
    void                          ClearLines();

    M_POINTER                     ( Graphics,       QGraphicsScene )
    M_POINTER                     ( Document,       TypeDocument )
    M_VALUE                       ( TopZ,           double )
    M_VALUE                       ( Items,          QList<TypeSceneItem*> )
    M_VALUE                       ( Lines,          QList<TypeSceneLine*> )

private:

    static long                   m_IdCount;

    friend class                  TypeDocument;
    friend class                  TypeSceneItem;
    friend class                  TypeSceneLine;

};



#endif // TypeSCENE_H

#include "scene_item.h"

