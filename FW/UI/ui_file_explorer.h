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

    void                                    FileNew();

    void                                    FileOpen();
    void                                    FileOpen( QString file_name );

    void                                    FileRemove();
    void                                    FileRemove( QString file_name );

    void                                    FileMkDir();

public slots:

    void                                    OnRootButtonClicked();
    void                                    OnUpButtonClicked();
    void                                    OnDoubleClicked( const QModelIndex& index );
    void                                    OnLineEditReturnPressed();
    void                                    OnCustomContextMenuRequested(const QPoint& point);

private:

    QString                                 FullPath();
    Ui::TypeUiFileExplorer*                 ui;
};

#endif // UIFILEEXPLORER_H
