#ifndef TypeRECORD_CONTEXT_MENU_H
#define TypeRECORD_CONTEXT_MENU_H

#include "FW/macro.h"

#include <QObject>

class TypeRecord;
class TypeController;

class TypeUiRecordContextMenu : QObject
{
    Q_OBJECT

public:

    TypeUiRecordContextMenu( TypeController& controller, const QPoint& global_point, QObject* parent = 0 );
    ~TypeUiRecordContextMenu() override;

    M_POINTER           ( Controller, TypeController )

};

#endif // TypeRECORD_CONTEXT_MENU_H
