//////////////////////////////////////////////////////////////////////////////
// Filename    : AbilityBalance.cpp
// Written By  : 김성민
// Description :
// 각 크리쳐 별로 능력치를 계산하는 함수들을 모아놓은 파일이다.
//////////////////////////////////////////////////////////////////////////////

#include "AbilityBalance.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "ItemUtil.h"
#include "Properties.h"
#include "VariableManager.h"

// 이거 바뀌면 Slayer::load(), Vampire::load(), Ousters::load() 에서
// maxHP를 계산해서 설정해주는 부분도 바꿔줘야 한다. by sigi.
HP_t computeHP(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance)
{
	Assert(pAttr != NULL);

	HP_t   maxHP = 0;
	double CSTR   = pAttr->nSTR;
	double CDEX   = pAttr->nDEX;
	double CINT   = pAttr->nINT;
	double CLEVEL = pAttr->nLevel;
	Item* pWeapon = pAttr->pWeapon;
	/*	
	 add by Coffee 錦맣槨벴륩돨劤HP셕친駕

	훙잚
	 Sword, Blade 
	 STR*3+Domain Level*5
	Gun, Enchant, heal
	 STR*2+Domain Level*4
	뱁
	 (STR*3 + INT + DEX + Level)*1.5 + 10
	MO濫却
	 (STR*3 + INT + DEX + Level)*1.5 + 10
	MO랬可
	 (STR*3 + (INT*0.7) + DEX + Level)*1.5 + 10
	 */
	 //==========================================================
	 
	
	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		maxHP = (int)(CSTR*3.00);

//#ifndef __CHINA_SERVER__
		if ( pWeapon != NULL )
		{
			switch ( pWeapon->getItemClass() )
			{
				case Item::ITEM_CLASS_SWORD:
					maxHP += ( pAttr->pDomainLevel[SKILL_DOMAIN_SWORD] * 5);
					break;
				case Item::ITEM_CLASS_BLADE:
					maxHP += ( pAttr->pDomainLevel[SKILL_DOMAIN_BLADE] * 5);
					break;
				case Item::ITEM_CLASS_CROSS:
					maxHP = (int)(CSTR*2.00);
					maxHP += ( pAttr->pDomainLevel[SKILL_DOMAIN_HEAL] * 4);
					break;
				case Item::ITEM_CLASS_MACE:
					maxHP = (int)(CSTR*2.00);
					maxHP += ( pAttr->pDomainLevel[SKILL_DOMAIN_ENCHANT] * 4);
					break;
				case Item::ITEM_CLASS_AR:
				case Item::ITEM_CLASS_SMG:
				case Item::ITEM_CLASS_SR:
				case Item::ITEM_CLASS_SG:
					maxHP = (int)(CSTR*2.00);
					maxHP += ( pAttr->pDomainLevel[SKILL_DOMAIN_GUN] * 2);
					break;
				default:
					break;
			}
		}
//#endif

		maxHP = getPercentValue( maxHP, g_pVariableManager->getVariable(SLAYER_HP_RATIO) );
		maxHP = min((int)maxHP, SLAYER_MAX_HP);
	}
	else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		maxHP = (int)((CSTR*4.00 + CINT + CDEX + CLEVEL) );
		maxHP = getPercentValue( maxHP, g_pVariableManager->getVariable(VAMPIRE_HP_RATIO) );
		maxHP = min((int)maxHP, VAMPIRE_MAX_HP);
		//cout << "STR:" << CSTR << " DEX/2:" << (int)(CDEX/2) << " INT:" << CINT << " LEV:" << CLEVEL << " HPMAX:" << maxHP << endl;
	}
	// 아우스터스 추가 by bezz 2003.04.22
	else if (CClass == Creature::CREATURE_CLASS_OUSTERS)
	{
		
		//maxHP = (int)((CSTR*3.00 + CINT + CDEX + CLEVEL));
		
		maxHP = (int)(CSTR*3.00 + CINT/2.00 + CDEX + CLEVEL );
		maxHP = getPercentValue( maxHP, g_pVariableManager->getVariable(OUSTERS_HP_RATIO) );
		maxHP = min((int)maxHP, OUSTERS_MAX_HP);
	}
	else if (CClass == Creature::CREATURE_CLASS_MONSTER)
	{
		maxHP = (int)(CSTR*(2.00 + CLEVEL/100.0));
		maxHP += getPercentValue(maxHP, enhance);
		maxHP = getPercentValue( maxHP, g_pVariableManager->getVariable(MONSTER_HP_RATIO) );
		maxHP = min((int)maxHP, MONSTER_MAX_HP);
//		maxHP = min((int)maxHP, 20000);
	}

	if ( g_pConfig->hasKey("Hardcore") && g_pConfig->getPropertyInt("Hardcore")!=0 )
	{
		maxHP *= 3;
	}

	return maxHP;
	
	//================================================================================
	
	/*
	// 혼딜覩윱돨셕炬무駕

	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		maxHP = (int)(CSTR*2.00);

#ifndef __CHINA_SERVER__
		if ( pWeapon != NULL )
		{
			switch ( pWeapon->getItemClass() )
			{
				case Item::ITEM_CLASS_SWORD:
					maxHP += pAttr->pDomainLevel[SKILL_DOMAIN_SWORD];
					break;
				case Item::ITEM_CLASS_BLADE:
					maxHP += pAttr->pDomainLevel[SKILL_DOMAIN_BLADE];
					break;
				case Item::ITEM_CLASS_CROSS:
					maxHP += pAttr->pDomainLevel[SKILL_DOMAIN_HEAL];
					break;
				case Item::ITEM_CLASS_MACE:
					maxHP += pAttr->pDomainLevel[SKILL_DOMAIN_ENCHANT];
					break;
				case Item::ITEM_CLASS_AR:
				case Item::ITEM_CLASS_SMG:
				case Item::ITEM_CLASS_SR:
				case Item::ITEM_CLASS_SG:
					maxHP += pAttr->pDomainLevel[SKILL_DOMAIN_GUN];
					break;
				default:
					break;
			}
		}
#endif

		maxHP = getPercentValue( maxHP, g_pVariableManager->getVariable(SLAYER_HP_RATIO) );
		maxHP = min((int)maxHP, SLAYER_MAX_HP);
	}
	else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		maxHP = (int)(CSTR*2.00 + CINT + CDEX + CLEVEL);
		maxHP = getPercentValue( maxHP, g_pVariableManager->getVariable(VAMPIRE_HP_RATIO) );
		maxHP = min((int)maxHP, VAMPIRE_MAX_HP);
		//cout << "STR:" << CSTR << " DEX/2:" << (int)(CDEX/2) << " INT:" << CINT << " LEV:" << CLEVEL << " HPMAX:" << maxHP << endl;
	}
	// 아우스터스 추가 by bezz 2003.04.22
	else if (CClass == Creature::CREATURE_CLASS_OUSTERS)
	{
		maxHP = (int)(CSTR*1.50 + CINT/2.00 + CDEX + CLEVEL );
		maxHP = getPercentValue( maxHP, g_pVariableManager->getVariable(OUSTERS_HP_RATIO) );
		maxHP = min((int)maxHP, OUSTERS_MAX_HP);
	}
	else if (CClass == Creature::CREATURE_CLASS_MONSTER)
	{
		maxHP = (int)(CSTR*(2.00 + CLEVEL/100.0));
		maxHP += getPercentValue(maxHP, enhance);
		maxHP = getPercentValue( maxHP, g_pVariableManager->getVariable(MONSTER_HP_RATIO) );
		maxHP = min((int)maxHP, MONSTER_MAX_HP);
//		maxHP = min((int)maxHP, 20000);
	}

	if ( g_pConfig->hasKey("Hardcore") && g_pConfig->getPropertyInt("Hardcore")!=0 )
	{
		maxHP *= 3;
	}
	

	return maxHP;
	*/
	
}

