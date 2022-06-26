#include "windows/main/TetrisModel.h"

TetrisModel::TetrisModel()
{

}

void TetrisModel::init()
{
    gameField = ext.getClearGameField();
    updateView();
}

void TetrisModel::newGame()
{
    gameField = ext.getClearGameField();

    updateNextItem();
    prepareNewItem();

    updateView();
}

void TetrisModel::onReceiveAction(int action)
{
    checkCompleteLines();

    switch(action)
    {
        case ACTION_NEW_GAME:
            newGame();
            emit onEvent(EVENT_NEW_GAME);
            break;

        case ACTION_PAUSE:
            emit onEvent(EVENT_PAUSED);
            break;

        case ACTION_MOVE_LEFT:
            if(!hasSideCollision(action)) {
                currentItemY--;
                emit onEvent(EVENT_ITEM_MOVED_SIDEWAY);
            }
            break;

        case ACTION_MOVE_RIGHT:
            if(!hasSideCollision(action)) {
                currentItemY++;
                emit onEvent(EVENT_ITEM_MOVED_SIDEWAY);
            }

            break;

        case ACTION_MOVE_DOWN:
            if(!hasCollisions()) {
                currentItemX++;
            } else {
                emit onEvent(EVENT_ITEM_PLACED);
                onItemCollide();
                prepareNewItem();

                if(!isEnoughtSpaceForNewItem()) {
                    currentItem = { { 0 } };
                    emit onEvent(EVENT_BLOCK_OUT);
                }
            }
            break;

        case ACTION_ROTATE:
            if(rotateItem())
                emit onEvent(EVENT_ITEM_ROTATED);
            break;

    }
    updateView();
}

void TetrisModel::updateNextItem()
{
    nextItem = ext.generateNewTetromino();
    emit onNextItemUpdated(nextItem);
}

void TetrisModel::prepareNewItem()
{
    currentItem = nextItem;
    currentItemX = 1;
    currentItemY = (gameField[0].size() / 2) - 2;

    updateNextItem();
}

void TetrisModel::moveLinesDown(int startLine)
{
    for (size_t x = startLine; x > 0; x--)
        for (size_t y = 0; y < gameField[y].size(); y++) {
            if (gameField[x][y] != -1 && gameField[x][y] != 0) {
                gameField[x+1][y] = gameField[x][y];
                gameField[x][y] = 0;
            }
        }

}

void TetrisModel::onItemCollide()
{
    for(size_t itemSizeX = 0; itemSizeX < currentItem.size(); itemSizeX++)
        for(size_t itemSizeY = 0; itemSizeY < currentItem[itemSizeX].size(); itemSizeY++)
            if(currentItem[itemSizeX][itemSizeY] != 0)
                gameField[currentItemX + itemSizeX][currentItemY + itemSizeY] = currentItem[itemSizeX][itemSizeY];

}


void TetrisModel::checkCompleteLines()
{
    int lineSeries = 0;

    for (size_t x = 0; x < gameField.size(); x++)
    {
        size_t yLineCount = 0;
        for (size_t y = 0; y < gameField[y].size(); y++)
            if(!isOutOfBounds(gameField[x][y]) && !isEmptySpace(gameField[x][y]))
                yLineCount++;


        if (yLineCount == (gameField[x].size() - 2))
        {
            for (size_t y = 0; y < gameField[y].size(); y++)
            {
                 if (!isOutOfBounds(gameField[x][y]))
                     gameField[x][y] = 0;

            }
            lineSeries++;
            moveLinesDown(x);
        }
    }

    if(lineSeries > 0)
    {
        if(lineSeries == 1)
            emit onEvent(EVENT_LINE_COMPLETED_S1);
        else if(lineSeries == 2)
            emit onEvent(EVENT_LINE_COMPLETED_S2);
        else if(lineSeries == 3)
            emit onEvent(EVENT_LINE_COMPLETED_S3);
        else
            emit onEvent(EVENT_LINE_COMPLETED_S4);
    }
}

bool TetrisModel::rotateItem()
{
    Matrix rotatedItem = currentItem;

    //clear rotated matrix
    for(size_t itemSizeX = 0; itemSizeX < rotatedItem.size(); itemSizeX++)
        for(size_t itemSizeY = 0; itemSizeY < rotatedItem[itemSizeX].size(); itemSizeY++)
            rotatedItem[itemSizeX][itemSizeY] = 0;

    //rotate matrix
    for(size_t itemSizeX = 0; itemSizeX < currentItem.size(); itemSizeX++)
        for(size_t itemSizeY = 0; itemSizeY < currentItem[itemSizeX].size(); itemSizeY++)
            rotatedItem[itemSizeY][itemSizeX] = currentItem[currentItem.size() - itemSizeX - 1][itemSizeY];


    for(size_t itemSizeX = 0; itemSizeX < rotatedItem.size(); itemSizeX++)
        for(size_t itemSizeY = 0; itemSizeY < rotatedItem[itemSizeX].size(); itemSizeY++)
            if (!isEmptySpace(rotatedItem[itemSizeX][itemSizeY]))
                if (gameField[currentItemX + itemSizeX][currentItemY + itemSizeY])
                    return false;


    currentItem = rotatedItem;
    return true;
}

bool TetrisModel::hasCollisions()
{
    for(size_t itemSizeX = 0; itemSizeX < currentItem.size(); itemSizeX++) {
        for(size_t itemSizeY = 0; itemSizeY < currentItem[itemSizeX].size(); itemSizeY++) {
            if(!isEmptySpace(currentItem[itemSizeX][itemSizeY]) &&
                    !isEmptySpace(gameField[currentItemX + itemSizeX + 1][currentItemY + itemSizeY]))
               return true;

        }
    }

    return false;
}

bool TetrisModel::hasSideCollision(int action)
{
    for(size_t itemSizeX = 0; itemSizeX < currentItem.size(); itemSizeX++) {
        for(size_t itemSizeY = 0; itemSizeY < currentItem[itemSizeX].size(); itemSizeY++)
            if(!isEmptySpace(currentItem[itemSizeX][itemSizeY])) {
                if(action == ACTION_MOVE_LEFT) {
                    if (!isEmptySpace(gameField[currentItemX + itemSizeX][currentItemY + itemSizeY - 1]))
                        return true;
                } else if (action == ACTION_MOVE_RIGHT) {
                    if (!isEmptySpace(gameField[currentItemX + itemSizeX][currentItemY + itemSizeY + 1]))
                        return true;
                }
            }

        }

    return false;
}

bool TetrisModel::isEnoughtSpaceForNewItem()
{
    for(size_t itemSizeX = 0; itemSizeX < currentItem.size(); itemSizeX++)
        for(size_t itemSizeY = 0; itemSizeY < currentItem[itemSizeX].size(); itemSizeY++)
            if(!isEmptySpace(currentItem[itemSizeX][itemSizeY]) &&
                    !isEmptySpace(gameField[currentItemX + itemSizeX][currentItemY + itemSizeY]))
                        return false;

    return true;
}

bool TetrisModel::isEmptySpace(int pos) {
    if (pos == 0)
        return true;
    else
        return false;
}

bool TetrisModel::isOutOfBounds(int pos) {
    if (pos == -1)
        return true;
    else
        return false;
}

void TetrisModel::updateView()
{
    emit onModelUpdated(gameField, currentItem, currentItemX, currentItemY);
}

TetrisModel::~TetrisModel()
{

}
