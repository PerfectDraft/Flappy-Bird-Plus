#ifndef ENTITIES_H
#define ENTITIES_H

class FlappyBird {
public:
  int posX, posY;
  float velocity;
};

class GamePipe {
public:
  int posX, posY;
  int initialPosY;
  bool isPassed;
  int verticalDirection;
};

#endif // ENTITIES_H