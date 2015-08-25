#ifndef C_UIREALRECORDPROPERTIES_H
#define C_UIREALRECORDPROPERTIES_H

#include "FW/macro.h"
#include <QDialog>

class C_Record;
class C_RealRecord;
class C_Document;

namespace Ui
{
class C_UiRealRecordProperties;
}

class C_UiRealRecordProperties : public QDialog
{
    Q_OBJECT

public:

    C_UiRealRecordProperties( C_RealRecord& record, C_Document& document, QWidget* parent = 0 );
    ~C_UiRealRecordProperties() override;

    M_POINTER           ( Record,   C_RealRecord )
    M_POINTER           ( Document, C_Document )

private slots:

    void                OnButtonBoxAccepted();
    void                OnRemoveButtonClicked();

private:

    Ui::C_UiRealRecordProperties* ui;
};

#endif // C_UIREALRECORDPROPERTIES_H
