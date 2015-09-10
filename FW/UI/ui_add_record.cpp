#include "FW/RC/record.h"
#include "FW/document.h"
#include "FW/context.h"
#include "FW/SC/scene.h"
#include "FW/UI/ui_add_record.h"
#include "FW/RC/reference_record.h"
#include "ui_addrecord.h"
#include <QMessageBox>
#include <QStringListModel>

TypeUiAddRecord::TypeUiAddRecord( TypeController& controller, TypeContext& context, int index, QWidget* parent ) :
    QDialog( parent ),
    TypeVariant(0),
    m_Context( &context ),
    m_Controller( &controller ),
    ui( new Ui::TypeUiAddRecord )
{
    ui->setupUi( this );

    QStringListModel* model = new QStringListModel( this );
    QStringList class_list;

    for( TypeRecordFactory* record_factory : TypeStruct::FactoryList() )
        class_list << record_factory->RecordClass();

    model->setStringList( class_list );
    ui->ListView->setModel( model );
    ui->ListView->setCurrentIndex( model->index( 0 ) );
    ui->SpinBox->setMaximum( ( index < 0 ) ? Context().Struct().Size() : index );
    ui->SpinBox->setMinimum( 0 );
    ui->SpinBox->setValue( index  );
    ui->LineEdit->setText( "" );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::accepted,
        this,
        TypeUiAddRecord::OnButtonBoxAccepted );

    connect(
        ui->ButtonBox,
        QDialogButtonBox::rejected,
        this,
        TypeUiAddRecord::OnButtonBoxRejected );
}

TypeUiAddRecord::~TypeUiAddRecord()
{
    delete ui;
}

bool TypeUiAddRecord::CheckFormData() const
{
    int index = ui->SpinBox->value();

    if ( ( index > Context().Struct().Size() ) || ( index < 0 ) )
    {
        TypeController::Message( tr( "Position out of bounds" ) );
        return false;
    }

    if( !QRegExp( "[A-Za-z][\\w.]*" ).exactMatch( ui->LineEdit->text() ) )
    {
        TypeController::Message( tr( "Bad record name" ) );
        return false;
    }

    return true;
}

void TypeUiAddRecord::OnButtonBoxAccepted()
{
    if( CheckFormData() )
    {
        auto iter = TypeStruct::FactoryList().begin();
        int count = 0;

        while( count < ui->ListView->currentIndex().row() )
        {
            ++iter;
            ++count;
        }

        QString class_name = ( *iter )->RecordClass();
        QString name = ui->LineEdit->text();
        int index = ui->SpinBox->value();

        TypeRecord* record = Context().Struct().NewRecord(
                               name, "", class_name, index, &Context().Root() );

        if( ui->CheckBox->isChecked() )
            Context().Scene().NewItem( *record );

        emit Controller().SetActiveRecord( record );
        emit Controller().RecordsChanged();
        close();
    }
}


void TypeUiAddRecord::OnButtonBoxRejected()
{
    close();
}
