// create by snowcat jan 21 1998

inherit ROOM;

void create ()
{
  set ("short", "����·");
  set ("long", @LONG

һ��С·���ź����������ƣ����ߵĺ�ˮ����һ�㣬�紵����ˮ����
����΢�����ں�ˮ�ϻζ��ų����ĵ�Ӱ����ʱ��ݺ����������������
�����Ŀ�������

LONG);

  set("exits", ([
        "north" : __DIR__"xihu4",
        "southwest" : __DIR__"xihu7",
        "east" : __DIR__"guting2",
      ]));

  set("outdoors", __DIR__);

  setup();
}

