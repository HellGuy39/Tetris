#include "settings/Settings.h"

void Settings::saveGroupSound(SoundModel mSound)
{
    QSettings settings(COMPANY_NAME, APP_NAME);

    settings.beginGroup(GROUP_SOUND);
    settings.setValue(PARAM_MUSIC_VOLUME, mSound.getMusicVolume());
    settings.setValue(PARAM_SFX_VOLUME, mSound.getSfxVolume());
    settings.endGroup();
}

SoundModel Settings::getGroupSound()
{
    QSettings settings(COMPANY_NAME, APP_NAME);

    settings.beginGroup(GROUP_SOUND);
    int paramSfxVolume = settings.value(PARAM_SFX_VOLUME, DEFAULT_SFX_VOLUME).toInt();
    int paramMusicVolume = settings.value(PARAM_MUSIC_VOLUME, DEFAULT_MUSIC_VOLUME).toInt();
    settings.endGroup();

    return SoundModel(paramMusicVolume, paramSfxVolume);
}

void Settings::saveGroupControls(ControlsModel mControls)
{
    QSettings settings(COMPANY_NAME, APP_NAME);

    settings.beginGroup(GROUP_CONTROLS);

    settings.setValue(PARAM_KEY_MOVE_LEFT, mControls.getKeyLeft());
    settings.setValue(PARAM_KEY_MOVE_RIGHT, mControls.getKeyRight());
    settings.setValue(PARAM_KEY_DROP_DOWN, mControls.getKeyDown());
    settings.setValue(PARAM_KEY_ROTATE, mControls.getKeyRotate());
    settings.setValue(PARAM_KEY_START, mControls.getKeyStart());
    settings.setValue(PARAM_KEY_PAUSE, mControls.getKeyPause());

    settings.endGroup();
}

ControlsModel Settings::getGroupControls()
{
    QSettings settings(COMPANY_NAME, APP_NAME);

    settings.beginGroup(GROUP_CONTROLS);
    int paramKeyMoveRight = settings.value(PARAM_KEY_MOVE_RIGHT, Qt::Key_D).toInt();
    int paramKeyMoveLeft = settings.value(PARAM_KEY_MOVE_LEFT, Qt::Key_A).toInt();
    int paramKeyDropDown = settings.value(PARAM_KEY_DROP_DOWN, Qt::Key_S).toInt();
    int paramKeyRotate = settings.value(PARAM_KEY_ROTATE, Qt::Key_W).toInt();
    int paramKeyPause = settings.value(PARAM_KEY_PAUSE, Qt::Key_Escape).toInt();
    int paramKeyStart = settings.value(PARAM_KEY_START, Qt::Key_Space).toInt();
    settings.endGroup();

    return ControlsModel(paramKeyDropDown, paramKeyMoveRight, paramKeyMoveLeft,
                         paramKeyRotate, paramKeyPause, paramKeyStart);
}

void Settings::saveGroupMainWindow(MainWindowModel mMainWindow)
{
    QSettings settings(COMPANY_NAME, APP_NAME);

    settings.beginGroup(GROUP_MAIN_WINDOW);
    settings.setValue(PARAM_SFX_MUTED, mMainWindow.getIsSfxMuted());
    settings.setValue(PARAM_MUSIC_MUTED, mMainWindow.getIsMusicMuted());
    settings.endGroup();
}

MainWindowModel Settings::getGroupMainWindow()
{
    QSettings settings(COMPANY_NAME, APP_NAME);

    settings.beginGroup(GROUP_MAIN_WINDOW);
    bool paramIsMusicMuted = settings.value(PARAM_MUSIC_MUTED, false).toBool();
    bool paramIsSfxMuted = settings.value(PARAM_SFX_MUTED, false).toBool();
    settings.endGroup();

    return MainWindowModel(paramIsMusicMuted, paramIsSfxMuted);
}
