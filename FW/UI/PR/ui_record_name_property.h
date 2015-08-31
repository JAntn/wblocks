#ifndef UI_RECORDNAME_PROPERTY_H
#define UI_RECORDNAME_PROPERTY_H

#include "FW/macro.h"
#include "FW/UI/PR/ui_property.h"
#include <QWidget>

class C_Record;
class C_StringRecord;
class C_Document;

namespace Ui
{
class C_UiRecordNameProperty;
}

class C_UiRecordNameProperty : public C_UiProperty
{
    Q_OBJECT

public:

    C_UiRecordNameProperty( QString tag_name, QString value, on_changed_t on_changed, QWidget* parent  = 0 );
    ~C_UiRecordNameProperty() override;

    QString                       Value();
    void                          SetValue( QString value );

private slots:

    void                          OnReturnPressed();

private:

    Ui::C_UiRecordNameProperty*    ui;
};


#endif // UI_RECORDNAME_PROPERTY_H
