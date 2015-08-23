#ifndef C_RECORD_CONTEXT_MENU_H
#define C_RECORD_CONTEXT_MENU_H

#include "FW/macro.h"

#include <QObject>

class C_Record;
class C_Document;

class C_UiRecordContextMenu : QObject
{
    Q_OBJECT

public:

    C_UiRecordContextMenu( C_Document& document,
                           const QPoint& global_point,
                           QObject* parent = 0 );

    ~C_UiRecordContextMenu() override;

    M_POINTER           ( Document, C_Document )

};

#endif // C_RECORD_CONTEXT_MENU_H
