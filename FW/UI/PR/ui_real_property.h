#ifndef TypeUIREALPROPERTY_H
#define TypeUIREALPROPERTY_H

#include "FW/macro.h"
#include <QWidget>
#include "FW/UI/PR/ui_property.h"


namespace Ui
{
class TypeUiRealProperty;
}

class TypeUiRealProperty : public TypeUiProperty
{
    Q_OBJECT

public:

    TypeUiRealProperty( QString tag_name, double value, on_changed_t on_changed, QWidget* parent  = 0 );
    ~TypeUiRealProperty() override;

    double                        Value();
    void                          SetValue( double value );

public slots:

    void                          OnReturnPressed();

private:

    Ui::TypeUiRealProperty* ui;
};

#endif // TypeUIREALPROPERTY_H
