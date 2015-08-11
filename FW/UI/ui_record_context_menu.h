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

                        C_UiRecordContextMenu(C_Document& document,
                                  const QPoint& global_point,
                                  long position = -1,
                                  C_Record* record = 0,
                                  QObject* parent = 0);

                        ~C_UiRecordContextMenu() override;

    ATR_POINTER         (Record,   C_Record)
    ATR_POINTER         (Document, C_Document)
    ATR_VALUE           (Position, long)

public slots:

    void                OnEdit();
    void                OnRemove();
    void                OnAdd();
    void                OnAddSceneItem();
    void                OnCopy();
    void                OnPaste();

};

#endif // C_RECORD_CONTEXT_MENU_H
