#ifndef TypeUILINETEXTPROPERTY_H
#define TypeUILINETEXTPROPERTY_H

#include "FW/macro.h"
#include "FW/UI/PR/ui_property.h"
#include <QWidget>

namespace Ui
{
class TypeUiLineTextProperty;
}

class TypeUiLineTextProperty : public TypeUiProperty
{
    Q_OBJECT

public:

    TypeUiLineTextProperty( QString tag_name, QString value, on_changed_t on_changed, QWidget* parent  = 0 );
    ~TypeUiLineTextProperty() override;

    QString                       Value();
    void                          SetValue( QString value );

private slots:

    void                          OnReturnPressed();

private:

    Ui::TypeUiLineTextProperty*         ui;
};

#endif // TypeUILINETEXTPROPERTY_H
