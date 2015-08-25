#include "ui_texteditor.h"
#include "FW/UI/ui_file_text_editor.h"
#include "FW/document.h"
#include <QFileDialog>


C_UiFileTextEditor::C_UiFileTextEditor(QString id, QString file_name, QWidget* parent ) :
    C_UiTextEditor( id, file_name, file_name.split("/").back(), parent ),
    m_FileName(file_name)
{
    SetText( C_Document::LoadTextFile( file_name ), true );
}

void C_UiFileTextEditor::SaveState()
{
    C_Document::SaveTextFile( FileName(), Text() );
    SetHasChanged( false );
}
