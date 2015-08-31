#ifndef C_UILINETEXTPROPERTY_H
#define C_UILINETEXTPROPERTY_H

#include "FW/macro.h"
#include "FW/UI/PR/ui_property.h"
#include <QWidget>

namespace Ui
{
class C_UiLineTextProperty;
}

class C_UiLineTextProperty : public C_UiProperty
{
    Q_OBJECT

public:

    C_UiLineTextProperty( QString tag_name, QString value, on_changed_t on_changed, QWidget* parent  = 0 );
    ~C_UiLineTextProperty() override;

    QString                       Value();
    void                          SetValue( QString value );

private slots:

    void                          OnReturnPressed();

private:

    Ui::C_UiLineTextProperty*         ui;
};

#endif // C_UILINETEXTPROPERTY_H
