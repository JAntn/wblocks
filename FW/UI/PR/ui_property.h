#ifndef UIPROPERTY_H
#define UIPROPERTY_H

#include "FW/variant.h"
#include "FW/macro.h"
#include <QWidget>
#include <functional>

class TypeUiProperty : public QWidget, public TypeVariant
{
    Q_OBJECT

public:

    typedef std::function<void( TypeUiProperty& )> TypeSaveCallback;

    TypeUiProperty( TypeSaveCallback save, QWidget* parent );

    M_VALUE             ( SaveCallback, TypeSaveCallback )

public slots:

    void                OnApplyChanges();

};

#endif // UIPROPERTY_H
