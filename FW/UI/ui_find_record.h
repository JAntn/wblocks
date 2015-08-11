#ifndef C_UIFINDRECORD_H
#define C_UIFINDRECORD_H

#include "FW/macro.h"

#include <QDialog>

class C_Record;
class C_Document;

namespace Ui {
class C_UiFindRecord;
}

class C_UiFindRecord : public QDialog
{
    Q_OBJECT

public:

    explicit C_UiFindRecord(C_Document& document, QWidget *parent = 0);
    ~C_UiFindRecord() override;

    ATR_POINTER         (Document, C_Document)
    ATR_POINTER         (Record, C_Record)

private slots:

    void                on_LineEdit_returnPressed();
    void                on_SpinBox_valueChanged(int index);
    void                on_CloseButton_clicked();
    void                on_EditButton_clicked();
    void                on_RemoveButton_clicked();

private:

    Ui::C_UiFindRecord *ui;
};

#endif // C_UIFINDRECORD_H
