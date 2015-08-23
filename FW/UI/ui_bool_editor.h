#ifndef C_UIBOOLEDITOR_H
#define C_UIBOOLEDITOR_H

#include "FW/macro.h"

#include <QDialog>

class C_Record;
class C_BoolRecord;
class C_Document;

namespace Ui
{
class C_UiBoolEditor;
}

class C_UiBoolEditor : public QDialog
{
    Q_OBJECT

public:

    C_UiBoolEditor( C_BoolRecord& record, C_Document& document, QWidget* parent = 0 );
    ~C_UiBoolEditor() override;

    M_POINTER           ( Record,   C_BoolRecord )
    M_POINTER           ( Document, C_Document )

public slots:

    void                OnButtonBoxAccepted();
    void                OnRemoveButtonClicked();

private:

    Ui::C_UiBoolEditor* ui;
};

#endif // C_UIBOOLEDITOR_H
