#include "FW/RC/record.h"
#include "FW/document.h"
#include "FW/context.h"
#include "FW/SC/scene.h"
#include "FW/UI/ui_add_record.h"
#include "ui_addrecord.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <QStringListModel>

TypeUiAddRecord::TypeUiAddRecord( TypeController& controller, TypeContext& context, int index, QWidget* parent ) :
    QDialog( parent ),
    TypeVariant( 0 ),
    m_Context( &context ),
    m_Controller( &controller ),
    ui( new Ui::TypeUiAddRecord )
{
    ui->setupUi( this );

    QStringListModel* model = new QStringListModel( this );
    QStringList class_list;

    for( TypeRecordFactory* record_factory : TypeController::FactoryList() )
        class_list << record_factory->RecordClass();

    model->setStringList( class_list );
    ui->ListView->setModel( model );
    ui->ListView->setCurrentIndex( model->index( 0 ) );
    ui->SpinBox->setMaximum( ( index < 0 ) ? Context().Struct().Size() : index );
    ui->SpinBox->setMinimum( 0 );
    ui->SpinBox->setValue( index  );
    ui->LineEdit->setText( "record" + QString::number( 1 + TypeRecordFactory::IdCount().toLong() ) );

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

    connect(
        ui->ListView->selectionModel(),
        QItemSelectionModel::selectionChanged,
        this,
        TypeUiAddRecord::OnSelectionChanged );
}

TypeUiAddRecord::~TypeUiAddRecord()
{
    delete ui;
}

bool TypeUiAddRecord::CheckFormData() const
{
    //
    // Check selected index to be inside allowed bounds:

    int index = ui->SpinBox->value();

    if ( ( index > Context().Struct().Size() ) || ( index < 0 ) )
    {
        TypeController::Message( tr( "Position out of bounds" ) );
        return false;
    }

    //
    // Check new record name correctness:

    if( !QRegExp( "[A-Za-z][A-Za-z0-9]*" ).exactMatch( ui->LineEdit->text() ) )
    {
        TypeController::Message( tr( "Bad record name" ) );
        return false;
    }

    return true;
}

void TypeUiAddRecord::OnSelectionChanged( const QItemSelection&, const QItemSelection& )
{
    //
    // Look for a record factory from input data:

    auto iter = TypeController::FactoryList().begin();
    int count = 0;

    while( count < ui->ListView->currentIndex().row() )
    {
        ++iter;
        ++count;
    }

    QString class_name = ( *iter )->RecordClass();

    ui->LineEdit->setText( class_name + QString::number( 1 + TypeRecordFactory::IdCount().toLong() ) );
}

void TypeUiAddRecord::OnButtonBoxAccepted()
{
    if( CheckFormData() )
    {
        //
        // Look for a record factory from input data:

        auto iter = TypeController::FactoryList().begin();
        int count = 0;

        while( count < ui->ListView->currentIndex().row() )
        {
            ++iter;
            ++count;
        }

        QString class_name = ( *iter )->RecordClass();

        //
        // Build new record using the record factory:

        QString name = ui->LineEdit->text();
        int index = ui->SpinBox->value();

        TypeRecord* record = Context().Struct().NewRecord( name, "", class_name, index );

        if( ui->CheckBox->isChecked() )
            Context().Scene().NewItem( *record );

        emit Controller().SetActiveRecord( record );
        emit Controller().RecordChanged( record );
        emit Controller().RecordChanged(/*generic slot*/);
        close();
    }
}


void TypeUiAddRecord::OnButtonBoxRejected()
{
    close();
}
