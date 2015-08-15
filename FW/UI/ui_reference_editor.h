#ifndef UI_REFERENCE_EDITOR_H
#define UI_REFERENCE_EDITOR_H

#include <QDialog>
#include "FW/macro.h"

class C_ReferenceRecord;
class C_Document;
class C_StringRecord;
class C_Document;

namespace Ui {
class C_UiReferenceEditor;
}

class C_UiReferenceEditor : public QDialog
{
    Q_OBJECT

public:
    explicit C_UiReferenceEditor(C_ReferenceRecord& record, C_Document& document, QWidget *parent = 0);
    ~C_UiReferenceEditor();

    ATR_POINTER                  ( Record,   C_ReferenceRecord )
    ATR_POINTER                  ( Document, C_Document )

private slots:

    void OnButtonBoxAccepted();
    void OnRemoveButtonClicked();

private:
    Ui::C_UiReferenceEditor *ui;
};

#endif // UI_REFERENCE_EDITOR_H
