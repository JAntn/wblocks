#ifndef UI_REFERENCE_EDITOR_H
#define UI_REFERENCE_EDITOR_H

#include <QDialog>
#include "FW/macro.h"

class C_ReferenceRecord;
class C_Document;
class C_StringRecord;
class C_Document;

namespace Ui
{
class C_UiReferenceRecordProperties;
}

class C_UiReferenceRecordProperties : public QDialog
{
    Q_OBJECT

public:
    explicit C_UiReferenceRecordProperties( C_ReferenceRecord& record, C_Document& document, QWidget* parent = 0 );
    ~C_UiReferenceRecordProperties();

    M_POINTER                    ( Record,   C_ReferenceRecord )
    M_POINTER                    ( Document, C_Document )

private slots:

    void                         OnButtonBoxAccepted();
    void                         OnRemoveButtonClicked();
    void                         OnReferenceLineEditReturnPressed();

private:
    Ui::C_UiReferenceRecordProperties* ui;
};

#endif // UI_REFERENCE_EDITOR_H