MP_t computeMP(Creature::CreatureClass CClass, BASIC_ATTR* pAttr)
{
	Assert(pAttr != NULL);

	MP_t   maxMP = 0;
	double CINTE = pAttr->nINT;
	double CLEVEL = pAttr->nLevel;

	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		maxMP = (int)(CINTE*2.0);
		maxMP = min((int)maxMP, SLAYER_MAX_MP);
	}
	// 아우스터스 추가 by bezz 2003.04.22
	else if ( CClass == Creature::CREATURE_CLASS_OUSTERS )
	{
		maxMP = (int)((CINTE + CLEVEL)*0.7);
		maxMP = min((int)maxMP, OUSTERS_MAX_MP);
	}

	return maxMP;
}

ToHit_t computeToHit(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance)
{
	Assert(pAttr != NULL);

	ToHit_t toHit             = 0;
	double  CDEX              = pAttr->nDEX;
	double  CLEVEL            = pAttr->nLevel;

	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		toHit = (int)(CDEX/2);

		if (pAttr->pWeapon != NULL)
		{
			// 무사 무기나, 군인 무기를 들고 있을 경우,
			// 도메인 레벨에 의해서 보너스 포인트가 존재한다.
			if (pAttr->pWeapon->getItemClass() == Item::ITEM_CLASS_SWORD)
			{
				toHit += (int)(pAttr->pDomainLevel[SKILL_DOMAIN_SWORD]*1.5*10);
			}
			else if (pAttr->pWeapon->getItemClass() == Item::ITEM_CLASS_BLADE)
			{
				toHit += (int)(pAttr->pDomainLevel[SKILL_DOMAIN_BLADE]*1.5);
			}
			else if (pAttr->pWeapon->getItemClass() == Item::ITEM_CLASS_CROSS)
			{
				toHit += (int)(pAttr->pDomainLevel[SKILL_DOMAIN_HEAL]*1.5);
			}
			else if (pAttr->pWeapon->getItemClass() == Item::ITEM_CLASS_MACE)
			{
				toHit += (int)(pAttr->pDomainLevel[SKILL_DOMAIN_ENCHANT]*1.5);
			}
			else if (isArmsWeapon(pAttr->pWeapon))
			{
				toHit += (int)(pAttr->pDomainLevel[SKILL_DOMAIN_GUN]*1.5);
			}
		}

		toHit = min((int)toHit, SLAYER_MAX_TOHIT);
	}
	else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		toHit = (int)(CDEX + CLEVEL/2.5);
		toHit = min((int)toHit, VAMPIRE_MAX_TOHIT);
	}
	// 아우스터스 추가 by bezz 2003.04.22
	else if ( CClass == Creature::CREATURE_CLASS_OUSTERS )
	{
		toHit = (int)(CDEX/2.0 + CLEVEL);
		toHit = min((int)toHit, OUSTERS_MAX_TOHIT);
	}
	else if (CClass == Creature::CREATURE_CLASS_MONSTER)
	{
		toHit = (int)((CDEX/2.0) * (1.0 + CLEVEL/100.0));
		toHit += getPercentValue(toHit, enhance);
		toHit = min((int)toHit, MONSTER_MAX_TOHIT);
	}

	return toHit;
}

