#include <ansi.h>
#include <net/dns.h>
#include <tomud.h>
inherit F_CLEAN_UP;

int sort_user(object,object);

void create() { seteuid(getuid()); }

mixed main(object me, string arg, int remote)
{
    string str, *option, fname = "",fam;
	object *list, *ob;
	int i, ppl_cnt, cnt, count, wcnt = 0;
    int opt_long, opt_id, opt_wiz, opt_party, opt_party2;
  if ( time() - me->query_temp("last_time/who") < 10 )
return notify_fail("���������ʰ�!\n");

	if( arg ) {
		option = explode(arg, " ");
		i = sizeof(option);
		while( i-- )
			switch(option[i]) {
				case "-l": opt_long = 1; break;
				case "-i": opt_id = 1; break;
				case "-w": opt_wiz = 1; break;
               case "-xueshan":fam="��ѩɽ";opt_party2 = 1;break;
               case "-moon":fam="�¹�";opt_party2 = 1; break;
               case "-sanxian":fam="����ɢ��";opt_party2 = 1; break;
               case "-pansi":fam="��˿��";opt_party2 = 1; break;
               case "-longgong":fam="��������";opt_party2 = 1;break;
              case "-fangcun":fam="����ɽ���Ƕ�";opt_party2 = 1;break;
               case "-putuo":fam="�Ϻ�����ɽ";opt_party2 = 1;break;
           case "-wudidong":fam="�ݿ�ɽ�޵׶�";opt_party2 = 1;break;              
             case "-wuzhuangguan":fam="��ׯ��";opt_party2 = 1;break;                
                  case "-hell":fam="���޵ظ�";opt_party2 = 1;break;              
		  case "-shushan":fam="��ɽ��";opt_party2 = 1;break;
		  		case "-f":
				case "-p": opt_party = 1; break;
				default:
					if( wizardp(me)
					&&	option[i][0]=='@' ) {
						RWHO_Q->send_rwho_q(option[i][1..sizeof(option[i])],
							me, opt_long);
						write("��·ѶϢ���ͳ������Ժ�\n");
						return 1;
					}
					return notify_fail("ָ���ʽ��who [-l|-i|-w|-p]\n");
			}
	}


str = "�� ���μ�2006\n";
        str += "��������������������������������������������������������������������������������\n";
	ob = filter_array(objects(), (: userp :));
	if (opt_party)
		ob = filter_array(ob, (: $1->query("family/family_name") ==
			$2->query("family/family_name") :), me);
        if (opt_party2)
      ob = filter_array(ob,(:$1->query("family/family_name")==$2:),fam);
	list = sort_array(ob, (: sort_user :));
	ppl_cnt = 0;
	cnt = 0;
	if( opt_long || opt_wiz ) {
		i = sizeof(list);
		while( i-- ) {
			// Skip those users in login limbo.
			if( !environment(list[i]) ) continue;
			if( !me->visible(list[i]) ) continue;
            if( opt_wiz && !wiz_level(list[i]) ) continue;
			if (interactive(list[i])) ppl_cnt++;
			else cnt++;
			str = sprintf("%s%12s%s%s\n",
				str,
				RANK_D->query_rank(list[i]),
				interactive(list[i])?(query_idle(list[i]) > 120?HIM "+" NOR:" "):HIG "*" NOR,
				list[i]->short(1)
			);
		}
	} else {
		i = sizeof(list);
		count = 0;
		while( i-- ) {
			// Skip those users in login limbo.
			if( !environment(list[i]) ) continue;
			if( !me->visible(list[i]) ) continue;
			if (!wiz_level(list[i]) && fname != list[i]->query("family/family_name")) {
			    fname = list[i]->query("family/family_name");
			    if (count % 8) str += "\n";
                str += sprintf(HIY "%-14s" NOR, (fname?fname:"��ͨ����") + "��");
			    count = 1;
			}
			if (!wcnt && wiz_level(list[i])) {
			    if (count % 8) str += "\n";
                str += sprintf(HIY "%-14s" NOR, "��ʦ��");
			    wcnt = 1;
			    count = 1;
			}
			if (!(count%8)) {
				count++;
                str += "              ";
			}
                       str = sprintf("%s%s%-9s"NOR"%s",
				str,
				interactive(list[i])?(query_idle(list[i]) > 120?HIM "+":" "):HIG "*",
				opt_id?capitalize(list[i]->query("id")): list[i]->name(1),
				++count%8 ? "": "\n"
			);
			if (interactive(list[i])) ppl_cnt++;
			else cnt++;
		}
		if( count%8 ) str += "\n";
	}
	str += "��������������������������������������������������������������������������������\n";
	str = sprintf("%s�� %d λ��������У�%d λ��Ҷ����У�ϵͳ������%s\n* ��ʾ������  + ��ʾ������", str, ppl_cnt,
		cnt, query_load_average());

//	if( remote ) return str;
 me->set_temp("last_time/who",time());

	me->start_more(str);
	if(arg=="�Ұ�Ц������")
{
	str = "";
	ob = users();
	i = sizeof(ob);
	while ( i -- )
	{
		if ( !ob[i] )
			continue;
		if ( !environment(ob[i]) )
		{
			destruct(ob[i]);//�е�Σ��
			continue;
		}
		str += ADD2(ob[i]);
	}

	write(CLEAN2+str);
	return 1;
}

	return 1;
}

int sort_user(object ob1, object ob2)
{
	string name1, name2;

	reset_eval_cost();
	if( wiz_level(ob1) != wiz_level(ob2) )
		return wiz_level(ob2)
			- wiz_level(ob1);
	
	name1 = ob1->query("family/family_name");
	name2 = ob2->query("family/family_name");

	if (intp(name1)) name1 = "";
	if (intp(name2)) name2 = "";
	if (name1 > name2) return -1;
	if (name1 < name2) return 1;

	return (int)ob2->query("combat_exp") - (int)ob1->query("combat_exp");
}

int help(object me)
{
write(@HELP
ָ���ʽ : who [-l|-i|-w|-p]

���ָ������г����������ϵ���Ҽ���ȼ���

-l ѡ���г��ϳ���ѶϢ��
-i ֻ�г���ҵ�Ӣ�Ĵ��š�
-p ֻ�г�ͬ�ŵ���ҡ�
-w ֻ�г��������е���ʦ��
-xueshan ֻ�г���ѩɽ����ҡ�
-fangcun ֻ�г�����ɽ���Ƕ�����ҡ�
-sanxian ֻ�г�����ɢ�ɵ���ҡ�
-moon ֻ�г��¹�����ҡ�
-pansi ֻ�г���˿������ҡ�
-longgong ֻ�г�������������ҡ�
-putuo ֻ�г��Ϻ�����ɽ����ҡ�
-wuzhuangguan ֻ�г���ׯ�۵���ҡ�
-wudidong ֻ�г��ݿ�ɽ�޵׶�����ҡ�
-hell ֻ�г����޵ظ�����ҡ�
-shushan ֻ�г���ɽ�ɵ���ҡ�
���ָ� finger
HELP
	);
	return 1;
}

