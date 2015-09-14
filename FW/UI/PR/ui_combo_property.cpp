#include "FW/UI/PR/ui_combo_property.h"
#include "ui_comboproperty.h"


TypeUiComboProperty::TypeUiComboProperty(QString tag_name, int value, QStringList value_list, TypeSaveCallback save_callback, QWidget* parent ) :
    TypeUiProperty( save_callback, parent ),
    ui( new Ui::TypeUiComboProperty )
{
    ui->setupUi( this );
    ui->Label->setText( tag_name );

    for( QString item : value_list )
        ui->ComboBox->addItem( item );

    ui->ComboBox->setCurrentIndex( value );

    QObject::connect(
        ui->ComboBox,
        static_cast<void( QComboBox::* )( int )>( &QComboBox::currentIndexChanged ),
        this,
        TypeUiComboProperty::OnCurrentIndexChanged
    );
}

TypeUiComboProperty::~TypeUiComboProperty()
{
    delete ui;
}

int TypeUiComboProperty::Value()
{
    return ui->ComboBox->currentIndex();
}

void TypeUiComboProperty::SetValue( int value )
{
    ui->ComboBox->setCurrentIndex( value );
}

void TypeUiComboProperty::OnCurrentIndexChanged( int )
{
    OnActionSave();
}

