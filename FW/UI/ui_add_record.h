#ifndef C_UIADDRECORD_H
#define C_UIADDRECORD_H

#include "FW/macro.h"

#include <QDialog>

class C_Record;
class C_Context;
class C_Controller;

namespace Ui
{
class C_UiAddRecord;
}

class C_UiAddRecord : public QDialog
{
    Q_OBJECT

public:

    explicit C_UiAddRecord( C_Controller& controller, C_Context& context, int position = -1, QWidget* parent = 0 );
    ~C_UiAddRecord() override;

    bool                CheckFormData() const;

    M_POINTER           ( Context,    C_Context )
    M_POINTER           ( Controller, C_Controller )

public slots:

    void                OnButtonBoxAccepted();
    void                OnButtonBoxRejected();

private:

    Ui::C_UiAddRecord* ui;
};

#endif // C_UIADDRECORD_H
