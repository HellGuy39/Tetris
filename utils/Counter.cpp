#include "utils/Counter.h"

Counter::Counter()
{
    clear();
}

void Counter::clear() {
    score = 0;
    lines = 0;
    level = 1;
    linesForNextLevel = 0;

    emit onScoreChanged(score);
    emit onLinesChanged(lines);
    emit onLevelChanged(level);
}

void Counter::increaseScore(int reason)
{
    switch(reason)
    {
        case EVENT_ITEM_PLACED:
            score += POINTS_FOR_TETROMINO;
            break;

        case EVENT_LINE_COMPLETED_S1:
            score += POINTS_FOR_LINE * 1;
            break;

        case EVENT_LINE_COMPLETED_S2:
            score += POINTS_FOR_LINE * 2;
            break;

        case EVENT_LINE_COMPLETED_S3:
            score += POINTS_FOR_LINE * 3;
            break;

        case EVENT_LINE_COMPLETED_S4:
            score += POINTS_FOR_LINE * 4;
            break;
    }
    emit onScoreChanged(score);
}

void Counter::increaseLines()
{
    lines++;
    emit onLinesChanged(lines);

    linesForNextLevel++;
}

bool Counter::isNextLevel()
{
    if(linesForNextLevel == LINES_FOR_COMPLETED_LEVEL)
    {
        linesForNextLevel = 0;
        level++;
        emit onLevelChanged(level);
        return true;
    }
    else
    {
        return false;
    }
}

int Counter::getLevel()
{
    return level;
}

int Counter::getLines()
{
    return lines;
}

int Counter::getScore()
{
    return score;
}
