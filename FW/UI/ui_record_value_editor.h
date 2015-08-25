#ifndef C_UIRECORDVALUEEDITOR_H
#define C_UIRECORDVALUEEDITOR_H

#include <QWidget>
#include "FW/macro.h"
#include "FW/UI/ui_text_editor.h"

class C_Record;

class C_UiRecordValueEditor : public C_UiTextEditor
{
public:

    C_UiRecordValueEditor(QString id, QString name, C_Record& record, QWidget* parent = 0 );

    void                 SaveState() override;

    M_POINTER            ( Record, C_Record )

};

#endif // C_UIRECORDVALUEEDITOR_H
