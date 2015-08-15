#ifndef C_UIFINDRECORD_H
#define C_UIFINDRECORD_H

#include "FW/macro.h"

#include <QDialog>

class C_Record;
class C_Document;

namespace Ui
{
class C_UiFindRecord;
}

class C_UiFindRecord : public QDialog
{
    Q_OBJECT

public:

    explicit C_UiFindRecord( C_Document& document, QWidget* parent = 0 );
    ~C_UiFindRecord() override;

    ATR_POINTER         ( Document, C_Document )
    ATR_POINTER         ( Record, C_Record )

public slots:

    void                OnLineEditReturnPressed();
    void                OnSpinBoxValueChanged( int index );
    void                OnCloseButtonClicked();
    void                OnEditButtonClicked();
    void                OnRemoveButtonClicked();

private:

    Ui::C_UiFindRecord* ui;
};

#endif // C_UIFINDRECORD_H
