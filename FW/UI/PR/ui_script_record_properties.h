#ifndef C_UISCRIPTRECORDPROPERTIES_H
#define C_UISCRIPTRECORDPROPERTIES_H

#include "FW/macro.h"

#include <QDialog>

class C_Record;
class C_ScriptRecord;
class C_Document;

namespace Ui
{
class C_UiScriptRecordProperties;
}

class C_UiScriptRecordProperties : public QDialog
{
    Q_OBJECT

public:

    C_UiScriptRecordProperties( C_ScriptRecord& record, C_Document& document, QWidget* parent = 0 );
    ~C_UiScriptRecordProperties() override;

    M_POINTER                    ( Record,   C_ScriptRecord )
    M_POINTER                    ( Document, C_Document )

private slots:

    void                          OnButtonBoxAccepted();
    void                          OnRemoveButtonClicked();

private:

    Ui::C_UiScriptRecordProperties*         ui;
};

#endif // C_UISCRIPTRECORDPROPERTIES_H
