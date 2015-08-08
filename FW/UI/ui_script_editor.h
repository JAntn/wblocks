#ifndef UI_SCRIPT_EDITOR_H
#define UI_SCRIPT_EDITOR_H

#include "FW/macro.h"
#include <QDialog>

namespace Ui {
class C_UiScriptEditor;
}

class C_Document;
class C_ScriptRecord;

class C_UiScriptEditor : public QDialog
{
    Q_OBJECT

public:

                                 C_UiScriptEditor(C_ScriptRecord& record, C_Document& document, QWidget* parent = 0);
                                 ~C_UiScriptEditor() override;

    C_POINTER                    (Record,   C_ScriptRecord)
    C_POINTER                    (Document, C_Document)

public slots:

    void                         on_ButtonBox_accepted();
    void                         on_RemoveButton_clicked();
    void                         on_LoadButton_clicked();
    void                         on_SaveButton_clicked();
    void                         on_FileCheckBox_stateChanged(int arg1);

private:
    Ui::C_UiScriptEditor *ui;
};

#endif // UI_SCRIPT_EDITOR_H
