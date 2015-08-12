#ifndef C_UIMAINWINDOW_H
#define C_UIMAINWINDOW_H

#include "FW/macro.h"
#include <QMainWindow>


class C_Document;
class C_Record;
class C_UiRecordStructView;
class C_UiRecordTableModel;

namespace Ui {
class C_UiMainWindow;
}

class C_UiMainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit C_UiMainWindow(QWidget* parent = 0);
    ~C_UiMainWindow() override;

    void                          UpdateTableView();
    void                          UpdateScriptView();
    void                          UpdateSceneView();

    void                          ConnectSignals();

    ATR_POINTER                   (Document,         C_Document)
    ATR_POINTER                   (RecordStructView, C_UiRecordStructView)

private slots:

    void                          on_ActionNew_triggered();
    void                          on_ActionAdd_triggered();
    void                          on_ActionFind_triggered();
    void                          on_ActionExit_triggered();
    void                          on_ActionRun_triggered();
    void                          on_ActionCopy_triggered();
    void                          on_ActionPaste_triggered();
    void                          on_ActionRemove_triggered();
    void                          on_ActionAdd_to_scene_triggered();
    void                          on_ActionCut_triggered();

private:

    Ui::C_UiMainWindow*           ui;

};

#endif // C_UIMAINWINDOW_H
