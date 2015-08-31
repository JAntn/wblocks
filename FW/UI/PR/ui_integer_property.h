#ifndef C_UIINTEGERPROPERTY
#define C_UIINTEGERPROPERTY

#include "FW/macro.h"
#include "FW/UI/PR/ui_property.h"
#include <QWidget>

namespace Ui
{
class C_UiIntegerProperty;
}

class C_UiIntegerProperty : public C_UiProperty
{
    Q_OBJECT

public:

    C_UiIntegerProperty( QString tag_name, long value, on_changed_t on_changed, QWidget* parent  = 0 );
    ~C_UiIntegerProperty() override;

    long                          Value();
    void                          SetValue( long value );

public slots:

    void                          OnReturnPressed();

private:

    Ui::C_UiIntegerProperty* ui;
};

#endif // C_UIINTEGERPROPERTY
