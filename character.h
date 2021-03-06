#pragma once
#include "cocos2d.h"

//枚举角色的方向
enum class DIRECTION
{
	//NONE,
	LEFT,
	RIGHT
};

//枚举各种角色的类型
enum class Character_type
{
	Monster,
	Friend
};

//角色所需的技能属性
struct skillData
{
	int id;//技能的id
	int CoolDown;//技能的冷却时间
	int cdRealTime;//技能的冷却计时
};

//角色的基类，包含角色的移动和基本的属性，主角将继承此类
class character :public cocos2d::Sprite
{
public:
	static character* create();
	bool virtual init();

	void turnOff(DIRECTION dr);//转身的函数

	void move(DIRECTION dr);//实现移动的函数,参数为移动的方向
	void stop(DIRECTION dr);//停止移动的函数，参数为停止的方向

	void jump();//跳跃的函数
	void jumpToHead();//停止跳跃的函数，当撞到墙的时候调用

	bool getIsJumping() { return m_isJumping; }
	bool getIsFalling() { return m_isFalling; }

	void initSkill();

	void fallDown();//开始下落
	void land();//落到地面，停止下落

	//void attack();//攻击
	void startAttack(int num);//开始攻击
	int attack();//攻击的函数，返回要释放技能的编号，此处暂时固定为1
	bool isAttack() { return m_isAttacking; }//返回是否处于攻击状态

	DIRECTION getDirection() { return m_direction; }//获得角色的方向

	void stopped(bool left, bool right);

	//受伤
	void hit(int dmg);
	//获得治疗，保证生命值不超过最大生命值
	void heal(int heal);

	int getHp() { return m_hp; }
	bool getIsAlive() { return m_isAlive; }

	//根据顺序获取技能的冷却计时，返回-1表示没有该技能
	int getSkillCD(int id);

	//返回角色是否是怪物
	bool isMonster();

	void coolDown();
protected:
	//角色的朝向，默认为朝右
	DIRECTION m_direction = DIRECTION::RIGHT;

	//是否处于跳跃的状态
	bool m_isJumping = false;
	//是否处于下落的状态
	bool m_isFalling = false;

	//角色的速度，代表每走一格所需要的时间
	float m_speed = 1.0f;

	bool m_isLeftStop = false;
	bool m_isRightStop = false;

	//是否处于攻击的状态
	bool m_isAttacking = false;

	//角色的生命值和最大生命值
	int m_hp = 100;
	int m_maxHp = 100;

	bool m_isAlive = true;

	//角色的类型，默认是与玩家敌对的怪物
	Character_type m_standPoint = Character_type::Monster;

	std::vector<skillData>m_skills;

	//当前要使用技能的编号
	int m_skillNum = 0;
};