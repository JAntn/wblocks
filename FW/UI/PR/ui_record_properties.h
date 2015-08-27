#ifndef C_UIRECORDPROPERTIES_H
#define C_UIRECORDPROPERTIES_H

#include "FW/macro.h"
#include <QDialog>

class C_Record;
class C_Document;

namespace Ui
{
class C_UiRecordProperties;
}

class C_UiRecordProperties : public QDialog
{
    Q_OBJECT

public:

    C_UiRecordProperties( C_Record& record, C_Document& document, QWidget* parent = 0 );
    ~C_UiRecordProperties() override;

    M_POINTER           ( Record,   C_Record )
    M_POINTER           ( Document, C_Document )

private slots:

    void                OnButtonBoxAccepted();
    void                OnRemoveButtonClicked();

private:

    Ui::C_UiRecordProperties* ui;
};

#endif // C_UIRECORDPROPERTIES_H
