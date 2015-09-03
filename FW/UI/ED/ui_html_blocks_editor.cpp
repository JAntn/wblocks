#include "FW/UI/ED/ui_html_blocks_editor.h"
#include "FW/UI/ED/ui_text_editor.h"

#include "FW/BK/block.h"
#include "FW/BK/block_stream.h"
#include "FW/controller.h"
#include "FW/document.h"
#include "FW/htmlbuilder.h"
#include "FW/RC/record_struct.h"
#include "FW/controller.h"
#include "FW/tools.h"
#include <QTextEdit>
#include <QLineEdit>

TypeUiHtmlBlocksEditor::TypeUiHtmlBlocksEditor(
    TypeController& controller, QString id, QString name, QString tab_name,
    QWidget* parent, TypeSaveCallback save_callback,
    TypeUiSyntaxHighlighter* syntax_higlighter ):
    TypeUiTextEditor( id, name, tab_name, parent, save_callback, syntax_higlighter ),
    m_Controller( &controller )
{

    connect(
        &TextEditWidget(),
        QTextEdit::cursorPositionChanged,
        this,
        TypeUiHtmlBlocksEditor::OnCursorPositionChanged
    );

    TextEditWidget().setReadOnly( true );
}

void TypeUiHtmlBlocksEditor::UpdateText( )
{
    SetText( Controller().Document().Html() );
    TextEditWidget().update();
}

void TypeUiHtmlBlocksEditor::SetFileTitle( QString title )
{
    NameLineEditWidget().setText( title );
}

void TypeUiHtmlBlocksEditor::OnCursorPositionChanged()
{

    int cursor_position = TextEditWidget().textCursor().position();
    int position  = 0;
    TypeVariantPtr<TypeBlock> prevblock = *Controller().Document().HtmlBlockStream().begin();

    for( TypeVariantPtr<TypeBlock> block : Controller().Document().HtmlBlockStream() )
    {
        position = block->Position();

        if( position > cursor_position )
        {
            TypeRecord* record = Controller().Document().Root().FromId(
                                     prevblock->RecordId(), true );

            if( record != 0 )
                Controller().SetPropertyWidgetRecord( *record );

            return;
        }

        prevblock = block;
    }
}


