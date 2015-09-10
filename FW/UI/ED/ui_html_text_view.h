#ifndef UIHTMLBLOCKSVIEW_H
#define UIHTMLBLOCKSVIEW_H

#include "FW/tools.h"
#include "FW/UI/ED/ui_text_editor.h"

class TypeUiSyntaxHighlighter;
class TypeController;
class TypeHtmlBlock;
class TypeRecord;

class TypeUiHtmlTextView : public TypeUiTextEditor
{
    Q_OBJECT

public:

    explicit TypeUiHtmlTextView( TypeController& controller, QString id, QString name, QString tab_name,
                                 QWidget* parent = 0,
                                 TypeSaveCallback save_callback = &TypeUiEditor::empty_save_callback ,
                                 TypeUiSyntaxHighlighter* syntax_higlighter = 0 );

    void                                    ActivateBlock( TypeHtmlBlock* block );
    void                                    ActivateRecord( TypeRecord* active_record );
    void                                    UpdateView();


    M_REFERENCE                             ( Controller,         TypeController )
    M_POINTER                               ( ActiveRecord,       TypeRecord )
    M_POINTER                               ( ActiveBlock,        TypeHtmlBlock )

public slots:

    void                                    OnCursorPositionChanged();
    void                                    OnHtmlTextChanged();
    void                                    OnCustomContextMenuRequested(const QPoint& point);
};

#endif // UIHTMLTEXTVIEW_H
