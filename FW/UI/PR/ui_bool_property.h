#ifndef TypeUIBOOLPROPERTY_H
#define TypeUIBOOLPROPERTY_H

#include "FW/macro.h"
#include "FW/UI/PR/ui_property.h"
#include <QWidget>

namespace Ui
{
class TypeUiBoolProperty;
}

class TypeUiBoolProperty : public TypeUiProperty
{
    Q_OBJECT

public:

    TypeUiBoolProperty( QString tag_name, bool value, on_changed_t on_changed, QWidget* parent  = 0 );
    ~TypeUiBoolProperty() override;

    bool        Value();
    void        SetValue( bool value );

public slots:

    void        OnCurrentIndexChanged( int );

private:

    Ui::TypeUiBoolProperty* ui;
};

#endif // TypeUIBOOLPROPERTY_H
