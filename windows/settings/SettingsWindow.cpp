#include "windows/settings/SettingsWindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);

    setWindowTitle(R.strings.title_settings);
    setWindowModality(Qt::ApplicationModal);

    prepareSettingsToUi();

    connectUi();

    setupIcons();

    displayKeySequence();
}

void SettingsWindow::setupIcons()
{
    ui->iconMoveRight->setPixmap(R.icon.arrow_right.pixmap(ICON_WIDTH,ICON_HEIGHT));
    ui->iconMoveLeft->setPixmap(R.icon.arrow_left.pixmap(ICON_WIDTH,ICON_HEIGHT));
    ui->iconDropDown->setPixmap(R.icon.arrow_down.pixmap(ICON_WIDTH, ICON_HEIGHT));
    ui->iconPause->setPixmap(R.icon.pause_circle.pixmap(ICON_WIDTH, ICON_HEIGHT));
    ui->iconStart->setPixmap(R.icon.play_circle.pixmap(ICON_WIDTH, ICON_HEIGHT));
    ui->iconRotate->setPixmap(R.icon.rotate.pixmap(ICON_WIDTH, ICON_HEIGHT));
}

void SettingsWindow::onClearDbButton()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
                this, "Confirmation",
                "Are you sure want to clear score table?",
                QMessageBox::Yes | QMessageBox::No
    );

    if (reply == QMessageBox::Yes) {
        emit onClearDatabase();
    }
}

void SettingsWindow::connectUi()
{
    connect(ui->btnOverrideDropDown, SIGNAL(clicked()),
            this, SLOT(onOverrideKey()));

    connect(ui->btnOverrideMoveLeft, SIGNAL(clicked()),
            this, SLOT(onOverrideKey()));

    connect(ui->btnOverrideMoveRight, SIGNAL(clicked()),
            this, SLOT(onOverrideKey()));

    connect(ui->btnOverridePause, SIGNAL(clicked()),
            this, SLOT(onOverrideKey()));

    connect(ui->btnOverrideStart, SIGNAL(clicked()),
            this, SLOT(onOverrideKey()));

    connect(ui->btnOverrideRotate, SIGNAL(clicked()),
            this, SLOT(onOverrideKey()));

    connect(ui->hsMusicVolume, SIGNAL(sliderReleased()),
            this, SLOT(onSliderReleased()));

    connect(ui->hsSfxVolume, SIGNAL(sliderReleased()),
            this, SLOT(onSliderReleased()));

    connect(ui->hsMusicVolume, SIGNAL(valueChanged(int)),
            this, SLOT(onSliderValueChanged(int)));

    connect(ui->hsSfxVolume, SIGNAL(valueChanged(int)),
            this, SLOT(onSliderValueChanged(int)));

    connect(ui->btnClearDatabase, SIGNAL(clicked()),
            this, SLOT(onClearDbButton()));
}

void SettingsWindow::prepareSettingsToUi()
{
    SoundModel mSound = settings.getGroupSound();
    ui->hsMusicVolume->setValue(mSound.getMusicVolume());
    ui->hsSfxVolume->setValue(mSound.getSfxVolume());
}

void SettingsWindow::onOverrideKey()
{
    if(!isListeningKey)
    {
        showStatusMessage(R.strings.listening_new_key);

        QPushButton *clickedButton = qobject_cast<QPushButton* >(sender());
        clickedButton->setText(R.strings.press_any_key);

        if (sender() == ui->btnOverrideDropDown)
            waitingKeyId = KEY_DROP_DOWN;
        else if (sender() == ui->btnOverrideMoveLeft)
            waitingKeyId = KEY_MOVE_LEFT;
        else if (sender() == ui->btnOverrideMoveRight)
            waitingKeyId = KEY_MOVE_RIGHT;
        else if (sender() == ui->btnOverrideRotate)
            waitingKeyId = KEY_ROTATE;
        else if (sender() == ui->btnOverridePause)
            waitingKeyId = KEY_PAUSE;
        else if (sender() == ui->btnOverrideStart)
            waitingKeyId = KEY_START;

        isListeningKey = true;
    }
    else
    {
        showStatusMessage(R.strings.canceled);
        setupDefaultTextOnButtons();

        isListeningKey = false;
        waitingKeyId = 0;
    }
}

void SettingsWindow::setupDefaultTextOnButtons()
{
    ui->btnOverrideDropDown->setText(R.strings.override);
    ui->btnOverrideMoveLeft->setText(R.strings.override);
    ui->btnOverrideMoveRight->setText(R.strings.override);
    ui->btnOverrideRotate->setText(R.strings.override);
    ui->btnOverridePause->setText(R.strings.override);
    ui->btnOverrideStart->setText(R.strings.override);
}

void SettingsWindow::keyPressEvent(QKeyEvent *ev)
{
    if(isListeningKey)
    {
        if(waitingKeyId == KEY_DROP_DOWN)
            mControls.setKeyDown(ev->key());
        else if(waitingKeyId == KEY_MOVE_LEFT)
            mControls.setKeyLeft(ev->key());
        else if(waitingKeyId == KEY_MOVE_RIGHT)
            mControls.setKeyRight(ev->key());
        else if(waitingKeyId == KEY_ROTATE)
            mControls.setKeyRotate(ev->key());
        else if(waitingKeyId == KEY_PAUSE)
            mControls.setKeyPause(ev->key());
        else if(waitingKeyId == KEY_START)
            mControls.setKeyStart(ev->key());

        setupDefaultTextOnButtons();

        showStatusMessage(R.strings.new_key + QKeySequence(ev->key()).toString());

        settings.saveGroupControls(mControls);

        emit onControlsGroupChanged(mControls);

        displayKeySequence();

        isListeningKey = false;
        waitingKeyId = 0;
    }
}

void SettingsWindow::displayKeySequence()
{
    ui->lDropDown->setText(R.strings.drop_down + QKeySequence(mControls.getKeyDown()).toString());
    ui->lMoveLeft->setText(R.strings.move_left + QKeySequence(mControls.getKeyLeft()).toString());
    ui->lMoveRight->setText(R.strings.move_right + QKeySequence(mControls.getKeyRight()).toString());
    ui->lPause->setText(R.strings.pause + QKeySequence(mControls.getKeyPause()).toString());
    ui->lStart->setText(R.strings.start + QKeySequence(mControls.getKeyStart()).toString());
    ui->lRotate->setText(R.strings.rotate + QKeySequence(mControls.getKeyRotate()).toString());
}

void SettingsWindow::onSliderValueChanged(int value)
{
    if(sender() == ui->hsMusicVolume)
    {
        showStatusMessage(R.strings.music_volume + QString::number(value) + R.strings.percent);
    }

    if(sender() == ui->hsSfxVolume)
    {
        showStatusMessage(R.strings.sfx_volume + QString::number(value) + R.strings.percent);
    }
}

void SettingsWindow::onSliderReleased()
{
    SoundModel mSound = SoundModel(
        ui->hsMusicVolume->value(),
        ui->hsSfxVolume->value()
    );

    settings.saveGroupSound(mSound);

    emit onSoundGroupChanged(mSound);
}

void SettingsWindow::closeEvent(QCloseEvent *ev)
{
    clearStatusMessage();
    ev->accept();
}

void SettingsWindow::clearStatusMessage()
{
    ui->statusbar->clearMessage();
}

void SettingsWindow::showStatusMessage(QString text)
{
    ui->statusbar->showMessage(text, STATUS_MESSAGE_TIMEOUT);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}
