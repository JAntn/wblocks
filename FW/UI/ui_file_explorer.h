#ifndef UIFILEEXPLORER_H
#define UIFILEEXPLORER_H

#include "FW/tools.h"
#include <QStringListModel>

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

    M_VALUE                                 ( Path,       QString )
    M_VALUE                                 ( ModelData,  QStringList )
    M_REFERENCE                             ( Model,      QStringListModel )
    M_REFERENCE                             ( Controller, TypeController )

    void                                    Update();
    void                                    Open( QString file_name );

public slots:

    void                                    OnRootButtonClicked();
    void                                    OnUpButtonClicked();
    void                                    OnDoubleClicked( const QModelIndex& index );
    void                                    OnLineEditReturnPressed();

private:

    QString                                 FullPath();
    Ui::TypeUiFileExplorer*                 ui;
};

#endif // UIFILEEXPLORER_H
