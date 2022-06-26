#ifndef TETRISMODEL_H
#define TETRISMODEL_H

#include <QObject>
#include "utils/Constants.h"
#include "utils/Extensions.h"

typedef std::vector<std::vector<int>> Matrix;

class TetrisModel : public QObject
{
        Q_OBJECT
    public:
        TetrisModel();
        ~TetrisModel();
        void init();
        void newGame();
        int getGameFieldWidth();
        int getGameFieldHeight();

    signals:
        void onModelUpdated(Matrix newGameField, Matrix newCurrentItem,
                            int currentItemX, int currentItemY);
        void onNextItemUpdated(Matrix nextItem);
        void onEvent(int event);

    public slots:
        void onReceiveAction(int action);

    private:
        Extension ext = Extension();
        Matrix gameField;
        Matrix currentItem;
        Matrix nextItem;
        void updateView();
        void updateNextItem();
        void onItemCollide();
        void prepareNewItem();
        bool rotateItem();
        void checkCompleteLines();
        void moveLinesDown(int startLine);
        bool hasCollisions();
        bool hasSideCollision(int action);
        bool isEmptySpace(int pos);
        bool isOutOfBounds(int pos);
        bool isEnoughtSpaceForNewItem();
        int currentItemX = 0;
        int currentItemY = 0;

};

#endif // TETRISMODEL_H
