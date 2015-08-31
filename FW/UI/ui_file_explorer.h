#ifndef UI_FILE_EXPLORER_VIEW_H
#define UI_FILE_EXPLORER_VIEW_H

#include <QWidget>
#include "FW/macro.h"
#include <QStringListModel>

class TypeDocument;
class TypeController;

namespace Ui
{
class TypeUiFileExplorer;
}

class TypeUiFileExplorer : public QWidget
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

    Ui::TypeUiFileExplorer* ui;
};

#endif // UI_FILE_EXPLORER_VIEW_H
