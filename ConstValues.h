#ifndef __CONST_VALUE_H__
#define __CONST_VALUE_H__

const char NAME_FONT[] = "Arial";
const int HP_NUM_FONT_SIZE = 18;
const int NAME_FONT_SIZE = 25;

static const int MAX_FILE_PATH_LENGTH = 50;

static const float BG_FADEIN_TIME = 0.5f;

static const int DEFAULT_DAMAGE_DIGIT = 3;	//初始伤害数字的个数

static const int SPECIAL_ATTACK_DURATION = 10;
static const int BUBBLE_MAX_COUNT = 10;
static const int BUBBLE_SPEED = 50;
static const int BUBBLE_SUCCESS_HIT = 10;

static float PLAYER_HEAD_HEIGHT = 0.0f;

static const int TOP_HP = 999;

static const char SKILL_TITLE[] = "SKILL SELECT";
static const char ITEM_TITLE[] = "ITEM SELECT";
static const float BACK_WIDTH = 461;
static const float BACK_HEIGHT = 327;
static const float BACK_LABEL_HEIGHT = 24;

//Target type
static const char ENEMY_ONE[] = "敌方单体";
static const char ENEMY_ALL[] = "敌方全体";
static const char PLAYER_ONE[] = "我方单体";
static const char PLAYER_ALL[] = "我方全体";

static const char NUMBER_SPRITE_NAME_TEMPLATE[] = "number_%c";

static const int CELL_WIDHT = 300;
static const int CELL_HEIGHT = 40;

static const char* KEYWORDS[] = { "label", "" };

//Walking
static const char WALKING_PATH[] = "images/walking/%s%d.jpg";
static const float BACK_MOVING_INTERVAL = 4.0f;
static const char WALKER_PLIST_PATH[] = "images/walking/walker.plist";
static const char WALKER_TEXTURE_PATH[] = "images/walking/walker.png";
#endif