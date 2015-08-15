#ifndef C_UiBoolEditor_H
#define C_UiBoolEditor_H

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

    ATR_POINTER         ( Record,   C_BoolRecord )
    ATR_POINTER         ( Document, C_Document )


public slots:

    void                OnButtonBoxAccepted();
    void                OnRemoveButtonClicked();

private:

    Ui::C_UiBoolEditor* ui;
};

#endif // C_UiBoolEditor_H
