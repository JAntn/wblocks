#ifndef C_UISTRINGEDITOR_H
#define C_UISTRINGEDITOR_H

#include "FW/macro.h"

#include <QDialog>

class C_Record;
class C_StringRecord;
class C_Document;

namespace Ui
{
class C_UiStringEditor;
}

class C_UiStringEditor : public QDialog
{
    Q_OBJECT

public:

    C_UiStringEditor( C_StringRecord& record, C_Document& document, QWidget* parent = 0 );
    ~C_UiStringEditor() override;

    M_POINTER                    ( Record,   C_StringRecord )
    M_POINTER                    ( Document, C_Document )

private slots:

    void                          OnButtonBoxAccepted();
    void                          OnRemoveButtonClicked();

private:

    Ui::C_UiStringEditor*         ui;
};

#endif // C_UISTRINGEDITOR_H
