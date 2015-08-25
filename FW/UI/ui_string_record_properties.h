#ifndef C_UISTRINGRECORDPROPERTIES_H
#define C_UISTRINGRECORDPROPERTIES_H

#include "FW/macro.h"

#include <QDialog>

class C_Record;
class C_StringRecord;
class C_Document;

namespace Ui
{
class C_UiStringRecordProperties;
}

class C_UiStringRecordProperties : public QDialog
{
    Q_OBJECT

public:

    C_UiStringRecordProperties( C_StringRecord& record, C_Document& document, QWidget* parent = 0 );
    ~C_UiStringRecordProperties() override;

    M_POINTER                    ( Record,   C_StringRecord )
    M_POINTER                    ( Document, C_Document )

private slots:

    void                          OnButtonBoxAccepted();
    void                          OnRemoveButtonClicked();

private:

    Ui::C_UiStringRecordProperties*         ui;
};

#endif // C_UISTRINGRECORDPROPERTIES_H
