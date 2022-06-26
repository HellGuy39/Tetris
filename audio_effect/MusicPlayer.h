#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QObject>
#include <QList>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "utils/Resources.h"

class MusicPlayer : public QObject
{
    Q_OBJECT
    public:
        MusicPlayer()
        {
            tracksUrlList = { R.music.track_2, R.music.track_3, R.music.track_4, R.music.track_1 };
            player->setAudioOutput(output);
            connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
                    this, SLOT(onMediaStatusChanged(QMediaPlayer::MediaStatus)));

            currentTrackIndex = 0;
            player->setSource(tracksUrlList.at(currentTrackIndex));
        }

        void play()
        {
            player->play();
        }

        void pause()
        {
            player->pause();
        }

        void skipToNext()
        {
            if(currentTrackIndex == (tracksUrlList.size() - 1))
            {
                currentTrackIndex = 0;
            }
            else
            {
                currentTrackIndex++;
            }
            player->setSource(tracksUrlList.at(currentTrackIndex));
            player->play();
        }

        void setVolume(qreal volume)
        {
            output->setVolume(volume);
        }

        void setMuted(bool isMuted)
        {
            output->setMuted(isMuted);
        }

        ~MusicPlayer()
        {
            delete player;
            delete output;
        }

    private slots:
        //void onPlaybackStateChanged(QMediaPlayer::PlaybackState state);
        void onMediaStatusChanged(QMediaPlayer::MediaStatus status)
        {
            if (status == QMediaPlayer::EndOfMedia)
            {
                skipToNext();
            }
        }

    private:
        Resources R;
        QMediaPlayer * player = new QMediaPlayer();
        QAudioOutput * output = new QAudioOutput();
        QList<QUrl> tracksUrlList;
        int currentTrackIndex = 0;
};

#endif // MUSICPLAYER_H
