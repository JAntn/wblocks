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
                                  const QPoint& position,
                                  C_Record* record = 0,
                                  QObject* parent = 0);

                        ~C_UiRecordContextMenu() override;

    C_POINTER           (Record,   C_Record)
    C_POINTER           (Document, C_Document)


public slots:

    void                OnEdit();
    void                OnRemove();
    void                OnAdd();
    void                OnAddSceneItem();

};

#endif // C_RECORD_CONTEXT_MENU_H
