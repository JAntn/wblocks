#ifndef C_UISTRINGEDITOR_H
#define C_UISTRINGEDITOR_H

#include "FW/macro.h"

#include <QDialog>

class C_Record;
class C_StringRecord;
class C_Document;

namespace Ui {
class C_UiStringEditor;
}

class C_UiStringEditor : public QDialog
{
    Q_OBJECT

public:

    explicit                      C_UiStringEditor(C_StringRecord& record, C_Document& document, QWidget* parent = 0);
                                  ~C_UiStringEditor();

    C_POINTER                    (Record,   C_StringRecord)
    C_POINTER                    (Document, C_Document)

private slots:

    void                          on_ButtonBox_accepted();
    void                          on_RemoveButton_clicked();

private:

    Ui::C_UiStringEditor*         ui;
};

#endif // C_UISTRINGEDITOR_H
