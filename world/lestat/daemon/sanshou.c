//lestat for moon
//2001 ����������
 
#include <ansi.h>

inherit F_DBASE;
inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        int skill;
//        int j;
       string msg;
//      int ap;
        if( !target ) target = offensive_target(me);
//         j = (int)me->query_skill("jueqingbian",1);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ�����������֡�?\n");
//        if(time()-(int)me->query_temp("JQB_perform_end") < 10) return notify_fail("����Ƶ��ʹ�á����������֡���\n");

        if(!me->query("JQB_known"))
                return notify_fail("����û�д��㡸���������֡�������\n");
        if(me->query_temp("JQB_perform")) 
                return notify_fail("���Ѿ�ʹ�������������֡��ˣ�\n");

        if(!me->is_fighting(target) )
                return notify_fail("����������ֻ����ս����ʹ��!!\n");

        if((int)me->query("max_force") <1000 )
                return notify_fail("�������������\n");

        if((int)me->query("force") < 500 )
                return notify_fail("����������㣡\n");

        if((int)me->query("sen") <50 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");

        if((int)me->query_skill("jueqingbian",1) <100)
                return notify_fail("��ľ���޼��𻹲���ʩչ��һ������������!!\n");
        if((int)me->query_skill("moondance",1) <100)
                return notify_fail("�������������ȼ�����!!\n");
        if((int)me->query_skill("moonforce",1)<100)
                return notify_fail("���Բ���ķ��ȼ�̫��!!\n");
        if((int)me->query_skill("moonshentong",1) <100)
                return notify_fail("����¹��ɷ��ȼ�����!!\n");
        if( (string)me->query("gender") !="Ů��")
                return notify_fail("���Ϊ����֮��,����֪��Ů���ҵ���˼??\n");
        if(me->query("family/family_name") != "�¹�" )
                return notify_fail("���������Ե,���򲻵��޷��ľ���!!\n");

        me->delete("env/brief_message");
        target->delete("env/brief_message");

//        ap = 2 + random(1);
        weapon=me->query_temp("weapon");
     msg = HIC
"\n��������Ϊ����?ֱ������������!$N����һ�����,�޷���Ȼ����鶯�쳣!\n" NOR;
    message_vision(msg, me, target);

/*        if( (int)me->query_skill("jueqingbian",1) > 120)
{
        me->set_temp("JQB_perform", 12);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

        me->set_temp("JQB_perform", 13);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 

        me->set_temp("JQB_perform", 14);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        me->start_busy(ap);
       } else {
      if( (int)me->query_skill("jueqingbian",1) > 90)
{
      me->set_temp("JQB_perform", 12);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
       me->set_temp("JQB_perform", 13);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
       me->start_busy(2);
} else {
       me->set_temp("JQB_perform", 12);
       COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
     me->start_busy(1);
}
}
        me->delete_temp("JQB_perform");
        me->add("force", -100);

        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                //        else target->kill_ob(me);
                }
        }

        return 1;
}
*/
        skill = me->query_skill("whip");
        me->set_temp("JQB_perform",1);
        call_out("checking", 1, me, target);
        me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), skill/2);
        me->add("force", -200);
        return 1;
}
void checking(object me, object target)
{

	object weapon;
	weapon = me->query_temp("weapon");

        if ( me->query_temp("JQB_perform")  ) {
        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "whip") {
                tell_object(me, "\n������û�гֱޣ������������֡��Ĺ��Ʊ㼴�߽⣡\n" NOR);
		me->delete_temp("JQB_perform");
                return;
           }


           else if ( weapon->query("weapon_prop") == 0 ) {
                tell_object(me, "\n���"+weapon->name()+"�ѻ٣��޷����������������֡��Ĺ��ƣ�\n\n" NOR);
		me->delete_temp("JQB_perform");
                return;
           }
           else if ( (int)me->query("force") < 400  ) {
                tell_object(me, "\n���������̲��㣬���Գ��������������֡���������ֻ���ջ����С�\n\n" NOR);
		me->delete_temp("JQB_perform");
                return;
           }
           else if ( me->query_skill_mapped("whip") != "jueqingbian" ) {
                tell_object(me, "\n��ת��ʩչ�����޷����޷����ԡ����������֡����У�\n\n" NOR);
		me->delete_temp("JQB_perform");
                return;
           }
           else if (!me->is_fighting()) {
                tell_object(me,  "\n������û�к��˹��У������ջ��ˡ����������֡��Ĺ��ơ�\n\n" NOR);
		me->delete_temp("JQB_perform");
                return;
           }
	   else call_out("checking", 1, me, target);
	}
	   else return;

}  



void remove_effect(object me, int amount)
{       
	if ( me->query_temp("JQB_perform") ) {
        message_vision(HIM"$N��ͷһ��,һ���������������\n"NOR, me);
        me->delete_temp("JQB_perform");
         }
}