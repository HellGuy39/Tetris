#include "utils/Extensions.h"

Matrix Extension::generateNewTetromino()
{
    int itemIndex = QRandomGenerator::global()->bounded(0,7);

    switch(itemIndex)
    {
        case 0: return gameObjects.I_Tetromino; break;
        case 1: return gameObjects.L_Tetromino; break;
        case 2: return gameObjects.J_Tetromino; break;
        case 3: return gameObjects.O_Tetromino; break;
        case 4: return gameObjects.S_Tetromino; break;
        case 5: return gameObjects.T_Tetromino; break;
        case 6: return gameObjects.Z_Tetromino; break;
        default: return { { 0 } }; break;
    }
}

QGraphicsPixmapItem* Extension::getBlock(int x, int y, int itemId)
{

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
    item->setPos(y, x);
    switch(itemId)
    {
        case -1: item->setPixmap(R.drawable.gray_block); break;
        case 1: item->setPixmap(R.drawable.cyan_block); break;
        case 2: item->setPixmap(R.drawable.blue_block); break;
        case 3: item->setPixmap(R.drawable.orange_block); break;
        case 4: item->setPixmap(R.drawable.yellow_block); break;
        case 5: item->setPixmap(R.drawable.green_block); break;
        case 6: item->setPixmap(R.drawable.magenta_block); break;
        case 7: item->setPixmap(R.drawable.red_block); break;
        default: break;
    }
    return item;
}

QGraphicsPixmapItem* Extension::getPauseItem()
{   
    int x = (getGameFieldHeight() * RESOLUTION) / 2, y = (getGameFieldWidth() * RESOLUTION) / 2;

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
    item->setPixmap(R.drawable.pause);
    item->setPos(x - (PAUSE_ITEM_WIDTH / 2),y - (PAUSE_ITEM_HEIGHT / 2));
    return item;
}

QGraphicsPixmapItem* Extension::getBlockOutItem()
{
    int x = (getGameFieldHeight() * RESOLUTION) / 2, y = (getGameFieldWidth() * RESOLUTION) / 2;

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
    item->setPixmap(R.drawable.block_out);
    item->setPos(x - (BLOCK_OUT_ITEM_WIDTH / 2),y - (BLOCK_OUT_ITEM_HEIGHT / 2));
    return item;
}

QString Extension::formatAsTime(long milliseconds)
{
    int seconds = milliseconds / 1000;
    int minits = 0, hours = 0;

    QString stdHours = "", stdSeconds = "", stdMinits = "";

    while (seconds > 3600)
    {
        seconds -= 3600;
        hours++;
    }

    if (hours < 10)
        stdHours = "0" + QString::number(hours);
    else
        stdHours = QString::number(hours);

    while (seconds > 60)
    {
        seconds -= 60;
        minits++;
    }


    if (minits < 10)
        stdMinits = "0" + QString::number(minits);
    else
        stdMinits = QString::number(minits);

    if (seconds < 10)
        stdSeconds = "0" + QString::number(seconds);
    else
        stdSeconds = QString::number(seconds);

    return stdHours + ":" + stdMinits + ":" + stdSeconds;
}

qreal Extension::toVolumeValue(int value)
{
    qreal newValue = value;
    return newValue / 100;
}

Matrix Extension::getClearGameField()
{
    return gameObjects.gameField;
}

int Extension::getGameFieldWidth()
{
    return gameObjects.gameField.size();
}

int Extension::getGameFieldHeight()
{
    return gameObjects.gameField[0].size();
}
