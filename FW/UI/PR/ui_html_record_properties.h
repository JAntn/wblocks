#ifndef C_UIHTMLRECORDPROPERTIES_H
#define C_UIHTMLRECORDPROPERTIES_H

#include "FW/macro.h"
#include <QDialog>

class C_Record;
class C_HtmlRecord;
class C_Document;

namespace Ui
{
class C_UiHtmlRecordProperties;
}

class C_UiHtmlRecordProperties : public QDialog
{
    Q_OBJECT

public:

    C_UiHtmlRecordProperties( C_HtmlRecord& record, C_Document& document, QWidget* parent = 0 );
    ~C_UiHtmlRecordProperties() override;

    M_POINTER                    ( Record,   C_HtmlRecord )
    M_POINTER                    ( Document, C_Document )

private slots:

    void                          OnButtonBoxAccepted();
    void                          OnRemoveButtonClicked();

private:

    Ui::C_UiHtmlRecordProperties*         ui;
};

#endif // C_UIHTMLRECORDPROPERTIES_H
