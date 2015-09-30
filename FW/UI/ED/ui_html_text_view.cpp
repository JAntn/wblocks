#include "FW/UI/ED/ui_html_text_view.h"
#include "FW/UI/ED/ui_text_editor.h"
#include "FW/RC/record.h"

#include "FW/BK/html_block.h"
#include "FW/BK/html_block_stream.h"
#include "FW/controller.h"
#include "FW/document.h"
#include "FW/BK/html_builder.h"
#include "FW/RC/root_struct.h"
#include "FW/controller.h"
#include "FW/tools.h"
#include "FW/context.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QMouseEvent>
#include "ui_texteditor.h"
#include "FW/UI/ui_main_window.h"
#include "FW/UI/ui_record_explorer.h"
#include <FW/UI/ui_record_contextmenu.h>

TypeUiHtmlTextView::TypeUiHtmlTextView(
    TypeController& controller,
    QString id,
    QString name,
    QString tab_name,
    QWidget* parent,
    TypeSaveCallback save_callback,
    TypeSaveCallback save_as_callback,
    TypeUpdateCallback update_callback,
    TypeUiSyntaxHighlighter* syntax_higlighter ):

    TypeUiTextEditor(
        id,
        name,
        tab_name,
        parent,
        save_callback,
        save_as_callback,
        update_callback,
        syntax_higlighter ),

    m_Controller( &controller ),
    m_ActiveRecord( 0 ),
    m_ActiveBlock( 0 )
{
    //
    // Active record is shared by many widgets through SetActiveRecord:

    qDebug() << "Creating Html Text Widget..";

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

    ui->TextEdit->setReadOnly( true );
    ui->TextEdit->setContextMenuPolicy( Qt::CustomContextMenu );
    SetFormattedText( Controller().Document().HtmlBuilder().FormattedText() );
    SetHasChanged( false );
    OnActionUpdate();

    qDebug() << "Html Text Widget created";
}

void TypeUiHtmlTextView::OnCustomContextMenuRequested( const QPoint& point )
{
    int cursor_position = ui->TextEdit->cursorForPosition( point ).position();
    QPoint global_point = ui->TextEdit->viewport()->mapToGlobal( point );
    TypeHtmlBlockStream& block_stream = Controller().Document().HtmlBuilder().BlockStream();
    TypeHtmlBlock* block = block_stream.BlockFromCursorPosition( cursor_position );
    long action_flags;

    if( block == 0 )
    {
        //
        // There is no selection on html text view:

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
        //
        // The selected block doesn't contain any record:

        action_flags = Controller().Document().Context().Struct().Flags();//WHY?--------------
        TypeUiRecordContextMenu context_menu( Controller(), action_flags, false, global_point, this );
        return;
    }

    //
    // Open a context menu for selected record:

    action_flags = record->ParentStruct()->Flags();
    TypeUiRecordContextMenu context_menu( Controller(), action_flags, true, global_point, this );
}


void TypeUiHtmlTextView::ActivateRecord( TypeRecord* active_record )
{
    if( ActiveRecord() == active_record )
        return;

    SetActiveRecord( active_record );

    if( active_record != 0 )
    {
        TypeHtmlBlockStream& block_stream = Controller().Document().HtmlBuilder().BlockStream();
        TypeHtmlBlock* block = block_stream.BlockFromRecordId( active_record->Id() );

        if( block != 0 )
            ActivateBlock( block );
    }
}

void TypeUiHtmlTextView::ActivateBlock( TypeHtmlBlock* block )
{
    //
    // Clear previous selection:

    if( ActiveBlock() != 0 )
        ActiveBlock()->SetSelected( false );

    //
    // Select block:

    SetActiveBlock( block );

    if( ActiveBlock() != 0 )
        ActiveBlock()->SetSelected( true );

    SetFormattedText( Controller().Document().HtmlBuilder().FormattedText() );
}

void TypeUiHtmlTextView::OnCursorPositionChanged()
{
    int cursor_position = ui->TextEdit->textCursor().position();
    TypeHtmlBlockStream& block_stream = Controller().Document().HtmlBuilder().BlockStream();
    TypeHtmlBlock* block =  block_stream.BlockFromCursorPosition( cursor_position );

    if( block != 0 )
    {
        TypeRootStruct& root = Controller().Document().Root();
        TypeRecord* record = root.FromId( block->RecordId(), true );

        if( record != 0 )
        {
            SetActiveRecord( record );
            ActivateBlock( block );

            emit Controller().SetActiveRecord( record );
        }
    }
}