Defense_t computeDefense(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance)
{
	Assert(pAttr != NULL);

	Defense_t Defense = 0;
	double    CDEX    = pAttr->nDEX;
	double    CLEVEL  = pAttr->nLevel;

	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		Defense = (int)(CDEX/2.0);
		Defense = min((int)Defense, SLAYER_MAX_DEFENSE);
	}
	else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		Defense = (int)(CDEX/2.0 + CLEVEL/5.0);
		Defense = min((int)Defense, VAMPIRE_MAX_DEFENSE);
	}
	// 아우스터스 추가 by bezz 2003.04.22
	else if ( CClass == Creature::CREATURE_CLASS_OUSTERS )
	{
		Defense = (int)(CDEX/2.0 + CLEVEL/5.0);
		Defense = min((int)Defense, OUSTERS_MAX_DEFENSE);
	}
	else if (CClass == Creature::CREATURE_CLASS_MONSTER)
	{
		Defense = (int)((CDEX/2.0) * (1.0 + CLEVEL/100.0));
		Defense += getPercentValue(Defense, enhance);
		Defense = min((int)Defense, MONSTER_MAX_DEFENSE);
	}

	return Defense;
}

Protection_t computeProtection(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance)
{
	Assert(pAttr != NULL);

	Protection_t Protection  = 0;
	double       CSTR        = pAttr->nSTR;
	//double       CSTRBonus   = pAttr->nSTR/15.0;
	double       CLEVEL      = pAttr->nLevel;

	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		//Protection = (int)(CSTRBonus);
		Protection = (int)(CSTR);
		Protection = min((int)Protection, SLAYER_MAX_PROTECTION);
	}
	else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		//Protection = (int)(CSTR/5.0 + CLEVEL/5.0);
		Protection = (int)(CSTR + CLEVEL / 5.0 );
		Protection = min((int)Protection, VAMPIRE_MAX_PROTECTION);
	}
	// 아우스터스 추가 by bezz 2003.04.22
	else if ( CClass == Creature::CREATURE_CLASS_OUSTERS )
	{
		Protection = (int)(CSTR + CLEVEL/10.0 );
		Protection = min((int)Protection, OUSTERS_MAX_PROTECTION);
	}
	else if (CClass == Creature::CREATURE_CLASS_MONSTER)
	{
		Protection = (int)(CSTR / (5.0 - CLEVEL/100.0));
		Protection += getPercentValue(Protection, enhance);
		Protection = min((int)Protection, MONSTER_MAX_PROTECTION);
	}

	return Protection;
}

