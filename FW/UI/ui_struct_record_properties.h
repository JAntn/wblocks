#ifndef UI_STRUCT_EDITOR_H
#define UI_STRUCT_EDITOR_H

#include "FW/macro.h"
#include <QDialog>

class C_StructRecord;
class C_Document;

namespace Ui
{
class C_UiStructRecordProperties;
}

class C_UiStructRecordProperties : public QDialog
{
    Q_OBJECT

public:

    C_UiStructRecordProperties( C_StructRecord& record, C_Document& document, QWidget* parent = 0 );
    ~C_UiStructRecordProperties() override;

    M_POINTER           ( Record,   C_StructRecord )
    M_POINTER           ( Document, C_Document )


private slots:

    void                 OnRemoveButtonClicked();
    void                 OnButtonBoxAccepted();

private:

    Ui::C_UiStructRecordProperties* ui;
};

#endif // UI_STRUCT_EDITOR_H
