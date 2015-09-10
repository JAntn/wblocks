#include "FW/UI/PR/ui_label_property.h"
#include "FW/controller.h"
#include "ui_labelproperty.h"


TypeUiLabelProperty::TypeUiLabelProperty( QString tag_name, QString value, QWidget* parent ):
    TypeUiProperty( &TypeUiProperty::empty_save_callback, parent ),
    ui( new Ui::TypeUiLabelProperty )
{
    ui->setupUi( this );
    ui->Label->setText( tag_name );
    ui->Label2->setText( value );
}

TypeUiLabelProperty::~TypeUiLabelProperty()
{
    delete ui;
}


void TypeUiLabelProperty::SetValue( QString value )
{
    ui->Label2->setText( value );
}

QString TypeUiLabelProperty::Value()
{
    return ui->Label2->text();
}



