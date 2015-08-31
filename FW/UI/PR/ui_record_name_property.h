#ifndef UI_RECORDNAME_PROPERTY_H
#define UI_RECORDNAME_PROPERTY_H

#include "FW/macro.h"
#include "FW/UI/PR/ui_property.h"
#include <QWidget>

class TypeRecord;
class TypeStringRecord;
class TypeDocument;

namespace Ui
{
class TypeUiRecordNameProperty;
}

class TypeUiRecordNameProperty : public TypeUiProperty
{
    Q_OBJECT

public:

    TypeUiRecordNameProperty( QString tag_name, QString value, on_changed_t on_changed, QWidget* parent  = 0 );
    ~TypeUiRecordNameProperty() override;

    QString                       Value();
    void                          SetValue( QString value );

private slots:

    void                          OnReturnPressed();

private:

    Ui::TypeUiRecordNameProperty*    ui;
};


#endif // UI_RECORDNAME_PROPERTY_H
