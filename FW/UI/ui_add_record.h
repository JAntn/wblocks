#ifndef C_UIADDRECORD_H
#define C_UIADDRECORD_H

#include "FW/macro.h"

#include <QDialog>

class C_Record;
class C_Document;

namespace Ui {
class C_UiAddRecord;
}

class C_UiAddRecord : public QDialog
{
    Q_OBJECT

public:

    explicit C_UiAddRecord(C_Document& document, int position = -1, QWidget *parent = 0);
    ~C_UiAddRecord() override;

    bool                CheckFormData() const;

    ATR_POINTER         (Document, C_Document)

public slots:

    void                OnButtonBoxAccepted();
    void                OnButtonBoxRejected();
    void                OnEditButtonClicked();

private:

    Ui::C_UiAddRecord *ui;
};

#endif // C_UIADDRECORD_H
