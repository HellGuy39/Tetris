#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QKeySequence>
#include <QCloseEvent>
#include <QPushButton>
#include <QMessageBox>
#include "utils/Resources.h"
#include "utils/Constants.h"
#include "settings/Settings.h"

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QMainWindow
{
        Q_OBJECT
    public:
        explicit SettingsWindow(QWidget *parent = nullptr);
        ~SettingsWindow();
        void prepareSettingsToUi();

    private:
        Ui::SettingsWindow *ui;
        Settings settings;
        Resources R;
        ControlsModel mControls = settings.getGroupControls();
        int waitingKeyId;
        bool isListeningKey = false;
        void displayKeySequence();
        void connectUi();
        void setupIcons();
        void setupDefaultTextOnButtons();
        void clearStatusMessage();
        void showStatusMessage(QString text);
        const int STATUS_MESSAGE_TIMEOUT = 5000;

    signals:
        void onSoundGroupChanged(SoundModel);
        void onControlsGroupChanged(ControlsModel);
        void onClearDatabase();

    private slots:
        void onSliderValueChanged(int value);
        void onSliderReleased();
        void onOverrideKey();
        void onClearDbButton();

    protected:
        virtual void closeEvent(QCloseEvent *ev);
        virtual void keyPressEvent(QKeyEvent *ev);
};

#endif // SETTINGSWINDOW_H
