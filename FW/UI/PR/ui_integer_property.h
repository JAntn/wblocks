#ifndef UIINTEGERPROPERTY
#define UIINTEGERPROPERTY

#include "FW/macro.h"
#include "FW/UI/PR/ui_property.h"
#include <QWidget>

namespace Ui
{
class TypeUiIntegerProperty;
}

class TypeUiIntegerProperty : public TypeUiProperty
{
    Q_OBJECT

public:

    TypeUiIntegerProperty( QString tag_name, long value, TypeSaveCallback on_changed, QWidget* parent  = 0 );
    ~TypeUiIntegerProperty() override;

    long                          Value();
    void                          SetValue( long value );

public slots:

    void                          OnReturnPressed();

private:

    Ui::TypeUiIntegerProperty* ui;
};

#endif // UIINTEGERPROPERTY
