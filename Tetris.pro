QT += core gui \
    multimedia \
    sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    utils/Extensions.cpp \
    utils/Counter.cpp \
    database/Database.cpp \
    settings/Settings.cpp \
    windows/main/MainWindow.cpp \
    windows/settings/SettingsWindow.cpp \
    windows/main/TetrisController.cpp \
    windows/main/TetrisModel.cpp \

HEADERS += \
    audio_effect/MusicPlayer.h \
    utils/Extensions.h \
    utils/Resources.h \
    utils/Constants.h \
    utils/Counter.h \
    audio_effect/SFXObject.h \
    audio_effect/AudioEffect.h \
    database/Database.h \
    settings/SettingsModels.h \
    settings/Settings.h \
    windows/settings/SettingsWindow.h \
    windows/main/MainWindow.h \
    windows/main/TetrisController.h \
    windows/main/TetrisModel.h \

FORMS += \
    ui/mainwindow.ui \
    ui/settingswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

ICON = tetris_icon.icns

RC_ICONS += tetris_icon.icns
