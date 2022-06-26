#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QRandomGenerator>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QHideEvent>
#include <QShowEvent>
#include <QKeySequence>
#include "windows/main/TetrisModel.h"
#include "windows/main/TetrisController.h"
#include "utils/Constants.h"
#include "utils/Extensions.h"
#include "utils/Counter.h"
#include "database/Database.h"
#include "audio_effect/AudioEffect.h"
#include "utils/Resources.h"
#include "settings/Settings.h"
#include "windows/settings/SettingsWindow.h"

typedef std::vector<std::vector<int>> Matrix;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
        Q_OBJECT
    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
    
    private:
        Ui::MainWindow *ui;
        SettingsWindow *settingsWindow = new SettingsWindow(this);
        TetrisModel *model = new TetrisModel();
        TetrisController *controller = new TetrisController();
        QGraphicsScene *mainScene = new QGraphicsScene;
        QGraphicsScene *nextItemScene = new QGraphicsScene;
        Database * database = new Database();
        Counter * counter = new Counter();
        AudioEffect * audioEffect = new AudioEffect();
        void connectToCounter();
        void connectToSettingsWindow();
        void connectUi();
        void connectToModel();
        void connectToController();
        void prepareUi();
        void configurateWindow();
        void onAction(int action);
        void updateScoreTable();
        void updateCheckBoxIcons();
        void drawBlock(QGraphicsScene *scene, int x, int y, int itemId);
    
    private slots:
        void refreshMainScene(Matrix gameField, Matrix currentItem,
                           int currentItemX, int currentItemY);
        void refreshNextItemScene(Matrix nextItem);
        void onReceiveEvent(int event);
        void onControlsChanged(ControlsModel newControls);
        void onCheckBoxStateChanged(int state);
        void onButtonClick();
        void updateScore(int score);
        void updateLines(int lines);
        void updateLevel(int level);
        void updateTime(long milliseconds);
        void onClearDatabaseAccepted();
    
    private:
        Resources R;
        Settings settings = Settings();
        Extension ext = Extension();
        ControlsModel mControls = settings.getGroupControls();
        MainWindowModel mMainWindow = settings.getGroupMainWindow();

    protected:
        virtual void keyPressEvent(QKeyEvent *ev);
        virtual void keyReleaseEvent(QKeyEvent *ev);
        virtual void showEvent(QShowEvent *ev);
        virtual void hideEvent(QHideEvent *ev);
};
#endif // MAINWINDOW_H
