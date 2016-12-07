/* 強化学習(Q学習) 迷路探索を学習する */
#include <stdio.h>
#include <stdlib.h>

/* 記号定数定義 */
#define GENMAX  1000  // 学習の反復回数
#define NODENO  15    // Q値のノード数
#define ALPHA   0.1   // 学習係数
#define GAMMA   0.9   // 割引率
#define EPSILON 0.3   // 行動選択に置いて確率εでランダム選択 ε-greedy法
#define SEED    32767 // 乱数のシード

/* 関数のプロトタイプ宣言 */
int rand100();  // 0~100の乱数生成
int rand01();   // 0または1を出す
double rand1(); // 0~1の乱数生成
void printQvalue(int qvalue[NODENO]); // Q値出力
int selectA(int s, int qvalue[NODENO]); // 行動選択
int updateQ(int s, int qvalue[NODENO]); // Q値を更新

int main()
{
  int s; // 状態s
  int t; // 時刻t
  int qvalue[NODENO]; // Q値

  srand(SEED); // 乱数の初期化

  /* Q値初期化 */
  for (int i = 0; i < NODENO; ++i) {
    qvalue[i] = rand100();
  }
  printQvalue(qvalue);

  /* 学習の本体*/
  for (int i = 0; i < GENMAX; ++i) {
    s = 0; // 状態sを初期化
    for (t = 0; t < 3; ++t) { // 迷路の最下段まで反復
      s = selectA(s, qvalue); // 行動選択
      qvalue[s] = updateQ(s, qvalue); // Q値更新
    }
    printQvalue(qvalue);
  }
  return 0;
}

int updateQ(int s, int qvalue[NODENO])
{
  int qv; // 更新されるQ値
  int qmax; // Q値の最大値

  /* 最下段の場合 */
  if (s > 6) {
    if (s == 14) { // 報酬の付与
      qv = qvalue[s] + ALPHA * (1000 - qvalue[s]);
    }
    //else if (s == 11) {
    //  qv = qvalue[s] + ALPHA * (500 - qvalue[s]);
    //}
    else {
      qv = qvalue[s]; //報酬なし
    }
  }
    // 最下段以外
  else {
    if ((qvalue[2 * s + 1]) > (qvalue[2 * s + 2])) {
      qmax = qvalue[2 * s + 1];
    } else {
      qmax = qvalue[2 * s + 2];
    }
      qv = qvalue[s] + ALPHA * (GAMMA * qmax - qvalue[s]);
    }
    return qv;
}

int selectA(int olds, int qvalue[NODENO])
{
  int s;
  /* ε-greedy法による行動選択 */
  if (rand1() < EPSILON) {
    // ランダムに行動
    if (rand01() == 0) {
      s = 2 * olds + 1;
    } else {
      s = 2 * olds + 2;
    }
  }
  else {
    //Q値最大値を選択
    if ((qvalue[2 * olds + 1]) > qvalue[2 * olds + 2]) {
      s = 2 * olds + 1;
    } else {
      s = 2 * olds + 2;
    }
  }
  return s;
}

void printQvalue(int qvalue[NODENO])
{
  for (int i = 1; i < NODENO; ++i) {
    printf("%d\t", qvalue[i]);
  }
  printf("\n");
}

int rand100()
{
  int rnd;
  while ((rnd = rand()) == RAND_MAX);
  return (int) ((double) rnd / RAND_MAX * 101);
}

int rand01()
{
  int rnd;
  while ((rnd = rand()) == RAND_MAX);
  return (int) ((double) rnd / RAND_MAX * 2);
}

double rand1()
{
  return (double) rand() / RAND_MAX;
}
