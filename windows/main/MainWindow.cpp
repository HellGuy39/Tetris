#include "windows/main/MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(R.strings.title_tetris);

    connectToCounter();
    connectToSettingsWindow();
    connectUi();
    connectToController();
    connectToModel();

    model->init();

    configurateWindow();
    updateScoreTable();

    audioEffect->playBackgroundMusic();

    prepareUi();
}

void MainWindow::connectToSettingsWindow()
{
    connect(settingsWindow, SIGNAL(onSoundGroupChanged(SoundModel)),
            audioEffect, SLOT(onSoundSettingsChanged(SoundModel)));

    connect(settingsWindow, SIGNAL(onControlsGroupChanged(ControlsModel)),
            this, SLOT(onControlsChanged(ControlsModel)));

    connect(settingsWindow, SIGNAL(onClearDatabase()),
            this, SLOT(onClearDatabaseAccepted()));
}

void MainWindow::connectUi()
{
    connect(ui->cbMuteMusic, SIGNAL(stateChanged(int)),
            this, SLOT(onCheckBoxStateChanged(int)));

    connect(ui->cbMuteSFX, SIGNAL(stateChanged(int)),
            this, SLOT(onCheckBoxStateChanged(int)));

    connect(ui->btnSettings, SIGNAL(clicked()),
            this, SLOT(onButtonClick()));

    connect(ui->btnSkipTrack, SIGNAL(clicked()),
            this, SLOT(onButtonClick()));
}

void MainWindow::connectToController()
{
    connect(controller, SIGNAL(onSendAction(int)),
            model, SLOT(onReceiveAction(int)));

    connect(controller, SIGNAL(onTimeChanged(long)),
            this, SLOT(updateTime(long)));
}

void MainWindow::connectToModel()
{

    connect(model,SIGNAL(onModelUpdated(Matrix,Matrix,int,int)),
            this, SLOT(refreshMainScene(Matrix,Matrix,int,int)));

    connect(model,SIGNAL(onNextItemUpdated(Matrix)),
            this, SLOT(refreshNextItemScene(Matrix)));

    connect(model, SIGNAL(onEvent(int)),
            this, SLOT(onReceiveEvent(int)));

}

void MainWindow::connectToCounter()
{
    connect(counter, SIGNAL(onScoreChanged(int)),
            this, SLOT(updateScore(int)));

    connect(counter, SIGNAL(onLinesChanged(int)),
            this, SLOT(updateLines(int)));

    connect(counter, SIGNAL(onLevelChanged(int)),
            this, SLOT(updateLevel(int)));
}

void MainWindow::onClearDatabaseAccepted()
{
    database->clearDatabase();
    updateScoreTable();
}

void MainWindow::updateScore(int score)
{
    ui->lScore->setText(R.strings.score + QString::number(score));
}

void MainWindow::updateLines(int lines)
{
    ui->lLines->setText(R.strings.lines + QString::number(lines));
}

void MainWindow::updateLevel(int level)
{
    ui->lLevel->setText(R.strings.level + QString::number(level));
    controller->updateInterval(level);
}

void MainWindow::prepareUi()
{
    ui->btnSettings->setIcon(R.icon.settings);
    ui->btnSkipTrack->setIcon(R.icon.skip_forward);

    ui->iconTime->setPixmap(R.icon.time.pixmap(ICON_HEIGHT, ICON_WIDTH));

    if(mMainWindow.getIsMusicMuted())
        ui->cbMuteMusic->setCheckState(Qt::Checked);
    else
        ui->cbMuteMusic->setCheckState(Qt::Unchecked);

    if(mMainWindow.getIsSfxMuted())
        ui->cbMuteSFX->setCheckState(Qt::Checked);
    else
        ui->cbMuteSFX->setCheckState(Qt::Unchecked);

    updateCheckBoxIcons();

    mainScene->setBackgroundBrush(R.drawable.background);
    nextItemScene->setBackgroundBrush(R.drawable.background);

    ui->graphicsView->setScene(mainScene);
    ui->gvNextItem->setScene(nextItemScene);
}

