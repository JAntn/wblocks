#ifndef C_UIREALPROPERTY_H
#define C_UIREALPROPERTY_H

#include "FW/macro.h"
#include <QWidget>
#include "FW/UI/PR/ui_property.h"


namespace Ui
{
class C_UiRealProperty;
}

class C_UiRealProperty : public C_UiProperty
{
    Q_OBJECT

public:

    C_UiRealProperty( QString tag_name, double value, on_changed_t on_changed, QWidget* parent  = 0 );
    ~C_UiRealProperty() override;

    double                        Value();
    void                          SetValue( double value );

public slots:

    void                          OnReturnPressed();

private:

    Ui::C_UiRealProperty* ui;
};

#endif // C_UIREALPROPERTY_H
