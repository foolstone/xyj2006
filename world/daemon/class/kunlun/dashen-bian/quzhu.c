#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
string msg;
int myexp,yourexp,mystr,yourstr,lv;
object weapon;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("������ħֻ�ܶ�ս���еĶ���ʹ�á�\n");
        if(me->query("family/family_name")!="����ɽ���鶴")
        return notify_fail("��������ħ��ֻ������ɽ���鶴���˲ſ����ã�\n");
        if (me->query_skill("dashen-bian",1) < 80)
        return notify_fail("��Ĵ���޷����д���ߡ�\n");
weapon = target->query_temp("weapon");
if(!objectp(weapon)) return notify_fail("��Ķ���û���ñ�����\n");
myexp=me->query("combat_exp");
mystr=me->query_str();
yourexp=target->query("combat_exp");
yourstr=target->query_str();
lv=me->query_skill("mace",1)/10+1;
msg = YEL "$N�Ӷ�����"+weapon->name()+YEL"��$n�ı�����֪��ô�������˵��£� \n" NOR;
if(objectp(weapon) )
{
//if( random(myexp * lv * mystr) > (yourexp * 2) )
if( random(myexp ) > (yourexp / 2) )
{
weapon->unequip();
weapon->move(environment(target));
message_vision(msg, me, target);
target->start_busy(2);
}
else
{
COMBAT_D->do_attack(target,me, weapon);
}
me->start_busy(2);
}
return 1;
}