void MainWindow::configurateWindow()
{
    int height = ext.getGameFieldHeight(), width = ext.getGameFieldWidth();

    setFocus();
    ui->gvNextItem->setMinimumSize(5 * RESOLUTION, 5 * RESOLUTION);
    ui->graphicsView->setFixedSize(height * RESOLUTION, width* RESOLUTION);
    this->adjustSize();
}

void MainWindow::refreshNextItemScene(Matrix nextItem)
{
    if(!nextItemScene->items().isEmpty())
        qDeleteAll(nextItemScene->items());


    for(size_t itemSizeX = 0; itemSizeX < nextItem.size(); itemSizeX++)
        for(size_t itemSizeY = 0; itemSizeY < nextItem[itemSizeX].size(); itemSizeY++)
            if(nextItem[itemSizeX][itemSizeY] != 0)
                drawBlock(nextItemScene,
                         (0 + itemSizeX) * RESOLUTION,
                         (0 + itemSizeY) * RESOLUTION,
                         nextItem[itemSizeX][itemSizeY]);
}

void MainWindow::onReceiveEvent(int event)
{
    switch(event)
    {
        case EVENT_ITEM_ROTATED:
            audioEffect->makeSoundEffect(EFFECT_ITEM_ROTATED);
            break;

        case EVENT_ITEM_MOVED_SIDEWAY:
            audioEffect->makeSoundEffect(EFFECT_ITEM_MOVED_SIDEWAY);
            break;

        case EVENT_NEW_GAME:
            counter->clear();
            break;

        case EVENT_ITEM_PLACED:
            counter->increaseScore(event);

            audioEffect->makeSoundEffect(EFFECT_ITEM_PLACED);
            break;

        case EVENT_LINE_COMPLETED_S1:
            counter->increaseScore(event);
            counter->increaseLines();
            if(counter->isNextLevel())
                audioEffect->makeSoundEffect(EFFECT_NEXT_LEVEL);
            else
                audioEffect->makeSoundEffect(EFFECT_LINE_COMPLETED);
            break;

        case EVENT_LINE_COMPLETED_S2:
            counter->increaseScore(event);
            counter->increaseLines();
            if(counter->isNextLevel())
                audioEffect->makeSoundEffect(EFFECT_NEXT_LEVEL);
            else
                audioEffect->makeSoundEffect(EFFECT_LINE_COMPLETED);
            break;

        case EVENT_LINE_COMPLETED_S3:
            counter->increaseScore(event);
            counter->increaseLines();
            if(counter->isNextLevel())
                audioEffect->makeSoundEffect(EFFECT_NEXT_LEVEL);
            else
                audioEffect->makeSoundEffect(EFFECT_LINE_COMPLETED);
            break;

        case EVENT_LINE_COMPLETED_S4:
            counter->increaseScore(event);
            counter->increaseLines();
            if(counter->isNextLevel())
                audioEffect->makeSoundEffect(EFFECT_NEXT_LEVEL);
            else
                audioEffect->makeSoundEffect(EFFECT_LINE_COMPLETED);
            break;

        case EVENT_BLOCK_OUT:
            controller->onAction(ACTION_BLOCK_OUT);
            database->insertScore(0, counter->getScore(), counter->getLevel(), counter->getLines());
            updateScoreTable();
            audioEffect->makeSoundEffect(EFFECT_GAME_OVER);
            break;

        case EVENT_PAUSED:
            //mainScene->addItem(ext.getPauseItem());
            break;
    }
}

