#ifndef UIPROPERTY_H
#define UIPROPERTY_H

#include "FW/tools.h"

class TypeUiProperty : public QWidget, public TypeVariant
{
    Q_OBJECT

public:

    typedef std::function<bool( TypeUiProperty& )> TypeSaveCallback;

    TypeUiProperty( TypeSaveCallback save, QWidget* parent );

    M_VALUE                                 ( SaveCallback, TypeSaveCallback )

    static bool                             empty_save_callback( TypeUiProperty& );

public slots:

    void                                    OnActionSave();

signals:

    void                                    HasSaved();

};

#endif // UIPROPERTY_H
