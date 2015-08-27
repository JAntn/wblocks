#ifndef C_UIFILERECORDPROPERTIES_H
#define C_UIFILERECORDPROPERTIES_H

#include "FW/macro.h"
#include <QDialog>

class C_FileRecord;
class C_Document;

namespace Ui
{
class C_UiFileRecordProperties;
}

class C_UiFileRecordProperties : public QDialog
{
    Q_OBJECT

public:

    C_UiFileRecordProperties( C_FileRecord& record, C_Document& document, QWidget* parent = 0 );
    ~C_UiFileRecordProperties() override;

    M_POINTER           ( Record,   C_FileRecord )
    M_POINTER           ( Document, C_Document )


private slots:

    void                OnButtonBoxAccepted();
    void                OnRemoveButtonClicked();
    void                OnSelectButtonClicked();

private:

    Ui::C_UiFileRecordProperties* ui;
};

#endif // C_UIFILERECORDPROPERTIES_H
