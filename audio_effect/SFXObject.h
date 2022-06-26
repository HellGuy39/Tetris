#ifndef SFXOBJECT_H
#define SFXOBJECT_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "utils/Resources.h"
#include "utils/Constants.h"
#include "settings/Settings.h"

class SFXObject : public QObject
{
    Q_OBJECT
    public:
        SFXObject(int effect, qreal volume, bool isMuted) {
            player->setAudioOutput(output);
            player->setSource(getSource(effect));
            output->setVolume(volume);
            output->setMuted(isMuted);
            connect(player, SIGNAL(playbackStateChanged(QMediaPlayer::PlaybackState)),
                    this, SLOT(onStateChanged(QMediaPlayer::PlaybackState)));
            player->play();
        }
        ~SFXObject() {
            delete player;
            delete output;
        }

    private:
        QMediaPlayer * player = new QMediaPlayer();
        QAudioOutput * output = new QAudioOutput();
        Resources R;
        QUrl getSource(int effect)
        {
            switch(effect)
            {
                case EFFECT_ITEM_PLACED: return R.sfx.item_placed; break;
                case EFFECT_ITEM_ROTATED: return R.sfx.item_rotated; break;
                case EFFECT_LINE_COMPLETED: return R.sfx.line_completed; break;
                case EFFECT_GAME_OVER: return R.sfx.game_over; break;
                case EFFECT_ITEM_MOVED_SIDEWAY: return R.sfx.item_moved_sideway; break;
                case EFFECT_NEXT_LEVEL: return R.sfx.next_level; break;
                default: return QUrl(""); break;
            }
        }

    private slots:
        void onStateChanged(QMediaPlayer::PlaybackState state) {
            if(state == QMediaPlayer::StoppedState) {
                delete this;
            }
        }

};

#endif // SFXOBJECT_H
