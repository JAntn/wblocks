#include "FW/UI/PR/ui_bool_property.h"
#include "ui_boolproperty.h"


TypeUiBoolProperty::TypeUiBoolProperty( QString tag_name, bool value, on_changed_t on_changed, QWidget* parent ) :
    TypeUiProperty( on_changed, parent ),
    ui( new Ui::TypeUiBoolProperty )
{
    ui->setupUi( this );
    ui->Label->setText( tag_name );
    ui->ComboBox->addItem( "False" );
    ui->ComboBox->addItem( "True" );
    ui->ComboBox->setCurrentIndex( value ? 1 : 0 );

    QObject::connect(
        ui->ComboBox,
        static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        this,
        TypeUiBoolProperty::OnCurrentIndexChanged
    );
}

TypeUiBoolProperty::~TypeUiBoolProperty()
{
    delete ui;
}

bool TypeUiBoolProperty::Value()
{
    bool value =  false;

    if( ui->ComboBox->currentIndex() == 1 )
        value = true;

    return value;
}

void TypeUiBoolProperty::SetValue( bool value )
{
    ui->ComboBox->setCurrentIndex( value ? 1 : 0 );
}

void TypeUiBoolProperty::OnCurrentIndexChanged( int )
{
    OnApplyChanges();
}

