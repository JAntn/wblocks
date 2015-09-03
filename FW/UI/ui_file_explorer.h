#ifndef UIFILEEXPLORER_H
#define UIFILEEXPLORER_H

#include "FW/variant.h"
#include "FW/macro.h"
#include <QStringListModel>
#include <QWidget>

class TypeDocument;
class TypeController;

namespace Ui
{
class TypeUiFileExplorer;
}

class TypeUiFileExplorer : public QWidget, public TypeVariant
{
    Q_OBJECT

public:

    TypeUiFileExplorer( TypeController& controller, QWidget* parent = 0 );
    ~TypeUiFileExplorer();

    M_VALUE                       ( Path,       QString )
    M_VALUE                       ( ModelData,  QStringList )
    M_POINTER                     ( Model,      QStringListModel )
    M_POINTER                     ( Controller, TypeController )

    void                          Update();
    void                          Open( QString file_name );

public slots:

    void OnRootButtonClicked();
    void OnUpButtonClicked();
    void OnDoubleClicked( const QModelIndex& index );
    void OnLineEditReturnPressed();

private:

    QString                       FullPath();
    Ui::TypeUiFileExplorer*       ui;
};

#endif // UIFILEEXPLORER_H
