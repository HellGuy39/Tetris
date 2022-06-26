#ifndef RESOURCES_H
#define RESOURCES_H

#include <QObject>
#include <QUrl>
#include <QIcon>
#include <QPixmap>

struct Paths {
    protected:
        //Drawable
        const QString PAUSE_PATH = ":/texture/resources/texture/pause.png";
        const QString BLOCK_OUT_PATH = ":/texture/resources/texture/block_out.png";
        const QString BACKGROUND_PATH = ":/texture/resources/texture/background.png";
        const QString GRAY_SQ_PATH = ":/texture/resources/texture/gray_sq_32.png";
        const QString CYAN_SQ_PATH = ":/texture/resources/texture/cyan_sq_32.png";
        const QString BLUE_SQ_PATH = ":/texture/resources/texture/blue_sq_32.png";
        const QString ORANGE_SQ_PATH = ":/texture/resources/texture/orange_sq_32.png";
        const QString YELLOW_SQ_PATH = ":/texture/resources/texture/yellow_sq_32.png";
        const QString GREEN_SQ_PATH = ":/texture/resources/texture/green_sq_32.png";
        const QString MAGENTA_SQ_PATH = ":/texture/resources/texture/magenta_sq_32.png";
        const QString RED_SQ_PATH = ":/texture/resources/texture/red_sq_32.png";

        //Sfx
        const QString ITEM_PLACED_PATH = "qrc:/sfx/resources/sfx/item_placed.wav";
        const QString GAME_OVER_PATH = "qrc:/sfx/resources/sfx/game_over.wav";
        const QString ITEM_MOVED_SIDEWAY_PATH = "qrc:/sfx/resources/sfx/item_moved_sideway.wav";
        const QString ITEM_ROTATE_PATH = "qrc:/sfx/resources/sfx/item_rotate.wav";
        const QString LINE_COMPLETED_PATH = "qrc:/sfx/resources/sfx/line_completed.wav";
        const QString NEXT_LEVEL_PATH = "qrc:/sfx/resources/sfx/next_level.wav";

        //Music
        const QString TRACK_1_PATH = "qrc:/music/resources/music/track_1.mp3";
        const QString TRACK_2_PATH = "qrc:/music/resources/music/track_2.mp3";
        const QString TRACK_3_PATH = "qrc:/music/resources/music/track_3.mp3";
        const QString TRACK_4_PATH = "qrc:/music/resources/music/track_4.mp3";

        //Icon
        const QString SETTINGS_PATH = ":/icon/resources/icon/settings.svg";
        const QString ARROW_LEFT_PATH = ":/icon/resources/icon/arrow_left.svg";
        const QString ARROW_RIGHT_PATH = ":/icon/resources/icon/arrow_right.svg";
        const QString ARROW_UP_PATH = ":/icon/resources/icon/arrow_up.svg";
        const QString ARROW_DOWN_PATH = ":/icon/resources/icon/arrow_down.svg";
        const QString PLAY_CIRCLE_PATH = ":/icon/resources/icon/play_circle.svg";
        const QString PAUSE_CIRCLE_PATH = ":/icon/resources/icon/pause_circle.svg";
        const QString ROTATE_PATH = ":/icon/resources/icon/rotate.svg";
        const QString TIME_PATH = ":/icon/resources/icon/time.svg";
        const QString VOLUME_MUTE_PATH = ":/icon/resources/icon/volume_mute.svg";
        const QString VOLUME_DOWN_PATH = ":/icon/resources/icon/volume_down.svg";
        const QString VOLUME_UP_PATH = ":/icon/resources/icon/volume_up.svg";
        const QString SKIP_FORWARD_PATH = ":/icon/resources/icon/skip_forward.svg";
};

class Resources : public QObject {
    Q_OBJECT

    class Drawable : Paths {
        public:
            QPixmap pause = QPixmap(PAUSE_PATH);
            QPixmap block_out = QPixmap(BLOCK_OUT_PATH);
            QPixmap background = QPixmap(BACKGROUND_PATH);
            QPixmap gray_block = QPixmap(GRAY_SQ_PATH);
            QPixmap cyan_block = QPixmap(CYAN_SQ_PATH);
            QPixmap blue_block = QPixmap(BLUE_SQ_PATH);
            QPixmap orange_block = QPixmap(ORANGE_SQ_PATH);
            QPixmap yellow_block = QPixmap(YELLOW_SQ_PATH);
            QPixmap green_block = QPixmap(GREEN_SQ_PATH);
            QPixmap magenta_block = QPixmap(MAGENTA_SQ_PATH);
            QPixmap red_block = QPixmap(RED_SQ_PATH);
    };

    class Sfx : Paths {
        public:
            QUrl item_placed = QUrl(ITEM_PLACED_PATH);
            QUrl game_over = QUrl(GAME_OVER_PATH);
            QUrl item_rotated = QUrl(ITEM_ROTATE_PATH);
            QUrl line_completed = QUrl(LINE_COMPLETED_PATH);
            QUrl item_moved_sideway = QUrl(ITEM_MOVED_SIDEWAY_PATH);
            QUrl next_level = QUrl(NEXT_LEVEL_PATH);
    };

    class Music : Paths {
        public:
            QUrl track_1 = QUrl(TRACK_1_PATH);
            QUrl track_2 = QUrl(TRACK_2_PATH);
            QUrl track_3 = QUrl(TRACK_3_PATH);
            QUrl track_4 = QUrl(TRACK_4_PATH);
    };

    class Icon : Paths {
        public:
            QIcon settings = QIcon(SETTINGS_PATH);
            QIcon arrow_up = QIcon(ARROW_UP_PATH);
            QIcon arrow_down = QIcon(ARROW_DOWN_PATH);
            QIcon arrow_left = QIcon(ARROW_LEFT_PATH);
            QIcon arrow_right = QIcon(ARROW_RIGHT_PATH);
            QIcon pause_circle = QIcon(PAUSE_CIRCLE_PATH);
            QIcon play_circle = QIcon(PLAY_CIRCLE_PATH);
            QIcon rotate = QIcon(ROTATE_PATH);
            QIcon time = QIcon(TIME_PATH);
            QIcon volume_mute = QIcon(VOLUME_MUTE_PATH);
            QIcon volume_up = QIcon(VOLUME_UP_PATH);
            QIcon volume_down = QIcon(VOLUME_DOWN_PATH);
            QIcon skip_forward = QIcon(SKIP_FORWARD_PATH);
    };

    class Strings {
        public:
            QString title_tetris = "Tetris";
            QString title_settings = "Settings";
            QString press_any_key = "Press any key...";
            QString override = "Override";
            QString music_volume = "Music volume: ";
            QString sfx_volume = "SFX volume: ";
            QString overrided = "Overrided";
            QString new_key = "New key: ";
            QString move_right = "Move right: ";
            QString move_left = "Move left: ";
            QString drop_down = "Drop down: ";
            QString rotate = "Rotate: ";
            QString pause = "Pause: ";
            QString start = "Start: ";
            QString percent = "%";
            QString listening_new_key = "Listening new key... Click on the same button to cancel";
            QString canceled = "Canceled";
            QString score = "Score: ";
            QString level = "Level: ";
            QString lines = "Lines: ";
            QString time = "Time: ";

    };

    public:
        Drawable drawable;
        Sfx sfx;
        Music music;
        Icon icon;
        Strings strings;

};

#endif // RESOURCES_H
