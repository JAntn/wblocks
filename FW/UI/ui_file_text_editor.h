#ifndef C_UITEXTFILEEDITOR_H
#define C_UITEXTFILEEDITOR_H

#include <QFile>
#include <QWidget>
#include "FW/macro.h"
#include "FW/UI/ui_text_editor.h"


class C_UiFileTextEditor : public C_UiTextEditor
{
public:

    C_UiFileTextEditor( QString id, QString file_name, QWidget* parent = 0 );

    void                          SaveState();

    M_VALUE                       ( FileName, QString )
};

#endif // C_UITEXTFILEEDITOR_H
