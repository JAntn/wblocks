#ifndef TypeUIADDRECORD_H
#define TypeUIADDRECORD_H

#include "FW/macro.h"

#include <QDialog>

class TypeRecord;
class TypeContext;
class TypeController;

namespace Ui
{
class TypeUiAddRecord;
}

class TypeUiAddRecord : public QDialog
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

#endif // TypeUIADDRECORD_H
