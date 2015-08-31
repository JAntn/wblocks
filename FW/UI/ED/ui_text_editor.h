#ifndef C_UITEXTEDITOR_H
#define C_UITEXTEDITOR_H

#include "FW/macro.h"
#include "FW/UI/ED/ui_editor.h"

namespace Ui
{
class C_UiTextEditor;
}

class C_UiTextEditor : public C_UiEditor
{
    Q_OBJECT

public:

    explicit C_UiTextEditor( QString id, QString name, QString tab_name, save_callback_t save_callback, QWidget* parent = 0 );
    ~C_UiTextEditor();

    virtual QString              Text();
    virtual void                 SetText( QString text, bool signal_block = false );

public slots:

    void                         OnTextChanged();

private:

    Ui::C_UiTextEditor* ui;
};

#endif // C_UITEXTEDITOR_H
