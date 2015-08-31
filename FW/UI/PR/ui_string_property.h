#ifndef C_UISTRINGPROPERTY_H
#define C_UISTRINGPROPERTY_H

#include "FW/macro.h"
#include "FW/UI/PR/ui_property.h"
#include <QWidget>

namespace Ui
{
class C_UiStringProperty;
}

class C_UiStringProperty : public C_UiProperty
{
    Q_OBJECT

public:

    C_UiStringProperty( QString tag_name, QString value, on_changed_t on_changed, QWidget* parent  = 0 );
    ~C_UiStringProperty() override;

    QString                       Value();
    void                          SetValue( QString value );

private slots:

    void                          OnApplyButtonClicked();

private:

    Ui::C_UiStringProperty*         ui;
};

#endif // C_UISTRINGPROPERTY_H
