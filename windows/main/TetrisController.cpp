#include "windows/main/TetrisController.h"

TetrisController::TetrisController()
{
    timer->setInterval(INTERVAL_LEVEL_1);
    connect(timer, SIGNAL(timeout()), this, SLOT(onUpdate()));
}

void TetrisController::updateInterval(int newLevel)
{
    level = newLevel;

    if(level == 1)
        timer->setInterval(INTERVAL_LEVEL_1);
    else if (level == 2)
        timer->setInterval(INTERVAL_LEVEL_2);
    else if (level == 3)
        timer->setInterval(INTERVAL_LEVEL_3);
    else if (level == 4)
        timer->setInterval(INTERVAL_LEVEL_4);
    else if (level == 5)
        timer->setInterval(INTERVAL_LEVEL_5);
    else if (level == 6)
        timer->setInterval(INTERVAL_LEVEL_6);
    else if (level == 7)
        timer->setInterval(INTERVAL_LEVEL_7);
    else if (level == 8)
        timer->setInterval(INTERVAL_LEVEL_8);
    else if (level == 9)
        timer->setInterval(INTERVAL_LEVEL_9);
    else if (level == 10)
        timer->setInterval(INTERVAL_LEVEL_10);
    else if (level == 11)
        timer->setInterval(INTERVAL_LEVEL_11);
    else
        timer->setInterval(INTERVAL_LEVEL_12);

}

void TetrisController::onDropEnabled(bool isEnabled)
{
    if(isEnabled) {
        timer->setInterval(INTERVAL_FAST_DROP);
    } else {
        updateInterval(level);
    }

}

void TetrisController::onStart()
{
    if(state != PLAYING)
    {
        emit onSendAction(ACTION_NEW_GAME);
        state = PLAYING;
        time = 0;
        timer->start();
    }
}

void TetrisController::onPause()
{
    if(state == PLAYING)
    {
        state = PAUSED;
        timer->stop();
        emit onSendAction(ACTION_PAUSE);
    }
}

void TetrisController::onResume()
{
    if(state == PAUSED)
    {
        state = PLAYING;
        timer->start();
        emit onSendAction(ACTION_CONTINUE);
    }
}

void TetrisController::onStop()
{
    if(state == PLAYING)
    {
        state = BLOCK_OUT;
        timer->stop();
    }
}

void TetrisController::onAction(int action)
{
    switch(action)
    {
        case ACTION_PAUSE:
            if(state == PLAYING)
                onPause();
            else if(state == PAUSED)
                onResume();
            break;

        case ACTION_START:
            if(state != PLAYING)
                onStart();
            break;

        case ACTION_BLOCK_OUT:
            if(state == PLAYING)
                onStop();
            break;

        default:
            if(state == PLAYING)
                emit onSendAction(action);
            break;
    }
}

int TetrisController::getGameState()
{
    return state;
}

void TetrisController::onUpdate()
{
    emit onSendAction(ACTION_MOVE_DOWN);
    time += timer->interval();
    emit onTimeChanged(time);
}

TetrisController::~TetrisController()
{
    delete timer;
}
