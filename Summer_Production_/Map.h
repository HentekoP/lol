#pragma once

const int SIZE_MAP_X = 32;  //< マップチップXサイズ
const int SIZE_MAP_Y = 32;	//< マップチップYサイズ
const int NUM_CHIP_X = 10;  //< 横10種類
const int NUM_CHIP_Y = 4;   //< 縦4種類
const int NUM_CHIP_ALL = NUM_CHIP_X * NUM_CHIP_Y; //< 40個
int chip[NUM_CHIP_ALL];

// マップチップを使った背景
const int NUM_MAP_X = 20; // 32x20=640
const int NUM_MAP_Y = 15; // 32x15=480
