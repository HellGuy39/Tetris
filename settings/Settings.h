#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include "settings/SettingsModels.h"
#include <QSettings>

class Settings : public QObject
{
        Q_OBJECT
    public:
        void saveGroupSound(SoundModel mSound);
        SoundModel getGroupSound();
        void saveGroupControls(ControlsModel mControls);
        ControlsModel getGroupControls();
        void saveGroupMainWindow(MainWindowModel mMainWindow);
        MainWindowModel getGroupMainWindow();

    private:
        const QString COMPANY_NAME = "HellGuy39";
        const QString APP_NAME = "Tetris";
        const QString GROUP_SOUND = "Sound";
        const QString GROUP_CONTROLS = "Controls";
        const QString GROUP_MAIN_WINDOW = "MainWindow";
        const QString PARAM_MUSIC_VOLUME = "music_volume";
        const QString PARAM_SFX_VOLUME = "sfx_volume";
        const QString PARAM_KEY_MOVE_RIGHT = "key_move_right";
        const QString PARAM_KEY_MOVE_LEFT = "key_move_left";
        const QString PARAM_KEY_DROP_DOWN = "key_drop_down";
        const QString PARAM_KEY_ROTATE = "key_rotate";
        const QString PARAM_KEY_START = "key_start";
        const QString PARAM_KEY_PAUSE = "key_pause";
        const QString PARAM_MUSIC_MUTED = "is_music_muted";
        const QString PARAM_SFX_MUTED = "is_sfx_muted";
        const int DEFAULT_SFX_VOLUME = 50;
        const int DEFAULT_MUSIC_VOLUME = 50;

};

#endif // SETTINGS_H
