#ifndef TypeUIFILEPROPERTY_H
#define TypeUIFILEPROPERTY_H

#include "FW/UI/PR/ui_property.h"
#include "FW/macro.h"
#include <QWidget>


namespace Ui
{
class TypeUiFileProperty;
}

class TypeUiFileProperty : public TypeUiProperty
{
    Q_OBJECT

public:

    TypeUiFileProperty( QString tag_name, QString value, on_changed_t on_changed, QWidget* parent  = 0 );
    ~TypeUiFileProperty() override;

    QString                       Value();
    void                          SetValue( QString value );

private slots:

    void                          OnReturnPressed();
    void                          OnSelectButtonClicked();

private:

    Ui::TypeUiFileProperty* ui;
};

#endif // TypeUIFILEPROPERTY_H
