#ifndef C_UIINTEGERRECORDPROPERTIES_H
#define C_UIINTEGERRECORDPROPERTIES_H

#include "FW/macro.h"
#include <QDialog>

class C_IntegerRecord;
class C_Document;

namespace Ui
{
class C_UiIntegerRecordProperties;
}

class C_UiIntegerRecordProperties : public QDialog
{
    Q_OBJECT

public:

    C_UiIntegerRecordProperties( C_IntegerRecord& record, C_Document& document, QWidget* parent = 0 );
    ~C_UiIntegerRecordProperties() override;

    M_POINTER           ( Record, C_IntegerRecord )
    M_POINTER           ( Document, C_Document )

public slots:

    void                OnButtonBoxAccepted();
    void                OnRemoveButtonClicked();

private:

    Ui::C_UiIntegerRecordProperties* ui;
};

#endif // C_UIINTEGERRECORDPROPERTIES_H
