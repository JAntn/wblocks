#ifndef UIRECORDCONTEXTMENU_H
#define UIRECORDCONTEXTMENU_H

#include "FW/tools.h"

class TypeRecord;
class TypeController;

class TypeUiRecordContextMenu : public QObject, public TypeVariant
{
    Q_OBJECT

public:

    TypeUiRecordContextMenu(TypeController& controller, long action_flags, bool has_selection, const QPoint& global_point, QObject* parent = 0 );
    ~TypeUiRecordContextMenu() override;

    M_REFERENCE                             ( Controller, TypeController )

};

#endif // UIRECORDCONTEXTMENU2_H
