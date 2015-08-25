#ifndef C_UIBOOLRECORDPROPERTIES_H
#define C_UIBOOLRECORDPROPERTIES_H

#include "FW/macro.h"
#include <QDialog>

class C_Record;
class C_BoolRecord;
class C_Document;

namespace Ui
{
class C_UiBoolRecordProperties;
}

class C_UiBoolRecordProperties : public QDialog
{
    Q_OBJECT

public:

    C_UiBoolRecordProperties( C_BoolRecord& record, C_Document& document, QWidget* parent = 0 );
    ~C_UiBoolRecordProperties() override;

    M_POINTER           ( Record,   C_BoolRecord )
    M_POINTER           ( Document, C_Document )

public slots:

    void                OnButtonBoxAccepted();
    void                OnRemoveButtonClicked();

private:

    Ui::C_UiBoolRecordProperties* ui;
};

#endif // C_UIBOOLRECORDPROPERTIES_H
