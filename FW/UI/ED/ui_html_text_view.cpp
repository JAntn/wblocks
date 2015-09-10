#include "FW/UI/ED/ui_html_text_view.h"
#include "FW/UI/ED/ui_text_editor.h"
#include "FW/RC/record.h"

#include "FW/BK/html_block.h"
#include "FW/BK/html_block_stream.h"
#include "FW/controller.h"
#include "FW/document.h"
#include "FW/htmlbuilder.h"
#include "FW/RC/root_struct.h"
#include "FW/controller.h"
#include "FW/tools.h"
#include "FW/context.h"
#include <QTextEdit>
#include <QLineEdit>
#include "ui_texteditor.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_record_explorer.h"
#include <FW/UI/ui_record_contextmenu.h>

TypeUiHtmlTextView::TypeUiHtmlTextView(
    TypeController& controller, QString id, QString name, QString tab_name,
    QWidget* parent, TypeSaveCallback save_callback,
    TypeUiSyntaxHighlighter* syntax_higlighter ):
    TypeUiTextEditor( id, name, tab_name, parent, save_callback, syntax_higlighter ),
    m_Controller( &controller ), m_ActiveRecord( 0 ), m_ActiveBlock( 0 )
{
    connect(
        &controller,
        TypeController::SetActiveRecord,
        this,
        TypeUiHtmlTextView::ActivateRecord
    );

    connect(
        ui->TextEdit,
        QTextEdit::cursorPositionChanged,
        this,
        TypeUiHtmlTextView::OnCursorPositionChanged
    );


    connect(
        ui->TextEdit,
        QWidget::customContextMenuRequested,
        this,
        TypeUiHtmlTextView::OnCustomContextMenuRequested
    );


    connect(
        &controller,
        TypeController::HtmlTextChanged,
        this,
        TypeUiHtmlTextView::OnHtmlTextChanged
    );

    ui->TextEdit->setReadOnly( true );
    ui->TextEdit->setContextMenuPolicy( Qt::CustomContextMenu );

    ui->NameLineEdit->setText( name );
    SetHasChanged( false );
    UpdateTitle();
}

void TypeUiHtmlTextView::OnCustomContextMenuRequested( const QPoint& point )
{
    int cursor_position = ui->TextEdit->cursorForPosition( point ).position();
    QPoint global_point = ui->TextEdit->viewport()->mapToGlobal( point );

    TypeHtmlBlockStream& block_stream = Controller().HtmlBuilder().BlockStream();
    TypeHtmlBlock* block = block_stream.BlockFromCursorPosition( cursor_position );

    long action_flags;

    if( block == 0 )
    {
        action_flags = Controller().Document().Context().Struct().Flags();
        TypeUiRecordContextMenu context_menu( Controller(), action_flags, false, global_point, this );
        return;
    }

    TypeRootStruct& root = Controller().Document().Root();
    TypeRecord* record = root.FromId( block->RecordId(), true );

    SetActiveRecord( record );
    ActivateBlock( block );

    emit Controller().SetActiveRecord( record );

    if( record == 0 )
    {
        action_flags = Controller().Document().Context().Struct().Flags();
        TypeUiRecordContextMenu context_menu( Controller(), action_flags, false, global_point, this );
        return;
    }

    action_flags = record->ParentStruct()->Flags();
    TypeUiRecordContextMenu context_menu( Controller(), action_flags, true, global_point, this );
}


void TypeUiHtmlTextView::ActivateRecord( TypeRecord* active_record )
{
    if( ActiveRecord() == active_record )
        return;

    TypeHtmlBlockStream& block_stream = Controller().HtmlBuilder().BlockStream();
    TypeRootStruct& root = Controller().Document().Root();

    for( TypeVariantPtr<TypeHtmlBlock> block : block_stream )
    {
        if( !block->RecordId().isEmpty() )
        {
            TypeRecord* record = root.FromId( block->RecordId(), true );

            if( ( record != 0 ) && ( record == active_record ) )
            {
                SetActiveRecord( record );
                ActivateBlock( block );

                return;
            }
        }
    }
}

void TypeUiHtmlTextView::ActivateBlock( TypeHtmlBlock* block )
{
    // clear previous selection
    if( ActiveBlock() != 0 )
        ActiveBlock()->SetSelected( false );

    SetActiveBlock( block );

    if( ActiveBlock() != 0 )
        ActiveBlock()->SetSelected( true );

    UpdateView();
}

void TypeUiHtmlTextView::OnHtmlTextChanged()
{
    SetHasChanged( true );
    UpdateView();
    UpdateTitle();
}

void TypeUiHtmlTextView::UpdateView( )
{
    SetFormattedText( Controller().HtmlBuilder().FormattedText() );
}



void TypeUiHtmlTextView::OnCursorPositionChanged()
{
    int cursor_position = ui->TextEdit->textCursor().position();
    int position  = 0;
    TypeHtmlBlockStream& block_stream = Controller().HtmlBuilder().BlockStream();
    TypeVariantPtr<TypeHtmlBlock> prev_block = *block_stream.begin();

    for( TypeVariantPtr<TypeHtmlBlock> block : block_stream )
    {
        position = block->Position();

        if( position > cursor_position )
        {
            TypeRootStruct& root = Controller().Document().Root();
            TypeRecord* record = root.FromId( prev_block->RecordId(), true );

            if( record != 0 )
            {
                SetActiveRecord( record );
                ActivateBlock( prev_block );

                emit Controller().SetActiveRecord( record );
            }

            return;
        }

        prev_block = block;
    }
}


