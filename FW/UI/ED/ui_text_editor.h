#ifndef UITEXTEDITOR_H
#define UITEXTEDITOR_H

#include "FW/macro.h"
#include "FW/UI/ED/ui_editor.h"

class TypeUiSyntaxHighlighter;
class QTextEdit;
class QLineEdit;

namespace Ui
{
class TypeUiTextEditor;
}

class TypeUiTextEditor : public TypeUiEditor
{
    Q_OBJECT

public:

    explicit TypeUiTextEditor( QString id, QString name, QString tab_name,
                               QWidget* parent = 0,
                               TypeSaveCallback save_callback = TypeUiEditor::empty_save_callback,
                               TypeUiSyntaxHighlighter* syntax_higlighter = 0 );
    ~TypeUiTextEditor();

    virtual QString                    Text();
    virtual void                       SetText( QString text, bool signal_block = false );
    void                               SetSyntaxHighlighter( TypeUiSyntaxHighlighter* syntax_higlighter = 0 );

protected:

    QTextEdit&                         TextEditWidget();
    QLineEdit&                         NameLineEditWidget();

public slots:

    void                               OnTextChanged();

private:

    TypeUiSyntaxHighlighter*           m_SyntaxHighlighter;
    Ui::TypeUiTextEditor*              ui;
};

#endif // UITEXTEDITOR_H