Damage_t computeMinDamage(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance)
{
	Assert(pAttr != NULL);

	Damage_t minDamage  = 0;
	double   CSTR       = pAttr->nSTR;
	double   CLEVEL     = pAttr->nLevel;

	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		minDamage = (int)(CSTR/15.0);

		if (pAttr->pWeapon != NULL)
		{
			// 군인 무기 같은 경우에는 힘에 의한 보너스가 존재하지 않는다.
			if (isArmsWeapon(pAttr->pWeapon))
			{
				minDamage = 1;
			}
		}

		minDamage += g_pVariableManager->getCombatSlayerDamageBonus();

		minDamage = min((int)minDamage, SLAYER_MAX_DAMAGE);
	}
	else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		minDamage = (int)(CSTR/6.0 + CLEVEL/5.0);

		minDamage += g_pVariableManager->getCombatVampireDamageBonus();
		
		minDamage = min((int)minDamage, VAMPIRE_MAX_DAMAGE);
	}
	// 아우스터스 추가 by bezz 2003.04.22
	else if ( CClass == Creature::CREATURE_CLASS_OUSTERS )
	{
		minDamage = (int)(CSTR/10.0 + CLEVEL/10.0);

		minDamage = min((int)minDamage, OUSTERS_MAX_DAMAGE);
	}
	else if (CClass == Creature::CREATURE_CLASS_MONSTER)
	{
		minDamage = (int)(CSTR / (6.0 - CLEVEL/100.0));
		minDamage += getPercentValue(minDamage, enhance);
		minDamage = getPercentValue(minDamage, g_pVariableManager->getVariable( MONSTER_DAMAGE_RATIO ));
		minDamage = min((int)minDamage, MONSTER_MAX_DAMAGE);
	}

	return minDamage;
}

Damage_t computeMaxDamage(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance)
{
	Assert(pAttr != NULL);

	Damage_t maxDamage = 0;
	double   CSTR      = pAttr->nSTR;
	double   CLEVEL    = pAttr->nLevel;

	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		maxDamage = (int)(CSTR/10.0);

		if (pAttr->pWeapon != NULL)
		{
			// 군인 무기 같은 경우에는 힘에 의한 보너스가 존재하지 않는다.
			if (isArmsWeapon(pAttr->pWeapon))
			{
				maxDamage = 2;
			}
		}
		 
		maxDamage += g_pVariableManager->getCombatSlayerDamageBonus();

		maxDamage = min((int)maxDamage, SLAYER_MAX_DAMAGE);
	}
	else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		maxDamage = (int)(CSTR / 4.0 + CLEVEL / 5.0);

		maxDamage += g_pVariableManager->getCombatVampireDamageBonus();

		maxDamage = min((int)maxDamage, VAMPIRE_MAX_DAMAGE);
	}
	// 아우스터스 추가 by bezz 2003.04.22
	else if ( CClass == Creature::CREATURE_CLASS_OUSTERS )
	{
		maxDamage = (int)(CSTR / 6.0 + CLEVEL / 6.0);

		maxDamage = min((int)maxDamage, OUSTERS_MAX_DAMAGE);
	}
	else if (CClass == Creature::CREATURE_CLASS_MONSTER)
	{
		maxDamage = (int)(CSTR / (4.0 - CLEVEL/100.0));
		maxDamage += getPercentValue(maxDamage, enhance);
		maxDamage = getPercentValue(maxDamage, g_pVariableManager->getVariable( MONSTER_DAMAGE_RATIO ));
		maxDamage = min((int)maxDamage, MONSTER_MAX_DAMAGE);
	}
	
	return maxDamage;
}

