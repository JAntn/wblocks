#ifndef UIADDRECORD_H
#define UIADDRECORD_H

#include "FW/tools.h"
#include <QDialog>

class TypeRecord;
class TypeContext;
class TypeController;
class TypeVariant;

namespace Ui
{
class TypeUiAddRecord;
}

class TypeUiAddRecord : public QDialog, public TypeVariant
{
    Q_OBJECT

public:

    explicit TypeUiAddRecord( TypeController& controller, TypeContext& context, int position = -1, QWidget* parent = 0 );
    ~TypeUiAddRecord() override;

    bool                CheckFormData() const;

    M_REFERENCE         ( Context,    TypeContext )
    M_REFERENCE         ( Controller, TypeController )

public slots:

    void                OnButtonBoxAccepted();
    void                OnButtonBoxRejected();
    void                OnSelectionChanged( const QItemSelection&, const QItemSelection& );

private:

    Ui::TypeUiAddRecord* ui;
};

#endif // UIADDRECORD_H
