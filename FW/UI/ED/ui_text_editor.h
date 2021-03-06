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

    TypeUiTextEditor(
        QString id,
        QString name,
        QString tab_name,
        QWidget* parent = 0,
        TypeSaveCallback save_callback = &TypeUiEditor::empty_save_callback,
        TypeSaveCallback save_as_callback = &TypeUiEditor::empty_save_callback,
        TypeUpdateCallback update_callback = &TypeUiEditor::empty_update_callback,
        TypeUiSyntaxHighlighter* syntax_higlighter = 0 );

    ~TypeUiTextEditor();

    QString                                 Text();
    void                                    SetText( QString text );
    void                                    SetFormattedText( QString text );
    void                                    SetTitle( QString title );
    void                                    SetSyntaxHighlighter( TypeUiSyntaxHighlighter* syntax_higlighter = 0 );

    M_VALUE                                 ( ShowTitleAsterisc, bool )

public slots:

    void                                    OnTextChanged();
    void                                    OnTextSaved();

protected:

    TypeUiSyntaxHighlighter*                m_SyntaxHighlighter;
    Ui::TypeUiTextEditor*                   ui;

};

#endif // UITEXTEDITOR_H
