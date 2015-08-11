#ifndef C_UIREALEDITOR_H
#define C_UIREALEDITOR_H

#include "FW/macro.h"

#include <QDialog>

class C_Record;
class C_RealRecord;
class C_Document;

namespace Ui {
class C_UiRealEditor;
}

class C_UiRealEditor : public QDialog
{
    Q_OBJECT

public:

                        C_UiRealEditor(C_RealRecord& record, C_Document& document, QWidget* parent=0);
                        ~C_UiRealEditor() override;

    ATR_POINTER         (Record,   C_RealRecord)
    ATR_POINTER         (Document, C_Document)


private slots:

    void                on_ButtonBox_accepted();
    void                on_RemoveButton_clicked();

private:

    Ui::C_UiRealEditor* ui;
};

#endif // C_UIREALEDITOR_H
