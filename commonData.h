#pragma once
//���������Ҫ�Ĳ�������ֻ֤��cpp�ļ����ø�ͷ�ļ�

//ÿһ��Ĵ�С
const int GRID_SIZE = 32;
//15 10

//���������ĸ�����Ŀ
const int GRID_X = 30;
const int GRID_Y = 20;

//��Ծʱ�ƶ����ٶȼ�����
const float SLOW = 1.2f;

//����ÿһ������Ҫ��ʱ��
const float HERO_FALL_TIME = 0.10f;

//Ӣ���ƶ�һ������Ҫ��ʱ��
const float HERO_MOVE_TIME = 0.25f;

//��ȡ��Ļ��С
#define VISIBLE_SIZE Director::getInstance()->getVisibleSize()

//�������н���ɫ�������б���ɾ���Ķ�����tag
const int DEL_TAG = 777;

//�������zorder
#define BG_ZORDER -1
#define BR_ZORDER 1
#define HERO_ZOREDER 4