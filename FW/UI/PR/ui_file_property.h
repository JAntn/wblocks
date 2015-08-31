#ifndef C_UIFILEPROPERTY_H
#define C_UIFILEPROPERTY_H

#include "FW/UI/PR/ui_property.h"
#include "FW/macro.h"
#include <QWidget>


namespace Ui
{
class C_UiFileProperty;
}

class C_UiFileProperty : public C_UiProperty
{
    Q_OBJECT

public:

    C_UiFileProperty( QString tag_name, QString value, on_changed_t on_changed, QWidget* parent  = 0 );
    ~C_UiFileProperty() override;

    QString                       Value();
    void                          SetValue( QString value );

private slots:

    void                          OnReturnPressed();
    void                          OnSelectButtonClicked();

private:

    Ui::C_UiFileProperty* ui;
};

#endif // C_UIFILEPROPERTY_H
