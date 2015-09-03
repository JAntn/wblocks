#ifndef UIHTMLBLOCKSVIEW_H
#define UIHTMLBLOCKSVIEW_H

#include "FW/macro.h"
#include "FW/UI/ED/ui_text_editor.h"

class TypeUiSyntaxHighlighter;
class TypeController;


class TypeUiHtmlBlocksEditor : public TypeUiTextEditor
{
    Q_OBJECT

public:

    explicit TypeUiHtmlBlocksEditor( TypeController& controller, QString id, QString name, QString tab_name,
                                 QWidget* parent = 0,
                                 TypeSaveCallback save_callback = &TypeUiEditor::empty_save_callback ,
                                 TypeUiSyntaxHighlighter* syntax_higlighter = 0 );

    void                         UpdateText();

    // !!!
    void                         SetFileTitle(QString title);
    // TODO: multiple module support implementation

    M_POINTER                    ( Controller,         TypeController )

public slots:

    void                         OnCursorPositionChanged();

};

#endif // UIHTMLTEXTVIEW_H
