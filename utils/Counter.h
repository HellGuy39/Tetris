#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
#include "utils/Constants.h"

class Counter : public QObject
{
        Q_OBJECT
    public:
        Counter();
        void clear();
        void increaseScore(int reason);
        void increaseLines();
        bool isNextLevel();
        int getLevel();
        int getLines();
        int getScore();
        const int POINTS_FOR_TETROMINO = 50;
        const int POINTS_FOR_LINE = 200;
        const int LINES_FOR_COMPLETED_LEVEL = 5;

    signals:
        void onScoreChanged(int);
        void onLinesChanged(int);
        void onLevelChanged(int);

    private:
        int level = 0;
        int score = 0;
        int lines = 0;
        int linesForNextLevel = 0;
};

#endif // COUNTER_H
