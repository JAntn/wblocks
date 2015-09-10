#ifndef UITEXTEDITOR_H
#define UITEXTEDITOR_H

#include "FW/tools.h"
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

    QString                                 Text();
    void                                    SetText( QString text );
    void                                    SetFormattedText( QString text );

    void                                    SetSyntaxHighlighter( TypeUiSyntaxHighlighter* syntax_higlighter = 0 );
    void                                    UpdateTitle();

    M_VALUE                                 ( ShowTitleAsterisc, bool )

public slots:

    void                                    OnTextChanged();
    void                                    OnTextSaved();

protected:

    TypeUiSyntaxHighlighter*                m_SyntaxHighlighter;
    Ui::TypeUiTextEditor*                   ui;
};

#endif // UITEXTEDITOR_H