Speed_t computeAttackSpeed(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance)
{
	Assert(pAttr != NULL);

	Speed_t  AttackSpeed       = 0;
	double   CSTR              = pAttr->nSTR;
	double   CDEX              = pAttr->nDEX;
	double   CLEVEL            = pAttr->nLevel;

	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		// 기본적으로는 힘에 의해 어택 스피드가 결정된다.
		AttackSpeed = (int)(CSTR/10.0);

		if (pAttr->pWeapon != NULL)
		{
			// 무사 무기나, 군인 무기를 들고 있을 경우,
			// 도메인 레벨에 의해서 보너스 포인트가 존재한다.
			if (pAttr->pWeapon->getItemClass() == Item::ITEM_CLASS_SWORD)
			{
				AttackSpeed += (int)(pAttr->pDomainLevel[SKILL_DOMAIN_SWORD]/5.0);
			}
			else if (pAttr->pWeapon->getItemClass() == Item::ITEM_CLASS_BLADE)
			{
				AttackSpeed += (int)(pAttr->pDomainLevel[SKILL_DOMAIN_BLADE]/5.0);
			}
			else if (isArmsWeapon(pAttr->pWeapon))
			{
				// 군인 무기일 경우에는 덱스에 의해 어택 스피드가 결정된다.
				AttackSpeed = (int)(CDEX/10.0);
				AttackSpeed += (int)(pAttr->pDomainLevel[SKILL_DOMAIN_GUN]/5.0);
			}
		}
		AttackSpeed = min( (Speed_t)SLAYER_MAX_ATTACK_SPEED, AttackSpeed );
	}
	else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		AttackSpeed = (int)(CDEX/10.0 + 10.0);
		AttackSpeed = min( (Speed_t)VAMPIRE_MAX_ATTACK_SPEED, AttackSpeed );
	}
	// 아우스터스 추가 by bezz 2003.04.22
	else if ( CClass == Creature::CREATURE_CLASS_OUSTERS )
	{
		AttackSpeed = (int)(CDEX/10.0 + CLEVEL/10.0);
		AttackSpeed = min( (Speed_t)OUSTERS_MAX_ATTACK_SPEED, AttackSpeed );
	}
	
	return AttackSpeed;
}

int computeCriticalRatio(Creature::CreatureClass CClass, BASIC_ATTR* pAttr, int enhance)
{
	Assert(pAttr != NULL);

	int    CriticalRatio = 0;
	double CDEX          = pAttr->nDEX;

	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		if (pAttr->pWeapon != NULL)
		{
			if (pAttr->pWeapon->getItemClass() == Item::ITEM_CLASS_SWORD)
			{
				CriticalRatio = (int)(pAttr->pDomainLevel[SKILL_DOMAIN_SWORD]/5.0);
			}
			else if (pAttr->pWeapon->getItemClass() == Item::ITEM_CLASS_BLADE)
			{
				CriticalRatio = (int)(pAttr->pDomainLevel[SKILL_DOMAIN_BLADE]/5.0);
			}
			else if (isArmsWeapon(pAttr->pWeapon))
			{
				// 군인 무기일 경우에는 덱스에 의해 어택 스피드가 결정된다.
				CriticalRatio = (int)(pAttr->pDomainLevel[SKILL_DOMAIN_GUN]/5.0);
			}
		}
	}
	else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		CriticalRatio = (int)((CDEX-20.0)/30.0);
	}
	// 아우스터스 추가 by bezz 2003.04.22
	else if ( CClass == Creature::CREATURE_CLASS_OUSTERS )
	{
		CriticalRatio = (int)((CDEX-20.0)/30.0);
	}
	else if (CClass == Creature::CREATURE_CLASS_MONSTER)
	{
		CriticalRatio = (int)((CDEX-20.0)/30.0);
		CriticalRatio += getPercentValue(CriticalRatio, enhance);
	}

	return CriticalRatio;
}

Steal_t computeStealRatio(Creature::CreatureClass CClass, Steal_t amount, BASIC_ATTR* pAttr)
{
	// 만일 스틸하는 양이 0이라면, 스틸할 확률 역시 0이다.
	if (amount == 0) return 0;

	Steal_t result = 0;

	if (CClass == Creature::CREATURE_CLASS_SLAYER)
	{
		if (pAttr->pWeapon != NULL)
		{
			switch (pAttr->pWeapon->getItemClass())
			{
				case Item::ITEM_CLASS_SWORD:
				case Item::ITEM_CLASS_BLADE:
					result = (Steal_t)(90.0 - (float)amount * 1.4);
					break;
				default:
					result = (Steal_t)(65.0 - (float)amount * 1.4);
					break;
			}
		}
		else
		{
			result = (Steal_t)(90.0 - (float)amount * 1.4);
		}
	}
	else if (CClass == Creature::CREATURE_CLASS_VAMPIRE)
	{
		result = (Steal_t)(90.0 - (float)amount * 1.4);
	}
	// 아우스터스 추가 by bezz 2003.04.22
	else if ( CClass == Creature::CREATURE_CLASS_OUSTERS )
	{
		result = (Steal_t)(90.0 - (float)amount * 1.4 );
	}
	else if (CClass == Creature::CREATURE_CLASS_MONSTER)
	{
	}

	return result;
}

