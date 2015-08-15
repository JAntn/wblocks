#ifndef UI_SCRIPT_EDITOR_H
#define UI_SCRIPT_EDITOR_H

#include "FW/macro.h"
#include <QDialog>

namespace Ui
{
class C_UiScriptEditor;
}

class C_Document;
class C_ScriptRecord;

class C_UiScriptEditor : public QDialog
{
    Q_OBJECT

public:

    C_UiScriptEditor( C_ScriptRecord& record, C_Document& document, QWidget* parent = 0 );
    ~C_UiScriptEditor() override;

    ATR_POINTER                  ( Record,   C_ScriptRecord )
    ATR_POINTER                  ( Document, C_Document )

public slots:

    void                         OnButtonBoxAccepted();
    void                         OnRemoveButtonClicked();
    void                         OnLoadButtonClicked();
    void                         OnSaveButtonClicked();
    void                         OnFileCheckBoxStateChanged( int arg1 );

private:
    Ui::C_UiScriptEditor* ui;
};

#endif // UI_SCRIPT_EDITOR_H
