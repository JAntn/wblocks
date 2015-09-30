#ifndef UIVALUEOPENPROPERTY_H
#define UIVALUEOPENPROPERTY_H

#include "FW/tools.h"
#include "FW/UI/PR/ui_property.h"

namespace Ui
{
class TypeUiValueOpenProperty;
}

class TypeUiValueOpenProperty : public TypeUiProperty
{
    Q_OBJECT

public:

    typedef std::function<void( TypeUiProperty& )> TypeOpenCallback;

    TypeUiValueOpenProperty( QString tag_name, QString value, TypeSaveCallback on_changed, TypeOpenCallback on_open, QWidget* parent  = 0 );
    ~TypeUiValueOpenProperty() override;

    QString                              Value();
    void                                 SetValue( QString value );

    M_VALUE                              ( OpenCallback, TypeOpenCallback )

private slots:

    void                                 OnReturnPressed();
    void                                 OnOpenButtonClicked();

private:

    Ui::TypeUiValueOpenProperty*         ui;
};

#endif // UIVALUEOPENPROPERTY_H
