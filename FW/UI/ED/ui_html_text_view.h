#ifndef UIHTMLBLOCKSVIEW_H
#define UIHTMLBLOCKSVIEW_H

#include "FW/tools.h"
#include "FW/UI/ED/ui_text_editor.h"

class TypeUiSyntaxHighlighter;
class TypeController;
class TypeHtmlBlock;
class TypeRecord;
class TypeDocument;

class TypeUiHtmlTextView : public TypeUiTextEditor
{
    Q_OBJECT

public:

    TypeUiHtmlTextView(
        TypeController& controller,
        TypeDocument& document,
        QString id,
        QString name,
        QString tab_name,
        QWidget* parent = 0,
        TypeSaveCallback save_callback = &TypeUiEditor::empty_save_callback,
        TypeSaveCallback save_as_callback = &TypeUiEditor::empty_save_callback,
        TypeUpdateCallback update_callback = &TypeUiEditor::empty_update_callback,
        TypeUiSyntaxHighlighter* syntax_higlighter = 0 );

    void                                    ActivateBlock( TypeHtmlBlock* block );
    void                                    ActivateRecord( TypeRecord* active_record );
    void                                    UpdateText();

    M_REFERENCE                             ( Controller,         TypeController )
    M_REFERENCE                             ( Document,         TypeDocument )
    M_POINTER                               ( ActiveRecord,       TypeRecord )
    M_POINTER                               ( ActiveBlock,        TypeHtmlBlock )

public slots:

    void                                    OnCursorPositionChanged();
    void                                    OnCustomContextMenuRequested( const QPoint& point );

};

#define UIHTMLTEXTVIEW_UPDATE_VIEW 1

#endif // UIHTMLTEXTVIEW_H
