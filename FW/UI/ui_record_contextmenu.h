#ifndef UIRECORDCONTEXTMENU_H
#define UIRECORDCONTEXTMENU_H

#include "FW/variant.h"
#include "FW/macro.h"
#include <QObject>

class TypeRecord;
class TypeController;

class TypeUiRecordContextMenu : public QObject, public TypeVariant
{
    Q_OBJECT

public:

    TypeUiRecordContextMenu( TypeController& controller, const QPoint& global_point, QObject* parent = 0 );
    ~TypeUiRecordContextMenu() override;

    M_POINTER           ( Controller, TypeController )

};

#endif // UIRECORDCONTEXTMENU_H
