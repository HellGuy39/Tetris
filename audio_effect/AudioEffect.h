#ifndef AUDIOEFFECTEXTENSION_H
#define AUDIOEFFECTEXTENSION_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QList>
#include "audio_effect/SFXObject.h"
#include "utils/Resources.h"
#include "utils/Constants.h"
#include "settings/Settings.h"
#include "utils/Extensions.h"
#include "audio_effect/MusicPlayer.h"

class AudioEffect : public QObject
{
        Q_OBJECT
    public:
        AudioEffect()
        {
            Settings settings;
            onSoundSettingsChanged(settings.getGroupSound());
        }

        ~AudioEffect()
        {
            delete musicPlayer;
        }

        void pauseBackgroundMusic()
        {
            musicPlayer->pause();
        }

        void playBackgroundMusic()
        {
            musicPlayer->play();
        }

        void makeSoundEffect(int effect)
        {
             // This object will be automatically
             // delete after making sound.
             SFXObject * sfxObj = new SFXObject(effect, sfxVolume, isMutedSfx);
        }

        void muteSFX(bool isMuted = true)
        {
            isMutedSfx = isMuted;
        }

        void muteMusic(bool isMuted = true)
        {
            musicPlayer->setMuted(isMuted);
        }

        void skipToNext()
        {
            musicPlayer->skipToNext();
        }

    private:
        MusicPlayer * musicPlayer = new MusicPlayer();
        Resources R;
        Extension ext;
        qreal sfxVolume = 0.5;
        bool isMutedSfx = false;


    public slots:
        void onSoundSettingsChanged(SoundModel mSound)
        {
            musicPlayer->setVolume(ext.toVolumeValue(mSound.getMusicVolume()));
            sfxVolume = ext.toVolumeValue(mSound.getSfxVolume());
        }
};

#endif // AUDIOEFFECTEXTENSION_H