void MainWindow::refreshMainScene(Matrix gameField, Matrix currentItem, int currentItemX, int currentItemY)
{

    if(!mainScene->items().isEmpty())
        qDeleteAll(mainScene->items());

    for (size_t x = 0; x < gameField.size(); x++)
        for (size_t y = 0; y < gameField[y].size(); y++)
            if(gameField[x][y] != 0)
                drawBlock(mainScene,
                         x * RESOLUTION,
                         y * RESOLUTION,
                         gameField[x][y]);

    for(size_t itemSizeX = 0; itemSizeX < currentItem.size(); itemSizeX++)
        for(size_t itemSizeY = 0; itemSizeY < currentItem[itemSizeX].size(); itemSizeY++)
            if(currentItem[itemSizeX][itemSizeY] != 0)
                drawBlock(mainScene,
                         (currentItemX + itemSizeX) * RESOLUTION,
                         (currentItemY + itemSizeY) * RESOLUTION,
                         currentItem[itemSizeX][itemSizeY]);


    // Draw this pause or block out items after
    // main scene, because it must in front of
    // other game objects.
    if (controller->getGameState() == PAUSED)
        mainScene->addItem(ext.getPauseItem());
    else if (controller->getGameState() == BLOCK_OUT)
        mainScene->addItem(ext.getBlockOutItem());

}

void MainWindow::drawBlock(QGraphicsScene *scene, int x, int y, int itemId)
{
    scene->addItem(ext.getBlock(x, y, itemId));
}

void MainWindow::updateCheckBoxIcons()
{
    if(ui->cbMuteMusic->checkState())
        ui->cbMuteMusic->setIcon(R.icon.volume_mute);
    else
        ui->cbMuteMusic->setIcon(R.icon.volume_up);

    if(ui->cbMuteSFX->checkState())
         ui->cbMuteSFX->setIcon(R.icon.volume_mute);
    else
        ui->cbMuteSFX->setIcon(R.icon.volume_up);
}

void MainWindow::onCheckBoxStateChanged(int state)
{
    if(sender() == ui->cbMuteMusic)
    {
        if (state == Qt::Checked)
            audioEffect->muteMusic(true);
        else
            audioEffect->muteMusic(false);
    }

    if(sender() == ui->cbMuteSFX)
    {
        if (state == Qt::Checked)
            audioEffect->muteSFX(true);
        else
            audioEffect->muteSFX(false);
    }

    updateCheckBoxIcons();

    settings.saveGroupMainWindow(
        MainWindowModel(
            ui->cbMuteMusic->checkState(),
            ui->cbMuteSFX->checkState()
        )
    );
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == mControls.getKeyRotate())
        controller->onAction(ACTION_ROTATE);
    else if (ev->key() == mControls.getKeyLeft())
        controller->onAction(ACTION_MOVE_LEFT);
    else if (ev->key() == mControls.getKeyRight())
        controller->onAction(ACTION_MOVE_RIGHT);
    else if (ev->key() == mControls.getKeyDown())
        controller->onDropEnabled(true);
    else if (ev->key() == mControls.getKeyPause())
        controller->onAction(ACTION_PAUSE);
    else if (ev->key() == mControls.getKeyStart())
        controller->onAction(ACTION_START);
    else
        QWidget::keyPressEvent(ev);
}

void MainWindow::keyReleaseEvent(QKeyEvent *ev)
{
    if(ev->key() == mControls.getKeyDown())
        controller->onDropEnabled(false);
    else
        QWidget::keyReleaseEvent(ev);
}


void MainWindow::onControlsChanged(ControlsModel newControls)
{
    mControls = newControls;
}

void MainWindow::onButtonClick()
{
    if(sender() == ui->btnSettings) {
        settingsWindow->show();
    }

    if(sender() == ui->btnSkipTrack) {
        audioEffect->skipToNext();
    }
}

void MainWindow::updateTime(long milliseconds)
{
    ui->lTime->setText(ext.formatAsTime(milliseconds));
}

void MainWindow::updateScoreTable()
{
    ui->tableView->setModel(database->getModel());
    // Hiding column with id, because it always equals 0
    ui->tableView->hideColumn(0);
    ui->tableView->show();
}

void MainWindow::showEvent(QShowEvent *ev)
{
    audioEffect->playBackgroundMusic();
    ev->accept();
}

void MainWindow::hideEvent(QHideEvent *ev)
{
    controller->onAction(ACTION_PAUSE);
    audioEffect->pauseBackgroundMusic();
    ev->accept();
}

MainWindow::~MainWindow()
{
    delete database;
    delete model;
    delete counter;
    delete controller;
    delete mainScene;
    delete nextItemScene;
    delete ui;
}

