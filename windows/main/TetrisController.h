#ifndef TETRISCONTROLLER_H
#define TETRISCONTROLLER_H

#include <QTimer>
#include <QObject>
#include <QDebug>
#include "utils/Constants.h"

class TetrisController: public QObject
{
        Q_OBJECT
    public:
        TetrisController();
        ~TetrisController();
        void onAction(int action);
        void onDropEnabled(bool isEnabled);
        void updateInterval(int newLevel);
        int getGameState();

    signals:
        void onSendAction(int action);
        void onTimeChanged(long);

    private slots:
        void onUpdate();

    private:
        int state = WAITING;
        void onStart();
        void onStop();
        void onPause();
        void onResume();
        long time = 0;
        bool isRunning = false;
        int level = 1;
        QTimer *timer = new QTimer();
};

#endif // TETRISCONTROLLER_H
