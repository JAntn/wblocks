#include "FW/UI/PR/ui_bool_property.h"
#include "ui_boolproperty.h"


C_UiBoolProperty::C_UiBoolProperty( QString tag_name, bool value, on_changed_t on_changed, QWidget* parent ) :
    C_UiProperty( on_changed, parent ),
    ui( new Ui::C_UiBoolProperty )
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
        C_UiBoolProperty::OnCurrentIndexChanged
    );
}

C_UiBoolProperty::~C_UiBoolProperty()
{
    delete ui;
}

bool C_UiBoolProperty::Value()
{
    bool value =  false;

    if( ui->ComboBox->currentIndex() == 1 )
        value = true;

    return value;
}

void C_UiBoolProperty::SetValue( bool value )
{
    ui->ComboBox->setCurrentIndex( value ? 1 : 0 );
}

void C_UiBoolProperty::OnCurrentIndexChanged( int )
{
    OnApplyChanges();
}

