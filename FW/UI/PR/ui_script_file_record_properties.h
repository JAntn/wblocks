#ifndef UISCRIPTFILERECORDPROPERTIES_H
#define UISCRIPTFILERECORDPROPERTIES_H

#include "FW/macro.h"
#include <QDialog>

namespace Ui
{
class C_UiScriptFileRecordProperties;
}

class C_Document;
class C_ScriptFileRecord;

class C_UiScriptFileRecordProperties : public QDialog
{
    Q_OBJECT

public:

    C_UiScriptFileRecordProperties( C_ScriptFileRecord& record, C_Document& document, QWidget* parent = 0 );
    ~C_UiScriptFileRecordProperties() override;

    M_POINTER                    ( Record,   C_ScriptFileRecord )
    M_POINTER                    ( Document, C_Document )


public slots:

    void                         OnButtonBoxAccepted();
    void                         OnRemoveButtonClicked();
    void                         OnSelectButtonClicked();

private:
    Ui::C_UiScriptFileRecordProperties* ui;
};

#endif // UISCRIPTFILERECORDPROPERTIES_H
