#ifndef TypeUITEXTEDITOR_H
#define TypeUITEXTEDITOR_H

#include "FW/macro.h"
#include "FW/UI/ED/ui_editor.h"

namespace Ui
{
class TypeUiTextEditor;
}

class TypeUiTextEditor : public TypeUiEditor
{
    Q_OBJECT

public:

    explicit TypeUiTextEditor( QString id, QString name, QString tab_name, save_callback_t save_callback, QWidget* parent = 0 );
    ~TypeUiTextEditor();

    virtual QString              Text();
    virtual void                 SetText( QString text, bool signal_block = false );

public slots:

    void                         OnTextChanged();

private:

    Ui::TypeUiTextEditor* ui;
};

#endif // TypeUITEXTEDITOR_H
