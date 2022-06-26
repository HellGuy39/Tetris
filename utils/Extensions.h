#ifndef ITEMEXTENSION_H
#define ITEMEXTENSION_H

#include <QRandomGenerator>
#include <QGraphicsPixmapItem>
#include "utils/Resources.h"
#include "utils/Constants.h"

typedef std::vector<std::vector<int>> Matrix;

class GameObjects {
    public:
        Matrix I_Tetromino = {
            { 0, 0, 0, 0 },
            { 1, 1, 1, 1 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
        };

        Matrix O_Tetromino = {
            { 4, 4},
            { 4, 4},
        };
        Matrix T_Tetromino = {
            { 0, 6, 0 },
            { 6, 6, 6 },
            { 0, 0, 0 },
        };

        Matrix J_Tetromino =  {
            { 2, 0, 0 },
            { 2, 2, 2 },
            { 0, 0, 0 },
        };
        Matrix L_Tetromino = {
            { 0, 0, 3 },
            { 3, 3, 3 },
            { 0, 0, 0 },
        };

        Matrix S_Tetromino = {
            { 0, 5, 5 },
            { 5, 5, 0 },
            { 0, 0, 0 },
        };

        Matrix Z_Tetromino = {
            { 7, 7, 0 },
            { 0, 7, 7 },
            { 0, 0, 0 },
        };

        Matrix gameField = { //22x12
            { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },
            { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
            { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
            { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
            { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
            { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
            { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
            { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
            { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
            { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
            { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
            { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
            { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
            { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
            { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
            { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
            { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
            { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
            { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
            { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
            { -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
            { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },
        };
};

class Extension
{
    public:
        Matrix generateNewTetromino();
        Matrix getClearGameField();
        QGraphicsPixmapItem* getBlock(int x, int y, int itemId);
        QGraphicsPixmapItem* getPauseItem();
        QGraphicsPixmapItem* getBlockOutItem();
        QString formatAsTime(long milliseconds);
        qreal toVolumeValue(int value);
        int getGameFieldWidth();
        int getGameFieldHeight();

    private:
        Resources R;
        GameObjects gameObjects;

};


#endif // ITEMEXTENSION_H
