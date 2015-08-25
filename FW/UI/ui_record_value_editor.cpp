#include "ui_texteditor.h"
#include "FW/UI/ui_record_value_editor.h"
#include "FW/document.h"
#include <QFileDialog>
#include "FW/RC/record.h"

C_UiRecordValueEditor::C_UiRecordValueEditor( QString id, QString name, C_Record& record, QWidget* parent ):
    C_UiTextEditor( id, name, name.split(".").back(), parent ),
    m_Record( &record )
{
    SetText( Record().Value(), true );
}

void C_UiRecordValueEditor::SaveState()
{
    Record().SetValue( Text() );
    SetHasChanged( false );
}
