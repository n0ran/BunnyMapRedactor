#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QPushButton>
#include <map>
#include "plist.h"
#include "helper.h"
using std::map;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    enum toolsButtonAction {
      nothing,
      cursor,
      set_original,
      set_bunny,
      set_active,
      set_bomb,
      set_fire,
      set_block,
      set_strong,
      set_teleport,
      set_monster
    };

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void labelClicked( QWidget * wdg );
    void RBOriginalClicked();
    void RBActiveClicked();
    void RBBlockClicked();
    void RBBombClicked();
    void RBBunnyClicked();
    void RBFireClicked();
    void RBMonsterClicked();
    void RBStrongClicked();
    void RBTeleportClicked();
    void CBVisibleClicked();
    void SBTimerValueChanged( int val );
    void OpenFileButtonClicked();
    void SaveFileButtonClicked();
    void CreateFileButtonClicked();
    void ToolsClicked( QWidget * wdg );
private:
    void Clear();
    void StartInit();
    void Init();
    void Init( QString &filename );
		void SetupParamsDialog();
    void PropertiesLogic( state st );
    void SetupWidgets();
    void ResetWidgets();
    void ResetWidgets( QString &filename );
    void UpdateControls();
    void ToolAction( cell * item );
    QPushButton * LastChecked;
    long  curItemIndex;
    QSignalMapper * signalMapper;
    QSignalMapper * toolMapper;
    Ui::MainWindow * ui;
    plist plst;

    toolsButtonAction tool_action;
    QPushButton * lastToolClicked;
};

//QStandardItem * GetStandardItemImage( QString & filename );

#endif // MAINWINDOW_H
