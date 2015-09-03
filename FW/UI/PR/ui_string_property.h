#ifndef UISTRINGPROPERTY_H
#define UISTRINGPROPERTY_H

#include "FW/macro.h"
#include "FW/UI/PR/ui_property.h"
#include <QWidget>

namespace Ui
{
class TypeUiStringProperty;
}

class TypeUiStringProperty : public TypeUiProperty
{
    Q_OBJECT

public:

    TypeUiStringProperty( QString tag_name, QString value, TypeSaveCallback on_changed, QWidget* parent  = 0 );
    ~TypeUiStringProperty() override;

    QString                       Value();
    void                          SetValue( QString value );

private slots:

    void                          OnApplyButtonClicked();

private:

    Ui::TypeUiStringProperty*         ui;
};

#endif // UISTRINGPROPERTY_H
