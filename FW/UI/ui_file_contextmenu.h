#ifndef UIFILECONTEXTMENU_H
#define UIFILECONTEXTMENU_H

#include "FW/tools.h"

class TypeRecord;
class TypeController;

class TypeUiFileContextMenu : public QObject, public TypeVariant
{
    Q_OBJECT

public:

    TypeUiFileContextMenu( TypeController& controller, bool has_selection, const QPoint& global_point, QObject* parent = 0 );
    ~TypeUiFileContextMenu() override;

    M_REFERENCE                             ( Controller, TypeController )
};

#endif // UIFileCONTEXTMENU2_H
