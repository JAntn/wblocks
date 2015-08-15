#ifndef C_UIINTEGEREDITOR_H
#define C_UIINTEGEREDITOR_H

#include "FW/macro.h"
#include <QDialog>

class C_IntegerRecord;
class C_Document;

namespace Ui
{
class C_UiIntegerEditor;
}

class C_UiIntegerEditor : public QDialog
{
    Q_OBJECT

public:

    C_UiIntegerEditor( C_IntegerRecord& record, C_Document& document, QWidget* parent = 0 );
    ~C_UiIntegerEditor() override;

    ATR_POINTER         ( Record, C_IntegerRecord )
    ATR_POINTER         ( Document, C_Document )

public slots:

    void                OnButtonBoxAccepted();
    void                OnRemoveButtonClicked();

private:

    Ui::C_UiIntegerEditor* ui;
};

#endif // C_UIINTEGEREDITOR_H
