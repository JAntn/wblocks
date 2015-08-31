#ifndef C_RECORD_CONTEXT_MENU_H
#define C_RECORD_CONTEXT_MENU_H

#include "FW/macro.h"

#include <QObject>

class C_Record;
class C_Controller;

class C_UiRecordContextMenu : QObject
{
    Q_OBJECT

public:

    C_UiRecordContextMenu( C_Controller& controller, const QPoint& global_point, QObject* parent = 0 );
    ~C_UiRecordContextMenu() override;

    M_POINTER           ( Controller, C_Controller )

};

#endif // C_RECORD_CONTEXT_MENU_H
