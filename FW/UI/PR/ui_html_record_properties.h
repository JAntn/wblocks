#ifndef TypeUIHTMLRECORDPROPERTIES_H
#define TypeUIHTMLRECORDPROPERTIES_H

#include "FW/macro.h"
#include <QDialog>
#include "FW/UI/PR/ui_property.h"

class TypeRecord;
class TypeHtmlRecord;
class TypeDocument;

namespace Ui
{
class TypeUiHtmlRecordProperties;
}

class TypeUiHtmlRecordProperties : public QDialog
{
    Q_OBJECT

public:

    TypeUiHtmlRecordProperties( TypeHtmlRecord& record, TypeDocument& document, QWidget* parent = 0 );
    ~TypeUiHtmlRecordProperties() override;

    M_POINTER                    ( Record,   TypeHtmlRecord )
    M_POINTER                    ( Document, TypeDocument )

private slots:

    void                          OnButtonBoxAccepted();
    void                          OnRemoveButtonClicked();

private:

    Ui::TypeUiHtmlRecordProperties*         ui;
};

#endif // TypeUIHTMLRECORDPROPERTIES_H
