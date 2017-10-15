#pragma once
class Score {
  int p1 = 0;
  int p2 = 0;

public:
  void bumpScoreP1();
  void setScoreP1(int newP1);
  int getScoreP1() const;
  void bumpScoreP2();
  void setScoreP2(int newP2);
  int getScoreP2() const;
};
