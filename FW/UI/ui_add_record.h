#ifndef UIADDRECORD_H
#define UIADDRECORD_H

#include "FW/macro.h"
#include "FW/variant.h"
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

    M_POINTER           ( Context,    TypeContext )
    M_POINTER           ( Controller, TypeController )

public slots:

    void                OnButtonBoxAccepted();
    void                OnButtonBoxRejected();

private:

    Ui::TypeUiAddRecord* ui;
};

#endif // UIADDRECORD_H
