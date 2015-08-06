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
    explicit            C_UiAddRecord(C_Document& document, int position = -1, QWidget *parent = 0);
                        ~C_UiAddRecord();

    bool                CheckFormData() const;

    C_POINTER           (Document, C_Document)

private slots:

    void                on_ButtonBox_accepted();
    void                on_EditButton_clicked();

    void on_ButtonBox_rejected();

private:

    Ui::C_UiAddRecord *ui;
};

#endif // C_UIADDRECORD_H
