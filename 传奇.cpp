/*
Copyright 2013-2016 Yuer

This file is part of Story.

    Story is free software: you can redistribute it and/or 
	modify it under the terms of the GNU General Public 
	License as published by the Free Software Foundation, 
	either version 3 of the License, or (at your option) 
	any later version.

    Story is distributed in the hope that it will be useful, 
	but WITHOUT ANY WARRANTY; without even the implied 
	warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
	PURPOSE.  See the GNU General Public License for more 
	details.

    You should have received a copy of the GNU General 
	Public License along with Story.  If not, see 
	<http://www.gnu.org/licenses/>.
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<conio.h>
#include<stdbool.h>

#define size 2552                // 20+20+20+8*12+28*17+80*24
#define grade 40

#define storyfolder "/sdcard/story/"
#define savefolder "/sdcard/story/save/"
#define accountfile "/sdcard/story/account.ys"
#define onlinefile "/sdcard/story/onlineact.ys"
#define namefile "/sdcard/story/name.ys"
#define troopfile "/sdcard/story/troops.ys"
#define tfile "/sdcard/story/t.ys"
#define logfile "log.txt"

struct GOODS
{
	char name[20];               // 物品名字
	char nam;                    // 符号
	int q;                       // 数量
};

struct EQUIPMENT
{
	char name[20];               // 装备名字
	char kind[20];               // 装备种类
	int grd;                     // 装备级数
	char rank;                   // 装备级别
	double axHP;                 // 增加生命量
	double axMP;                 // 增加魔法量
	double aatc;                 // 增加攻击量
	double adef;                 // 增加防御量
};

struct MONSTER
{
	char name[20];               // 名字
	int grd;				 	 // 等级
	double HP;                   // 生命
	double atc;		 	         // 攻击力
	double def;		  	         // 防御力
	double exp;			         // 得到经验值
	double mny;	 	             // 爆出金币
	struct GOODS out[10];		 // 爆出物品
	struct EQUIPMENT oequ[10];   // 爆出装备
};

struct CHARACTER
{
	char name[20];               // 名字
	int grd;				   	 // 等级
	char prof[20];               // 职业
	double xHP;	      	         // 生命上限
	double HP;                   // 生命值
	double xMP;                  // 魔法上限
	double MP;                   // 魔法值
	double atc;				     // 攻击力
	double def;			         // 防御力
	double mny;			         // 金币
	struct EQUIPMENT equ[24];	 // 装备
	double xexp;			     // 经验上限
	double exp;		  	         // 经验值
	struct GOODS goods[17];		 // 物品
	char v[20];                  // 所在地方
	int t;						 // 物品变量
	int e;                       // 装备变量
	int n,m,q;                   // 临时变量
	double h,k;                  // 临时变量
	char filename[100];          // 文件
	int p;                       // 角色号
	int trp;                     // 队里号
	char trpname[37];            // 队名
	char buddy1[20];             // 队员
	char buddy2[20];             // 队员
	char buddy3[20];             // 队员
	char b1;                     // 准备
	char b2;                     // 准备
	char b3;                     // 准备
};

struct MONSTER Out(struct MONSTER mon,int b);
void Printf(struct CHARACTER cha);
struct CHARACTER SeeGoods(struct CHARACTER cha);
void Choice(struct CHARACTER cha);
struct CHARACTER Uptrp(struct CHARACTER cha);

char act[20];

void cqlog(int t,int e)
{
	FILE *f;
	f=fopen(logfile,"w");
	fprintf(f,"物品数量%d\n",t);
	fprintf(f,"装备数量%d\n",e);
	fprintf(f,"\n");
	fclose(f);
}

struct CHARACTER Equname(struct CHARACTER cha)
{
 int t=cha.n;
 if(cha.equ[t].rank=='D')
  {
  if(strcmp(cha.equ[t].kind,"头盔")==0)
  {
   strcpy(cha.equ[t].name,"普通头盔");
  }
  if(strcmp(cha.equ[t].kind,"盔甲")==0)
  {
   strcpy(cha.equ[t].name,"普通盔甲");
  }
  if(strcmp(cha.equ[t].kind,"裤子")==0)
  {
   strcpy(cha.equ[t].name,"普通裤子");
  }
  if(strcmp(cha.equ[t].kind,"武器")==0)
  {
   strcpy(cha.equ[t].name,"普通武器");
  }
  if(strcmp(cha.equ[t].kind,"鞋子")==0)
  {
   strcpy(cha.equ[t].name,"普通鞋子");
  }
  }
 if(cha.equ[t].grd>=5&&cha.equ[t].grd<=10)
 {
  if(cha.equ[t].rank=='C'||cha.equ[t].rank=='B')
  {
  if(strcmp(cha.equ[t].kind,"头盔")==0)
  {
   strcpy(cha.equ[t].name,"  粗布帽");
  }
  if(strcmp(cha.equ[t].kind,"盔甲")==0)
  {
   strcpy(cha.equ[t].name,"  粗布衣");
  }
  if(strcmp(cha.equ[t].kind,"裤子")==0)
  {
   strcpy(cha.equ[t].name,"  粗布裤");
  }
  if(strcmp(cha.equ[t].kind,"武器")==0)
  {
   strcpy(cha.equ[t].name,"  乌木剑");
  }
  if(strcmp(cha.equ[t].kind,"鞋子")==0)
  {
   strcpy(cha.equ[t].name,"  粗布鞋");
  }
  if(strcmp(cha.equ[t].kind,"戒指")==0)
  {
   strcpy(cha.equ[t].name,"普通戒指");
  }
  }
  if(cha.equ[t].rank=='A'&&cha.equ[t].grd==10)
  {
  if(strcmp(cha.equ[t].kind,"头盔")==0)
  {
   strcpy(cha.equ[t].name,"精灵头盔");
  }
  if(strcmp(cha.equ[t].kind,"盔甲")==0)
  {
   strcpy(cha.equ[t].name,"精灵盔甲");
  }
  if(strcmp(cha.equ[t].kind,"裤子")==0)
  {
   strcpy(cha.equ[t].name,"  精灵裤");
  }
  if(strcmp(cha.equ[t].kind,"武器")==0)
  {
   strcpy(cha.equ[t].name,"    匕首");
  }
  if(strcmp(cha.equ[t].kind,"鞋子")==0)
  {
   strcpy(cha.equ[t].name,"  精灵鞋");
  }
  if(strcmp(cha.equ[t].kind,"戒指")==0)
  {
   strcpy(cha.equ[t].name,"麻痹戒指");
  }
  }
 }
 if(cha.equ[t].grd>10&&cha.equ[t].grd<=15)
 {
  if(cha.equ[t].rank=='C'||cha.equ[t].rank=='B')
  {
  if(strcmp(cha.equ[t].kind,"头盔")==0)
  {
   strcpy(cha.equ[t].name,"轻型头盔");
  }
  if(strcmp(cha.equ[t].kind,"盔甲")==0)
  {
   strcpy(cha.equ[t].name,"轻型盔甲");
  }
  if(strcmp(cha.equ[t].kind,"裤子")==0)
  {
   strcpy(cha.equ[t].name,"  轻型裤");
  }
  if(strcmp(cha.equ[t].kind,"武器")==0)
  {
   strcpy(cha.equ[t].name,"    铁剑");
  }
  if(strcmp(cha.equ[t].kind,"鞋子")==0)
  {
   strcpy(cha.equ[t].name,"  轻型鞋");
  }
  if(strcmp(cha.equ[t].kind,"戒指")==0)
  {
   strcpy(cha.equ[t].name,"    战戒");
  }
  }
  if(cha.equ[t].rank=='A'&&cha.equ[t].grd==15)
  {
  if(strcmp(cha.equ[t].kind,"头盔")==0)
  {
   strcpy(cha.equ[t].name,"青铜头盔");
  }
  if(strcmp(cha.equ[t].kind,"盔甲")==0)
  {
   strcpy(cha.equ[t].name,"青铜盔甲");
  }
  if(strcmp(cha.equ[t].kind,"裤子")==0)
  {
   strcpy(cha.equ[t].name,"  青铜裤");
  }
  if(strcmp(cha.equ[t].kind,"武器")==0)
  {
   strcpy(cha.equ[t].name,"  青铜剑");
  }
  if(strcmp(cha.equ[t].kind,"鞋子")==0)
  {
   strcpy(cha.equ[t].name,"  青铜鞋");
  }
  if(strcmp(cha.equ[t].kind,"戒指")==0)
  {
   strcpy(cha.equ[t].name,"古铜戒指");
  }
  }
 }
 if(cha.equ[t].grd>15&&cha.equ[t].grd<=25)
 {
  if(cha.equ[t].rank=='C'||cha.equ[t].rank=='B')
  {
  if(strcmp(cha.equ[t].kind,"头盔")==0)
  {
   strcpy(cha.equ[t].name,"中型头盔");
  }
  if(strcmp(cha.equ[t].kind,"盔甲")==0)
  {
   strcpy(cha.equ[t].name,"中型盔甲");
  }
  if(strcmp(cha.equ[t].kind,"裤子")==0)
  {
   strcpy(cha.equ[t].name,"  中型裤");
  }
  if(strcmp(cha.equ[t].kind,"武器")==0)
  {
   strcpy(cha.equ[t].name,"  斩马刀");
  }
  if(strcmp(cha.equ[t].kind,"鞋子")==0)
  {
   strcpy(cha.equ[t].name,"  中型鞋");
  }
  if(strcmp(cha.equ[t].kind,"戒指")==0)
  {
   strcpy(cha.equ[t].name,"力量戒指");
  }
  }
  if(cha.equ[t].rank=='A'&&cha.equ[t].grd==20)
  {
  if(strcmp(cha.equ[t].kind,"头盔")==0)
  {
   strcpy(cha.equ[t].name,"祈祷头盔");
  }
  if(strcmp(cha.equ[t].kind,"盔甲")==0)
  {
   strcpy(cha.equ[t].name,"祈祷盔甲");
  }
  if(strcmp(cha.equ[t].kind,"裤子")==0)
  {
   strcpy(cha.equ[t].name,"  祈祷裤");
  }
  if(strcmp(cha.equ[t].kind,"武器")==0)
  {
   strcpy(cha.equ[t].name,"祈祷之刃");
  }
  if(strcmp(cha.equ[t].kind,"鞋子")==0)
  {
   strcpy(cha.equ[t].name,"  祈祷鞋");
  }
  if(strcmp(cha.equ[t].kind,"戒指")==0)
  {
   strcpy(cha.equ[t].name,"牛角戒指");
  }
  }
  if(cha.equ[t].rank=='A'&&cha.equ[t].grd==25)
  {
  if(strcmp(cha.equ[t].kind,"头盔")==0)
  {
   strcpy(cha.equ[t].name,"沃玛头盔");
  }
  if(strcmp(cha.equ[t].kind,"盔甲")==0)
  {
   strcpy(cha.equ[t].name,"沃玛盔甲");
  }
  if(strcmp(cha.equ[t].kind,"裤子")==0)
  {
   strcpy(cha.equ[t].name,"  沃玛裤");
  }
  if(strcmp(cha.equ[t].kind,"武器")==0)
  {
   strcpy(cha.equ[t].name,"半月弯刀");
  }
  if(strcmp(cha.equ[t].kind,"鞋子")==0)
  {
   strcpy(cha.equ[t].name,"  沃玛鞋");
  }
  if(strcmp(cha.equ[t].kind,"戒指")==0)
  {
   strcpy(cha.equ[t].name,"水晶戒指");
  }
  }
 }
 if(cha.equ[t].grd>25&&cha.equ[t].grd<=40)
 {
  if(cha.equ[t].rank=='C'||cha.equ[t].rank=='B')
  {
  if(strcmp(cha.equ[t].kind,"头盔")==0)
  {
   strcpy(cha.equ[t].name,"重型头盔");
  }
  if(strcmp(cha.equ[t].kind,"盔甲")==0)
  {
   strcpy(cha.equ[t].name,"重型盔甲");
  }
  if(strcmp(cha.equ[t].kind,"裤子")==0)
  {
   strcpy(cha.equ[t].name,"  重型裤");
  }
  if(strcmp(cha.equ[t].kind,"武器")==0)
  {
   if(strcmp(cha.prof,"战士")==0)
   {
    strcpy(cha.equ[t].name,"  破空剑");
   }
   if(strcmp(cha.prof,"法师")==0)
   {
    strcpy(cha.equ[t].name,"   魔杖");
   }
   if(strcmp(cha.prof,"道士")==0)
   {
    strcpy(cha.equ[t].name,"  游龙剑");
   }
  }
  if(strcmp(cha.equ[t].kind,"鞋子")==0)
  {
   strcpy(cha.equ[t].name,"  重型鞋");
  }
  if(strcmp(cha.equ[t].kind,"戒指")==0)
  {
   strcpy(cha.equ[t].name,"玻璃戒指");
  }
  }
  if(cha.equ[t].rank=='A'&&cha.equ[t].grd==32)
  {
  if(strcmp(cha.equ[t].kind,"头盔")==0)
  {
   strcpy(cha.equ[t].name,"记忆头盔");
  }
  if(strcmp(cha.equ[t].kind,"盔甲")==0)
  {
   strcpy(cha.equ[t].name,"记忆盔甲");
  }
  if(strcmp(cha.equ[t].kind,"裤子")==0)
  {
   strcpy(cha.equ[t].name,"  记忆裤");
  }
  if(strcmp(cha.equ[t].kind,"武器")==0)
  {
   if(strcmp(cha.prof,"战士")==0)
   {
    strcpy(cha.equ[t].name,"  记忆剑");
   }
   if(strcmp(cha.prof,"法师")==0)
   {
    strcpy(cha.equ[t].name,"裁决之杖");
   }
   if(strcmp(cha.prof,"道士")==0)
   {
    strcpy(cha.equ[t].name,"  龙纹剑");
   }
  }
  if(strcmp(cha.equ[t].kind,"鞋子")==0)
  {
   strcpy(cha.equ[t].name,"  记忆鞋");
  }
  if(strcmp(cha.equ[t].kind,"戒指")==0)
  {
   strcpy(cha.equ[t].name,"记忆戒指");
  }
  }
  if(cha.equ[t].rank=='A'&&cha.equ[t].grd==40)
  {
  if(strcmp(cha.equ[t].kind,"头盔")==0)
  {
   strcpy(cha.equ[t].name,"恶魔头盔");
  }
  if(strcmp(cha.equ[t].kind,"盔甲")==0)
  {
   strcpy(cha.equ[t].name,"恶魔长袍");
  }
  if(strcmp(cha.equ[t].kind,"裤子")==0)
  {
   strcpy(cha.equ[t].name,"  恶魔裤");
  }
  if(strcmp(cha.equ[t].kind,"武器")==0)
  {
   if(strcmp(cha.prof,"战士")==0)
   {
    strcpy(cha.equ[t].name,"    血饮");
   }
   if(strcmp(cha.prof,"法师")==0)
   {
    strcpy(cha.equ[t].name,"噬魂法杖");
   }
   if(strcmp(cha.prof,"道士")==0)
   {
    strcpy(cha.equ[t].name,"  无极棍");
   }
  }
  if(strcmp(cha.equ[t].kind,"鞋子")==0)
  {
   strcpy(cha.equ[t].name,"  恶魔鞋");
  }
  if(strcmp(cha.equ[t].kind,"戒指")==0)
  {
   strcpy(cha.equ[t].name,"魔血戒指");
  }
  }
 }//45级再出朱雀一套，54级霸者一套不好弄
 return cha;
}

struct MONSTER Out(struct MONSTER mon,int b)
{
 int a,k=0;
 while(mon.out[k].nam!='*')
 {
  k++;
 }
 k = k + b;
 a = 1 + rand()%7;
 if(a==1)
 {
    strcpy(mon.oequ[k].kind,"武器");
 }
 if(a==2||a==3)
 {
	strcpy(mon.oequ[k].kind,"戒指");
 }
 if(a==4)
 {
	strcpy(mon.oequ[k].kind,"盔甲");
 }
 if(a==5)
 {
    strcpy(mon.oequ[k].kind,"头盔");
 }
 if(a==6)
 {
	strcpy(mon.oequ[k].kind,"裤子");
 }
 if(a==7)
 {
	strcpy(mon.oequ[k].kind,"鞋子");
 }
 return mon;
}

struct MONSTER Monster(struct CHARACTER cha)
{
	struct MONSTER mon;
	int a;
	int grd;
	for(int i=0;i<=9;i++)
	{
	  mon.out[i].nam = '\0';
	  strcpy(mon.out[i].name,"\0");
	  mon.out[i].q = 0;
	  strcpy(mon.oequ[i].name,"\0");
	  strcpy(mon.oequ[i].kind,"\0");
	  mon.oequ[i].grd=0;
	  mon.oequ[i].rank=' ';
	  mon.oequ[i].aatc=0;
	  mon.oequ[i].adef=0;
	  mon.oequ[i].axHP=0;
	  mon.oequ[i].axMP=0;
	}
	if(strcmp(cha.v,"村镇周边")==0)
	{
	 a = 1 + rand()%10;
	 if (a<=10-cha.grd*3)
	 {
		strcpy(mon.name,"鸡");
		mon.grd = 1;
		mon.HP = 5;
		mon.atc = 4;
		mon.def = 2;
		mon.exp = 5;
		mon.mny = 1;
		return mon;
	 }
	 if (a>=6)
	 {
		strcpy(mon.name,"稻草人");
		mon.grd = 2;
		mon.HP = 20;
		mon.atc = 10;
		mon.def = 5;
		mon.exp = 8;
		mon.mny = 5;
		return mon;
	 }
	 if (a<=5)
	 {
		strcpy(mon.name,"鹿");
		mon.grd = 3;
		mon.HP = 50;
		mon.atc = 16;
		mon.def = 8;
		mon.exp = 15;
		mon.mny = 3;
		return mon;
	 }
	}
	if (strcmp(cha.v,"森林")==0)
	{
		a = 1 + rand()%100;
		grd = cha.grd;
		if(cha.grd>=11)
		{
		 grd = 11;
		}
		if(a>3&&a<=75-grd*5)
		{
		 mon.grd=5;
		 strcpy(mon.name,"多钩猫");
		}
		if(a>75-grd*5&&a<=100-grd*5)
		{
		 mon.grd=6;
		 strcpy(mon.name,"食人花");
		}
		if(a>100-grd*5&&a<=125-grd*5)
		{
		 mon.grd=8;
		 strcpy(mon.name,"蜘蛛精");
		}
		if(a>125-grd*5&&a<=100)
		{
		 mon.grd=9;
		 strcpy(mon.name,"兽人");
		}
		if(a<=3)
		{
		 strcpy(mon.name,"半兽勇士");
		 mon.grd = 10;
		 mon.HP = 500;
		 mon.atc = 120;
		 mon.def = 40;
         mon.exp = 50;
		 mon.mny = 20;
		 mon.out[0].nam = '*';
		 mon.oequ[0].rank = 'A';
         mon = Out(mon,0);
		 if(grd<=10)
		 {
		  mon.exp = 250;
		  mon.mny = 100;
		  mon.out[1].nam = '@';
		  strcpy(mon.out[1].name,"中级恢复药水");
		  mon.out[1].q = 3;
		 }
		 return mon;
		}
		mon.HP = mon.grd * 15;
		mon.atc = mon.grd * 4.5;
		mon.def = mon.grd * 3;
		mon.exp = mon.grd * 4;
		mon.mny = mon.grd;
		a = 1 + rand()%10;
		if(a>=9&&mon.grd<=6)
		{
		 mon.out[0].nam = '*';
		 mon.oequ[0].rank = 'C';
         mon = Out(mon,0);
		}
		if(a<=2&&mon.grd<=8)
		{
		 mon.out[0].nam = '*';
		 mon.oequ[0].rank = 'B';
         mon = Out(mon,0);
		}
		return mon;
	}
	if (strcmp(cha.v,"僵尸洞")==0)
	{
		a = 1 + rand()%100;
		if(a<=40)
		{
		 strcpy(mon.name,"僵尸");
		 if(a<20)
		 {
		  mon.grd = 10;
		 }
		 if(a>=20)
		 {
		  mon.grd = 15;
		 }
		 mon.HP = mon.grd * 15;
		 mon.atc = mon.grd * 4.7;
		 mon.def = mon.grd * 3;
		 mon.exp = mon.grd * 4;
		 mon.mny = mon.grd-5;
		 a = 21 + rand()%18;
	     if(a==25)
		 {
		  mon.out[0].nam = 'a';
		  strcpy(mon.out[0].name,"青铜");
		  mon.out[0].q = 1;
		 }
		 return mon;
		}
        if(a>40&&a<=75)
		{
		 strcpy(mon.name,"雷电僵尸");
		 if(a<55)
		 {
		  mon.grd = 13;
		 }
		 if(a>=55)
		 {
		  mon.grd = 15;
		 }
		 mon.HP = mon.grd * 18;
		 mon.atc = mon.grd * 4.9;
		 mon.def = mon.grd * 3;
		 mon.exp = mon.grd * 4;
		 mon.mny = mon.grd-5;
		 a = 21 + rand()%10;
	     if(a==26)
		 {
		  mon.out[0].nam = 'a';
		  strcpy(mon.out[0].name,"青铜");
		  mon.out[0].q = 1;
		 }
		 return mon;
		}
		if (a>95)
		{
			strcpy(mon.name,"僵尸王");
			mon.grd = 15;
			mon.HP = mon.grd * 50 + 50;    //800
			mon.atc = mon.grd * 5 * 1.6;   //120
			mon.def = mon.grd * 3 * 1.5;   //68
			mon.exp = (4 * mon.grd) * 4;
			mon.mny = mon.grd * 2;
			mon.out[0].nam = '*';
			mon.oequ[0].rank = 'B';
			mon = Out(mon,0);
			mon.out[1].nam = '%';
			strcpy(mon.out[1].name,"中级恢复药水");
		    mon.out[1].q = 1;
			mon.out[2].nam = 'a';
			strcpy(mon.out[2].name,"青铜");
		    mon.out[2].q = 1;
			return mon;
		}
		if (a>75&&a<=95)
		{
			strcpy(mon.name,"鬼僵尸");
			mon.grd = 13;
			mon.HP = mon.grd * 30;
			mon.atc = mon.grd * 4.7 * 1.5;
			mon.def = mon.grd * 3 * 1.4;
			mon.exp = (4 * mon.grd) * 2;
			mon.mny = mon.grd;
			mon.out[0].nam = '*';
			mon.oequ[0].rank = 'C';
			mon = Out(mon,0);
			if(a>80)
			{
			  mon.out[1].nam = '#';
			  strcpy(mon.out[1].name,"低级恢复药水");
		      mon.out[1].q = 1;
			  a = 21 + rand()%5;
			  if(a==23)
			  {
			   mon.out[2].nam = 'a';
			   strcpy(mon.out[2].name,"青铜");
		       mon.out[2].q = 1;
			  }
			}
			else
			{
			  a = 21 + rand()%5;
			  if(a==23)
			  {
			   mon.out[1].nam = 'a';
			   strcpy(mon.out[1].name,"青铜");
		       mon.out[1].q = 1;
			  }
			}
			return mon;
		}
	}
	if(strcmp(cha.v,"蜈蚣洞")==0)
	{
	 a = 1 + rand()%100;
	 if(a<=50)
		{
		 strcpy(mon.name,"蜈蚣精");
		 mon.grd = 17;
		 mon.HP = mon.grd * 15;
		 mon.atc = mon.grd * 5.3;
		 mon.def = mon.grd * 3.4;
		 mon.exp = mon.grd * 4;
		 mon.mny = mon.grd-5;
		 return mon;
		}
        if(a>50&&a<=90)
		{
		 strcpy(mon.name,"蛾蛆");
		 mon.grd = 19;
		 mon.HP = mon.grd * 18;
		 mon.atc = mon.grd * 5.4;
		 mon.def = mon.grd * 3.5;
		 mon.exp = mon.grd * 4;
		 mon.mny = mon.grd-5;
		 a = 21 + rand()%5;
	     if(a==24)
		 {
		  mon.out[0].nam = '*';
	      mon.oequ[0].rank = 'C';
		  mon = Out(mon,0);
		 }
		 return mon;
		}
		if (a>90)
		{
			strcpy(mon.name,"蝎子");
			mon.grd = 19;
			mon.HP = mon.grd * 30;
			mon.atc = mon.grd * 4.7 * 1.4;
			mon.def = mon.grd * 3 * 1.3;
			mon.exp = (4 * mon.grd) * 2;
			mon.mny = mon.grd * 2;
			mon.out[0].nam = '*';
			mon.oequ[0].rank = 'B';
			mon = Out(mon,0);
			mon.out[1].nam = '#';
			strcpy(mon.out[1].name,"低级恢复药水");
		    mon.out[1].q = 1;
			a = 21 + rand()%5;
			if(a==23)
			{
			  mon.out[2].nam = 'b';
			  strcpy(mon.out[2].name,"沃玛宝石");
		      mon.out[2].q = 1;
			}
			return mon;
		}
	}
	if(strcmp(cha.v,"石窟")==0)
	{
	 a = 1 + rand()%100;
	 if(a<=45)
		{
		 strcpy(mon.name,"山洞蝙蝠");
		 mon.grd = 21;
		 mon.HP = mon.grd * 15;
		 mon.atc = mon.grd * 5.3;
		 mon.def = mon.grd * 3.4;
		 mon.exp = mon.grd * 4;
		 mon.mny = mon.grd-10;
		 a = 21 + rand()%20;
		 if(a==34)
		 {
		  mon.out[0].nam = 'b';
		  strcpy(mon.out[0].name,"沃玛宝石");
		  mon.out[0].q = 1;
		 }
		 if(a==28)
		 {
		  mon.grd = 20;
		  mon.out[0].nam = '*';
		  mon.oequ[0].rank = 'A';
		  mon = Out(mon,0);
		 }
		 return mon;
		}
        if(a>45&&a<=85)
		{
		 strcpy(mon.name,"骷髅");
		 mon.grd = 23;
		 mon.HP = mon.grd * 18;
		 mon.atc = mon.grd * 5.5;
		 mon.def = mon.grd * 3.5;
		 mon.exp = mon.grd * 4;
		 mon.mny = mon.grd-5;
		 a = 21 + rand()%15;
	     if(a==26)
		 {
		  mon.out[0].nam = 'b';
		  strcpy(mon.out[0].name,"沃玛宝石");
		  mon.out[0].q = 1;
		 }
		 if(a==28)
		 {
		  mon.grd = 20;
		  mon.out[0].nam = '*';
		  mon.oequ[0].rank = 'A';
		  mon = Out(mon,0);
		 }
		 return mon;
		}
		if (a>85&&a<=95)
		{
			strcpy(mon.name,"骷髅战将");
			mon.grd = 21;
			mon.HP = mon.grd * 30;
			mon.atc = mon.grd * 4.7 * 1.3;
			mon.def = mon.grd * 3 * 1.3;
			mon.exp = (4 * mon.grd) * 2;
			mon.mny = mon.grd * 2;
			mon.out[0].nam = '*';
			mon.oequ[0].rank = 'C';
			mon = Out(mon,0);
			mon.out[1].nam = '#';
			strcpy(mon.out[1].name,"低级恢复药水");
		    mon.out[1].q = 1;
			a = 21 + rand()%10;
			if(a==23||a==27)
			{
			  mon.out[2].nam = 'b';
			  strcpy(mon.out[2].name,"沃玛宝石");
		      mon.out[2].q = 1;
			}
			return mon;
		}
		if (a>95)
		{
		   a = 1 + rand()%10;
		   if(a<=8)
		   {
		    strcpy(mon.name,"骷髅精灵");
			mon.grd = 24;
			mon.HP = mon.grd * 40;
			mon.atc = mon.grd * 4.7 * 1.5;
			mon.def = mon.grd * 3 * 1.4;
			mon.exp = (4 * mon.grd) * 3;
			mon.mny = mon.grd * 2;
			mon.out[0].nam = '*';
			mon.oequ[0].rank = 'B';
			mon = Out(mon,0);
			mon.out[1].nam = '#';
			strcpy(mon.out[1].name,"低级恢复药水");
		    mon.out[1].q = 1;
			a = 21 + rand()%4;
			if(a==23)
			{
			  mon.out[2].nam = 'b';
			  strcpy(mon.out[2].name,"沃玛宝石");
		      mon.out[2].q = 1;
			}
			return mon;
		   }
		   else
		   {
		    strcpy(mon.name,"沃玛教主");
			mon.grd = 25;
			mon.HP = mon.grd * 50 + 50;
			mon.atc = mon.grd * 5 * 1.6;
			mon.def = mon.grd * 3 * 1.5;
			mon.exp = (4 * mon.grd) * 4;
			mon.mny = mon.grd * 3;
			mon.out[0].nam = 'b';
			strcpy(mon.out[0].name,"沃玛宝石");
		    mon.out[0].q = 1;
			mon.out[1].nam = '%';
			strcpy(mon.out[1].name,"中级恢复药水");
		    mon.out[1].q = 1;
			a = 21 + rand()%3;
			if(a==23)
			{
			mon.out[2].nam = '*';
			mon.oequ[2].rank = 'A';
			mon = Out(mon,0);
			}
			return mon;
		   }
		}
	}
	if(strcmp(cha.v,"野猪洞")==0)
	{
	 a = 1 + rand()%100;
	 if(a<=45)
		{
		 strcpy(mon.name,"蝎蛇");
		 mon.grd = 28;
		 mon.HP = mon.grd * 15;
		 mon.atc = mon.grd * 5.3;
		 mon.def = mon.grd * 3.4;
		 mon.exp = mon.grd * 4;
		 mon.mny = mon.grd-10;
		 a = 21 + rand()%5;
		 if(a==23)
		 {
		  mon.out[0].nam = '*';
		  mon.oequ[0].rank = 'C';
		  mon = Out(mon,0);
		 }
		 return mon;
		}
        if(a>45&&a<=85)
		{
		 strcpy(mon.name,"黑野猪");
		 mon.grd = 30;
		 mon.HP = mon.grd * 18;
		 mon.atc = mon.grd * 5.5;
		 mon.def = mon.grd * 3.5;
		 mon.exp = mon.grd * 4;
		 mon.mny = mon.grd-5;
		 a = 21 + rand()%5;
		 if(a==23)
		 {
		  mon.out[0].nam = '*';
		  mon.oequ[0].rank = 'B';
		  mon = Out(mon,0);
		 }
		 return mon;
		}
		if(a>85)
		{
			strcpy(mon.name,"白野猪");
			mon.grd = 32;
			mon.HP = mon.grd * 40;
			mon.atc = mon.grd * 4.7 * 1.5;
			mon.def = mon.grd * 3 * 1.4;
			mon.exp = (4 * mon.grd) * 2;
			mon.mny = mon.grd * 2;
			mon.out[0].nam = '#';
			strcpy(mon.out[0].name,"低级恢复药水");
		    mon.out[0].q = 1;
			a = 21 + rand()%5;
			if(a==22)
			{
			 mon.out[1].nam = '*';
			 mon.oequ[1].rank = 'A';
			 mon = Out(mon,0);
			}
			return mon;
		}
	}
	if(strcmp(cha.v,"封魔谷")==0)
	{
	 a = 1 + rand()%100;
	 if(a<=45)
		{
		 strcpy(mon.name,"暗黑战士");
		 if(a<=30)
		 {
		  mon.grd = 34;
		 }
		 else
		 {
		  mon.grd = 36;
		 }
		 mon.HP = mon.grd * 15;
		 mon.atc = mon.grd * 5.3;
		 mon.def = mon.grd * 3.4;
		 mon.exp = mon.grd * 4;
		 mon.mny = mon.grd-10;
		 a = 21 + rand()%5;
		 if(a==23)
		 {
		  mon.out[0].nam = '*';
		  mon.oequ[0].rank = 'C';
		  mon = Out(mon,0);
		 }
		 return mon;
		}
        if(a>45&&a<=85)
		{
		 strcpy(mon.name,"幽魂");
		 if(a<=73)
		 {
		  mon.grd = 36;
		 }
		 else
		 {
		  mon.grd = 38;
		 }
		 mon.HP = mon.grd * 18;
		 mon.atc = mon.grd * 5.5;
		 mon.def = mon.grd * 3.5;
		 mon.exp = mon.grd * 4;
		 mon.mny = mon.grd-5;
		 a = 21 + rand()%5;
		 if(a==23)
		 {
		  mon.out[0].nam = '*';
		  mon.oequ[0].rank = 'B';
		  mon = Out(mon,0);
		 }
		 return mon;
		}
		if(a>85&&a<=95)
		{
			strcpy(mon.name,"触龙神");
			mon.grd = 38;
			mon.HP = mon.grd * 40;
			mon.atc = mon.grd * 4.7 * 1.5;
			mon.def = mon.grd * 3 * 1.4;
			mon.exp = (4 * mon.grd) * 2;
			mon.mny = mon.grd * 2;
			mon.out[0].nam = '#';
			strcpy(mon.out[0].name,"低级恢复药水");
		    mon.out[0].q = 1;
			a = 21 + rand()%5;
			if(a==22)
			{
			 mon.out[1].nam = 'c';
			 strcpy(mon.out[1].name,"恶魔气息");
		     mon.out[1].q = 1;
			}
			return mon;
		}
		if(a>95)
		{
			strcpy(mon.name,"赤月恶魔");
			mon.grd = 40;
			mon.HP = mon.grd * 50 + 50;
			mon.atc = mon.grd * 5 * 1.6;
			mon.def = mon.grd * 3 * 1.5;
			mon.exp = (4 * mon.grd) * 4;
			mon.mny = mon.grd * 3;
			mon.out[0].nam = '%';
			strcpy(mon.out[0].name,"中级恢复药水");
		    mon.out[0].q = 2;
			a = 21 + rand()%3;
			if(a==22)
			{
			 mon.out[1].nam = 'c';
			 strcpy(mon.out[1].name,"恶魔气息");
		     mon.out[1].q = 1;
			}
			return mon;
		}
	}
	return mon;
}

struct MONSTER Monbackup(struct CHARACTER cha)
{
	struct MONSTER mon;
	for(int i=0;i<=9;i++)
	{
	  mon.out[i].nam = '\0';
	  strcpy(mon.out[i].name,"\0");
	  mon.out[i].q = 0;
	}
	if(cha.grd>=25)
	{
		strcpy(mon.name,"沃玛教主");
		mon.grd = 25;
		mon.HP = 3500;
		mon.atc = mon.grd * 5 * 1.6+15.0;
		mon.def = mon.grd * 3 * 1.5;
		mon.mny = mon.grd * 3;
		mon.exp = 0;
		if(cha.trp==0)
		{
		 mon.out[0].nam = '%';
		 strcpy(mon.out[0].name,"中级恢复药水");
		 mon.out[0].q = 1;
		}
		if(cha.trp!=0)
		{
		 mon.out[0].nam = '%';
		 strcpy(mon.out[0].name,"中级恢复药水");
		 mon.out[0].q = 3;
		 strcpy(mon.out[1].name,"25级装备强化卷轴");
		 mon.out[1].nam = '$';
		 mon.out[1].q = 1;
		}
		return mon;
	}
	return mon;
}

void SeeAbi(struct CHARACTER cha)
{
	printf("名字       %s\n",cha.name);
	printf("等级       %d\n", cha.grd);
	printf("职业       %s\n", cha.prof);
	printf("HP         %.0lf/%.0lf\n", cha.HP, cha.xHP);
	printf("MP         %.0lf/%.0lf\n", cha.MP, cha.xMP);
	printf("攻击力     %.0lf\n", cha.atc);
	printf("防御力     %.0lf\n", cha.def);
	printf("经验       %.0lf/%.0lf\n", cha.exp, cha.xexp);
	printf("确认");
	getchar();
	printf("\n");
}

struct CHARACTER SeeEqu(struct CHARACTER cha)
{
    int t = cha.n,s,n,m;
	if(t!=0)
	{
	 if(strcmp(cha.equ[t].kind,"头盔")==0)
	 {
	  s = 0;
	 }
	 if(strcmp(cha.equ[t].kind,"盔甲")==0)
	 {
	  s = 1;
	 }
	 if(strcmp(cha.equ[t].kind,"裤子")==0)
	 {
	  s = 2;
	 }
	 if(strcmp(cha.equ[t].kind,"武器")==0)
	 {
	  s = 3;
	 }
	 if(strcmp(cha.equ[t].kind,"鞋子")==0)
	 {
	  s = 4;
	 }
	 if(strcmp(cha.equ[t].kind,"戒指")==0)
	 {
	  s = 5;
	 }
	 if(strcmp(cha.equ[s].name,"\0")==0)
	 {
	  printf("   ");
	  printf("%s\n",cha.equ[t].name);
	  printf("种类:%s\n",cha.equ[t].kind);
	  printf("装备级数   %d\n",cha.equ[t].grd);
	  printf("装备级别   %c\n",cha.equ[t].rank);
	  printf("HP         +%.0lf\n", cha.equ[t].axHP);
	  printf("MP         +%.0lf\n", cha.equ[t].axMP);
	  printf("攻击力     +%.0lf\n", cha.equ[t].aatc);
	  printf("防御力     +%.0lf\n", cha.equ[t].adef);
	 }
	 else
	 {
	  printf("   ");
	  printf("%s",cha.equ[t].name);
	  printf("           |   ");
	  printf("%s\n",cha.equ[s].name);
	  printf("种类:%s             |种类:%s\n", cha.equ[t].kind,cha.equ[s].kind);
	  printf("装备级数   %d         |装备级数   %d\n", cha.equ[t].grd, cha.equ[s].grd);
	  printf("装备级别   %c          |装备级别   %c\n", cha.equ[t].rank, cha.equ[s].rank);
	  printf("HP         +%-5.0lf     |HP         +%.0lf\n", cha.equ[t].axHP, cha.equ[s].axHP);
	  printf("MP         +%-5.0lf     |MP         +%.0lf\n", cha.equ[t].axMP, cha.equ[s].axMP);
	  printf("攻击力     +%-5.0lf     |攻击力     +%.0lf\n", cha.equ[t].aatc, cha.equ[s].aatc);
	  printf("防御力     +%-5.0lf     |防御力     +%.0lf\n", cha.equ[t].adef, cha.equ[s].adef);
	 }
	}
	if(t==0)
	{
	  int i=0;
      while(i==0)
	  {
		  printf("      1.%c\n\n",cha.equ[0].rank);
		  printf("2.%c          6.%c\n\n",cha.equ[1].rank,cha.equ[5].rank);
		  printf("3.%c          7.%c\n\n",cha.equ[2].rank,cha.equ[6].rank);
		  printf("4.%c   5.%c\n",cha.equ[3].rank,cha.equ[4].rank);
		  printf("请选择");
		  scanf("%d",&s);
		  getchar();
		  if(s!=1&&s!=2&&s!=3&&s!=4&&s!=5&&s!=6&&s!=7)
		  {
			  return cha;
		  }
		  s--;
		  if(strcmp(cha.equ[s].name,"\0")==0)
		  {
			  printf("无装备\n");
			  printf("确认");
			  getchar();
			  printf("\n");
		  }
		  if(strcmp(cha.equ[s].name,"\0")!=0)
		  {
			  printf("   ");
			  printf("%s\n",cha.equ[s].name);
			  printf("种类:%s\n", cha.equ[s].kind);
			  printf("装备级数   %d\n", cha.equ[s].grd);
			  printf("装备级别   %c\n", cha.equ[s].rank);
			  printf("HP         +%.0lf\n", cha.equ[s].axHP);
			  printf("MP         +%.0lf\n", cha.equ[s].axMP);
			  printf("攻击力     +%.0lf\n", cha.equ[s].aatc);
			  printf("防御力     +%.0lf\n", cha.equ[s].adef);
			  printf("1.确认  2.卸下装备\n");
			  printf("请选择");
			  scanf("%d",&t);
			  getchar();
			  if(t==2)
			  {
				  n = cha.e;
				  m = cha.t;
				  if(m==17)
				  {
					  printf("背包空间不足\n");
					  printf("确认");
					  getchar();
					  return cha;
				  }
				  cha.equ[n] = cha.equ[s];
				  strcpy(cha.equ[s].name,"\0");
				  strcpy(cha.equ[s].kind,"\0");
				  cha.equ[s].grd = 0;
				  cha.equ[s].rank = ' ';
				  cha.equ[s].axHP = 0;
				  cha.equ[s].axMP = 0;
				  cha.equ[s].aatc = 0;
				  cha.equ[s].adef = 0;
				  cha.goods[m].nam = '*';
				  if(cha.HP>cha.xHP-cha.equ[n].axHP)
				  {
					  cha.HP = cha.xHP-cha.equ[n].axHP;
				  }
				  cha.xHP = cha.xHP-cha.equ[n].axHP;
				  if(cha.MP>cha.xMP-cha.equ[n].axMP)
				  {
					  cha.MP = cha.xMP-cha.equ[n].axMP;
				  }
				  cha.xMP = cha.xMP-cha.equ[n].axMP;
				  cha.atc = cha.atc-cha.equ[n].aatc;
				  cha.def = cha.def-cha.equ[n].adef;
				  if(cha.equ[0].rank==' '&&cha.equ[1].rank==' '&&cha.equ[2].rank==' '&&cha.equ[3].rank==' '&&
					  cha.equ[4].rank==' '&&cha.equ[5].rank==' '&&cha.equ[6].rank==' ')
				  {
					  if(strcmp(cha.prof,"战士")==0)
					  {
						  cha.xHP=cha.grd*19;
						  cha.HP=cha.xHP;
						  cha.xMP=cha.grd*3;
						  cha.MP=cha.xMP;
						  cha.atc=cha.grd*5;
						  cha.def=cha.grd*3;
					  }
					  if(strcmp(cha.prof,"法师")==0)
					  {
						  cha.xHP=cha.grd*5;
						  cha.HP=cha.xHP;
						  cha.xMP=cha.grd*20;
						  cha.MP=cha.xMP;
						  cha.atc=cha.grd*2;
						  cha.def=cha.grd*3;
					  }
					  if(strcmp(cha.prof,"道士")==0)
					  {
						  cha.xHP=cha.grd*12;
						  cha.HP=cha.xHP;
						  cha.xMP=cha.grd*11;
						  cha.MP=cha.xMP;
						  cha.atc=cha.grd*3.5;
						  cha.def=cha.grd*3;
					  }
				  }
				  cha.e+=1;
				  cha.t+=1;
			  }
			  printf("\n");
		  }
      }
    }
	return cha;
}

void SeeGood(struct CHARACTER cha)
{
    int m;
    m = cha.m;
	if(m==-1)
	{
	 printf("效果   增加HP100%%\n");
	 printf("       增加MP100%%\n");
	}
    if(cha.goods[m].nam=='#')
	{
	  printf("    %s\n",cha.goods[m].name);
      printf("效果   增加HP30%%\n");
	  printf("       增加MP30%%\n");
    }
    if(cha.goods[m].nam=='%')
    {
	  printf("    %s\n",cha.goods[m].name);
      printf("效果   增加HP50%%\n");
	  printf("       增加MP50%%\n");
    }
    if(cha.goods[m].nam=='@')
    {
	  printf("    %s\n",cha.goods[m].name);
      printf("效果   增加HP100%%\n");
	  printf("       增加MP100%%\n");
    }
	if(cha.goods[m].nam=='a')
	{
	  printf("    %s\n",cha.goods[m].name);
	  printf("用来制作青铜套装的材料。\n");
	}
	if(cha.goods[m].nam=='b')
	{
	  printf("    %s\n",cha.goods[m].name);
	  printf("用来制作沃玛套装的材料。\n");
	}
	if(cha.goods[m].nam=='$')
	{
	  printf("    %s\n",cha.goods[m].name);
	  printf("可强化25级以下的装备。成长值为50%%\n");
	  printf("强化过的装备不可再次强化。\n");
	}
	if(cha.goods[m].nam=='c')
	{
	  printf("    %s\n",cha.goods[m].name);
	  printf("用来制作恶魔套装的材料。\n");
	}
}

struct CHARACTER EquAtt(struct CHARACTER cha)
{
	int s;
	double t;
	s = cha.e-1;
	if (cha.equ[s].rank == 'A')
	{
        t = 0.5;
	}
	if (cha.equ[s].rank == 'B')
	{
	    t = 0.4;
	}
	if (cha.equ[s].rank == 'C')
	{
	    t = 0.3;
	}
	if (cha.equ[s].rank == 'D')
	{
	    t = 0.15;
	}
	if(strcmp(cha.prof,"战士")==0)
	{
	if(strcmp(cha.equ[s].kind,"武器")==0)
	{
		cha.equ[s].axHP = 0;
		cha.equ[s].axMP = 0;
		cha.equ[s].aatc = cha.equ[s].grd*5*t*0.684;
		cha.equ[s].adef = cha.equ[s].grd*3*t*0.087;
	}
	if(strcmp(cha.equ[s].kind,"戒指")==0)
	{
		cha.equ[s].axHP = cha.equ[s].grd*19*t*0.14;
		cha.equ[s].axMP = cha.equ[s].grd*3*t*0.14;
	    cha.equ[s].aatc = cha.equ[s].grd*5*t*0.158;
		cha.equ[s].adef = 0;
	}
	if(strcmp(cha.equ[s].kind,"盔甲")==0)
	{
	    cha.equ[s].axHP = cha.equ[s].grd*19*t*0.3;
		cha.equ[s].axMP = cha.equ[s].grd*3*t*0.3;
		cha.equ[s].aatc = 0;
		cha.equ[s].adef = cha.equ[s].grd*3*t*0.391;
	}
	if(strcmp(cha.equ[s].kind,"头盔")==0||strcmp(cha.equ[s].kind,"裤子")==0||strcmp(cha.equ[s].kind,"鞋子")==0)
	{
	    cha.equ[s].axHP = cha.equ[s].grd*19*t*0.14;
		cha.equ[s].axMP = cha.equ[s].grd*3*t*0.14;
		cha.equ[s].aatc = 0;
		cha.equ[s].adef = cha.equ[s].grd*3*t*0.174;
	}
	}
	if(strcmp(cha.prof,"法师")==0)
	{
	if(strcmp(cha.equ[s].kind,"武器")==0)
	{
		cha.equ[s].axHP = 0;
		cha.equ[s].axMP = 0;
		cha.equ[s].aatc = cha.equ[s].grd*2*t*0.684;
		cha.equ[s].adef = cha.equ[s].grd*3*t*0.087;
	}
	if(strcmp(cha.equ[s].kind,"戒指")==0)
	{
		cha.equ[s].axHP = cha.equ[s].grd*5*t*0.14;
		cha.equ[s].axMP = cha.equ[s].grd*20*t*0.14;
	    cha.equ[s].aatc = cha.equ[s].grd*2*t*0.158;
		cha.equ[s].adef = 0;
	}
	if(strcmp(cha.equ[s].kind,"盔甲")==0)
	{
	    cha.equ[s].axHP = cha.equ[s].grd*5*t*0.3;
		cha.equ[s].axMP = cha.equ[s].grd*20*t*0.3;
		cha.equ[s].aatc = 0;
		cha.equ[s].adef = cha.equ[s].grd*3*t*0.391;
	}
	if(strcmp(cha.equ[s].kind,"头盔")==0||strcmp(cha.equ[s].kind,"裤子")==0||strcmp(cha.equ[s].kind,"鞋子")==0)
	{
	    cha.equ[s].axHP = cha.equ[s].grd*5*t*0.14;
		cha.equ[s].axMP = cha.equ[s].grd*20*t*0.14;
		cha.equ[s].aatc = 0;
		cha.equ[s].adef = cha.equ[s].grd*3*t*0.174;
	}
	}
	if(strcmp(cha.prof,"道士")==0)
	{
	if(strcmp(cha.equ[s].kind,"武器")==0)
	{
		cha.equ[s].axHP = 0;
		cha.equ[s].axMP = 0;
		cha.equ[s].aatc = cha.equ[s].grd*3.5*t*0.684;
		cha.equ[s].adef = cha.equ[s].grd*3*t*0.087;
	}
	if(strcmp(cha.equ[s].kind,"戒指")==0)
	{
		cha.equ[s].axHP = cha.equ[s].grd*12*t*0.14;
		cha.equ[s].axMP = cha.equ[s].grd*11*t*0.14;
	    cha.equ[s].aatc = cha.equ[s].grd*3.5*t*0.158;
		cha.equ[s].adef = 0;
	}
	if(strcmp(cha.equ[s].kind,"盔甲")==0)
	{
	    cha.equ[s].axHP = cha.equ[s].grd*12*t*0.3;
		cha.equ[s].axMP = cha.equ[s].grd*11*t*0.3;
		cha.equ[s].aatc = 0;
		cha.equ[s].adef = cha.equ[s].grd*3*t*0.391;
	}
	if(strcmp(cha.equ[s].kind,"头盔")==0||strcmp(cha.equ[s].kind,"裤子")==0||strcmp(cha.equ[s].kind,"鞋子")==0)
	{
	    cha.equ[s].axHP = cha.equ[s].grd*12*t*0.14;
		cha.equ[s].axMP = cha.equ[s].grd*11*t*0.14;
		cha.equ[s].aatc = 0;
		cha.equ[s].adef = cha.equ[s].grd*3*t*0.174;
	}
	}
	cha.n = s;
	cha = Equname(cha);
	return cha;
}

struct CHARACTER Equip(struct CHARACTER cha)
{
    int n=cha.n,m=cha.m,t;
    struct EQUIPMENT p;
	if(cha.grd<cha.equ[n].grd)
	{
	    printf("装备等级过高\n");
		return cha;
	}
	if(strcmp(cha.equ[n].kind,"头盔")==0)
	{
	 t = 0;
	}
	if(strcmp(cha.equ[n].kind,"盔甲")==0)
	{
	 t = 1;
	}
	if(strcmp(cha.equ[n].kind,"裤子")==0)
	{
	 t = 2;
	}
	if(strcmp(cha.equ[n].kind,"武器")==0)
	{
	 t = 3;
	}
	if(strcmp(cha.equ[n].kind,"鞋子")==0)
	{
	 t = 4;
	}
	if(strcmp(cha.equ[n].kind,"戒指")==0)
	{
	 t = 5;
	 if(cha.equ[t].rank!=' ')
	 {
	  t = 6;
	  if(cha.equ[t].rank!=' ')
	  {
	   t = 5;
	  }
	 }
	}
	if (cha.equ[t].rank != ' ')
	{
		if (cha.HP >= cha.xHP - cha.equ[t].axHP)
		{
			cha.HP = cha.xHP-cha.equ[t].axHP+cha.equ[n].axHP;
		}
		cha.xHP = cha.xHP-cha.equ[t].axHP+cha.equ[n].axHP;
		if (cha.MP >= cha.xMP - cha.equ[t].axMP)
		{
			cha.MP = cha.xMP-cha.equ[t].axMP+cha.equ[n].axMP;
		}
		cha.xMP = cha.xMP-cha.equ[t].axMP+cha.equ[n].axMP;
		cha.atc = cha.atc-cha.equ[t].aatc+cha.equ[n].aatc;
		cha.def = cha.def-cha.equ[t].adef+cha.equ[n].adef;
		p = cha.equ[t];
		cha.equ[t] = cha.equ[n];
		cha.equ[n] = p;
	}
	if (cha.equ[t].rank == ' ')
	{
	    p = cha.equ[t];
	    cha.equ[t] = cha.equ[n];
	    while(n<=cha.e-2)
	    {
	      cha.equ[n] = cha.equ[n+1];
	      n++;
	     }
	    cha.equ[cha.e-1] = p;
	    while(m<=cha.t-2)
	    {
	      cha.goods[m] = cha.goods[m+1];
	      m++;
	     }
	    cha.goods[cha.t-1].nam = '\0';
	    cha.t -= 1;
	    cha.e -= 1;
		if (cha.HP == cha.xHP)
		{
			cha.HP = cha.HP+cha.equ[t].axHP;
		}
		cha.xHP = cha.xHP+cha.equ[t].axHP;
		if (cha.MP == cha.xMP)
		{
			cha.MP = cha.MP+cha.equ[t].axMP;
		}
		cha.xMP = cha.xMP+cha.equ[t].axMP;
		cha.atc = cha.atc+cha.equ[t].aatc;
		cha.def = cha.def+cha.equ[t].adef;
	}
	return cha;
}

struct CHARACTER MakeEqu(struct CHARACTER cha)
{
 printf("1.(15Lv)青铜套装\n");
 printf("2.(25Lv)沃玛套装\n");
 printf("3.(40Lv)恶魔套装\n");
 int m,n,a,t,e,i;
 t = cha.t-1;
 e = cha.e;
 printf("请选择");
 scanf("%d",&m);
 getchar();
 if(m==1)
 {
  printf("1.青铜头盔\n");
  printf("2.青铜盔甲\n");
  printf("3.青铜裤\n");
  printf("4.青铜剑\n");
  printf("5.青铜鞋\n");
  printf("6.古铜戒指\n");
  printf("请选择");
  scanf("%d",&n);
  getchar();
  i=0;
  while(i<=t)
  {
	  if(cha.goods[i].nam=='a')
	  {
		  break;
	  }
	  i++;
  }
  if(n==1||n==3||n==5)
  {
   printf("需要2块青铜\n");
   printf("手续费8金币\n");
   printf("1.确定  2.不做了\n");
   printf("请选择");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-2<0||i==cha.t)
	{
	 printf("青铜不够\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("背包空间不足\n");
	  return cha;
	}
	if(cha.mny<8)
	{
	 printf("金币不足\n");
	 return cha;
	}
	cha.mny -= 8;
	if(cha.goods[i].q==2)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>2)
	{
	 cha.goods[i].q -= 2;
	}
	if(n==1)
	{
	 printf("获得青铜头盔\n");
	 strcpy(cha.equ[e].kind,"头盔");
	}
	if(n==3)
	{
	 printf("获得青铜裤\n");
	 strcpy(cha.equ[e].kind,"裤子");
	}
	if(n==5)
	{
	 printf("获得青铜鞋\n");
	 strcpy(cha.equ[e].kind,"鞋子");
	}
	cha.goods[t+1].nam = '*';
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 15;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
  if(n==2)
  {
   printf("需要8块青铜\n");
   printf("手续费32金币\n");
   printf("1.确定  2.不做了\n");
   printf("请选择");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-8<0||i==cha.t)
	{
	 printf("青铜不够\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("背包空间不足\n");
	  return cha;
	}
	if(cha.mny<32)
	{
	 printf("金币不足\n");
	 return cha;
	}
	cha.mny -= 32;
	if(cha.goods[i].q==8)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>8)
	{
	 cha.goods[i].q -= 8;
	}
	printf("获得青铜盔甲\n");
	cha.goods[t+1].nam = '*';
	strcpy(cha.equ[e].kind,"盔甲");
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 15;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
  if(n==4)
  {
   printf("需要12块青铜\n");
   printf("手续费48金币\n");
   printf("1.确定  2.不做了\n");
   printf("请选择");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-12<0||i==cha.t)
	{
	 printf("青铜不够\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("背包空间不足\n");
	  return cha;
	}
	if(cha.mny<48)
	{
	 printf("金币不足\n");
	 return cha;
	}
	cha.mny -= 48;
	if(cha.goods[i].q==12)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>12)
	{
	 cha.goods[i].q -= 12;
	}
	printf("获得青铜剑\n");
	cha.goods[t+1].nam = '*';
	strcpy(cha.equ[e].kind,"武器");
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 15;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
   if(n==6)
  {
   printf("需要4块青铜\n");
   printf("手续费16金币\n");
   printf("1.确定  2.不做了\n");
   printf("请选择");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-4<0||i==cha.t)
	{
	 printf("青铜不够\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("背包空间不足\n");
	  return cha;
	}
	if(cha.mny<16)
	{
	 printf("金币不足\n\n");
	 return cha;
	}
	cha.mny -= 16;
	if(cha.goods[i].q==4)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>4)
	{
	 cha.goods[i].q -= 4;
	}
	printf("获得古铜戒指\n");
	cha.goods[t+1].nam = '*';
	strcpy(cha.equ[e].kind,"戒指");
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 15;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
 }
 if(m==2)
 {
  printf("1.沃玛头盔\n");
  printf("2.沃玛盔甲\n");
  printf("3.沃玛裤\n");
  printf("4.半月弯刀\n");
  printf("5.沃玛鞋\n");
  printf("6.水晶戒指\n");
  printf("请选择");
  scanf("%d",&n);
  getchar();
  i=0;
  while(i<=t)
  {
	  if(cha.goods[i].nam=='b')
	  {
		  break;
	  }
	  i++;
  }
  if(n==1||n==3||n==5)
  {
   printf("需要2块沃玛宝石\n");
   printf("手续费14金币\n");
   printf("1.确定  2.不做了\n");
   printf("请选择");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-2<0||i==cha.t)
	{
	 printf("沃玛宝石不够\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("背包空间不足\n");
	  return cha;
	}
	if(cha.mny<14)
	{
	 printf("金币不足\n");
	 return cha;
	}
	cha.mny -= 14;
	if(cha.goods[i].q==2)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>2)
	{
	 cha.goods[i].q -= 2;
	}
	if(n==1)
	{
	 printf("获得沃玛头盔\n");
	 strcpy(cha.equ[e].kind,"头盔");
	}
	if(n==3)
	{
	 printf("获得沃玛裤\n");
	 strcpy(cha.equ[e].kind,"裤子");
	}
	if(n==5)
	{
	 printf("获得沃玛鞋\n");
	 strcpy(cha.equ[e].kind,"鞋子");
	}
	cha.goods[t+1].nam = '*';
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 25;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
  if(n==2)
  {
   printf("需要8块沃玛宝石\n");
   printf("手续费56金币\n");
   printf("1.确定  2.不做了\n");
   printf("请选择");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-8<0||i==cha.t)
	{
	 printf("沃玛宝石不够\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("背包空间不足\n");
	  return cha;
	}
	if(cha.mny<56)
	{
	 printf("金币不足\n");
	 return cha;
	}
	cha.mny -= 56;
	if(cha.goods[i].q==8)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>8)
	{
	 cha.goods[i].q -= 8;
	}
	printf("获得沃玛盔甲\n");
	cha.goods[t+1].nam = '*';
	strcpy(cha.equ[e].kind,"盔甲");
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 25;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
  if(n==4)
  {
   printf("需要12块沃玛宝石\n");
   printf("手续费84金币\n");
   printf("1.确定  2.不做了\n");
   printf("请选择");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-12<0||i==cha.t)
	{
	 printf("沃玛宝石不够\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("背包空间不足\n");
	  return cha;
	}
	if(cha.mny<84)
	{
	 printf("金币不足\n");
	 return cha;
	}
	cha.mny -= 84;
	if(cha.goods[i].q==12)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>12)
	{
	 cha.goods[i].q -= 12;
	}
	printf("获得半月弯刀\n");
	cha.goods[t+1].nam = '*';
	strcpy(cha.equ[e].kind,"武器");
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 25;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
   if(n==6)
  {
   printf("需要4块沃玛宝石\n");
   printf("手续费28金币\n");
   printf("1.确定  2.不做了\n");
   printf("请选择");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-4<0||i==cha.t)
	{
	 printf("沃玛宝石不够\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("背包空间不足\n");
	  return cha;
	}
	if(cha.mny<28)
	{
	 printf("金币不足\n");
	 return cha;
	}
	cha.mny -= 28;
	if(cha.goods[i].q==4)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>4)
	{
	 cha.goods[i].q -= 4;
	}
	printf("获得水晶戒指\n");
	cha.goods[t+1].nam = '*';
	strcpy(cha.equ[e].kind,"戒指");
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 25;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
 }
 if(m==3)
 {
  printf("1.恶魔头盔\n");
  printf("2.恶魔长袍\n");
  printf("3.恶魔裤\n");
  if(strcmp(cha.prof,"战士")==0)
  {
   printf("4.血饮\n");
  }
  if(strcmp(cha.prof,"法师")==0)
  {
   printf("4.噬魂法杖\n");
  }
  if(strcmp(cha.prof,"道士")==0)
  {
   printf("4.无极棍\n");
  }
  printf("5.恶魔鞋\n");
  printf("6.魔血戒指\n");
  printf("请选择");
  scanf("%d",&n);
  getchar();
  i=0;
  while(i<=t)
  {
	  if(cha.goods[i].nam=='c')
	  {
		  break;
	  }
	  i++;
  }
  if(n==1||n==3||n==5)
  {
   printf("需要2个恶魔气息\n");
   printf("手续费21金币\n");
   printf("1.确定  2.不做了\n");
   printf("请选择");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-2<0||i==cha.t)
	{
	 printf("恶魔气息不够\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("背包空间不足\n");
	  return cha;
	}
	if(cha.mny<21)
	{
	 printf("金币不足\n");
	 return cha;
	}
	cha.mny -= 21;
	if(cha.goods[i].q==2)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>2)
	{
	 cha.goods[i].q -= 2;
	}
	if(n==1)
	{
	 printf("获得恶魔头盔\n");
	 strcpy(cha.equ[e].kind,"头盔");
	}
	if(n==3)
	{
	 printf("获得恶魔裤\n");
	 strcpy(cha.equ[e].kind,"裤子");
	}
	if(n==5)
	{
	 printf("获得恶魔鞋\n");
	 strcpy(cha.equ[e].kind,"鞋子");
	}
	cha.goods[t+1].nam = '*';
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 40;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
  if(n==2)
  {
   printf("需要8个恶魔气息\n");
   printf("手续费85金币\n");
   printf("1.确定  2.不做了\n");
   printf("请选择");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-8<0||i==cha.t)
	{
	 printf("恶魔气息不够\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("背包空间不足\n");
	  return cha;
	}
	if(cha.mny<85)
	{
	 printf("金币不足\n");
	 return cha;
	}
	cha.mny -= 85;
	if(cha.goods[i].q==8)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>8)
	{
	 cha.goods[i].q -= 8;
	}
	printf("获得恶魔长袍\n");
	cha.goods[t+1].nam = '*';
	strcpy(cha.equ[e].kind,"盔甲");
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 40;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
  if(n==4)
  {
   printf("需要12个恶魔气息\n");
   printf("手续费127金币\n");
   printf("1.确定  2.不做了\n");
   printf("请选择");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-12<0||i==cha.t)
	{
	 printf("恶魔气息不够\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("背包空间不足\n");
	  return cha;
	}
	if(cha.mny<127)
	{
	 printf("金币不足\n");
	 return cha;
	}
	cha.mny -= 127;
	if(cha.goods[i].q==12)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>12)
	{
	 cha.goods[i].q -= 12;
	}
	if(strcmp(cha.prof,"战士")==0)
	{
	 printf("获得血饮\n");
	}
	if(strcmp(cha.prof,"法师")==0)
	{
	 printf("获得噬魂法杖\n");
	}
	if(strcmp(cha.prof,"道士")==0)
	{
	 printf("获得无极棍\n");
	}
	cha.goods[t+1].nam = '*';
	strcpy(cha.equ[e].kind,"武器");
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 40;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
   if(n==6)
  {
   printf("需要4个恶魔气息\n");
   printf("手续费42金币\n");
   printf("1.确定  2.不做了\n");
   printf("请选择");
   scanf("%d",&a);
   getchar();
   if(a==1)
   {
	if(cha.goods[i].q-4<0||i==cha.t)
	{
	 printf("恶魔气息不够\n");
	 return cha;
	}
	if(t==17)
	{
	  printf("背包空间不足\n");
	  return cha;
	}
	if(cha.mny<42)
	{
	 printf("金币不足\n");
	 return cha;
	}
	cha.mny -= 42;
	if(cha.goods[i].q==4)
	{
	 while(i<=t-1)
	 {
	  cha.goods[i] = cha.goods[i+1];
	  i++;
	 }
	 cha.goods[i].nam = '\0';
	 strcpy(cha.goods[i].name,"\0");
	 cha.t--;
	 t = cha.t-1;
	 cha.goods[i].q = 0;
	}
	if(cha.goods[i].q>4)
	{
	 cha.goods[i].q -= 4;
	}
	printf("获得魔血戒指\n");
	cha.goods[t+1].nam = '*';
	strcpy(cha.equ[e].kind,"戒指");
	cha.equ[e].rank = 'A';
	cha.equ[e].grd = 40;
	cha.e++;
	cha.t++;
	cha = EquAtt(cha);
   }
  }
 }     //m=3
 return cha;
}

struct CHARACTER BuyEqu(struct CHARACTER cha)
{
	printf("1.头盔  2.盔甲  3.裤子  4.武器  5.鞋子\n");
	printf("请选择");
	int n;
	scanf("%d", &n);
	getchar();
	if(n!=1&&n!=2&&n!=3&&n!=4&&n!=5)
	{
	 printf("\n");
	 return cha;
	}
	if (((n==1||n==3||n==5)&&cha.mny<cha.grd*4/17.0)||(n==2&&cha.mny<cha.grd*4/17.0*4)||
		(n==4&&cha.mny<cha.grd*4/17.0*6))
	{
		printf("金币不足\n");
		printf("确认");
		getchar();
		printf("\n");
		return cha;
	}
	else
	{
		int w,s,r;
		w = cha.t;
		if(w==17)
		{
			printf("背包空间不足\n");
			printf("\n");
			return cha;
		}
		if(n==1||n==3||n==5)
		{
		 printf("需要 %d金币\n",(int)(cha.grd*4/17.0));
		}
		if(n==2)
		{
		 printf("需要 %d金币\n",(int)(cha.grd*4/17.0*4));
		}
		if(n==4)
		{
		 printf("需要 %d金币\n",(int)(cha.grd*4/17.0*6));
		}
		printf("是否继续\n");
		printf("1.继续  2.不买了\n");
		printf("请选择");
		scanf("%d",&r);
		getchar();
		if(r!=1)
		{
			printf("\n");
			return cha;
		}
		cha.goods[w].nam = '*';
		cha.t += 1;
		s = cha.e;
		cha.equ[s].grd = cha.grd;
		if(n==1)
		{
			strcpy(cha.equ[s].kind,"头盔");
		}
		if(n==2)
		{
		    strcpy(cha.equ[s].kind,"盔甲");
		}
		if(n==3)
		{
			strcpy(cha.equ[s].kind,"裤子");
		}
		if(n==4)
		{
			strcpy(cha.equ[s].kind,"武器");
		}
		if(n==5)
		{
			strcpy(cha.equ[s].kind,"鞋子");
		}
		cha.e += 1;
		cha.equ[s].rank = 'D';
		cha = EquAtt(cha);
		if(n==1||n==3||n==5)
		{
		 cha.mny -= cha.grd*4/17.0;
		 printf("共计 %d金币\n",(int)(cha.grd*4/17.0));
		}
		if(n==2)
		{
		 cha.mny -= cha.grd*4/17.0*4;
		 printf("共计 %d金币\n",(int)(cha.grd*4/17.0*4));
		}
		if(n==4)
		{
		 cha.mny -= cha.grd*4/17.0*6;
		 printf("共计 %d金币\n",(int)(cha.grd*4/17.0*6));
		}
		printf("\n");
		return cha;
    }
}

struct CHARACTER BuyGoods(struct CHARACTER cha)
{
    printf("1.#  2.%%  3.@\n请选择");
    int n,t,w,r,i;
    scanf("%d",&n);
    getchar();
    if(n!=1&&n!=2&&n!=3)
    {
      printf("\n");
      return cha;
    }
    printf("购买数量:");
    w = cha.t;
    scanf("%d",&t);
    getchar();
    if(t<=0)
    {
      printf("\n");
	  return cha;
    }
    if((n==1&&cha.mny-cha.grd*3*t/3<0)||(n==2&&cha.mny-cha.grd*5*t/3<0)||(n==3&&cha.mny-cha.grd*10*t/3<0))
    {
      printf("金币不足\n");
      printf("确认");
      getchar();
      printf("\n");
      return cha;
    }
	if(w==17)
	{
	  printf("背包空间不足\n");
	  printf("\n");
	  return cha;
	}
	if(n==1)
	{
	 printf("需要 %d金币\n",cha.grd*3*t/3);
	}
	if(n==2)
	{
	 printf("需要 %d金币\n",cha.grd*5*t/3);
	}
	if(n==3)
	{
	 printf("需要 %d金币\n",cha.grd*10*t/3);
	}
	printf("是否继续\n");
    printf("1.继续  2.不买了\n");
	printf("请选择");
	scanf("%d",&r);
   	getchar();
	i = 0;
	if(r!=1)
	{
	 return cha;
	}
    if(n==1)
    {
	  while(i<=w-1)
	  {
	   if(cha.goods[i].nam=='#')
	   {
	    break;
	   }
	   i++;
	  }
	  if(i==w)
	  {
		strcpy(cha.goods[w].name,"低级恢复药水");
	    cha.goods[w].nam = '#';
	    cha.goods[w].q = t;
		cha.t++;
	  }
	  else
	  {
	    cha.goods[i].q += t;
	  }
	  cha.mny -= cha.grd*3*t/3;
	  printf("共计 %d金币\n",cha.grd*3*t/3);
     }
     if(n==2)
    {
	  while(i<=w-1)
	  {
	   if(cha.goods[i].nam=='%')
	   {
	    break;
	   }
	   i++;
	  }
	  if(i==w)
	  {
	    strcpy(cha.goods[w].name,"中级恢复药水");
	    cha.goods[w].nam = '%';
	    cha.goods[w].q = t;
		cha.t++;
	  }
	  else
	  {
	    cha.goods[i].q += t;
	  }
	  cha.mny -= cha.grd*5*t/3;
	  printf("共计 %d金币\n",cha.grd*5*t/3);
	 }
	 if(n==3)
    {
	  while(i<=w-1)
	  {
	   if(cha.goods[i].nam=='@')
	   {
	    break;
	   }
	   i++;
	  }
	  if(i==w)
	  {
		strcpy(cha.goods[w].name,"高级恢复药水");
	    cha.goods[w].nam = '@';
	    cha.goods[w].q = t;
		cha.t++;
	  }
	  else
	  {
	    cha.goods[i].q += t;
	  }
	  cha.mny -= cha.grd*10*t/3;
	  printf("共计 %d金币\n",cha.grd*10*t/3);
	 }
	printf("确认");
    getchar();
    printf("\n");
    return cha;
}

double GoodPrice(struct GOODS good,int grd)
{
 double mny;
 if(good.nam=='#')
 {
  mny = grd*3/3.0;
 }
 if(good.nam=='%')
 {
  mny = grd*5/3.0;
 }
 if(good.nam=='@')
 {
  mny = grd*10/3.0;
 }
 if(good.nam=='a')
 {
  mny = 15*18/17.0/2;
 }
 if(good.nam=='b')
 {
  mny = 25*18/17.0/2;
 }
 if(good.nam=='$')
 {
  mny = 2;
 }
 return mny;
}

double EquPrice(struct EQUIPMENT equ)
{
	double t,mny;
	if(strcmp(equ.kind,"头盔")==0)
	{
		t = 1/17.0;
	}
	if(strcmp(equ.kind,"盔甲")==0)
	{
		t = 4/17.0;
	}
	if(strcmp(equ.kind,"裤子")==0)
	{
		t = 1/17.0;
	}
	if(strcmp(equ.kind,"武器")==0)
	{
		t = 6/17.0;
	}
	if(strcmp(equ.kind,"鞋子")==0)
	{
		t = 1/17.0;
	}
	if(strcmp(equ.kind,"戒指")==0)
	{
		t = 2/17.0;
	}
	if(equ.rank == 'A')
	{
		mny = equ.grd*18*t;
	}
	if(equ.rank == 'B')
	{
		mny = equ.grd*12*t;
	}
	if(equ.rank == 'C')
	{
		mny = equ.grd*8*t;
	}
	if(equ.rank == 'D')
	{
		mny = equ.grd*4*t;
	}
	return mny;
}

struct CHARACTER Sell(struct CHARACTER cha)
{
    int i = 0,j = 0,n =6,s,m,w;
    double mny;
	printf("背包\n");
	while (cha.goods[i].nam != '\0'&&i<=16)
	{
	    if(cha.goods[i].nam=='*')
	    {
		  printf("%d.%c\n", i + 1, cha.goods[i].nam);
		}
		else
		{
		  printf("%d.%c×%d\n", i + 1, cha.goods[i].nam,cha.goods[i].q);
		}
		i++;
	}
	printf("请选择物品");
    scanf("%d", &i);
	getchar();
    if(cha.goods[i-1].nam == '*')
    {
        for(;j<=i-1;j++)
        {
            if(cha.goods[j].nam=='*')
            {
              n++;
            }
        }
        cha.m = i-1;
        cha.n = n;
        cha = SeeEqu(cha);
		mny = EquPrice(cha.equ[n])/2.0;
		printf("价值  %.0lf金币\n",mny);
        printf("1.卖出   2.确认\n");
        printf("请选择");
        scanf("%d",&s);
		getchar();
        if(s==1)
        {
          printf("确认");
		  getchar();
		  cha.mny += mny;
		  m = cha.m;
		  while(m<=cha.t-2)
		  {
		    cha.goods[m] = cha.goods[m+1];
		    m++;
		  }
		  cha.goods[cha.t-1].nam = '\0';
		  strcpy(cha.goods[cha.t-1].name,"\0'");
		  while(n<=cha.e-2)
		  {
			  cha.equ[n] = cha.equ[n+1];
			  n++;
		  }
		  cha.equ[cha.e-1].grd = 0;
		  strcpy(cha.equ[cha.e-1].name,"\0");
		  strcpy(cha.equ[cha.e-1].kind,"\0");
		  cha.equ[cha.e-1].rank = ' ';
		  cha.equ[cha.e-1].axHP = 0;
		  cha.equ[cha.e-1].axMP = 0;
		  cha.equ[cha.e-1].aatc = 0;
		  cha.equ[cha.e-1].adef = 0;
		  cha.t -= 1;
		  cha.e -= 1;
        }
        cha = Sell(cha);
        return cha;
    }
    if(cha.goods[i-1].nam != '*'&&cha.goods[i-1].nam!='\0')
    {
       cha.m = i-1;
       m = cha.m;
       SeeGood(cha);
	   mny = GoodPrice(cha.goods[i-1],cha.grd)/2.0;
	   if(m==-1)
	   {
	    mny = 0;
	   }
	   printf("单价  %.0lf金币\n",mny);
       printf("1.卖出    2.确认\n");
       printf("请选择");
       scanf("%d",&s);
	   getchar();
       if(s==1)
       {
         printf("卖出数目:");
         scanf("%d",&w);
		 getchar();
		 if(w<0)
		 {
		   w = 0;
		 }
		 if(w>cha.goods[i-1].q)
		 {
		  w = cha.goods[i-1].q;
		 }
		 mny = mny*w;
         printf("价值  %.0lf金币\n",mny);
         printf("确认");
		 getchar();
         cha.mny += mny;
	     cha.goods[i-1].q -= w;
		 if(cha.goods[i-1].q==0)
		 {
		   while(m<=cha.t-2)
		  {
		    cha.goods[m] = cha.goods[m+1];
		    m++;
		  }
		  cha.goods[cha.t-1].nam='\0';
		  strcpy(cha.goods[cha.t-1].name,"\0");
		  cha.t -= 1;
		 }
	   }
	   cha = Sell(cha);
	   return cha;
    }
    printf("\n");
    return cha;
}

struct CHARACTER Use(struct CHARACTER cha)
{
    int m,t;
    m = cha.m;
    t = cha.t;
    if(cha.goods[m].nam == '%')
    {
      if(cha.goods[m].q==1)
      {
        while(m<=t-2)
		  {
		    cha.goods[m] = cha.goods[m+1];
		    m++;
		  }
		  cha.goods[t-1].nam = '\0';
		  strcpy(cha.goods[t-1].name,"\0");
		  cha.t -= 1;
	  }
      cha.HP += cha.xHP*0.5;
	  cha.MP += cha.xMP*0.5;
      cha.goods[m].q -= 1;
    }
    if(cha.goods[m].nam == '#')
    {
      if(cha.goods[m].q==1)
      {
        while(m<=t-2)
		  {
		    cha.goods[m] = cha.goods[m+1];
		        m++;
		  }
		 cha.goods[t-1].nam = '\0';
		 strcpy(cha.goods[t-1].name,"\0");
		 cha.t -= 1;
	  }
      cha.HP += cha.xHP*0.3;
	  cha.MP += cha.xMP*0.3;
      cha.goods[m].q -= 1;
    }
    if(cha.goods[m].nam == '@')
    {
	  if(m<0)
	  {
	   cha.HP = cha.xHP;
	   cha.MP = cha.xMP;
	  }
	  else
	  {
       if(cha.goods[m].q==1)
       {
        while(m<=t-2)
		  {
		    cha.goods[m] = cha.goods[m+1];
		    m++;
		  }
		 cha.goods[t-1].nam = '\0';
		 strcpy(cha.goods[t-1].name,"\0");
		 cha.t -= 1;
	   }
       cha.HP = cha.xHP;
	   cha.MP = cha.xMP;
       cha.goods[m].q -= 1;
	  }
    }
    if(cha.HP>cha.xHP)
    {
      cha.HP = cha.xHP;
    }
	if(cha.MP>cha.xMP)
    {
      cha.MP = cha.xMP;
    }
    return cha;
}

struct CHARACTER UpEqu(struct CHARACTER cha)
{
	int s,t,m;
	char name[20];
	double a[4] = {1.0,1.0,1.0,1.0};
	m = cha.m;
	printf("      1.%c\n\n",cha.equ[0].rank);
	printf("2.%c          6.%c\n\n",cha.equ[1].rank,cha.equ[5].rank);
	printf("3.%c          7.%c\n\n",cha.equ[2].rank,cha.equ[6].rank);
	printf("4.%c   5.%c\n",cha.equ[3].rank,cha.equ[4].rank);
	printf("请选择");
	scanf("%d",&s);
	getchar();
	if(s!=1&&s!=2&&s!=3&&s!=4&&s!=5&&s!=6&&s!=7)
	{
	   return cha;
	}
	if(strcmp(cha.equ[s-1].name,"\0")==0)
	{
	 printf("无装备\n");
	 printf("确认");
	 getchar();
	 return cha;
	}
	if(cha.goods[m].nam=='$'&&cha.equ[s-1].grd>25)
	{
	 printf("装备等级过高\n");
	 printf("确认");
	 getchar();
	 return cha;
	}
	strcpy(name,cha.equ[s-1].name);
	name[2] = '\0';
	if(strcmp(name,"+1")==0)
	{
	 printf("该装备已强化过了\n");
	 printf("确认");
	 getchar();
	 return cha;
	}
    t = rand()%4;
	a[t] = 1.5;
	strcpy(name,"+1");
	strcat(name,cha.equ[s-1].name);
	strcpy(cha.equ[s-1].name,name);
	cha.equ[s-1].axHP *= a[0];
	cha.equ[s-1].axMP *= a[1];
	cha.equ[s-1].aatc *= a[2];
	cha.equ[s-1].adef *= a[3];
	if(t==0)
	{
	 cha.xHP += cha.equ[s-1].axHP/3.0;
	 cha.HP += cha.equ[s-1].axHP/3.0;
	 printf("增加HP%.0lf\n",cha.equ[s-1].axHP/3);
	}
	if(t==1)
	{
	 cha.xMP += cha.equ[s-1].axMP/3.0;
	 cha.MP += cha.equ[s-1].axMP/3.0;
	 printf("增加MP%.0lf\n",cha.equ[s-1].axMP/3);
	}
	if(t==2)
	{
	 cha.atc += cha.equ[s-1].aatc/3.0;
	 printf("增加攻击力%.0lf\n",cha.equ[s-1].aatc/3);
	}
	if(t==3)
	{
	 cha.def = cha.equ[s-1].adef/3.0;
	 printf("增加防御力%.0lf\n",cha.equ[s-1].adef/3);
	}
	cha.goods[m].q--;
	t = cha.t;
	if(cha.goods[m].q==0)
	{
		while(m<=t-2)
		{
			cha.goods[m] = cha.goods[m+1];
			m++;
		}
		cha.goods[t-1].nam = '\0';
		strcpy(cha.goods[t-1].name,"\0");
		cha.t -= 1;
	}
	printf("确认");
	getchar();
	return cha;
}

struct CHARACTER SeeGoods(struct CHARACTER cha)
{
	int i = 0,j = 0,n =6,t,s,m,w;

	//printf("cha.t=%d\n",cha.t);
	//printf("cha.e=%d\n",cha.e);
	cqlog(cha.t,cha.e);
	
	printf("背包\n");
	printf("金币       %.0lf\n", cha.mny);
	while (cha.goods[i].nam != '\0'&&i<=16)
	{
	    if(cha.goods[i].nam=='*')
	    {
		  printf("%d.%c\n", i + 1, cha.goods[i].nam);
		}
		else
		{
		 printf("%d.%c×%d\n", i + 1, cha.goods[i].nam,cha.goods[i].q);
		}
		i++;
	}
	printf("\n1.物品操作 2.确认\n");
	printf("请选择");
	scanf("%d", &t);
	getchar();
	if (t == 1)
	{
		printf("请选择物品");
		scanf("%d", &i);
		getchar();
        if(cha.goods[i-1].nam == '*')
        {
            for(;j<=i-1;j++)
            {
                if(cha.goods[j].nam=='*')
                {
                  n++;
                }
            }
            cha.m = i-1;       //选择的第i个物品
            cha.n = n;         //选择的第n个装备
            cha = SeeEqu(cha);
			cha.n = n;
            printf("1.装备    2.扔掉   3.确认\n");
            printf("请选择");
            scanf("%d",&s);
			getchar();
            if(s==1)
            {
              cha = Equip(cha);
              printf("确认");
		      getchar();
			  printf("\n");
            }
            if(s==2)
            {
              printf("确认");
		      getchar();
		      m = cha.m;
		      while(m<=cha.t-2)
		      {
		        cha.goods[m] = cha.goods[m+1];
		        m++;
		      }
		      cha.goods[cha.t-1].nam = '\0';
              strcpy(cha.goods[cha.t-1].name,"\0");
			  cha.goods[cha.t-1].q=0;
		      while(n<=cha.e-2)
	          {
	             cha.equ[n] = cha.equ[n+1];
	             n++;
	          }
	          cha.equ[cha.e-1].grd = 0;
			  strcpy(cha.equ[cha.e-1].name,"\0");
			  strcpy(cha.equ[cha.e-1].kind,"\0");
	          cha.equ[cha.e-1].rank = ' ';
	          cha.equ[cha.e-1].axHP = 0;
			  cha.equ[cha.e-1].axHP = 0;
	          cha.equ[cha.e-1].aatc = 0;
	          cha.equ[cha.e-1].adef = 0;
	          cha.t -= 1;
	          cha.e -= 1;
             }
            cha = SeeGoods(cha);
            return cha;
		}
        if(cha.goods[i-1].nam == '%'||cha.goods[i-1].nam == '#')
        {
           cha.m = i-1;
           m = cha.m;
           SeeGood(cha);
           printf("1.使用    2.扔掉   3.确认\n");
           printf("请选择");
           scanf("%d",&s);
		   getchar();
           if(s==1)
           {
              cha = Use(cha);
              printf("确认");
		      getchar();
           }
           if(s==2)
           {
             printf("扔掉数目:");
             scanf("%d",&w);
			 getchar();
             printf("确认");
		     getchar();
		     if(w<0)
		     {
		       w = 0;
		     }
		     cha.goods[i-1].q -= w;
		     if(cha.goods[i-1].q<=0)
		     {
		      while(m<=cha.t-2)
		      {
		        cha.goods[m] = cha.goods[m+1];
		        m++;
		      }
		      cha.goods[cha.t-1].nam='\0';
			  strcpy(cha.goods[cha.t-1].name,"\0");
		      cha.goods[cha.t-1].q = 0;
			  cha.t--;
		     }
		    }
		   cha = SeeGoods(cha);
		   return cha;
         }
        if(cha.goods[i-1].nam == '@')
        {
           cha.m = i-1;
           m = cha.m;
           SeeGood(cha);
		   if(m<0)
		   {
		    printf("1.使用    2.确认\n");
			printf("请选择");
			scanf("%d",&s);
			getchar();
			if(s==1)
            {
              cha = Use(cha);
              printf("确认");
	      	  getchar();
			}
		   }
		   else
		   {
            printf("1.使用    2.扔掉   3.确认\n");
            printf("请选择");
            scanf("%d",&s);
			getchar();
            if(s==1)
            {
              cha = Use(cha);
              printf("确认");
	      	  getchar();
            }
            if(s==2)
            {
             printf("扔掉数目:");
             scanf("%d",&w);
			 getchar();
             printf("确认");
		     getchar();
		     if(w<0)
		     {
		       w = 0;
		     }
		     cha.goods[i-1].q -= w;
		     if(cha.goods[i-1].q<=0)
		     {
		       while(m<=cha.t-2)
			   {
		        cha.goods[m] = cha.goods[m+1];
		        m++;
		       }
		      cha.goods[cha.t-1].nam='\0';
			  strcpy(cha.goods[cha.t-1].name,"\0");
		      cha.goods[cha.t-1].q = 0;
			  cha.t--;
		     }
		    }
		   }
		   cha = SeeGoods(cha);
		   return cha;
         }
		if(cha.goods[i-1].nam == 'a'||cha.goods[i-1].nam == 'b'||cha.goods[i-1].nam == 'c')
		{
		   cha.m = i-1;
           m = cha.m;
           SeeGood(cha);
           printf("1.扔掉   2.确认\n");
           printf("请选择");
           scanf("%d",&s);
		   getchar();
           if(s==1)
           {
             printf("扔掉数目:");
             scanf("%d",&w);
			 getchar();
             printf("确认");
		     getchar();
		     if(w<0)
		     {
		       w = 0;
		     }
		     cha.goods[i-1].q -= w;
		     if(cha.goods[i-1].q<=0)
		     {
		       while(m<=cha.t-2)
			   {
		        cha.goods[m] = cha.goods[m+1];
		        m++;
		       }
		      cha.goods[cha.t-1].nam='\0';
			  strcpy(cha.goods[cha.t-1].name,"\0");
		      cha.goods[cha.t-1].q = 0;
			  cha.t--;
		     }
		   }
		   cha = SeeGoods(cha);
		   return cha;
		}
		if(cha.goods[i-1].nam == '$')
        {
           cha.m = i-1;
           m = cha.m;
           SeeGood(cha);
           printf("1.使用    2.扔掉   3.确认\n");
           printf("请选择");
           scanf("%d",&s);
		   getchar();
           if(s==1)
           {
              cha = UpEqu(cha);
           }
           if(s==2)
           {
             printf("扔掉数目:");
             scanf("%d",&w);
			 getchar();
             printf("确认");
		     getchar();
		     if(w<0)
		     {
		       w = 0;
		     }
		     cha.goods[i-1].q -= w;
		     if(cha.goods[i-1].q<=0)
		     {
		       while(m<=cha.t-2)
		      {
		        cha.goods[m] = cha.goods[m+1];
		        m++;
		      }
		      cha.goods[cha.t-1].nam='\0';
			  strcpy(cha.goods[cha.t-1].name,"\0");
		      cha.goods[cha.t-1].q = 0;
			  cha.t--;
		     }
		    }
		   cha = SeeGoods(cha);
		   return cha;
         }
	}
	return cha;
}

void SeeSkill(struct CHARACTER cha)
{
 int i,t=0;
 if(strcmp(cha.prof,"法师")==0)
 {
	 while(t==0)
	 {
		 printf("1.小火球\n");
		 printf("2.雷电术\n");
		 printf("3.爆裂火焰\n");
		 printf("4.火墙\n");
		 printf("5.冰龙咆哮\n");
		 printf("6.魔力提升\n");
		 printf("7.激光电影\n");
		 printf("请选择");
		 scanf("%d",&i);
		 getchar();
		 if(i==1)
		 {
			 printf("等级 5级\n");
			 printf("消耗%.0lfMP，以魔法攻击的1.5倍攻击一个目标\n",(double)cha.grd*1.5);
			 printf("确认");
			 getchar();
			 printf("\n");
		 }
		 if(i==2)
		 {
			 printf("等级 10级\n");
			 printf("消耗%.0lfMP，以魔法攻击的1.8倍攻击一个目标\n",(double)(cha.grd)*1.8);
			 printf("确认");
			 getchar();
			 printf("\n");
		 }
		 if(i==3)
		 {
			 printf("等级 15级\n");
			 printf("消耗%.0lfMP，以魔法攻击的1.6倍攻击两个目标\n",(double)(cha.grd)*2.625);
			 printf("确认");
			 getchar();
			 printf("\n");
		 }
		 if(i==4)
		 {
			 printf("等级 20级\n");
			 printf("消耗%.0lfMP，以魔法攻击的1.6倍攻击三个目标\n",(double)(cha.grd)*3.5);
			 printf("确认");
			 getchar();
			 printf("\n");
		 }
		 if(i==5)
		 {
			 printf("等级 25级\n");
			 printf("消耗%.0lfMP，以魔法攻击的1.7倍攻击三个目标\n",(double)(cha.grd)*4.125);
			 printf("确认");
			 getchar();
			 printf("\n");
		 }
		 if(i==6)
		 {
			 printf("等级 30级\n");
			 printf("消耗%.0lfMP，提升%%50伤害\n",(double)(cha.grd)*1.5);
			 printf("确认");
			 getchar();
			 printf("\n");
		 }
		 if(i==7)
		 {
			 printf("等级 40级\n");
			 printf("消耗%.0lfMP，以魔法攻击的1.7倍攻击五个目标\n",(double)(cha.grd)*6.5);
			 printf("确认");
			 getchar();
			 printf("\n");
		 }
		 if(i!=1&&i!=2&&i!=3&&i!=4&&i!=5&&i!=6&&i!=7)
		 {
			 t = 1;
		 }
	 }
 }
 if(strcmp(cha.prof,"战士")==0)
 {
	 while(t==0)
	 {
		 printf("1.烈火剑法\n");
		 printf("2.神圣战术\n");
		 printf("3.半月弯刀\n");
		 printf("4.擒龙手\n");
		 printf("5.心灵启示\n");
		 printf("请选择");
		 scanf("%d",&i);
		 getchar();
		 if(i==1)
		 {
			 printf("等级 5级\n");
			 printf("消耗%.0lfMP，以攻击力的1.2倍攻击目标\n",(double)(cha.grd)/5.0*2.0);
			 printf("确认");
			 getchar();
			 printf("\n");
		 }
		 if(i==2)
		 {
			 printf("等级 15级\n");
			 printf("消耗%.0lfMP，以攻击力的1.4倍攻击目标\n",(double)(cha.grd)/5.0*3.0);
			 printf("确认");
			 getchar();
			 printf("\n");
		 }
		 if(i==3)
		 {
			 printf("等级 25级\n");
			 printf("消耗%dMP，为开关，开启后能攻击两个目标\n",cha.grd);
			 printf("确认");
			 getchar();
			 printf("\n");
		 }
		 if(i==4)
		 {
			 printf("等级 35级\n");
			 printf("消耗%.0lfMP，以攻击力的3倍攻击目标\n",(double)(cha.grd)/5.0*6.0);
			 printf("确认");
			 getchar();
			 printf("\n");
		 }
		 if(i==5)
		 {
			 printf("等级 40级\n");
			 printf("消耗%.0lfMP，提升%%30伤害\n",(double)(cha.grd)/5.0*3.0);
			 printf("确认");
			 getchar();
			 printf("\n");
		 }
		 if(i!=1&&i!=2&&i!=3&&i!=4&&i!=5)
		 {
			 t = 1;
		 }
	 }
 }
 if(strcmp(cha.prof,"道士")==0)
 {
	 while(t==0)
	 {
		 printf("1.召唤神兽\n");
		 printf("2.灵魂火符\n");
		 printf("3.无极真气\n");
		 printf("4.治愈术\n");
		 printf("5.圣言术\n");
		 printf("6.保护之盾\n");
		 printf("请选择");
		 scanf("%d",&i);
		 getchar();
		 if(i==1)
		 {
			 printf("等级 5级\n");
			 printf("消耗%.0lfMP，召唤出忠于自己的神兽，该神兽只能召唤一次\n",(double)(cha.grd)*2.2);
			 printf("确认");
			 getchar();
			 printf("\n");
		 }
		 if(i==2)
		 {
			 printf("等级 12级\n");
			 printf("消耗%.0lfMP，以魔法攻击的1倍攻击一个目标\n",(double)(cha.grd)*2.2);
			 printf("确认");
			 getchar();
			 printf("\n");
		 }
		 if(i==3)
		 {
			 printf("等级 18级\n");
			 printf("不消耗MP，给自己和队友恢复魔法攻击的0.5倍的MP\n");
			 printf("确认");
			 getchar();
			 printf("\n");
		 }
		 if(i==4)
		 {
			 printf("等级 25级\n");
			 printf("消耗%.0lfMP，给自己和队友恢复魔法攻击的1倍的HP，包括神兽\n",(double)(cha.atc)*1.3);
			 printf("确认");
			 getchar();
			 printf("\n");
		 }
		 if(i==5)
		 {
			 printf("等级 32级\n");
			 printf("消耗%.0lfMP，提升神兽的伤害%%30\n",(double)(cha.grd)*2.2);
			 printf("确认");
			 getchar();
			 printf("\n");
		 }
		 if(i==6)
		 {
			 printf("等级 40级\n");
			 printf("消耗%.0lfMP，生成保护之盾保护神兽\n",(double)(cha.atc)*0.75);
			 printf("确认");
			 getchar();
			 printf("\n");
		 }
		 if(i!=1&&i!=2&&i!=3&&i!=4&&i!=5&&i!=6)
		 {
			 t = 1;
		 }
	 }
 }
}

struct CHARACTER Skill(struct CHARACTER cha)
{
 int i,k;
 k = 0;
 cha.n = 0;
 if(strcmp(cha.prof,"法师")==0)
 {
  if(cha.grd>=5)
  {
   printf("1.(%.0lfMP)小火球\n",(double)cha.grd*1.5);
   k++;
  }
  if(cha.grd>=10)
  {
   printf("2.(%.0lfMP)雷电术\n",(double)(cha.grd)*1.8);
   k++;
  }
  if(cha.grd>=15)
  {
   printf("3.(%.0lfMP)爆裂火焰\n",(double)(cha.grd)*2.625);
   k++;
  }
  if(cha.grd>=20)
  {
   printf("4.(%.0lfMP)火墙\n",(double)(cha.grd)*3.5);
   k++;
  }
  if(cha.grd>=25)
  {
   printf("5.(%.0lfMP)冰龙咆哮\n",(double)(cha.grd)*4.125);
   k++;
  }
  if(cha.grd>=30)
  {
   printf("6.(%.0lfMP)魔力提升\n",(double)(cha.grd)*1.5);
   k++;
  }
  if(cha.grd>=40)
  {
   printf("7.(%.0lfMP)激光电影\n",(double)(cha.grd)*6.5);
   k++;
  }
  printf("请选择");
  scanf("%d",&i);
  getchar();
  if(i>k||i<=0)
  {
   cha.n = 2;
   return cha;
  }
  if((i==1&&cha.MP<(double)cha.grd*1.5)||(i==2&&cha.MP<(double)(cha.grd)*1.8)||(i==3&&cha.MP<(double)(cha.grd)*2.625)||
	  (i==4&&cha.MP<(double)(cha.grd)*3.5)||(i==5&&cha.MP<(double)(cha.grd)*4.125)||(i==6&&cha.MP<(double)(cha.grd)*1.5)||
	  (i==7&&cha.MP<(double)(cha.grd)*6.5))
  {
   return cha;
  }
  cha.n++;
  if(i==1)
  {
   cha.MP -= (double)cha.grd*1.5;
   cha.h = 1.5;
   cha.q = 1;
  }
  if(i==2)
  {
   cha.MP -= (double)(cha.grd)*1.8;
   cha.h = 1.8;
   cha.q = 1;
  }
  if(i==3)
  {
   cha.MP -= (double)(cha.grd)*2.625;
   cha.h = 1.6;
   cha.q = 2;
  }
  if(i==4)
  {
   cha.MP -= (double)(cha.grd)*3.5;
   cha.h = 1.6;
   cha.q = 3;
  }
  if(i==5)
  {
   cha.MP -= (double)(cha.grd)*4.125;
   cha.h = 1.7;
   cha.q = 3;
  }
  if(i==6)
  {
   if(cha.k==1.501)
   {
    cha.n = 2;
	printf("不可重复开启\n");
	printf("确认");
	getchar();
	return cha;
   }
   cha.MP -= (double)(cha.grd)*1.5;
   cha.k = 1.5;
  }
  if(i==7)
  {
   cha.MP -= (double)(cha.grd)*6.5;
   cha.h = 1.7;
   cha.q = 5;
  }
 }
 if(strcmp(cha.prof,"战士")==0)
 {
  if(cha.grd>=5)
  {
   printf("1.(%.0lfMP)烈火剑法\n",(double)(cha.grd)/5.0*2.0);
   k++;
  }
  if(cha.grd>=15)
  {
   printf("2.(%.0lfMP)神圣战术\n",(double)(cha.grd)/5.0*3.0);
   k++;
  }
  if(cha.grd>=25)
  {
   if(cha.q==1)
   {
    printf("3.(%dMP)半月弯刀(关)\n",cha.grd);
   }
   if(cha.q==2)
   {
    printf("3.(%dMP)半月弯刀(开)\n",cha.grd);
   }
   k++;
  }
  if(cha.grd>=35)
  {
   printf("4.(%.0lfMP)擒龙手\n",(double)(cha.grd)/5.0*6.0);
   k++;
  }
  if(cha.grd>=40)
  {
   printf("5.(%.0lfMP)心灵启示\n",(double)(cha.grd)/5.0*3.0);
   k++;
  }
  printf("请选择");
  scanf("%d",&i);
  getchar();
  if(i>k||i<=0)
  {
   cha.n = 2;
   return cha;
  }
  if((i==1&&cha.MP<(double)(cha.grd)/5.0*2.0)||(i==2&&cha.MP<(double)(cha.grd)/5.0*3.0)||(i==3&&cha.MP<cha.grd)||
	  (i==4&&cha.MP<(double)(cha.grd)/5.0*6.0)||(i==5&&cha.MP<(double)(cha.grd)/5.0*3.0))
  {
   return cha;
  }
  cha.n++;
  if(i==1)
  {
   cha.MP -= (double)(cha.grd)/5.0*2.0;
   cha.h = 1.2;
   cha.q = 1;
  }
  if(i==2)
  {
   cha.MP -= (double)(cha.grd)/5.0*3.0;
   cha.h = 1.4;
   cha.q = 1;
  }
  if(i==3)
  {
   cha.MP -= cha.grd;
   cha.h = 1.0;
   if(cha.q==1)
   {
    printf("已开启\n");
    cha.q = 2;
	return cha;
   }
   if(cha.q==2)
   {
    printf("已关闭\n");
    cha.q = 1;
   }
  }
  if(i==4)
  {
   cha.MP -= (double)(cha.grd)/5.0*6.0;
   cha.h = 3;
   cha.q = 1;
  }
  if(i==5)
  {
   if(cha.k==1.301)
   {
    cha.n = 2;
	printf("不可重复开启\n");
	printf("确认");
	getchar();
	return cha;
   }
   cha.MP -= (double)(cha.grd)/5.0*3.0;
   printf("已开启\n");
   cha.k = 1.3;
  }
 }
 if(strcmp(cha.prof,"道士")==0)
 {
  if(cha.grd>=5)
  {
   printf("1.(%.0lfMP)召唤神兽\n",(double)(cha.grd)*2.2);
   k++;
  }
  if(cha.grd>=12)
  {
   printf("2.(%.0lfMP)灵魂火符\n",(double)(cha.grd)*2.2);
   k++;
  }
  if(cha.grd>=18)
  {
   printf("3.(0MP)无极真气\n");
   k++;
  }
  if(cha.grd>=25)
  {
   printf("4.(%.0lfMP)治愈术\n",(double)(cha.atc)*1.3);
   k++;
  }
  if(cha.grd>=32)
  {
   printf("5.(%.0lfMP)圣言术\n",(double)(cha.grd)*2.2);
   k++;
  }
  if(cha.grd>=40)
  {
   printf("6.(%.0lfMP)保护之盾\n",(double)(cha.atc)*0.75);
   k++;
  }
  printf("请选择");
  scanf("%d",&i);
  getchar();
  if(i>k||i<=0)
  {
   cha.n = 2;
   return cha;
  }
  if((i==1&&cha.MP<(double)(cha.grd)*2.2)||(i==2&&cha.MP<(double)(cha.grd)*2.2)||
	  (i==4&&cha.MP<(double)(cha.atc)*1.3)||(i==5&&cha.MP<(double)(cha.grd)*2.2)||
	  (i==6&&cha.MP<(double)(cha.atc)*0.75))
  {
   return cha;
  }
  cha.n++;
  if(i==1)
  {
   if(cha.q==-1)
   {
    cha.n = 2;
	printf("神兽已召唤出来了\n");
	printf("确认");
	getchar();
	return cha;
   }
   if(cha.q==-2)
   {
    cha.n = 2;
	printf("神兽在一场战斗中只能召唤一次\n");
	printf("确认");
	getchar();
	return cha;
   }
   cha.MP -= (double)(cha.grd)*2.2;
   cha.h = 1.0;
   cha.q = -1;
  }
  if(i==2)
  {
   cha.MP -= (double)(cha.grd)*2.2;
   cha.h = 1.0;
   cha.q = 1;
  }
  if(i==3)
  {
   cha.h = 1.0;
   cha.q = 3;
  }
  if(i==4)
  {
   cha.MP -= (double)(cha.atc)*1.3;
   cha.h = 1.0;
   cha.q = 4;
  }
  if(i==5)
  {
   if(cha.q!=-1)
   {
    cha.n = 2;
	printf("无神兽\n");
	printf("确认");
	getchar();
	return cha;
   }
   if(cha.k==1.301)
   {
    cha.n = 2;
	printf("不可重复开启\n");
	printf("确认");
	getchar();
	return cha;
   }
   cha.MP -= (double)(cha.grd)*2.2;
   printf("已开启\n");
   cha.k = 1.3;
  }
  if(i==6)
  {
   if(cha.q!=-1)
   {
    cha.n = 2;
	printf("无神兽\n");
	printf("确认");
	getchar();
	return cha;
   }
   cha.MP -= (double)(cha.atc)*0.75;
   cha.h = 1.0;
   cha.q = 6;
  }
 }
 return cha;
}

struct CHARACTER Battle(struct CHARACTER cha, struct MONSTER mon[])
{
    int i=0,t,m,n,j,k,x;
	int y = 0;
	int g = 0,l=0;
	int wait = 0;
	double h;
	cha.k = 1;
	double a,b,c,d,e;
	char filename[100];
	double HP[3]={-1.0,-1.0,-1.0};
	double MP[3]={-1.0,-1.0,-1.0};
	int turn[3]={1,0,0};
	double anim = -1.0;          //神兽血量
	int freq = 1;                //神兽存活次数
	double ani[3]={-1.0,-1.0,-1.0};
	double mol=0;
	cha.q = 1;
	double value[6];

	FILE* f;
	if(cha.trp!=0)
	{
	 cha.HP = cha.xHP;
	 cha.MP = cha.xMP;
	 strcpy(filename,storyfolder);
	 strcat(filename,cha.trpname);
	 strcat(filename,".ys");
	 if(cha.trp==1)
	 {
	  f = fopen(filename,"wb");    //92字节
	  fwrite(&turn[0],4,1,f);
	  fwrite(&turn[1],4,1,f);
	  fwrite(&turn[2],4,1,f);
      fwrite(&cha.HP,8,1,f);
	  fwrite(&cha.MP,8,1,f);
	  fwrite(&anim,8,1,f);
	  fwrite(&HP[1],8,1,f);
	  fwrite(&MP[1],8,1,f);
	  fwrite(&ani[1],8,1,f);
	  fwrite(&HP[2],8,1,f);
	  fwrite(&MP[2],8,1,f);
	  fwrite(&ani[2],8,1,f);
	  fwrite(&mon[0].HP,8,1,f);
	  fclose(f);
	 }
	 else
	 {
	  f = fopen(filename,"rb+");
	  fseek(f,12L+(cha.trp-1)*24L,0);
	  fwrite(&cha.HP,8,1,f);
	  fwrite(&cha.MP,8,1,f);
	  fclose(f);
	 }
	 printf("请等待队友入场...\n");
	 while(i==0)
	 {
		 cha = Uptrp(cha);
		 f = fopen(filename,"rb");
		 fread(&turn[0],4,1,f);
		 fread(&turn[1],4,1,f);
		 fread(&turn[2],4,1,f);
		 fread(&HP[0],8,1,f);
		 fread(&MP[0],8,1,f);
		 fread(&ani[0],8,1,f);
		 fread(&HP[1],8,1,f);
		 fread(&MP[1],8,1,f);
		 fread(&ani[1],8,1,f);
		 if(strcmp(cha.buddy2,"\0")==0&&HP[1]==-1.0)
		 {
			 fclose(f);
			 i = 1;
		 }
		 if((strcmp(cha.buddy2,"\0")!=0&&HP[1]!=-1.0))
		 {
			 fread(&HP[2],8,1,f);
			 fread(&MP[2],8,1,f);
			 fread(&ani[2],8,1,f);
			 if((strcmp(cha.buddy3,"\0")!=0&&HP[2]!=-1.0))
			 {
				 fclose(f);
				 i = 1;
			 }
			 if((strcmp(cha.buddy3,"\0")==0&&HP[2]==-1.0))
			 {
				 fclose(f);
				 i = 1;
			 }
		 }
		 if(i==0)
		 {
			 fclose(f);
		 }
		 value[0] = HP[0];
		 value[1] = MP[0];
		 value[2] = HP[1];
		 value[3] = MP[1];
		 value[4] = HP[2];
		 value[5] = MP[2];
	 }
	}
	printf("遇到怪物\n");
	if(cha.trp==0)
	{
	 strcpy(cha.buddy1,cha.name);
     cha.buddy1[9] = '\0';
	}
	else
	{
	 cha.buddy1[9] = '\0';
	 cha.buddy2[9] = '\0';
	 cha.buddy3[9] = '\0';
	}
loop0:
	if(g==0)
	{
		printf("%9s",cha.buddy1);            //人名
		printf("%9s",cha.buddy2);
		printf("%9s",cha.buddy3);
		printf("    ");
		
		i = 0;                               //怪名
		while(i<=cha.m-1)
		{
			printf("%9s",mon[i].name);
			i++;
		}
		printf("\n");
	}
    
	if(cha.trp==0)                       //人生命值
	{
	 if(anim==-1.0)
	 {
	  printf("   %4.0lf",cha.HP);
	  printf("  ");
	 }
	 else
	 {
	  printf("%4.0lf %4.0lf",cha.HP,anim);
	 }
	 printf("         ");
	 printf("         ");
	}
	else
	{
	  if(HP[0]==-1)
	  {
	   printf("         ");
	  }
	  else
	  {
	   if(ani[0]==-1.0)
	   {
	    printf("   %4.0lf",HP[0]);
	    printf("  ");
	   }
	   else
	   {
	    printf("%4.0lf %4.0lf",HP[0],ani[0]);
	   }
	  }
	  if(HP[1]==-1)
	  {
	   printf("         ");
	  }
	  else
	  {
	   if(ani[1]==-1.0)
	   {
	    printf("   %4.0lf",HP[1]);
	    printf("  ");
	   }
	   else
	   {
	    printf("%4.0lf %4.0lf",HP[1],ani[1]);
	   }
	  }
	  if(HP[2]==-1)
	  {
	   printf("         ");
	  }
	  else
	  {
	   if(ani[2]==-1.0)
	   {
	    printf("   %4.0lf",HP[2]);
	    printf("  ");
	   }
	   else
	   {
	    printf("%4.0lf %4.0lf",HP[2],ani[2]);
	   }
	  }
	}
	printf("    ");
    
	i = 0;
	while(i<=cha.m-1)              //怪生命值
	{
	 printf("  %-4.0lf",mon[i].HP);
	 printf("   ");
	 i++;
	}
	printf("\n");
    
	if(strcmp(cha.buddy1,"\0")!=0)         //人
	{
	 if(g==0)
	 {
	  if(cha.trp==0)
	  {
		  if(anim==-1.0)
		  {
			  printf("     人  ");
		  }
		  else
		  {
			  printf(" 人   兽 ");
		  }
	  }
	  if(cha.trp!=0)
	  {
	      if(ani[0]==-1.0)
		  {
		      printf("     人  ");
		  }
		  else
		  {
			  printf(" 人   兽 ");
		  }
	  }
	 }
	 if(g==1)
	 {
	  if(cha.trp==0)
	  {
		  if(strcmp(cha.prof,"战士")==0&&cha.k!=1.3)
		  {
			  printf("         ");
		  }
		  if(strcmp(cha.prof,"战士")==0&&cha.k==1.3)
		  {
			  printf("     人  ");
		  }
		  if(strcmp(cha.prof,"法师")==0&&t==0)
		  {
			  printf("         ");
		  }
		  if(strcmp(cha.prof,"法师")==0&&t==1)
		  {
			  printf("     人  ");
		  }
		  if(strcmp(cha.prof,"道士")==0&&t==0)
		  {
			  if(anim==-1.0)
			  {
			   printf("         ");
			  }
			  else
			  {
				  if(l==0)
				  {
					  printf("      兽 ");
				  }
				  if(l==1)
				  {
					  printf(" 人      ");
				  }
			  }
		  }
		  if(strcmp(cha.prof,"道士")==0&&t==1)
		  {
			  if(cha.q==1||cha.q==-1||cha.k==1.3||cha.q==6)
			  {
			   if(anim==-1.0)
			   {
			    printf("     人  ");
			   }
			   else
			   {
			    if(l==0)
				{
				 printf(" 人   兽 ");
				}
				if(l==1)
				{
				 printf(" 人      ");
				}
			   }
			  }
			  if(cha.q==4||cha.q==3)
			  {
			   if(anim==-1.0)
			   {
			    printf("+%4.0lf人  ",a);
			   }
			   else
			   {
			    if(l==0)
				{
				 printf("+人%4.0lf兽",a);
				}
				if(l==1)
				{
				 printf(" 人      ");
				}
			   }
			  }
		  }
	  }
	  else
	  {
	   if(turn[0]==1)
	   {
	      if(strcmp(cha.prof,"战士")==0&&cha.k!=1.3)
		  {
			  printf("         ");
		  }
		  if(strcmp(cha.prof,"战士")==0&&cha.k==1.3)
		  {
			  printf("     人  ");
		  }
		  if(strcmp(cha.prof,"法师")==0&&t==0)
		  {
			  printf("         ");
		  }
		  if(strcmp(cha.prof,"法师")==0&&t==1)
		  {
			  printf("     人  ");
		  }
		  if(strcmp(cha.prof,"道士")==0&&t==0)
		  {
		      if(ani[0]==-1.0)
			  {
			   printf("         ");
			  }
			  else
			  {
				  if(l==0)
				  {
					  printf("      兽 ");
				  }
				  if(l==1)
				  {
					  printf(" 人      ");
				  }
			  }
		  }
		  if(strcmp(cha.prof,"道士")==0&&t==1)
		  {
			  if(cha.q==1||cha.q==-1||cha.k==1.3||cha.q==6)
			  {
			   if(ani[0]==-1.0)
			   {
			    printf("     人  ");
			   }
			   else
			   {
			    if(l==0)
				{
				 printf(" 人   兽 ");
				}
				if(l==1)
				{
				 printf(" 人      ");
				}
			   }
			  }
			  if(cha.q==4||cha.q==3)
			  {
			   if(ani[0]==-1.0)
			   {
			    printf("+%4.0lf人  ",a);
			   }
			   else
			   {
			    if(l==0)
				{
				 printf("+人%4.0lf兽",a);
				}
				if(l==1)
				{
				 printf(" 人      ");
				}
			   }
			  }
		  }
	   }
	   else
	   {
	      if(ani[0]==-1.0)
		  {
		      printf("     人  ");
		  }
		  else
		  {
			  printf(" 人   兽 ");
		  }
	   }
	  }
	 }
	 if(g==2)
	 {
	  if(cha.trp==0)
	  {
		  if(strcmp(cha.prof,"法师")==0&&t==1)
		  {
			  printf("     人  ");
		  }
		  else
		  {
			  if(anim==-1.0)
			  {
			   if(strcmp(cha.prof,"道士")==0&&t!=0&&cha.q!=3&&cha.q!=4&&cha.k!=1.3&&cha.q!=6)
			   {
			    printf("     人  ");
			   }
			   else
			   {
			    printf("-%-4.0lf人怪",a);
			   }
			  }
			  if(anim!=-1.0)
			  {
			   printf("-%-4.0lf兽怪",a);
			  }
		  }
	  }
	  else
	  {
	      if(turn[0]==1)
		  {
			  if(strcmp(cha.prof,"法师")==0&&t==1)
			  {
			      printf("     人  ");
			  }
			  else
			  {
				  if(ani[0]==-1.0)
				  {
					  if(strcmp(cha.prof,"道士")==0&&t!=0&&cha.q!=3&&cha.q!=4&&cha.k!=1.3&&cha.q!=6)
					  {
						  printf("     人  ");
					  }
					  else
					  {
						  printf("-%-4.0lf人怪",a);
					  }
				  }
				  if(ani[0]!=-1.0)
				  {
					  printf("-%-4.0lf兽怪",a);
				  }
			  }
		  }
		  else
		  {
			  if(ani[0]==-1.0)
			  {
				  printf("     人  ");
			  }
			  else
			  {
				  printf(" 人   兽 ");
			  }
		  }
	  }
	 }
	}

	if(strcmp(cha.buddy2,"\0")!=0)
	{
	 if(g==0)
	 {
		 if(ani[1]==-1.0)
		 {
			 printf("     人  ");
		 }
		 else
		 {
			 printf(" 人   兽 ");
		 }
	 }
	 if(g==1)
	 {
	  if(turn[1]==1)
	  {
		  if(strcmp(cha.prof,"战士")==0&&cha.k!=1.3)
		  {
			  printf("         ");
		  }
		  if(strcmp(cha.prof,"战士")==0&&cha.k==1.3)
		  {
			  printf("     人  ");
		  }
		  if(strcmp(cha.prof,"法师")==0&&t==0)
		  {
			  printf("         ");
		  }
		  if(strcmp(cha.prof,"法师")==0&&t==1)
		  {
			  printf("     人  ");
		  }
		  if(strcmp(cha.prof,"道士")==0&&t==0)
		  {
		      if(ani[1]==-1.0)
			  {
			   printf("         ");
			  }
			  else
			  {
				  if(l==0)
				  {
					  printf("      兽 ");
				  }
				  if(l==1)
				  {
					  printf(" 人      ");
				  }
			  }
		  }
		  if(strcmp(cha.prof,"道士")==0&&t==1)
		  {
			  if(cha.q==1||cha.q==-1||cha.k==1.3||cha.q==6)
			  {
			   if(ani[1]==-1.0)
			   {
			    printf("     人  ");
			   }
			   else
			   {
			    if(l==0)
				{
				 printf(" 人   兽 ");
				}
				if(l==1)
				{
				 printf(" 人      ");
				}
			   }
			  }
			  if(cha.q==4||cha.q==3)
			  {
			   if(ani[1]==-1.0)
			   {
			    printf("+%4.0lf人  ",a);
			   }
			   else
			   {
			    if(l==0)
				{
				 printf("+人%4.0lf兽",a);
				}
				if(l==1)
				{
				 printf(" 人      ");
				}
			   }
			  }
		  }
	  }
	  else
	  {
		  if(ani[1]==-1.0)
		  {
			  printf("     人  ");
		  }
		  else
		  {
			  printf(" 人   兽 ");
		  }
	  }
	 }
	 if(g==2)
	 {
		 if(turn[1]==1)
		  {
			  if(strcmp(cha.prof,"法师")==0&&t==1)
			  {
			      printf("     人  ");
			  }
			  else
			  {
				  if(ani[1]==-1.0)
				  {
					  if(strcmp(cha.prof,"道士")==0&&t!=0&&cha.q!=3&&cha.q!=4&&cha.k!=1.3&&cha.q!=6)
					  {
						  printf("     人  ");
					  }
					  else
					  {
						  printf("-%-4.0lf人怪",a);
					  }
				  }
				  if(ani[1]!=-1.0)
				  {
					  printf("-%-4.0lf兽怪",a);
				  }
			  }
		  }
		  else
		  {
			  if(ani[1]==-1.0)
			  {
				  printf("     人  ");
			  }
			  else
			  {
				  printf(" 人   兽 ");
			  }
		  }
	 }
	}
	else
	{
	 printf("         ");
	}

	if(strcmp(cha.buddy3,"\0")!=0)
	{
	 if(g==0)
	 {
		 if(ani[2]==-1.0)
		 {
			 printf("     人  ");
		 }
		 else
		 {
			 printf(" 人   兽 ");
		 }
	 }
	 if(g==1)
	 {
	  if(turn[2]==1)
	  {
		  if(strcmp(cha.prof,"战士")==0&&cha.k!=1.3)
		  {
			  printf("         ");
		  }
		  if(strcmp(cha.prof,"战士")==0&&cha.k==1.3)
		  {
			  printf("     人  ");
		  }
		  if(strcmp(cha.prof,"法师")==0&&t==0)
		  {
			  printf("         ");
		  }
		  if(strcmp(cha.prof,"法师")==0&&t==1)
		  {
			  printf("     人  ");
		  }
		  if(strcmp(cha.prof,"道士")==0&&t==0)
		  {
		      if(ani[2]==-1.0)
			  {
			   printf("         ");
			  }
			  else
			  {
				  if(l==0)
				  {
					  printf("      兽 ");
				  }
				  if(l==1)
				  {
					  printf(" 人      ");
				  }
			  }
		  }
		  if(strcmp(cha.prof,"道士")==0&&t==1)
		  {
			  if(cha.q==1||cha.q==-1||cha.k==1.3||cha.q==6)
			  {
			   if(ani[2]==-1.0)
			   {
			    printf("     人  ");
			   }
			   else
			   {
			    if(l==0)
				{
				 printf(" 人   兽 ");
				}
				if(l==1)
				{
				 printf(" 人      ");
				}
			   }
			  }
			  if(cha.q==4||cha.q==3)
			  {
			   if(ani[2]==-1.0)
			   {
			    printf("+%4.0lf人  ",a);
			   }
			   else
			   {
			    if(l==0)
				{
				 printf("+人%4.0lf兽",a);
				}
				if(l==1)
				{
				 printf(" 人      ");
				}
			   }
			  }
		  }
	  }
	  else
	  {
		  if(ani[2]==-1.0)
		  {
			  printf("     人  ");
		  }
		  else
		  {
			  printf(" 人   兽 ");
		  }
	  }
	 }
	 if(g==2)
	 {
		 if(turn[2]==1)
		  {
			  if(strcmp(cha.prof,"法师")==0&&t==1)
			  {
			      printf("     人  ");
			  }
			  else
			  {
				  if(ani[2]==-1.0)
				  {
					  if(strcmp(cha.prof,"道士")==0&&t!=0&&cha.q!=3&&cha.q!=4&&cha.k!=1.3&&cha.q!=6)
					  {
						  printf("     人  ");
					  }
					  else
					  {
						  printf("-%-4.0lf人怪",a);
					  }
				  }
				  if(ani[2]!=-1.0)
				  {
					  printf("-%-4.0lf兽怪",a);
				  }
			  }
		  }
		  else
		  {
			  if(ani[2]==-1.0)
			  {
				  printf("     人  ");
			  }
			  else
			  {
				  printf(" 人   兽 ");
			  }
		  }
	 }
	}
	else
	{
	 printf("         ");
	}
	printf("    ");

	i = 0;                            //怪
	while(i<=cha.m-1)
	{
	 if(g==1)
	 {
	     if(strcmp(cha.prof,"战士")==0&&cha.k!=1.3)
		 {
		     if(i==j-1)
			 {
			  printf("人");
			 }
			 else
			 {
			  printf("  ");
			 }
		 }
		 if(strcmp(cha.prof,"战士")==0&&cha.k==1.3)
		 {
		     printf("  ");
		 }
		 if(strcmp(cha.prof,"法师")==0&&t==0)
		 {
		     if(i==j-1)
			 {
			  printf("人");
			 }
			 else
			 {
			  printf("  ");
			 }
		 }
		 if(strcmp(cha.prof,"法师")==0&&t==1)
		 {
			 if(h==1.5&&i==j-1)
			 {
			  printf("-*");
			 }
			 if(h==1.8&&i==j-1)
			 {
			  printf("--");
			 }
			 if(h==1.6&&cha.q==2&&i==j-1)
			 {
			  printf("**");
			 }
			 if((h==1.6&&cha.q==3)||h==1.7||i!=j-1||cha.k==1.5||cha.q==5)
			 {
			  printf("  ");
			 }
		 }
		 if(strcmp(cha.prof,"道士")==0&&t==0)
		 {
			 if(anim==-1.0)
			 {
				 if(i==j-1)
				 {
					 printf("人");
				 }
				 else
				 {
					 printf("  ");
				 }
			 }
			 if(anim!=-1.0)
			 {
				 if(i==0&&l==1)
				 {
				     printf("兽");
				 }
				 if(i==j-1&&l==0)
				 {
					 printf("人");
				 }
				 if((i!=0&&l==1)||(i!=j-1&&l==0))
				 {
					 printf("  ");
				 }
			 }
		 }
		 if(strcmp(cha.prof,"道士")==0&&t==1)
		 {
			 if(anim==-1.0)
			 {
				 if(i==j-1)
				 {
				  printf("==");
				 }
				 else
				 {
				  printf("  ");
				 }
			 }
			 if(anim!=-1.0)
			 {
				 if(i==0&&l==1)
				 {
				     printf("兽");
				 }
				 if(i==j-1&&l==0)
				 {
				     printf("==");
				 }
				 if((i!=0&&l==1)||(i!=j-1&&l==0))
				 {
					 printf("  ");
				 }
			 }
		 }
	 }
	 if(g==0||g==2)
	 {
	  printf("  ");
	 }
	 if(i!=k)
	 {
	  printf("怪");
	 }
	 if(i==k)      //轮到第k个怪时
	 {
	   if((strcmp(cha.prof,"法师")==0&&t==1)||(strcmp(cha.prof,"道士")==0&&t==1&&anim==-1.0&&cha.q!=3&&cha.q!=4&&cha.k!=1.3&&cha.q!=6))
	   {
	    printf("怪");
		k = cha.m-1;
	   }
	   else
	   {
	    printf("  ");
	   }
	 }
	 if(g==1)
	 {
		 if(strcmp(cha.prof,"战士")==0&&cha.k!=1.3)
		 {
			 if(i==j-2)
			 {
				 if(cha.q==2)
				 {
					 if(cha.m>1&&cha.m==j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
				 }
			 }
			 if(i==j-1)
			 {
				 printf("-%4.0lf",a);
				 i++;
				 continue;
			 }
			 if(i==j)
			 {
				 if(cha.q==2)
				 {
					 if(cha.m>1&&cha.m!=j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
				 }
			 }
		 }
		 if(strcmp(cha.prof,"法师")==0)
		 {
			 if(cha.m==5&&cha.q==5)
			 {
				 if(i==0)
				 {
					 printf("-%4.0lf",a);
					 i++;
					 continue;
				 }
				 if(i==1)
				 {
					 printf("-%4.0lf",b);
					 i++;
					 continue;
				 }
				 if(i==2)
				 {
					 printf("-%4.0lf",c);
					 i++;
					 continue;
				 }if(i==3)
				 {
					 printf("-%4.0lf",d);
					 i++;
					 continue;
				 }
				 if(i==4)
				 {
					 printf("-%4.0lf",e);
					 i++;
					 continue;
				 }
			 }
			 if(i==j-4)
			 {
				 if(cha.q==5)
				 {
					 if(cha.m==4&&cha.m==j)
					 {
						 printf("-%4.0lf",d);
						 i++;
						 continue;
					 }
				 }
			 }
			 if(i==j-3)
			 {
				 if(cha.q==3)
				 {
					 if(cha.m>=3&&cha.m==j)
					 {
						 printf("-%4.0lf",c);
						 i++;
						 continue;
					 }
				 }
				 if(cha.q==5)
				 {
					 if(cha.m==3&&cha.m==j)
					 {
						 printf("-%4.0lf",c);
						 i++;
						 continue;
					 }
					 if(cha.m==4&&cha.m==j)
					 {
						 printf("-%4.0lf",c);
						 i++;
						 continue;
					 }
					 if(cha.m==4&&cha.m-1==j)
					 {
						 printf("-%4.0lf",d);
						 i++;
						 continue;
					 }
				 }
			 }
			 if(i==j-2)
			 {
				 if(cha.q==2)
				 {
					 if(cha.m>=2&&cha.m==j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
				 }
				 if(cha.q==3)
				 {
					 if(cha.m==2)
					 {
						 if(cha.m==j)
						 {
							 printf("-%4.0lf",b);
							 i++;
							 continue;
						 }
					 }
					 if(cha.m>=3&&cha.m==j+1)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
					 if(cha.m>=3&&cha.m==j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
				 }
				 if(cha.q==5)
				 {
					 if(cha.m==2&&cha.m==j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
					 if(cha.m==3&&cha.m==j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
					 if(cha.m==3&&cha.m-1==j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
					 if(cha.m==4&&cha.m==j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
					 if(cha.m==4&&cha.m-1==j)
					 {
						 printf("-%4.0lf",c);
						 i++;
						 continue;
					 }
					 if(cha.m==3&&cha.m-2==j)
					 {
						 printf("-%4.0lf",d);
						 i++;
						 continue;
					 }
				 }
			 }
			 if(i==j-1)
			 {
				 printf("-%4.0lf",a);
				 i++;
				 continue;
			 }
			 if(i==j)
			 {
				 if(cha.q==2)
				 {
					 if(cha.m>=2&&cha.m!=j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
				 }
				 if(cha.q==3)
				 {
					 if(cha.m==2)
					 {
						 if(cha.m!=j)
						 {
							 printf("-%4.0lf",b);
							 i++;
							 continue;
						 }
					 }
					 if(cha.m>=3&&cha.m-1==j)
					 {
						 printf("-%4.0lf",c);
						 i++;
						 continue;
					 }
					 if(cha.m>=3&&cha.m!=j&&cha.m!=j+1)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
				 }
				 if(cha.q==5)
				 {
					 if(cha.m==2&&cha.m!=j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
					 if(cha.m==3&&cha.m-1==j)
					 {
						 printf("-%4.0lf",c);
						 i++;
						 continue;
					 }
					 if(cha.m==3&&cha.m!=j&&cha.m!=j+1)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
					 if(cha.m==4&&cha.m-1==j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
					 if(cha.m==4&&cha.m-2==j)
					 {
						 printf("-%4.0lf",c);
						 i++;
						 continue;
					 }
					 if(cha.m==4&&cha.m-3==j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
				 }
			 }
			 if(i==j+1)
			 {
				 if(cha.q==3)
				 {
					 if(cha.m>=3&&cha.m!=j&&cha.m!=j+1)
					 {
						 printf("-%4.0lf",c);
						 i++;
						 continue;
					 }
				 }
				 if(cha.q==5)
				 {
					 if(cha.m==3&&cha.m!=j&&cha.m!=j+1)
					 {
						 printf("-%4.0lf",c);
						 i++;
						 continue;
					 }
					 if(cha.m==4&&cha.m-2==j)
					 {
						 printf("-%4.0lf",b);
						 i++;
						 continue;
					 }
					 if(cha.m==4&&cha.m-3==j)
					 {
						 printf("-%4.0lf",c);
						 i++;
						 continue;
					 }
				 }
			 }
			 if(i==j+2)
			 {
				 if(cha.q==5)
				 {
					 if(cha.m==4&&cha.m-3==j)
					 {
						 printf("-%4.0lf",d);
						 i++;
						 continue;
					 }
				 }
			 }
		 }
		 if(strcmp(cha.prof,"道士")==0)
		 {
			 if(i==0&&anim!=-1.0&&l!=0)
			 {
			  printf("-%4.0lf",b);
			  i++;
			  continue;
			 }
			 if(i==j-1)
			 {
				 if(cha.q==1||t==0)
				 {
				  printf("-%4.0lf",a);
				  i++;
				  continue;
				 }
			 }
		 }
	 }
	 printf("     ");
	 i++;
	}
	k++;
	printf("\n");

	struct MONSTER mo;          //检测怪的生命值
	i = 0;
    while(i<=cha.m-1)
	{
	 if(mon[i].HP==0)
	 {
	  strcpy(mon[i].name,"\0");
	  j=i;
	  while(j<=cha.m-2)
	  {
	   mo = mon[j];
	   mon[j] = mon[j+1];
	   mon[j+1] = mo;
	   j++;
	  }
	  cha.m--;
	  if(i==0&&cha.m==0)
	  {
	   if(cha.trp!=0)
	   {
		   i=0;
		   while(turn[i]!=1)
		   {
			   i++;
		   }
		   turn[i] = 0;
		   i++;
		   if(i==1&&strcmp(cha.buddy2,"\0")==0)
		   {
			   i = 0;
		   }
		   if(i==2&&strcmp(cha.buddy3,"\0")==0)
		   {
			   i = 0;
		   }
		   if(i==3)
		   {
			   i = 0;
		   }
		   turn[i] = 1;
		   f = fopen(filename,"wb");
		   fwrite(&turn[0],4,1,f);
		   fwrite(&turn[1],4,1,f);
		   fwrite(&turn[2],4,1,f);
		   fwrite(&HP[0],8,1,f);
		   fwrite(&MP[0],8,1,f);
		   fwrite(&ani[0],8,1,f);
		   fwrite(&HP[1],8,1,f);
		   fwrite(&MP[1],8,1,f);
		   fwrite(&ani[1],8,1,f);
		   fwrite(&HP[2],8,1,f);
		   fwrite(&MP[2],8,1,f);
		   fwrite(&ani[2],8,1,f);
		   fwrite(&mon[0].HP,8,1,f);
		   fclose(f);
		   printf("副本完成\n");
		   printf("确认");
		   getchar();
		   if(cha.trp==1)
		   {
		    unlink(filename);
		   }
		   cha.HP = cha.xHP;
		   cha.MP = cha.xMP;
	   }
	   return cha;
	  }
	 }
	 else
	 {
	  i++;
	 }
	}
    
	if(cha.trp==0)           //检测人的生命值
	{
		if(cha.HP==0)
		{
			printf("人物死亡\n");
			cha.mny -= (double)(cha.grd*10);
			if(cha.mny<0)
			{
				cha.mny = 0.0;
			}
			printf("损失%.0lf金币\n",(double)(cha.grd*10));
			printf("确认");
			getchar();
			printf("\n");
			cha.HP = 1;
			cha.m = -1;
			cha.n = -1;
			return cha;
		}
		if(anim==0.0)
		{
	     anim = -1.0;
		 freq--;
		}
	}
	else
	{
		if(anim==0.0)
		{
			anim = -1.0;
			if(cha.trp!=0)
			{
				ani[cha.trp-1] = anim;
			}
			freq--;
		}
		i = 0;
		if(strcmp(cha.buddy2,"\0")==0&&HP[0]==0.0)
		{
			i = 1;
		}
		if((strcmp(cha.buddy2,"\0")!=0&&HP[1]==0.0)&&HP[0]==0.0)
		{
			if((strcmp(cha.buddy3,"\0")!=0&&HP[2]==0.0)||(strcmp(cha.buddy3,"\0")==0))
			{
				i = 1;
			}
		}
		if(i==1)
		{
			i=0;
			while(turn[i]!=1)
			{
				i++;
			}
			turn[i] = 0;
			i++;
			if(i==1&&strcmp(cha.buddy2,"\0")==0)
			{
				i = 0;
			}
			if(i==2&&strcmp(cha.buddy3,"\0")==0)
			{
				i = 0;
			}
			if(i==3)
			{
				i = 0;
			}
			turn[i] = 1;
			f = fopen(filename,"wb");
			fwrite(&turn[0],4,1,f);
			fwrite(&turn[1],4,1,f);
			fwrite(&turn[2],4,1,f);
			fwrite(&HP[0],8,1,f);
			fwrite(&MP[0],8,1,f);
			fwrite(&ani[0],8,1,f);
			fwrite(&HP[1],8,1,f);
			fwrite(&MP[1],8,1,f);
			fwrite(&ani[1],8,1,f);
			fwrite(&HP[2],8,1,f);
			fwrite(&MP[2],8,1,f);
			fwrite(&ani[2],8,1,f);
			fwrite(&mon[0].HP,8,1,f);
			fclose(f);
			printf("全队团灭\n");
			cha.mny -= (double)(cha.grd*10);
			if(cha.mny<0)
			{
				cha.mny = 0.0;
			}
			printf("损失%.0lf金币\n",(double)(cha.grd*10));
			printf("确认");
			getchar();
			printf("\n");
			cha.HP = 1;
			cha.m = -1;
			cha.n = -1;
			if(cha.trp==1)
			{
				unlink(filename);
			}
			return cha;
		}
	}

	if(strcmp(cha.prof,"道士")==0)
	{
	 if(anim!=-1.0)
	 {
	  if(l==0)
	  {
		  l = 1;
		  b = cha.atc*1.3 - mon[0].def;
		  n = -10 + rand()%21;
		  b += n/10.0*b/3.0;
		  b = (double)((int)(b*cha.k));
		  if(b<1)
		  {
			  b = 1;
		  }
		  mon[0].HP -= b;
		  if(mon[0].HP<0)
		  {
			  b = mon[0].HP + b;
			  mon[0].HP = 0;
		  }
		  printf("\n");
		  goto loop0;
	  }
	 }
	}
    
    if(g==1)                 //技能显示
	{
	 g = 2;
	 k = 0;
	 if(strcmp(cha.prof,"法师")==0 && t==1 && (cha.q==3 || cha.q==5))
	 {
	   printf("         ");
	   printf("         ");
	   printf("         ");
	   printf("    ");
	   i = 0;
	   while(i<=cha.m-1)
	   {
		x = 0;
		printf("  ");
		if(cha.q==5)
		{
		 printf("-- - - - -- - - - -- - - - -- - - - --");
		 i = cha.m;
		 continue;
		}
		if(i==j-3)
		{
		  if(cha.m>=3&&cha.m==j)
		  {
			if(h==1.6)
			{
			 printf("**");
			 x = 1;
			}
			if(h==1.7)
			{
			 printf("&&");
			 x = 1;
			}
		  }
		}
		if(i==j-2)
		{
		  if(cha.m==2)
		  {
		   if(cha.m==j)
		   {
		    if(h==1.6)
			{
			 printf("**");
			 x = 1;
			}
			if(h==1.7)
			{
			 printf("&&");
			 x = 1;
			}
		   }
		  }
		  if(cha.m>=3&&cha.m==j+1)
		  {
		   if(h==1.6)
			{
			 printf("**");
			 x = 1;
			}
			if(h==1.7)
			{
			 printf("&&");
			 x = 1;
			}
		  }
		  if(cha.m>=3&&cha.m==j)
		  {
		    if(h==1.6)
			{
			 printf("**");
			 x = 1;
			}
			if(h==1.7)
			{
			 printf("&&");
			 x = 1;
			}
		  }
		}
		if(i==j-1)
		{
			if(h==1.6)
			{
				printf("**");
				x = 1;
			}
			if(h==1.7)
			{
				printf("&&");
				x = 1;
			}
		}
		if(i==j)
		{
		  if(cha.m==2)
		  {
		   if(cha.m!=j)
		   {
		    if(h==1.6)
			{
				printf("**");
				x = 1;
			}
			if(h==1.7)
			{
				printf("&&");
				x = 1;
			}
		   }
		  }
		  if(cha.m>=3&&cha.m-1==j)
		  {
		    if(h==1.6)
			{
				printf("**");
				x = 1;
			}
			if(h==1.7)
			{
				printf("&&");
				x = 1;
			}
		  }
		  if(cha.m>=3&&cha.m!=j&&cha.m!=j+1)
		  {
		    if(h==1.6)
			{
				printf("**");
				x = 1;
			}
			if(h==1.7)
			{
				printf("&&");
				x = 1;
			}
		  }
		}
		if(i==j+1)
		{
		  if(cha.m>=3&&cha.m!=j&&cha.m!=j+1)
		  {
		    if(h==1.6)
			{
				printf("**");
				x = 1;
			}
			if(h==1.7)
			{
				printf("&&");
				x = 1;
			}
		  }
		}
		if(x!=1)
		{
		 printf("  ");
		}
		printf("     ");
	    i++;
	   }
	 }
	}

	if(g==2)
	{
	 printf("\n");
	 if(k==cha.m)
	 {
	  g = 0;
loop1:
	  i = 0;
	  if(cha.trp!=0)
	  {
	   while(turn[i]!=1)
	   {
		i++;
	   }
	   turn[i] = 0;
	   i++;
	   if(i==1&&strcmp(cha.buddy2,"\0")==0)
	   {
	     i = 0;
	   }
	   if(i==2&&strcmp(cha.buddy3,"\0")==0)
	   {
		 i = 0;
	   }
	   if(i==3)
	   {
	    i = 0;
	   }
	   turn[i] = 1;
	   f = fopen(filename,"wb");
	   fwrite(&turn[0],4,1,f);
       fwrite(&turn[1],4,1,f);
	   fwrite(&turn[2],4,1,f);
	   fwrite(&HP[0],8,1,f);
	   fwrite(&MP[0],8,1,f);
	   fwrite(&ani[0],8,1,f);
	   fwrite(&HP[1],8,1,f);
	   fwrite(&MP[1],8,1,f);
	   fwrite(&ani[1],8,1,f);
	   fwrite(&HP[2],8,1,f);
	   fwrite(&MP[2],8,1,f);
	   fwrite(&ani[2],8,1,f);
	   fwrite(&mon[0].HP,8,1,f);
	   fclose(f);
	  }
	  goto loop0;
	 }
	 if(strcmp(cha.prof,"战士")==0||(strcmp(cha.prof,"法师")==0&&t==0)||
		 (strcmp(cha.prof,"道士")==0&&(t==0||cha.q==3||cha.q==4||cha.k==1.3||cha.q==6)&&anim==-1.0)||(anim!=-1.0&&anim!=0.0))
	 {         //怪对人的伤害
		 a = mon[k].atc - cha.def;
		 n = -10 + rand()%21;
		 a += n/10.0*a/3.0;
		 a = (double)((int)(a));
		 if(a<1)
		 {
			 a = 1;
		 }
		 if(anim!=-1.0)
		 {
		  if(mol==0)
		  {
			  anim -= a;
			  if(anim<0)
			  {
				  a = anim + a;
				  anim = 0.0;
				  cha.q = 0;
			  }
		  }
		  if(mol!=0)
		  {
			  mol -= a;
			  if(mol<0)
			  {
				  a = mol + a;
				  mol = 0;
			  }
		  }
		 }
		 else
		 {
		  cha.HP -= a;
		  if(cha.HP<0)
		  {
			 a = cha.HP + a;
			 cha.HP = 0;
		  }
		 }
		 if(cha.trp!=0)
		 {
		  HP[cha.trp-1] = cha.HP;
		  ani[cha.trp-1] = anim;
		 }
	 }
	 goto loop0;
	}

	if(cha.trp==0)           //蓝
	{
	 if(mol==0)
	 {
	  printf("   %4.0lf",cha.MP);
	  printf("  ");
	 }
	 else
	 {
		 printf("%4.0lf",cha.MP);
		 printf(" ");
	     printf("%4.0lf",mol);
	 }
	 printf("         ");
	 printf("         ");
	}
	else
	{
	 if(MP[0]!=-1.0)
	 {
	  if(cha.trp==1)
	  {
		  if(mol==0)
		  {
			  printf("   %4.0lf",cha.MP);
			  printf("  ");
		  }
		  else
		  {
			  printf("%4.0lf",cha.MP);
			  printf(" ");
			  printf("%4.0lf",mol);
		  }
	  }
	  else
	  {
	      printf("   %4.0lf",MP[0]);
	      printf("  ");
	  }
	 }
	 else
	 {
	  printf("         ");
	 }
	 if(MP[1]!=-1.0)
	 {
	  if(cha.trp==2)
	  {
		  if(mol==0)
		  {
			  printf("   %4.0lf",cha.MP);
			  printf("  ");
		  }
		  else
		  {
			  printf("%4.0lf",cha.MP);
			  printf(" ");
			  printf("%4.0lf",mol);
		  }
	  }
	  else
	  {
	      printf("   %4.0lf",MP[0]);
	      printf("  ");
	  }
	 }
	 else
	 {
	  printf("         ");
	 }
	 if(MP[2]!=-1.0)
	 {
	  if(cha.trp==3)
	  {
		  if(mol==0)
		  {
			  printf("   %4.0lf",cha.MP);
			  printf("  ");
		  }
		  else
		  {
			  printf("%4.0lf",cha.MP);
			  printf(" ");
			  printf("%4.0lf",mol);
		  }
	  }
	  else
	  {
	      printf("   %4.0lf",MP[0]);
	      printf("  ");
	  }
	 }
	 else
	 {
	  printf("         ");
	 }
	 printf("   ");
	}
	printf("    ");

	for(i=0;i<=cha.m-1;i++)        //怪的编号
	{
	 printf("   %d     ",i+1);
	}
	printf("\n");

	if(wait==0)
	{
	if(cha.trp!=0)
	{
		printf("请等待...\n");
		i = 0;
		while(i==0)
		{
			f = fopen(filename,"rb");
			fread(&turn[0],4,1,f);
			fread(&turn[1],4,1,f);
			fread(&turn[2],4,1,f);
			fread(&HP[0],8,1,f);
			fread(&MP[0],8,1,f);
			fread(&ani[0],8,1,f);
			fread(&HP[1],8,1,f);
			fread(&MP[1],8,1,f);
			fread(&ani[1],8,1,f);
			fread(&HP[2],8,1,f);
			fread(&MP[2],8,1,f);
			fread(&ani[2],8,1,f);
			fread(&mon[0].HP,8,1,f);
			fclose(f);
			if(turn[cha.trp-1]==1)
			{
				i = 1;
				
				if(HP[cha.trp-1]!=0&&mon[0].HP!=0)
				{
				 wait = 1;
				 cha.HP = HP[cha.trp-1];
				 cha.MP = MP[cha.trp-1];
				 anim = ani[cha.trp-1];
				 goto loop0;
				}
			}
		}
		if(HP[cha.trp-1]==0.0||mon[0].HP==0.0)
		{
			goto loop1;
		}
	}
	}
	wait = 0;
	if(strcmp(cha.prof,"战士")==0)
	{
		if(cha.k==1.3)
		{
			cha.k = 1.301;
		}
	}
	if(strcmp(cha.prof,"法师")==0)
	{
		if(cha.k==1.5)
		{
			cha.k = 1.501;
		}
	}
	if(strcmp(cha.prof,"道士")==0)
	{
		if(cha.k==1.3)
		{
			cha.k = 1.301;
		}
	}
loop2:
	printf("\n  0.攻击  1.技能   2.物品  3.逃跑\n");
	printf("请选择");
	scanf("%d", &t);
	getchar();
	if(t==0)
	{
     h = 1.0;
	 printf("请选择怪物");
	 scanf("%d",&j);
	 getchar();
	 if(j>cha.m||j<1)
	 {
	  j = 1;
	 }
	}
	if(t==1)
	{
	 if(strcmp(cha.prof,"道士")==0)
	 {
		 if(cha.trp==0)
		 {
			 if(anim!=-1.0)
			 {
				 cha.q = -1;
			 }
		 }
		 else
		 {
			 if(ani[cha.trp-1]!=-1.0)
			 {
				 cha.q = -1;
			 }
		 }
		 if(freq==0)
		 {
			 cha.q = -2;
		 }
	 }
	 cha = Skill(cha);
	 n = cha.n;
	 h = cha.h;
	 if(n==2)
	 {
	  goto loop0;
	 }
	 if(n==0)
	 {
	  printf("MP不足\n");
	  printf("确认");
	  getchar();
	  goto loop0;
	 }
	 if(cha.trp!=0)
	 {
	  MP[cha.trp-1] = cha.MP;
	 }
	 if((strcmp(cha.prof,"战士")==0&&cha.k!=1.3)||(strcmp(cha.prof,"道士")==0&&cha.q==1)||
		 (strcmp(cha.prof,"法师")==0&&cha.k!=1.5))
	 {
	  printf("请选择怪物");
	  scanf("%d",&j);
	  getchar();
	  if(j>cha.m||j<1)
	  {
	   j = 1;
	  }
	 }
	 else
	 {
	  j = 0;
	 }
	}
	if(t==2)
	{
	 if(cha.trp!=0)
	 {
	  printf("不可使用物品\n");
	  goto loop2;
	 }
	 m = cha.m;
	 cha = SeeGoods(cha);
	 cha.m = m;
	 goto loop0;
	}
	if(t==3)
	{
	 if(cha.trp!=0)
	 {
	  printf("无法逃跑\n");
	  goto loop2;
	 }
	 printf("\n");
	 cha.m = -1;
	 return cha;
	}
	if(t!=1&&t!=2&&t!=3&&t!=0)
	{
	  goto loop0;
	}
    
	if(t==0||t==1)                   //人对怪的伤害
	{
	 g = 1;
	 l = 0;
     if(strcmp(cha.prof,"战士")==0)
	 {
	  if(cha.k==1.3)
	  {
	   goto loop0;
	  }
	  a = cha.atc - mon[j-1].def;     //a是对第1个怪物的伤害
	  n = -10 + rand()%21;
	  a += n/10.0*a/3.0;
	  a = (double)((int)(a*h*cha.k));
	  if(a<1)
	  {
		  a = 1;
	  }
	  mon[j-1].HP -= a;
	  if(mon[j-1].HP<0)
	  {
		  a = mon[j-1].HP + a;
		  mon[j-1].HP = 0;
	  }
	  if(cha.q==2)
	  {
	   if(cha.m>1&&cha.m==j)
	   {
		   b = cha.atc - mon[j-2].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j-2].HP -= b;
		   if(mon[j-2].HP<0)
		   {
			   b = mon[j-2].HP + b;
			   mon[j-2].HP = 0;
		   }
	   }
	   if(cha.m>1&&cha.m!=j)
	   {
		   b = cha.atc - mon[j].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j].HP -= b;
		   if(mon[j].HP<0)
		   {
			   b = mon[j].HP + b;
			   mon[j].HP = 0;
		   }
	   }
	  }
	 }
	 if(strcmp(cha.prof,"法师")==0)
	 {
		if(cha.k==1.5)
		{
			goto loop0;
		}
		if(t==0)
		{
			a = cha.atc - mon[j-1].def;
			n = -10 + rand()%21;
			a += n/10.0*a/3.0;
			a = (double)((int)(a*h*cha.k));
			if(a<1)
			{
				a = 1;
			}
			mon[j-1].HP -= a;
			if(mon[j-1].HP<0)
			{
				a = mon[j-1].HP + a;
				mon[j-1].HP = 0;
			}
			goto loop0;
		}
		if(t!=0)     //t是选择的攻击还是技能
		{
			a = cha.atc*2 - mon[j-1].def;
			n = -10 + rand()%21;
			a += n/10.0*a/3.0;
			a = (double)((int)(a*h*cha.k));
			if(a<1)
			{
				a = 1;
			}
			mon[j-1].HP -= a;
			if(mon[j-1].HP<0)
			{
				a = mon[j-1].HP + a;
				mon[j-1].HP = 0;
			}
		}
		if(cha.q==2)
		 {
		  if(cha.m>=2&&cha.m==j)
		  {
		   b = cha.atc*2 - mon[j-2].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j-2].HP -= b;
		   if(mon[j-2].HP<0)
		   {
			   b = mon[j-2].HP + b;
			   mon[j-2].HP = 0;
		   }
		  }
		  if(cha.m>=2&&cha.m!=j)
		  {
		   b = cha.atc*2 - mon[j].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j].HP -= b;
		   if(mon[j].HP<0)
		   {
			   b = mon[j].HP + b;
			   mon[j].HP = 0;
		   }
		  }
		 }
		 if(cha.q==3)
		 {
		  if(cha.m==2)
		  {
		   if(cha.m==j)
		   {
			   b = cha.atc*2 - mon[j-2].def;
			   n = -10 + rand()%21;
			   b += n/10.0*b/3.0;
			   b = (double)((int)(b*h*cha.k));
			   if(b<1)
			   {
				   b = 1;
			   }
			   mon[j-2].HP -= b;
			   if(mon[j-2].HP<0)
			   {
				   b = mon[j-2].HP + b;
				   mon[j-2].HP = 0;
			   }
		   }
		   if(cha.m!=j)
		   {
		       b = cha.atc*2 - mon[j].def;
			   n = -10 + rand()%21;
			   b += n/10.0*b/3.0;
			   b = (double)((int)(b*h*cha.k));
			   if(b<1)
			   {
				   b = 1;
			   }
			   mon[j].HP -= b;
			   if(mon[j].HP<0)
			   {
				   b = mon[j].HP + b;
				   mon[j].HP = 0;
			   }
		   }
		  }
		  if(cha.m>=3&&cha.m==j)
		  {
		   b = cha.atc*2 - mon[j-2].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j-2].HP -= b;
		   if(mon[j-2].HP<0)
		   {
			   b = mon[j-2].HP + b;
			   mon[j-2].HP = 0;
		   }
		   c = cha.atc*2 - mon[j-3].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[j-3].HP -= c;
		   if(mon[j-3].HP<0)
		   {
			   c = mon[j-3].HP + c;
			   mon[j-3].HP = 0;
		   }
		  }
		  if(cha.m>=3&&cha.m-1==j)
		  {
		   b = cha.atc*2 - mon[j-2].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j-2].HP -= b;
		   if(mon[j-2].HP<0)
		   {
			   b = mon[j-2].HP + b;
			   mon[j-2].HP = 0;
		   }
		   c = cha.atc*2 - mon[j].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[j].HP -= c;
		   if(mon[j].HP<0)
		   {
			   c = mon[j].HP + c;
			   mon[j].HP = 0;
		   }
		  }
		  if(cha.m>=3&&cha.m!=j&&cha.m!=j+1)
		  {
		   b = cha.atc*2 - mon[j].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j].HP -= b;
		   if(mon[j].HP<0)
		   {
			   b = mon[j].HP + b;
			   mon[j].HP = 0;
		   }
		   c = cha.atc*2 - mon[j+1].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[j+1].HP -= c;
		   if(mon[j+1].HP<0)
		   {
			   c = mon[j+1].HP + c;
			   mon[j+1].HP = 0;
		   }
		  }
		 }
		 if(cha.q==5)
		 {
		  if(cha.m==2)
		  {
		   if(cha.m==j)
		   {
			   b = cha.atc*2 - mon[j-2].def;
			   n = -10 + rand()%21;
			   b += n/10.0*b/3.0;
			   b = (double)((int)(b*h*cha.k));
			   if(b<1)
			   {
				   b = 1;
			   }
			   mon[j-2].HP -= b;
			   if(mon[j-2].HP<0)
			   {
				   b = mon[j-2].HP + b;
				   mon[j-2].HP = 0;
			   }
		   }
		   if(cha.m!=j)
		   {
		       b = cha.atc*2 - mon[j].def;
			   n = -10 + rand()%21;
			   b += n/10.0*b/3.0;
			   b = (double)((int)(b*h*cha.k));
			   if(b<1)
			   {
				   b = 1;
			   }
			   mon[j].HP -= b;
			   if(mon[j].HP<0)
			   {
				   b = mon[j].HP + b;
				   mon[j].HP = 0;
			   }
		   }
		  }
		  if(cha.m==3&&cha.m==j)
		  {
		   b = cha.atc*2 - mon[j-2].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j-2].HP -= b;
		   if(mon[j-2].HP<0)
		   {
			   b = mon[j-2].HP + b;
			   mon[j-2].HP = 0;
		   }
		   c = cha.atc*2 - mon[j-3].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[j-3].HP -= c;
		   if(mon[j-3].HP<0)
		   {
			   c = mon[j-3].HP + c;
			   mon[j-3].HP = 0;
		   }
		  }
		  if(cha.m==3&&cha.m-1==j)
		  {
		   b = cha.atc*2 - mon[j-2].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j-2].HP -= b;
		   if(mon[j-2].HP<0)
		   {
			   b = mon[j-2].HP + b;
			   mon[j-2].HP = 0;
		   }
		   c = cha.atc*2 - mon[j].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[j].HP -= c;
		   if(mon[j].HP<0)
		   {
			   c = mon[j].HP + c;
			   mon[j].HP = 0;
		   }
		  }
		  if(cha.m==3&&cha.m!=j&&cha.m!=j+1)
		  {
		   b = cha.atc*2 - mon[j].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j].HP -= b;
		   if(mon[j].HP<0)
		   {
			   b = mon[j].HP + b;
			   mon[j].HP = 0;
		   }
		   c = cha.atc*2 - mon[j+1].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[j+1].HP -= c;
		   if(mon[j+1].HP<0)
		   {
			   c = mon[j+1].HP + c;
			   mon[j+1].HP = 0;
		   }
		  }
		  if(cha.m==4&&cha.m==j)
		  {
		   b = cha.atc*2 - mon[j-2].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j-2].HP -= b;
		   if(mon[j-2].HP<0)
		   {
			   b = mon[j-2].HP + b;
			   mon[j-2].HP = 0;
		   }
		   c = cha.atc*2 - mon[j-3].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[j-3].HP -= c;
		   if(mon[j-3].HP<0)
		   {
			   c = mon[j-3].HP + c;
			   mon[j-3].HP = 0;
		   }
		   d = cha.atc*2 - mon[j-4].def;
		   n = -10 + rand()%21;
		   d += n/10.0*d/3.0;
		   d = (double)((int)(d*h*cha.k));
		   if(d<1)
		   {
			   d = 1;
		   }
		   mon[j-4].HP -= d;
		   if(mon[j-4].HP<0)
		   {
			   d = mon[j-4].HP + d;
			   mon[j-4].HP = 0;
		   }
		  }
		  if(cha.m==4&&cha.m-1==j)
		  {
		   b = cha.atc*2 - mon[j].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j].HP -= b;
		   if(mon[j].HP<0)
		   {
			   b = mon[j].HP + b;
			   mon[j].HP = 0;
		   }
		   c = cha.atc*2 - mon[j-2].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[j-2].HP -= c;
		   if(mon[j-2].HP<0)
		   {
			   c = mon[j-2].HP + c;
			   mon[j-2].HP = 0;
		   }
		   d = cha.atc*2 - mon[j-3].def;
		   n = -10 + rand()%21;
		   d += n/10.0*d/3.0;
		   d = (double)((int)(d*h*cha.k));
		   if(d<1)
		   {
			   d = 1;
		   }
		   mon[j-3].HP -= d;
		   if(mon[j-3].HP<0)
		   {
			   d = mon[j-3].HP + d;
			   mon[j-3].HP = 0;
		   }
		  }
		  if(cha.m==4&&cha.m-2==j)
		  {
		   b = cha.atc*2 - mon[j+1].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j+1].HP -= b;
		   if(mon[j+1].HP<0)
		   {
			   b = mon[j+1].HP + b;
			   mon[j+1].HP = 0;
		   }
		   c = cha.atc*2 - mon[j].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[j].HP -= c;
		   if(mon[j].HP<0)
		   {
			   c = mon[j].HP + c;
			   mon[j].HP = 0;
		   }
		   d = cha.atc*2 - mon[j-2].def;
		   n = -10 + rand()%21;
		   d += n/10.0*d/3.0;
		   d = (double)((int)(d*h*cha.k));
		   if(d<1)
		   {
			   d = 1;
		   }
		   mon[j-2].HP -= d;
		   if(mon[j-2].HP<0)
		   {
			   d = mon[j-2].HP + d;
			   mon[j-2].HP = 0;
		   }
		  }
		  if(cha.m==4&&cha.m-3==j)
		  {
		   b = cha.atc*2 - mon[j].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[j].HP -= b;
		   if(mon[j].HP<0)
		   {
			   b = mon[j].HP + b;
			   mon[j].HP = 0;
		   }
		   c = cha.atc*2 - mon[j+1].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[j+1].HP -= c;
		   if(mon[j+1].HP<0)
		   {
			   c = mon[j+1].HP + c;
			   mon[j+1].HP = 0;
		   }
		   d = cha.atc*2 - mon[j+2].def;
		   n = -10 + rand()%21;
		   d += n/10.0*d/3.0;
		   d = (double)((int)(d*h*cha.k));
		   if(d<1)
		   {
			   d = 1;
		   }
		   mon[j+2].HP -= d;
		   if(mon[j+2].HP<0)
		   {
			   d = mon[j+2].HP + d;
			   mon[j+2].HP = 0;
		   }
		  }
		  if(cha.m==5)
		  {
		   a = cha.atc*2 - mon[0].def;
		   n = -10 + rand()%21;
		   a += n/10.0*a/3.0;
		   a = (double)((int)(a*h*cha.k));
		   if(a<1)
		   {
			   a = 1;
		   }
		   mon[0].HP -= a;
		   if(mon[0].HP<0)
		   {
			   a = mon[0].HP + a;
			   mon[0].HP = 0;
		   }
		   b = cha.atc*2 - mon[1].def;
		   n = -10 + rand()%21;
		   b += n/10.0*b/3.0;
		   b = (double)((int)(b*h*cha.k));
		   if(b<1)
		   {
			   b = 1;
		   }
		   mon[1].HP -= b;
		   if(mon[1].HP<0)
		   {
			   b = mon[1].HP + b;
			   mon[1].HP = 0;
		   }
		   c = cha.atc*2 - mon[2].def;
		   n = -10 + rand()%21;
		   c += n/10.0*c/3.0;
		   c = (double)((int)(c*h*cha.k));
		   if(c<1)
		   {
			   c = 1;
		   }
		   mon[2].HP -= c;
		   if(mon[2].HP<0)
		   {
			   c = mon[2].HP + c;
			   mon[2].HP = 0;
		   }
		   d = cha.atc*2 - mon[3].def;
		   n = -10 + rand()%21;
		   d += n/10.0*d/3.0;
		   d = (double)((int)(d*h*cha.k));
		   if(d<1)
		   {
			   d = 1;
		   }
		   mon[3].HP -= d;
		   if(mon[3].HP<0)
		   {
			   d = mon[3].HP + d;
			   mon[3].HP = 0;
		   }
		   e = cha.atc*2 - mon[4].def;
		   n = -10 + rand()%21;
		   e += n/10.0*e/3.0;
		   e = (double)((int)(e*h*cha.k));
		   if(e<1)
		   {
			   e = 1;
		   }
		   mon[4].HP -= e;
		   if(mon[4].HP<0)
		   {
			   e = mon[4].HP + e;
			   mon[4].HP = 0;
		   }
		  }
		 }
	 }
	 if(strcmp(cha.prof,"道士")==0)
	 {
		 if(cha.k==1.3)
		 {
			 goto loop0;
		 }
	     if(t==0)
		 {
		  a = cha.atc - mon[j-1].def;
		  n = -10 + rand()%21;
		  a += n/10.0*a/3.0;
		  a = (double)((int)(a*h));
		  if(a<1)
		  {
			  a = 1;
		  }
		  mon[j-1].HP -= a;
		  if(mon[j-1].HP<0)
		  {
			  a = mon[j-1].HP + a;
			  mon[j-1].HP = 0;
		  }
		 }
		 if(t!=0)
		 {
		  if(cha.q==-1)
		  {
		    anim = cha.xHP*1.5;
			if(cha.trp!=0)
			{
			 ani[cha.trp-1] = anim;
			}
		  }
		  if(cha.q==1)
		  {
		   a = cha.atc*1.3 - mon[j-1].def;
		   n = -10 + rand()%21;
		   a += n/10.0*a/3.0;
		   a = (double)((int)(a*h));
		   if(a<1)
		   {
			  a = 1;
		   }
		   mon[j-1].HP -= a;
		   if(mon[j-1].HP<0)
		   {
			  a = mon[j-1].HP + a;
			  mon[j-1].HP = 0;
		   }
		  }
		  if(cha.q==3)
		  {
		   a = cha.atc*1.3/2.0;
		   cha.MP += a;
		   if(cha.trp!=0)
		   {
			if(HP[0]!=0)
			{
			 MP[0] += a;
			}
			if(HP[1]!=0)
			{
			 MP[1] += a;
			}
			if(HP[2]!=0)
			{
			 MP[2] += a;
			}
			if(MP[0]>value[1])
			{
			 MP[0] = value[1];
			}
			if(MP[1]>value[3])
			{
			 MP[1] = value[3];
			}
			if(MP[2]>value[5])
			{
			 MP[2] = value[5];
			}
		   }
		   if(cha.MP>cha.xMP)
		   {
			a = cha.xMP-(cha.MP-a)+0.001;
		    cha.MP = cha.xMP;
		   }
		  }
		  if(cha.q==4)
		  {
           a = cha.atc*1.3;
		   cha.HP += a;
		   if(cha.trp!=0)
		   {
			if(HP[0]!=0)
			{
			 HP[0] += a;
			}
			if(ani[0]!=-1.0)
			{
			 ani[0] += a;
			}
			if(HP[1]!=0)
			{
			 HP[1] += a;
			}
			if(ani[1]!=-1.0)
			{
			 ani[1] += a;
			}
			if(HP[2]!=0)
			{
			 HP[2] += a;
			}
			if(ani[2]!=-1.0)
			{
			 ani[2] += a;
			}
			if(HP[0]>value[0])
			{
			 HP[0] = value[0];
			}
			if(ani[0]>value[0]*1.5)
			{
			 ani[0] = value[0]*1.5;
			}
			if(HP[1]>value[2])
			{
			 HP[1] = value[2];
			}
			if(ani[1]>value[2]*1.5)
			{
			 ani[1] = value[2]*1.5;
			}
			if(HP[2]>value[4])
			{
			 HP[2] = value[4];
			}
			if(ani[2]>value[4]*1.5)
			{
			 ani[2] = value[4]*1.5;
			}
		   }
		   if(anim!=-1.0)
		   {
		    anim += a;
		    if(anim>cha.xHP*1.5)
			{
		     anim = cha.xHP*1.5;
			}
		   }
		   if(cha.HP>cha.xHP)
		   {
			a = cha.xHP-(cha.HP-a)+0.001;
		    cha.HP = cha.xHP;
		   }
		  }
		  if(cha.q==6)
		  {
		   mol = cha.xHP*0.75;
		  }
		 }
	 }
	 goto loop0;
	}
	return cha;
}

struct CHARACTER UpAbi(struct CHARACTER cha)
{
    if(strcmp(cha.prof,"战士")==0)
	{
	 cha.grd += 1;
	 cha.xHP += 19;
	 cha.HP = cha.xHP;
	 cha.xMP += 3;
	 cha.MP = cha.xMP;
	 cha.atc += 5;
	 cha.def += 3;
	 cha.exp = cha.exp - cha.xexp;
	}
	if(strcmp(cha.prof,"法师")==0)
	{
	 cha.grd += 1;
	 cha.xHP += 5;
	 cha.HP = cha.xHP;
	 cha.xMP += 20;
	 cha.MP = cha.xMP;
	 cha.atc += 2;
	 cha.def += 3;
	 cha.exp = cha.exp - cha.xexp;
	}
	if(strcmp(cha.prof,"道士")==0)
	{
	 cha.grd += 1;
	 cha.xHP += 12;
	 cha.HP = cha.xHP;
	 cha.xMP += 11;
	 cha.MP = cha.xMP;
	 cha.atc += 3.5;
	 cha.def += 3;
	 cha.exp = cha.exp - cha.xexp;
	}
	return cha;
}

struct CHARACTER UpExp(struct CHARACTER cha)
{
    if (cha.grd == grade)
	{
		cha.exp = 0;
	}
	if (cha.grd < 5)
	{
		cha.xexp += 10;
	}
	if (cha.grd >= 5 && cha.grd < 10)
	{
		cha.xexp += 20;
	}
	if (cha.grd >= 10 && cha.grd < 25)
	{
		cha.xexp += 50;
	}
	if (cha.grd >= 25 && cha.grd < 40)
	{
		cha.xexp += 500;
	}
	if (cha.grd >= 40 && cha.grd < 50)
	{
		cha.xexp += 2000;
	}
	if (cha.grd >= 50)
	{
		cha.xexp += 5000;
	}
	return cha;
}

struct CHARACTER Upgrade(struct CHARACTER cha)
{
	double t=0, s=0;
	double exp=cha.exp;
	int w,r,i,j,k,n,v;
	struct MONSTER mon[5];
	struct MONSTER m[5];

	if(exp<=cha.xexp)
	{
		int z=0,a,h;
		if(strcmp(cha.v,"沃玛寺庙")!=0)
		{
			printf("打1个还是打1群\n");
			printf("1.1个  2.1群\n");
			scanf("%d",&h);
			getchar();
			while(z>=0)
			{
				m[z] = Monster(cha);
				mon[z] = m[z];
				if(h==1)
				{
					z++;
				    break;
				}
				if(h==2)
				{
					z++;
					a = 1 + rand() % 100;
					if(a<=10+z*10||z==5)
					{
					  break;
					}
				}
				if(h!=1&&h!=2)
				{
				 return cha;
				}
			}
		}
		else
		{
			m[0] = Monbackup(cha);
			mon[0] = m[0];
			z++;
		}
		cha.m = z;
		cha = Battle(cha,m);

		if(cha.m==-1)
		{
		 cha.m = 0;
		 return cha;
		}

		i = 0;
		while(i<=z-1)
		{
		 t += mon[i].exp;
		 s += mon[i].mny;
		 i++;
		}
		cha.exp += t;
		cha.mny += s;
		printf("增加经验%.0lf   ", t);
		printf("  得到%.0lf金币\n", s);
		if (cha.grd==grade)
		{
			cha.exp = 0;
		}
		
		k = 0;
		while(k<=z-1)
		{
			i = 0;
			while(mon[k].out[i].nam != '\0')
			{
				w = cha.t;
				n = w;
				v = 0;
				if(mon[k].out[i].nam!='*')
				{
					for(j=0;j<=w-1;j++)
					{
						if(cha.goods[j].nam == mon[k].out[i].nam)
						{
							n = j;
							break;
						}
					}
					if(n==w)
					{
						if(w==17)
						{
							printf("背包空间不足\n");
							v = 1;
						}
						else
						{
							cha.goods[w].nam = mon[k].out[i].nam;
							strcpy(cha.goods[w].name,mon[k].out[i].name);
							cha.t += 1;
							cha.goods[w].q = mon[k].out[i].q;
						}
					}
					else
					{
						cha.goods[n].q += mon[k].out[i].q;
					}
					if(v==0)
					{
						printf("得到物品%c\n", mon[k].out[i].nam);
					}
					if(v==1)
					{
						printf("无法得到物品%c\n", mon[k].out[i].nam);
						printf("\n");
					}
				}
				if(mon[k].out[i].nam=='*')
				{
					if(w==17)
					{
						printf("背包空间不足\n");
						printf("无法得到物品%c\n", mon[k].out[i].nam);
						printf("\n");
					}
					else
					{
						cha.goods[w].nam = mon[k].out[i].nam;
						cha.t += 1;
						r = cha.e;
						cha.equ[r].grd = mon[k].grd;
						cha.equ[r].rank = mon[k].oequ[i].rank;
						strcpy(cha.equ[r].kind,mon[k].oequ[i].kind);
						cha.e += 1;
						cha = EquAtt(cha);
						printf("得到物品%c\n", mon[k].out[i].nam);
					}
				}
				i++;
			}
			k++;
		}
		printf("确认");
		getchar();
		printf("\n\n");
		return cha;
	}
	printf("恭喜您，升级！\n");
	cha = UpAbi(cha);
	cha = UpExp(cha);
	printf("确认");
	getchar();
	printf("\n\n");
	return cha;
}

struct CHARACTER Go(struct CHARACTER cha)
{
 int v=0,t;
 if(strcmp(cha.v,"世外小村")==0)
 {
	printf("想去哪里可以跟我说!\n");
	printf("1.村镇周边   (1~4级)\n");
	printf("2.森林       (5~9级)\n");
    printf("3.僵尸洞     (10~15级)\n");
	printf("4.蜈蚣洞     (16~20级)\n");
	printf("5.石窟       (21~25级)\n");
	printf("6.进入副本 沃玛寺庙\n");
	printf("7.去其它城镇 比奇城\n");
	printf("请选择");
	scanf("%d",&v);
	getchar();
	if(v==1)
	{
	  strcpy(cha.v,"村镇周边");
	}
	if(v==2)
	{
	  strcpy(cha.v,"森林");
	}
	if(v==3)
	{
	  strcpy(cha.v,"僵尸洞");
	}
	if(v==4)
	{
	  strcpy(cha.v,"蜈蚣洞");
	}
	if(v==5)
	{
	  strcpy(cha.v,"石窟");
	}
	if(v==6)
	{
	  if(cha.grd<25)
	  {
		printf("等级不够，需25级\n");
		return cha;
	  }
	  strcpy(cha.v,"沃玛寺庙");
	}
	if(v==7)
	{
	  printf("需100金币，是否选择?\n");
	  printf("1.是 2.否\n");
	  printf("请选择");
	  scanf("%d",&t);
	  getchar();
	  if(t==1)
	  {
		  if(cha.mny<100)
		  {
			  printf("手续费不足\n");
			  printf("确认");
			  getchar();
			  return cha;
		  }
		  cha.mny -= 100;
		  printf("确认");
		  getchar();
		  strcpy(cha.v,"比奇城");
		  return cha;
	  }
	}
	printf("\n");
	return cha;
 }
 if(strcmp(cha.v,"村镇周边")==0||strcmp(cha.v,"森林")==0||strcmp(cha.v,"僵尸洞")==0||
	 strcmp(cha.v,"蜈蚣洞")==0||strcmp(cha.v,"石窟")==0||strcmp(cha.v,"沃玛寺庙")==0)
 {
	 strcpy(cha.v,"世外小村");
	 return cha;
 }
 if(strcmp(cha.v,"比奇城")==0)
 {
	printf("这里是最繁荣的城市!\n");
	printf("1.野猪洞     (26~32级)\n");
	printf("2.封魔谷     (33~40级)\n");
	printf("3.去其它城镇 世外小村\n");
	printf("请选择");
	scanf("%d",&v);
	getchar();
	if(v==1)
	{
	  strcpy(cha.v,"野猪洞");
	}
	if(v==2)
	{
	  strcpy(cha.v,"封魔谷");
	}
	if(v==3)
	{
	  printf("需100金币，是否选择?\n");
	  printf("1.是 2.否\n");
	  printf("请选择");
	  scanf("%d",&t);
	  getchar();
	  if(t==1)
	  {
		  if(cha.mny<100)
		  {
			  printf("手续费不足\n");
			  printf("确认");
			  getchar();
			  return cha;
		  }
		  cha.mny -= 100;
		  printf("确认");
		  getchar();
		  strcpy(cha.v,"世外小村");
		  return cha;
	  }
	}
	printf("\n");
	return cha;
 }
 if(strcmp(cha.v,"野猪洞")==0||strcmp(cha.v,"封魔谷")==0)
 {
	 strcpy(cha.v,"比奇城");
	 return cha;
 }
 return cha;
}

struct CHARACTER Foundtroop(struct CHARACTER cha)
{
 FILE* fp;
 char troop[37];
 char name[20];
 char z = '0';
 char u;
 strcpy(name,"\0");
 int i,k;
 if(cha.trp>=1&&cha.trp<=3)
 {
  return cha;
 }
 printf("请输入队伍名字:");
 gets(cha.trpname);
 fp = fopen(troopfile,"rb");
 if(fp==NULL)
 {
  fp = fopen(troopfile,"wb");
  i = 1;
  fwrite(&i,4,1,fp);
  fwrite(cha.trpname,37,1,fp);
  fwrite(cha.v,20,1,fp);
  fwrite(&z,1,1,fp);
  fwrite(cha.name,20,1,fp);
  fwrite(&z,1,1,fp);
  fwrite(name,20,1,fp);
  fwrite(&z,1,1,fp);
  fwrite(name,20,1,fp);
  fclose(fp);
 }
 else
 {
  fread(&i,4,1,fp);
  k = 1;
  while(k<=i)
  {
   fread(troop,37,1,fp);
   if(strcmp(cha.trpname,troop)==0)
   {
    printf("队伍名重名了\n");
	fclose(fp);
	strcpy(cha.trpname,"\0");
	return cha;
   }
   fread(name,20,1,fp);
   fread(&u,1,1,fp);
   fread(name,20,1,fp);
   fread(&u,1,1,fp);
   fread(name,20,1,fp);
   fread(&u,1,1,fp);
   fread(name,20,1,fp);
   k++;
  }
  fclose(fp);
  strcpy(name,"\0");
  fp = fopen(troopfile,"ab");
  fwrite(cha.trpname,37,1,fp);
  fwrite(cha.v,20,1,fp);
  fwrite(&z,1,1,fp);
  fwrite(cha.name,20,1,fp);
  fwrite(&z,1,1,fp);
  fwrite(name,20,1,fp);
  fwrite(&z,1,1,fp);
  fwrite(name,20,1,fp);
  fclose(fp);
  fp = fopen(troopfile,"rb+");
  i++;
  fwrite(&i,4,1,fp);
  fclose(fp);
 }
 cha.trp = 1;
 strcpy(cha.buddy1,cha.name);
 return cha;
}

struct CHARACTER Uptrp(struct CHARACTER cha)
{
	FILE* fp;
	int k,i=1;
	char troop[37];
	char name[20];
	char u;
	fp = fopen(troopfile,"rb+");
	fread(&k,4,1,fp);
	while(i<=k)
	{
		fread(troop,37,1,fp);
		if(strcmp(troop,cha.trpname)==0)
		{
			fread(name,20,1,fp);
			fread(&cha.b1,1,1,fp);
			fread(cha.buddy1,20,1,fp);
			fread(&cha.b2,1,1,fp);
			fread(cha.buddy2,20,1,fp);
			fread(&cha.b3,1,1,fp);
			fread(cha.buddy3,20,1,fp);
			break;
		}
		fread(name,20,1,fp);
		fread(&u,1,1,fp);
		fread(name,20,1,fp);
		fread(&u,1,1,fp);
		fread(name,20,1,fp);
		fread(&u,1,1,fp);
		fread(name,20,1,fp);
		i++;
	}
	fclose(fp);
	if(strcmp(cha.buddy1,cha.name)==0)
	{
	 cha.trp = 1;
	}
	if(strcmp(cha.buddy2,cha.name)==0)
	{
	 cha.trp = 2;
	}
	if(strcmp(cha.buddy3,cha.name)==0)
	{
	 cha.trp = 3;
	}
	return cha;
}

struct CHARACTER Prepare(struct CHARACTER cha)
{
    FILE* fp;
	int k,i=1;
	char troop[37];
	char name[20];
	char u;
	char n;
	if((cha.trp==1&&cha.b1=='1')||(cha.trp==2&&cha.b2=='1')||(cha.trp==3&&cha.b3=='1'))
	{
	 n = '0';
	}
	else
	{
	 n = '1';
	 if(cha.b1=='2')
	 {
	  n = '2';
	 }
	}
	fp = fopen(troopfile,"rb+");
	fread(&k,4,1,fp);
	while(i<=k)
	{
		fread(troop,37,1,fp);
		if(strcmp(troop,cha.trpname)==0)
		{
			fread(name,20,1,fp);
			if(cha.trp==1)
			{
			 fseek(fp,61L+(i-1)*120L,0);
			 fwrite(&n,1,1,fp);
			 fseek(fp,62L+(i-1)*120L,0);
			}
			else
			{
			 fread(&u,1,1,fp);
			}
			fread(name,20,1,fp);
			if(cha.trp==2)
			{
			 fseek(fp,82L+(i-1)*120L,0);
			 fwrite(&n,1,1,fp);
			 fseek(fp,83L+(i-1)*120L,0);
			}
			else
			{
			 fread(&u,1,1,fp);
			}
			fread(name,20,1,fp);
			if(cha.trp==3)
			{
			 fseek(fp,103L+(i-1)*120L,0);
			 fwrite(&n,1,1,fp);
			 fseek(fp,104L+(i-1)*120L,0);
			}
			else
			{
			 fread(&u,1,1,fp);
			}
			fread(name,20,1,fp);
			break;
		}
		fread(name,20,1,fp);
		fread(&u,1,1,fp);
		fread(name,20,1,fp);
		fread(&u,1,1,fp);
		fread(name,20,1,fp);
		fread(&u,1,1,fp);
		fread(name,20,1,fp);
		i++;
	}
	return cha;
}

struct CHARACTER Outtrp(struct CHARACTER cha)
{
	FILE* fp;
	FILE* ft;
	int k,i=1;
	char troop[37];
	char name[20];
	char u;
	fp = fopen(troopfile,"rb+");
	fread(&k,4,1,fp);
	while(i<=k)
	{
		fread(troop,37,1,fp);
		if(strcmp(troop,cha.trpname)==0)
		{
			fread(name,20,1,fp);
			fread(&cha.b1,1,1,fp);
			fread(cha.buddy1,20,1,fp);
			fread(&cha.b2,1,1,fp);
			fread(cha.buddy2,20,1,fp);
			fread(&cha.b3,1,1,fp);
			fread(cha.buddy3,20,1,fp);
			break;
		}
		fread(name,20,1,fp);
		fread(&u,1,1,fp);
		fread(name,20,1,fp);
		fread(&u,1,1,fp);
		fread(name,20,1,fp);
		fread(&u,1,1,fp);
		fread(name,20,1,fp);
		i++;
	}
	if(strcmp(cha.buddy1,cha.name)==0)
	{
	 cha.trp = 1;
	}
	if(strcmp(cha.buddy2,cha.name)==0)
	{
	 cha.trp = 2;
	}
	if(strcmp(cha.buddy3,cha.name)==0)
	{
	 cha.trp = 3;
	}
   if(cha.trp==1)
   {
    fseek(fp,61L+(i-1)*120L,0);
	strcpy(cha.buddy1,cha.buddy2);
	cha.b1 = cha.b2;
	strcpy(cha.buddy2,cha.buddy3);
	cha.b2 = cha.b3;
	strcpy(cha.buddy3,"\0");
	cha.b3 = '0';
	fwrite(&cha.b1,1,1,fp);
	fwrite(cha.buddy1,20,1,fp);
	fwrite(&cha.b2,1,1,fp);
	fwrite(cha.buddy2,20,1,fp);
	fwrite(&cha.b3,1,1,fp);
	fwrite(cha.buddy3,20,1,fp);
	fclose(fp);
	if(strcmp(cha.buddy1,"\0")==0)
	{
	 fp = fopen(troopfile,"rb");
	 ft = fopen(tfile,"wb");
	 char t;
	 int n;
	 t = fgetc(fp);
	 while(!feof(fp))
	 {
	  fputc(t,ft);
	  t = fgetc(fp);
	 }
	 fclose(fp);
	 fclose(ft);
	 fp = fopen(troopfile,"wb");
	 ft = fopen(tfile,"rb");
     fread(&k,4,1,ft);
	 k = k-1;
	 fwrite(&k,4,1,fp);
	 n = 2;
	 while(n<=i)
	 {
	  fread(troop,37,1,ft);
	  fwrite(troop,37,1,fp);
	  fread(name,20,1,ft);
	  fwrite(name,20,1,fp);
	  fread(&u,1,1,ft);
	  fwrite(&u,1,1,fp);
	  fread(name,20,1,ft);
	  fwrite(name,20,1,fp);
	  fread(&u,1,1,ft);
	  fwrite(&u,1,1,fp);
	  fread(name,20,1,ft);
	  fwrite(name,20,1,fp);
	  fread(&u,1,1,ft);
	  fwrite(&u,1,1,fp);
	  fread(name,20,1,ft);
	  fwrite(name,20,1,fp);
	  n++;
	 }
	 n++;
	 fseek(ft,120L,1);
	 while(n<=k+2)
	 {
	  fread(troop,37,1,ft);
	  fwrite(troop,37,1,fp);
	  fread(name,20,1,ft);
	  fwrite(name,20,1,fp);
	  fread(&u,1,1,ft);
	  fwrite(&u,1,1,fp);
	  fread(name,20,1,ft);
	  fwrite(name,20,1,fp);
	  fread(&u,1,1,ft);
	  fwrite(&u,1,1,fp);
	  fread(name,20,1,ft);
	  fwrite(name,20,1,fp);
	  fread(&u,1,1,ft);
	  fwrite(&u,1,1,fp);
	  fread(name,20,1,ft);
	  fwrite(name,20,1,fp);
	  n++;
	 }
	 fclose(ft);
	 fclose(fp);
	 unlink(tfile);
	}
   }
   if(cha.trp==2)
   {
    fseek(fp,82L+(i-1)*120L,0);
	strcpy(cha.buddy2,cha.buddy3);
	cha.b2 = cha.b3;
	strcpy(cha.buddy3,"\0");
	cha.b3 = '0';
	fwrite(&cha.b2,1,1,fp);
	fwrite(cha.buddy2,20,1,fp);
	fwrite(&cha.b3,1,1,fp);
	fwrite(cha.buddy3,20,1,fp);
	fclose(fp);
   }
   if(cha.trp==3)
   {
    fseek(fp,103L+(i-1)*120L,0);
	strcpy(name,"\0");
	cha.b3 = '0';
	fwrite(&cha.b3,1,1,fp);
	fwrite(name,20,1,fp);
	fclose(fp);
   }
   strcpy(cha.trpname,"\0");
   cha.trp = 0;
   strcpy(cha.buddy1,"\0");
   strcpy(cha.buddy2,"\0");
   strcpy(cha.buddy3,"\0");
   cha.b1 = '0';
   cha.b2 = '0';
   cha.b3 = '0';
   return cha;
}

struct CHARACTER Troops(struct CHARACTER cha)
{
 FILE* fp;
 FILE* ft;
 char troop[37];
 char troop1[100][37];
 char troop2[100][37];
 char name[20];
 char name1[20];
 char name2[20];
 char name3[20];
 int i,k,j,t;
 char z = '0';
 char h = '1';
 char u;
 for(i=0;i<=99;i++)
 {
  strcpy(troop1[i],"\0");
  strcpy(troop2[i],"\0");
 }
 fp = fopen(troopfile,"rb");
 if(fp==NULL)
 {
  fp = fopen(troopfile,"wb");
  i = 0;
  fwrite(&i,4,1,fp);
 }
 fclose(fp);
  i = 0;
  fp = fopen(troopfile,"rb");
  fread(&k,4,1,fp);
  while(i<=k-1)
  {
   fread(troop1[i],37,1,fp);
   fread(name,20,1,fp);
   fread(&u,1,1,fp);
   fread(name1,20,1,fp);
   fread(&u,1,1,fp);
   fread(name2,20,1,fp);
   fread(&u,1,1,fp);
   fread(name3,20,1,fp);
   if(strcmp(name,cha.v)!=0||(strcmp(name1,"\0")!=0 && strcmp(name2,"\0")!=0 && strcmp(name3,"\0")!=0))
   {
	k--;
    continue;
   }
   printf("%d.%s\n",i+1,troop1[i]);
   printf("^1.%s",name1);
   printf(" 2.%s",name2);
   printf(" 3.%s\n",name3);
   i++;
  }
  printf("\n请选择队伍");
  scanf("%d",&j);
  getchar();

  fseek(fp,0L,0);
  fread(&k,4,1,fp);
  i = 0;
  t = 0;
  int g = 1;
  while(i<=k-1)
  {
   fread(troop2[i],37,1,fp);
   if(strcmp(troop2[i],troop1[j-1])==0)
   {
    t = g;
   }
   fread(name,20,1,fp);
   fread(&u,1,1,fp);
   fread(name1,20,1,fp);
   fread(&u,1,1,fp);
   fread(name2,20,1,fp);
   fread(&u,1,1,fp);
   fread(name3,20,1,fp);
   g++;
   if(strcmp(name,cha.v)!=0||(strcmp(name1,"\0")!=0 && strcmp(name2,"\0")!=0 && strcmp(name3,"\0")!=0))
   {
	k--;
    continue;
   }
   i++;
  }
  fclose(fp);
  
  if(j<=k&&j>=1)
  {
   if(strcmp(troop1[j-1],troop2[j-1])!=0)
   {
    printf("无法加入\n");
    return cha;
   }
   fp = fopen(troopfile,"rb+");
   fseek(fp,4L+(t-1)*120L,0);
   fread(cha.trpname,37,1,fp);
   fread(name,20,1,fp);
   fread(&u,1,1,fp);
   fread(name,20,1,fp);
   cha.b1 = u;
   strcpy(cha.buddy1,name);
   fread(&u,1,1,fp);
   fread(name,20,1,fp);
   if(strcmp(name,"\0")==0)
   {
    fseek(fp,83L+(t-1)*120L,0);
	fwrite(cha.name,20,1,fp);
	fclose(fp);
	cha.trp = 2;
	strcpy(cha.buddy2,cha.name);
   }
   else
   {
	cha.b2 = u;
	strcpy(cha.buddy2,name);
	fread(&u,1,1,fp);
    fread(name,20,1,fp);
    if(strcmp(name,"\0")==0)
    {
     fseek(fp,104L+(t-1)*100L,0);
	 fwrite(cha.name,20,1,fp);
	 fclose(fp);
	 cha.trp = 3;
	 strcpy(cha.buddy3,cha.name);
    }
	else
	{
	 cha.b3 = u;
	 strcpy(cha.buddy3,name);
	}
   }
  }      //j
 return cha;
}

struct CHARACTER Group(struct CHARACTER cha)
{
	int k,y=0;
	printf("1.创建组队\n");
	printf("2.查看组队\n");
	printf("请选择");
	scanf("%d",&k);
	getchar();
	if(k==1)
	{
		cha = Foundtroop(cha);
	}
	if(k==2)
	{
		cha = Troops(cha);
	}
	if(cha.trp==0)
	{
		return cha;
	}
	while(y==0)
	{
		printf("                              //组队等候室//\n\n");
		printf("^1.%s",cha.buddy1);
		if(cha.b1=='1')
		{
			printf("* ");
		}
		else
		{
			printf("  ");
		}
		printf(" 2.%s",cha.buddy2);
		if(cha.b2=='1')
		{
			printf("* ");
		}
		else
		{
			printf("  ");
		}
		printf(" 3.%s",cha.buddy3);
		if(cha.b3=='1')
		{
			printf("* ");
		}
		else
		{
			printf("  ");
		}
		printf("\n");
		if((cha.trp==1&&cha.b1=='1')||(cha.trp==2&&cha.b2=='1')||(cha.trp==3&&cha.b3=='1'))
		{
		 printf("1.刷新  2.取消准备  3.退队  ");
		}
		else
		{
		 printf("1.刷新  2.准备  3.退队  ");
		}
		if(((cha.b1=='1'&&cha.b2=='1'&&cha.b3=='1'&&strcmp(cha.buddy1,"\0")!=0&&strcmp(cha.buddy2,"\0")!=0&&strcmp(cha.buddy3,"\0")!=0)||
		   (cha.b1=='1'&&cha.b2=='1'&&cha.b3=='0'&&strcmp(cha.buddy1,"\0")!=0&&strcmp(cha.buddy2,"\0")!=0&&strcmp(cha.buddy3,"\0")==0)||
		   (cha.b1=='1'&&cha.b2=='0'&&cha.b3=='0'&&strcmp(cha.buddy1,"\0")!=0&&strcmp(cha.buddy2,"\0")==0&&strcmp(cha.buddy3,"\0")==0))&&
		   cha.trp==1)
		{
		 printf("4.进入");
		}
		printf("\n");
		printf("请选择");
		scanf("%d",&k);
		getchar();
		if(k==1)
		{
			cha = Uptrp(cha);
			if(cha.b1=='2')
			{
			 cha = Upgrade(cha);
			 cha = Prepare(cha);
			 cha = Uptrp(cha);
			 cha.b1 = '0';
			}
		}
		if(k==2)
		{
			if(cha.b1=='2')
			{
			 printf("队伍已进入副本\n");
			 cha = Upgrade(cha);
			 cha = Prepare(cha);
			 cha = Uptrp(cha);
			 cha.b1 = '0';
			}
			else
			{
		     cha = Prepare(cha);
			 cha = Uptrp(cha);
			}
		}
		if(k==3)
		{
		    cha = Outtrp(cha);
			y = 1;
		}
		if(k==4&&cha.trp==1)
		{
		    cha = Uptrp(cha);
			if((cha.b1=='1'&&cha.b2=='1'&&cha.b3=='1'&&strcmp(cha.buddy1,"\0")!=0&&strcmp(cha.buddy2,"\0")!=0&&strcmp(cha.buddy3,"\0")!=0)||
		      (cha.b1=='1'&&cha.b2=='1'&&cha.b3=='0'&&strcmp(cha.buddy1,"\0")!=0&&strcmp(cha.buddy2,"\0")!=0&&strcmp(cha.buddy3,"\0")==0)||
		      (cha.b1=='1'&&cha.b2=='0'&&cha.b3=='0'&&strcmp(cha.buddy1,"\0")!=0&&strcmp(cha.buddy2,"\0")==0&&strcmp(cha.buddy3,"\0")==0))
			{
			   cha.b1 = '2';
			   cha = Prepare(cha);
		       cha = Upgrade(cha);
			   cha.b1 = '1';
			   cha = Prepare(cha);
			   cha = Uptrp(cha);
			}
		}
	}
	return cha;
}

struct CHARACTER Player(struct CHARACTER cha)
{
	FILE* f3;
	FILE* fp;
	int y,k,i,d,p,s;
	double a[12];
	struct GOODS c[17];
	char name[20];
    struct EQUIPMENT b[24];
	f3 = fopen(onlinefile,"rb");
	fread(&y,4,1,f3);
	k = 1;
	i = 1;
	struct MONSTER n[100];
	while(k<=y)
	{
		fread(name,20,1,f3);
		fread(n[i-1].name,20,1,f3);
		if(strcmp(n[i-1].name,"\0")!=0&&strcmp(cha.name,n[i-1].name)!=0)
		{
			printf("%d.%s\n",i,n[i-1].name);
			i++;
		}
		k++;
	}
	i--;
	printf("\n");
	fclose(f3);
	printf("请选择");
	scanf("%d",&d);
	getchar();
	k = 1;
	while(k!=3&&d>=1&&d<=i)
	{
		printf("1.查看  2.交易  3.退出\n");
		printf("请选择");
		scanf("%d",&k);
		getchar();
		f3 = fopen(onlinefile,"rb");
		fseek(f3,4L,0);
		char filename[100];
		char fileroad[100];
		strcpy(filename,savefolder);
		char acct[20];
		if(k==1)
		{
			fread(acct,20,1,f3);
			fread(name,20,1,f3);
			while(strcmp(name,n[d-1].name)!=0)
			{
				fread(acct,20,1,f3);
				fread(name,20,1,f3);
			}
			strcat(filename,acct);
			strcpy(acct,".ys");
			strcat(filename,acct);
			fclose(f3);
			f3 = fopen(filename,"rb");
			fread(&p,4,1,f3);
			fread(name,20,1,f3);
			while(strcmp(name,n[d-1].name)!=0)
			{
				fseek(f3,size-20,1);
				fread(name,20,1,f3);
			}
			printf("\n");
			puts(name);
			fread(acct,20,1,f3);
			fread(name,20,1,f3);
			fread(a,8,12,f3);
			printf("等级       %d\n",(int)a[0]);
			printf("职业       %s\n", acct);
			fread(c,sizeof(struct GOODS),17,f3);
			fread(b,sizeof(struct EQUIPMENT),24,f3);
			fclose(f3);
			i = 1;
			while(i==1)
			{
				printf("       1.%c\n\n",b[0].rank);
				printf("2.%c          6.%c\n\n",b[1].rank,b[5].rank);
				printf("3.%c          7.%c\n\n",b[2].rank,b[6].rank);
				printf("4.%c   5.%c\n",b[3].rank,b[4].rank);
				printf("请选择");
				scanf("%d",&s);
				getchar();
				if(s!=1&&s!=2&&s!=3&&s!=4&&s!=5&&s!=6&&s!=7)
				{
					break;
				}
				s--;
				if(strcmp(b[s].name,"\0")!=0)
				{
					if(strcmp(cha.equ[s].name,"\0")==0)
					{
						printf("   ");
						printf("%s\n",b[s].name);
						printf("种类:%s\n", b[s].kind);
						printf("装备级数   %d\n", b[s].grd);
						printf("装备级别   %c\n", b[s].rank);
						printf("HP         +%.0lf\n", b[s].axHP);
						printf("MP         +%.0lf\n", b[s].axMP);
						printf("攻击力     +%.0lf\n", b[s].aatc);
						printf("防御力     +%.0lf\n", b[s].adef);
					}
					else
					{
						printf("   ");
						printf("%s",b[s].name);
						printf("           |   ");
						printf("%s\n",cha.equ[s].name);
						printf("种类:%s             |种类:%s\n", b[s].kind,cha.equ[s].kind);
						printf("装备级数   %d         |装备级数   %d\n", b[s].grd,cha.equ[s].grd);
						printf("装备级别   %c          |装备级别   %c\n", b[s].rank,cha.equ[s].rank);
						printf("HP         +%-5.0lf     |HP         +%.0lf\n", b[s].axHP,cha.equ[s].axHP);
						printf("MP         +%-5.0lf     |MP         +%.0lf\n", b[s].axMP,cha.equ[s].axMP);
						printf("攻击力     +%-5.0lf     |攻击力     +%.0lf\n", b[s].aatc,cha.equ[s].aatc);
						printf("防御力     +%-5.0lf     |防御力     +%.0lf\n", b[s].adef,cha.equ[s].adef);
					}
					printf("确认");
					getchar();
					printf("\n");
				}
				if(strcmp(b[s].name,"\0")==0)
				{
					printf("无装备\n");
					printf("确认");
					getchar();
					printf("\n");
				}
			}  //i=1
		}   //k=1
		if(k==2)
		{
			FILE* fx;
			FILE* f2;
			clock_t t1;
			clock_t t2;
			int ti;
			i = 0;
			s = 0;
			/*
			f2 = fopen("temp.ys","rb");
			while(!feof(f2))
			{
				acct[i] = fgetc(f2);
				i++;
			}
			fclose(f2);
			*/
			strcpy(acct,act);
			strcat(acct,".ys");
			strcpy(fileroad,storyfolder);
			strcat(fileroad,acct);
			fx = fopen(fileroad,"wb");
			i = 0;
			fwrite(&i,4,1,fx);
			fclose(fx);
			fread(acct,20,1,f3);
			fread(name,20,1,f3);
			while(strcmp(name,n[d-1].name)!=0)
			{
				fread(acct,20,1,f3);
				fread(name,20,1,f3);
			}
			strcpy(filename,storyfolder);
			strcpy(name,".ys");
			strcat(acct,name);
			strcat(filename,acct);
			fclose(f3);
			t1 = clock();
			printf("请等待...10");
			t2 = clock();
			ti = 0;
			while((t2-t1)/1000<=10)
			{
				fx = fopen(filename,"rb");
				if(fx!=NULL)
				{
					fclose(fx);
					break;
				}
				if((t2-t1)/1000==ti)
				{
				 printf("\b \b\b \b%2d",10-ti);
				 ti++;
				}
				t2 = clock();
			}
			printf("\n");
			if((t2-t1)/1000<=10)
			{
              loop1:i = 0;
	          printf("背包\n");
	          printf("0.金币     %.0lf\n", cha.mny);
	          while (cha.goods[i].nam != '\0'&&i<=16)
			  {
				  if(cha.goods[i].nam=='*')
				  {
					  printf("%d.%c\n", i + 1, cha.goods[i].nam);
				  }
				  else
				  {
				      printf("%d.%c×%d\n", i + 1, cha.goods[i].nam,cha.goods[i].q);
				  }
				  i++;
			  }
			  i++;
			  printf("%d.确定 %d.取消\n",i,i+1);
			  int g;
			  g = i;
			  printf("请选择");
			  scanf("%d",&i);
			  getchar();
			  int l;
			  int j=0,n=6,r;
			  struct CHARACTER give;
			  struct CHARACTER get;
			  if(i==0)
			  {
				  printf("请输入金币数:");
				  scanf("%lf",&give.mny);
				  getchar();
				  if(give.mny>cha.mny)
				  {
					  give.mny = cha.mny;
				  }
				  if(give.mny<0)
				  {
					  give.mny = 0;
				  }
				  printf("确定?\n");
				  printf("1.是 2.否");
				  scanf("%d",&l);
				  getchar();
				  if(l==1)
				  {
					  fx = fopen(fileroad,"ab");
					  fwrite(&give.mny,8,1,fx);
					  fclose(fx);
					  s = 1;           //1为金币
					  r = s;
					  t1 = clock();
					  fx = fopen(fileroad,"rb+");
					  fwrite(&s,4,1,fx);
					  fclose(fx);
					  printf("请等待对方答复10");
					  t2 = clock();
					  ti = 0;
					  while((t2-t1)/1000<=10)
					  {
						  fx = fopen(filename,"rb");
						  if(fx==NULL)
						  {
							  printf("\n交易已被取消\n");
							  goto loop3;
						  }
						  fread(&s,4,1,fx);
						  fclose(fx);
						  if(s>=1)
						  {
							  if(s==9)
							  {
								  printf("\n交易已被取消\n");
								  break;
							  }
							  cha.mny -= give.mny;
							  goto loop2;
						  }
						  if((t2-t1)/1000==ti)
						  {
							  printf("\b \b\b \b%2d",10-ti);
							  ti++;
						  }
						  t2 = clock();
					  }
					  printf("\n");
					  unlink(fileroad);
				  }
				  else
				  {
					  goto loop1;
				  }
			  }
			  if(cha.goods[i-1].nam == '@'||cha.goods[i-1].nam == '%'||cha.goods[i-1].nam == '#'||cha.goods[i-1].nam == '*')
			  {
				  printf("该物品不能交易\n");
				  printf("确定");
				  getchar();
				  printf("\n");
				  goto loop1;
			  }
			  if(cha.goods[i-1].nam == 'a'||cha.goods[i-1].nam == 'b'||cha.goods[i-1].nam == '$'||cha.goods[i-1].nam == 'c')
			  {
				  printf("请输入数量:");
				  scanf("%d",&give.goods[0].q);
				  getchar();
				  if(give.goods[0].q>cha.goods[i-1].q)
				  {
					  give.goods[0].q = cha.goods[i-1].q;
				  }
				  if(give.goods[0].q<0)
				  {
					  give.goods[0].q = 0;
				  }
				  give.goods[0].nam = cha.goods[i-1].nam;
				  strcpy(give.goods[0].name,cha.goods[i-1].name);
				  printf("确定?\n");
				  printf("1.是 2.否");
				  scanf("%d",&l);
				  getchar();
				  if(l==1)
				  {
					  fx = fopen(fileroad,"ab");
					  fwrite(&give.goods[0],sizeof(struct GOODS),1,fx);
					  fclose(fx);
					  s = 3;
					  r = s;
					  t1 = clock();
					  n = i-1;
					  fx = fopen(fileroad,"rb+");
					  fwrite(&s,4,1,fx);
					  fclose(fx);
					  printf("请等待对方答复10");
					  t2 = clock();
					  ti = 0;
					  while((t2-t1)/1000<=10)
					  {
						  fx = fopen(filename,"rb");
						  if(fx==NULL)
						  {
							  printf("\n交易已被取消\n");
							  goto loop3;
						  }
						  fread(&s,4,1,fx);
						  fclose(fx);
						  if(s>=1)
						  {
							  if(s==9)
							  {
								  printf("\n交易已被取消\n");
								  break;
							  }
						      cha.goods[i-1].q -= give.goods[0].q;
							  if(cha.goods[i-1].q==0)
							  {
								  j = i-1;
								  while(j<=cha.t-2)
								  {
									  cha.goods[j] = cha.goods[j+1];
									  j++;
								  }
								  cha.goods[j].nam = '\0';
								  strcpy(cha.goods[j].name,"\0");
								  cha.goods[j].q = 0;
								  cha.t--;
							  }
							  goto loop2;
						  }
						  if((t2-t1)/1000==ti)
						  {
							  printf("\b \b\b \b%2d",10-ti);
							  ti++;
						  }
						  t2 = clock();
					  }
					  printf("\n");
					  unlink(fileroad);
				  }
				  else
				  {
					  goto loop1;
				  }
			  }
			  if(i==g)
			  {
				  s = 10;
				  r = s;
				  t1 = clock();
				  fx = fopen(fileroad,"rb+");
				  fwrite(&s,4,1,fx);
				  fclose(fx);
				  printf("请等待对方答复10");
				  t2 = clock();
				  ti = 0;
				  while((t2-t1)/1000<=10)
				  {
					  fx = fopen(filename,"rb");
					  if(fx==NULL)
					  {
						  goto loop3;
					  }
					  fread(&s,4,1,fx);
					  fclose(fx);
					  if(s>=1)
					  {
						  if(s==9)
						  {
						   printf("\n交易已被取消\n");
						   goto  loop3;
						  }
						  goto loop2;
					  }
					  if((t2-t1)/1000==ti)
					  {
						  printf("\b \b\b \b%2d",10-ti);
						  ti++;
					  }
					  t2 = clock();
				  }     //while
				  printf("\n");
				  unlink(fileroad);
			  }
        loop2:if(s>=1&&s!=9)
			  {
				  fx = fopen(filename,"rb");
				  fseek(fx,4L,0);
				  if(s==1)
				  {
					  fread(&get.mny,8,1,fx);
					  fclose(fx);
					  printf("\n对方给你\n");
					  printf("金币%.0lf\n",get.mny);
					  printf("确定?\n");
					  printf("1.是 2.否");
					  scanf("%d",&n);
					  getchar();
				  }
				  if(s==3)
				  {
					  fread(&get.goods[0],sizeof(struct GOODS),1,fx);
					  fclose(fx);
					  printf("\n对方给你\n");
					  printf("物品%c×%d\n",get.goods[0].nam,get.goods[0].q);
					  printf("确定?\n");
					  printf("1.是 2.否");
					  scanf("%d",&n);
					  getchar();
				  }
				  if(s==10)
				  {
					  fclose(fx);
					  printf("\n对方给你\n");
					  printf("无\n");
					  printf("确定?\n");
					  printf("1.是 2.否");
					  scanf("%d",&n);
					  getchar();
				  }
				  if(n==1)
				  {
					  fx = fopen(fileroad,"rb");
					  fread(&s,4,1,fx);
					  fclose(fx);
					  fx = fopen(fileroad,"rb+");
					  s = 10+s;
					  fwrite(&s,4,1,fx);
					  fclose(fx);
					  t1 = clock();
					  printf("请等待对方答复10");
					  t2 = clock();
					  ti = 0;
					  while((t2-t1)/1000<=10)
					  {
						  fx = fopen(filename,"rb");
						  if(fx==NULL)
						  {
							  printf("\n交易已被取消\n");
							  s = 9;
							  goto loop4;
						  }
						  fread(&s,4,1,fx);
						  fclose(fx);
						  if(s==9)
						  {
							  printf("\n交易已被取消\n");
							  goto loop4;
						  }
						  if(s>=11)
						  {
							  break;
						  }
						  if((t2-t1)/1000==ti)
						  {
							  printf("\b \b\b \b%2d",10-ti);
							  ti++;
						  }
						  t2 = clock();
					  }
					  printf("\n");
					  if((t2-t1)/1000>10)
					  {
					   goto loop4;
					  }
					  if(s>=11)
					  {
						  if(s==11)
						  {
							  cha.mny += get.mny;
							  printf("得到金币%.0lf\n",get.mny);
						  }
						  if(s==13)
						  {
							  n = cha.t;
							  if(get.goods[0].nam=='a'||get.goods[0].nam=='b'||get.goods[0].nam=='$'||cha.goods[i-1].nam == 'c')
							  {
								  i=0;
								  while(i<=cha.t-1)
								  {
									  if(cha.goods[i].nam==get.goods[0].nam)
									  {
										  break;
									  }
									  i++;
								  }
								  if(i<cha.t)
								  {
									  cha.goods[i].q += get.goods[0].q;
								  }
								  else
								  {
									  cha.goods[n].nam = get.goods[0].nam;
									  cha.goods[n].q = get.goods[0].q;
									  strcpy(cha.goods[n].name,get.goods[0].name);
									  cha.t += 1;
								  }
							  }
							  printf("得到物品%c×%d\n",get.goods[0].nam,get.goods[0].q);
						  }
						  t1 = clock();
						  t2 = clock();
						  while((t2-t1)/1000<1)
						  {
							  t2 = clock();
						  }
						  unlink(fileroad);
					  }
				  }
				  else
				  {
                loop4:if(r==1)
					  {
						  cha.mny += give.mny;
					  }
					  if(r==3)
					  {
						  n = cha.t;
						  cha.goods[n].nam = give.goods[0].nam;
						  strcpy(cha.goods[n].name,give.goods[0].name);
						  cha.goods[n].q = give.goods[0].q;
						  cha.t++;
					  }
					  i = g;
					  i++;
				  }
			   }
			  if(i>g)
			  {
				s = 9;
				fx = fopen(fileroad,"rb+");
				fwrite(&s,4,1,fx);
				fclose(fx);
				t1 = clock();
				t2 = clock();
				while((t2-t1)/1000<1)
				{
					t2 = clock();
				}
                loop3:unlink(fileroad);
			  }
			}
			else
			{
				unlink(fileroad);
			}
			return cha;
		}   //k=2
	}      //while
	return cha;
}

void Save(struct CHARACTER cha)
{
    double a[12];
	struct GOODS c[17];
    struct EQUIPMENT b[24];
    int i,p;
    FILE* fp;
	
	fp = fopen(cha.filename,"rb+");
	fread(&p,4,1,fp);
	fseek(fp,(cha.p-1)*size,1);
	fwrite(cha.name,20,1,fp);
	fwrite(cha.prof,20,1,fp);
	fwrite(cha.v,20,1,fp);
	a[0]=(double)cha.grd;
	a[1]=cha.HP;
	a[2]=cha.xHP;
	a[3]=cha.MP;
	a[4]=cha.xMP;
	a[5]=cha.atc;
	a[6]=cha.def;
	a[7]=cha.mny;
	a[8]=cha.exp;
	a[9]=cha.xexp;
	a[10]=(double)cha.t;
	a[11]=(double)cha.e;
	i=0;
	while(i<=16)
	{
		c[i]=cha.goods[i];
		b[i]=cha.equ[i];
		i++;
	}
	while(i<=23)
	{
		b[i]=cha.equ[i];
		i++;
	}
	fwrite(a,8,12,fp);
	fwrite(c,sizeof(struct GOODS),17,fp);
	fwrite(b,sizeof(struct EQUIPMENT),24,fp);
	fclose(fp);
}

void SelePla(struct CHARACTER cha)
{
	FILE* f;
	int k;
	char name[20];
	printf("\n");
	f = fopen(onlinefile,"rb+");
	fseek(f,4L,0);
	k = 1;
	fread(name,20,1,f);
	while(strcmp(act,name)!=0)
	{
		fread(name,20,1,f);
		k++;
		fread(name,20,1,f);
	}
	strcpy(name,"\0");
	fseek(f,4L+k*40L-20L,0);
	fwrite(name,20,1,f);
	fclose(f);
}

void GameOver()
{
	int i,y,k,d;
	FILE* f3;
	FILE* fp;
	char name[20];
	printf("确认?\n");
	printf("1.是 2.否");
	scanf("%d",&i);
	getchar();
	if(i==1)
	{
		printf("游戏结束");
		f3 = fopen(onlinefile,"rb");
		fp = fopen(tfile,"wb");
		char ch;
		ch = fgetc(f3);
		while(!feof(f3))
		{
			fputc(ch,fp);
			ch = fgetc(f3);
		}
		fclose(f3);
		fclose(fp);
		f3 = fopen(onlinefile,"wb");
		fp = fopen(tfile,"rb");
		fread(&y,4,1,fp);
		y--;
		fwrite(&y,4,1,f3);
		y++;
		d = 1;
		fread(name,20,1,fp);
		while(strcmp(act,name)!=0)
		{
			fread(name,20,1,fp);
			d++;
			fread(name,20,1,fp);
		}
		fseek(fp,4L,0);
		k = 1;
		while(k<=d-1)
		{
			fread(name,20,1,fp);
			fwrite(name,20,1,f3);
			fread(name,20,1,fp);
			fwrite(name,20,1,f3);
			k++;
		}
		fseek(fp,40L,1);
		while(k<=y-1)
		{
			fread(name,20,1,fp);
			fwrite(name,20,1,f3);
			fread(name,20,1,fp);
			fwrite(name,20,1,f3);
			k++;
		}
		fclose(f3);
		fclose(fp);
		unlink(tfile);
		//unlink("temp.ys");
		exit(0);
	}
}

void Printf(struct CHARACTER cha)
{
    int i,k,n,t;
	int des=0;
	
    while(cha.grd<=grade)
	{
	 printf("                            //%s//\n\n",cha.v);
	 printf("%s",cha.name);
	 printf("   %d级\n", cha.grd);
	 if(strcmp(cha.v,"世外小村")==0||strcmp(cha.v,"比奇城")==0)
	 {
		cha.HP = cha.xHP;
		cha.MP = cha.xMP;
		des=0;
	 }
	 else
	 {
		des=1;
	 }
	 printf("HP         %.0lf/%.0lf\n", cha.HP, cha.xHP);
	 printf("MP         %.0lf/%.0lf\n", cha.MP, cha.xMP);
	 printf("经验       %.2lf%%\n", cha.exp/cha.xexp*100);
	 
	 Save(cha);
	 
	 if (cha.exp>cha.xexp)
	 {
		 cha = Upgrade(cha);
	 }
	 else
	 {
	   if(des==0)
	   {
		printf(" 1.传送员    2.商店    3.查看角色    4.查看背包    5.在线操作\n");
		printf(" 7.更换角色    8.结束游戏\n请选择");
	   }
	   if(des==1)
	   {
		printf(" 1.打怪    2.回城    3.查看角色    4.查看背包");
	    if(strcmp(cha.v,"沃玛寺庙")==0)
		{
		  printf("    5.组队操作");
		}
	    printf("\n");
	    printf(" 7.更换角色    8.结束游戏\n请选择");
	   }
	   scanf("%d", &n);
	   getchar();
	   if(des==0)
	   {
		   if(n==1)
		   {
			   cha = Go(cha);
		   }
		   if(n==2)
		   {
			   t = 0;
			   while(t==0)
			   {
				   printf("无论你是买还是卖，我都赚了，呵呵呵!\n");
				   printf("1.购买装备  2.购买物品  3.卖出物品  4.制作装备\n请选择");
				   scanf("%d", &k);
				   getchar();
				   if(k==1)
				   {
					   printf("不好意思，我这里只有D级装备了，请问要哪一个\n");
					   cha = BuyEqu(cha);
				   }
				   if(k==2)
				   {
					   cha = BuyGoods(cha);
				   }
				   if(k==3)
				   {
					   cha = Sell(cha);
				   }
				   if(k==4)
				   {
					   cha = MakeEqu(cha);
					   printf("确认");
					   getchar();
					   printf("\n");
				   }
				   if(k!=1&&k!=2&&k!=3&&k!=4)
				   {
					   t = 1;
					   printf("\n");
				   }
			   }
		   }
	   }
	   if(des==1)
	   {
		   if(n==1)
		   {
			   cha = Upgrade(cha);
			   if(cha.n==-1)
			   {
				   cha.n = 0;
				   strcpy(cha.v,"世外小村");
				   continue;
			   }
		   }
		   if(n==2)
		   {
			   cha = Go(cha);
		   }
	   }
	   if(n==3)
	   {
		   i = 0;
		   while(i==0)
		   {
			   printf("1.查看能力  2.查看装备  3.查看技能\n");
			   printf("请选择");
			   scanf("%d",&k);
			   getchar();
			   if(k==1)
			   {
				   SeeAbi(cha);
			   }
			   if(k==2)
			   {
				   printf("\n");
				   cha.n = 0;
				   cha = SeeEqu(cha);
				   printf("\n");
			   }
			   if(k==3)
			   {
				   SeeSkill(cha);
				   printf("\n");
			   }
			   if(k!=1&&k!=2&&k!=3)
			   {
				   i = 1;
			   }
		   }
	   }	    
	   if(n==4)
	   {
		   cha = SeeGoods(cha);
		   printf("\n");
	   }
	   if(des==0)
	   {
		   if(n==5)
		   {
			   printf("1.在线玩家\n");
			   printf("请选择");
			   scanf("%d",&k);
			   getchar();
			   if(k==1)
			   {
				   cha = Player(cha);
			   }
		   }
	   }
	   if(des==1)
	   {
		   if(strcmp(cha.v,"沃玛寺庙")==0)
		   {
			   if(n==5)
			   {
				   cha = Group(cha);
			   }
		   }
	   }
	   if(n==7)
	   {
		   SelePla(cha);
		   return;
	   }
	   if(n==8)
	   {
		   GameOver();
	   }
	   if(n!=1&&n!=2&&n!=3&&n!=4&&n!=5&&n!=6&&n!=7&&n!=8)
	   {
		   printf("\n");
	   }
     }
	}
}

void Choice(struct CHARACTER cha)
{
    FILE* fr;
	FILE* f1;
    FILE* f2;
	FILE* f3;
    double a[12];
    struct GOODS c[17];
    struct EQUIPMENT b[24];
	char name[20];
	//char filename[100];
    int k,t=0,d,s,j,i=0;
	int p;
	strcpy(cha.filename,savefolder);
	strcat(cha.filename,act);
	strcat(cha.filename,".ys");
	
    fr = fopen(cha.filename,"rb");
    if(fr==NULL)
	{
     p = 0;
	}
	else
	{
	 fread(&p,4,1,fr);
	 fclose(fr);
	}
    
    while(t==0)
	{
     printf("1.选择角色  2.创建角色  3.删除角色  4.结束游戏\n");
	 printf("请选择");
     scanf("%d",&t);
	 getchar();

     while(t==1)
	 {
	  fr = fopen(cha.filename,"rb");
      if(fr==NULL)
	  {
	   printf("无角色\n");
	   printf("\n");
	   t = 0;
	  }
	  else
	  {
	   fread(&p,4,1,fr);
	   j = 1;
	   while(j<=p)
	   {
	    printf("%d.",j);
	    fread(cha.name,20,1,fr);
		fread(cha.prof,20,1,fr);
		fseek(fr,20L,1);
		fread(a,8,12,fr);
		printf("%s    %s  %d级\n",cha.name,cha.prof,(int)a[0]);
		fseek(fr,(size-156),1);
		j++;
	   }
	   printf("请选择");
	   scanf("%d",&d);
	   getchar();
	   if(d<=p && d>=1)
	   {
		f3 = fopen(onlinefile,"rb+");
		fseek(f3,4L,0);
		k = 1;
		fread(name,20,1,f3);
        while(strcmp(act,name)!=0)
		{
		 fread(name,20,1,f3);
		 k++;
		 fread(name,20,1,f3);
		}
		cha.p = d;
		fseek(fr,4L+((d-1)*size),0);
		fread(cha.name,20,1,fr);
		fseek(f3,4L+k*40L-20L,0);
		fwrite(cha.name,20,1,f3);
		fclose(f3);
		fread(cha.prof,20,1,fr);
		fread(cha.v,20,1,fr);
	    fread(a,8,12,fr);
	    fread(c,sizeof(struct GOODS),17,fr);
	    fread(b,sizeof(struct EQUIPMENT),24,fr);
	    cha.grd=(int)a[0];
	    cha.HP=a[1];
	    cha.xHP=a[2];
		cha.MP=a[3];
		cha.xMP=a[4];
	    cha.atc=a[5];
	    cha.def=a[6];
	    cha.mny=a[7];
	    cha.exp=a[8];
	    cha.xexp=a[9];
	    cha.t=(int)a[10];
	    cha.e=(int)a[11];
	    k=0;
	    while(k<=16)
		{
		 cha.goods[k] = c[k];
		 cha.equ[k] = b[k];
		 k++;
		}
		while(k<=23)
		{
		 cha.equ[k] = b[k];
		 k++;
		}
	    fclose(fr);

		cha.trp = 0;
		strcpy(cha.trpname,"\0");
		strcpy(cha.buddy1,"\0");
		strcpy(cha.buddy2,"\0");
		strcpy(cha.buddy3,"\0");
		cha.b1 = '0';
		cha.b2 = '0';
		cha.b3 = '0';

		/*
		if(strcmp(cha.name,"angk")==0)
		{
		 k = cha.t;
		 cha.goods[k].nam = '$';
		 strcpy(cha.goods[k].name,"25级装备强化卷轴");
		 cha.goods[k].q = 2;
		 cha.t++;
		}
		*/

		printf("\n");
	    break;
	   }
	   else
	   {
		fclose(fr);
		printf("\n");
	    t = 0;
	   }
	  }
	 }    //t=1
     
     while(t==2)
	 {
      printf("1.战士  2.法师  3.道士\n");
      printf("请选择");
	  scanf("%d",&d);
	  getchar();
	  if(d!=1&&d!=2&&d!=3)
	  {
	   t = 0;
	   break;
	  }
	  if(d==1)
	  {
	   printf("闯荡于森林的勇士！\n善于近身攻击，单体输出高\n");
	   printf("是否选择？\n1.是 2.否");
	  }
	  if(d==2)
	  {
	   printf("凌驾于世间的术士！\n善于远程攻击，群体输出，可不会被怪打到\n");
	   printf("是否选择？\n1.是 2.否");
	  }
	  if(d==3)
	  {
	   printf("研究于学术的学者！\n善于召唤攻击，可召唤神兽\n");
	   printf("是否选择？\n1.是 2.否");
	  }
	  scanf("%d",&s);
	  getchar();
	  if(s==1)
	  {
		  int o=0;
		  while(o==0)
		  {
			  printf("请输入角色名:");
			  gets(cha.name);
			  o = 1;
			  if(strlen(cha.name)>=20)
			  {
				  printf("角色名过长\n\n");
				  o = 0;
			  }
			  if(strlen(cha.name)==0)
			  {
				  printf("空名字\n\n");
				  o = 0;
			  }
			  if(o==1)
			  {
				  k = 0;
				  while(k<=strlen(cha.name)-1)
				  {
					  if(cha.name[k]!=' ')
					  {
						  break;
					  }
					  k++;
				  }
				  if(k==strlen(cha.name))
				  {
					  printf("角色名不合法\n\n");
					  o = 0;
				  }
			  }
			  int h;
			  f1 = fopen(namefile,"rb+");
			  if(f1==NULL)
			  {
				  f1 = fopen(namefile,"wb");
				  h = 0;
				  fwrite(&h,4,1,f1);
				  fclose(f1);
				  f1 = fopen(namefile,"rb+");
			  }
			  fread(&h,4,1,f1);
			  for(int x=1;x<=h;x++)
			  {
				  fread(name,20,1,f1);
				  if(strcmp(cha.name,name)==0)
				  {
					  printf("角色名已存在\n\n");
					  o = 0;
					  break;
				  }
			  }
			  if(o==1)
			  {
				  fclose(f1);
				  f1 = fopen(namefile,"ab");
				  fwrite(cha.name,20,1,f1);
				  fclose(f1);
				  f1 = fopen(namefile,"rb+");
				  h += 1;
				  fwrite(&h,4,1,f1);
			  }
			  fclose(f1);
		  }
		  p += 1;
		  fr = fopen(cha.filename,"rb");
		  if(fr==NULL)
		  {
			  fr = fopen(cha.filename,"wb");
			  fwrite(&p,4,1,fr);
		  }
		  else
		  {
			  if(p==6)
			  {
				  printf("角色栏已满\n");
				  printf("确定");
				  getchar();
				  fclose(fr);
				  t = 0;
				  printf("\n");
				  break;
			  }
			  fclose(fr);
			  fr = fopen(cha.filename,"rb+");
			  fwrite(&p,4,1,fr);
			  fclose(fr);
			  fr = fopen(cha.filename,"ab");
		  }
		  if(d==1)
		  {
			  fwrite(cha.name,20,1,fr);
			  strcpy(cha.prof,"战士");
			  fwrite(cha.prof,20,1,fr);
			  strcpy(cha.v,"世外小村");
			  fwrite(cha.v,20,1,fr);
			  cha.grd = 1;
			  cha.xHP = 19;
			  cha.HP = 19;
			  cha.xMP = 3;
			  cha.MP = 3;
			  cha.atc = 5;
			  cha.def = 3;
			  cha.mny = 0;
		  }
		  if(d==2)
		  {
			  fwrite(cha.name,20,1,fr);
			  strcpy(cha.prof,"法师");
			  fwrite(cha.prof,20,1,fr);
			  strcpy(cha.v,"世外小村");
			  fwrite(cha.v,20,1,fr);
			  cha.grd = 1;
			  cha.xHP = 5;
			  cha.HP = 5;
			  cha.xMP = 20;
			  cha.MP = 20;
			  cha.atc = 2;
			  cha.def = 3;
			  cha.mny = 0;
		  }
		  if(d==3)
		  {
			  fwrite(cha.name,20,1,fr);
			  strcpy(cha.prof,"道士");
			  fwrite(cha.prof,20,1,fr);
			  strcpy(cha.v,"世外小村");
			  fwrite(cha.v,20,1,fr);
			  cha.grd = 1;
			  cha.xHP = 12;
			  cha.HP = 12;
			  cha.xMP = 11;
			  cha.MP = 11;
			  cha.atc = 3.5;
			  cha.def = 3;
			  cha.mny = 0;
		  }
		  i = 0; 
		  while(i<=23)
		  {
			  cha.equ[i].grd = 0;
			  strcpy(cha.equ[i].name,"\0");
			  strcpy(cha.equ[i].kind,"\0");
			  cha.equ[i].rank = ' ';
			  cha.equ[i].axHP = 0;
			  cha.equ[i].axMP = 0;
			  cha.equ[i].aatc = 0;
			  cha.equ[i].adef = 0;
			  i++;
		  }
		  cha.xexp = 10;
		  cha.exp = 0;
		  i = 0;
		  while(i<=16)
		  {
			  cha.goods[i].nam = '\0';
			  strcpy(cha.goods[i].name,"\0");
			  cha.goods[i].q = 0;
			  i++;
		  }
		  cha.t = 0;
		  cha.e = 7;
		  
		  a[0]=(double)cha.grd;
		  a[1]=cha.HP;
		  a[2]=cha.xHP;
		  a[3]=cha.MP;
		  a[4]=cha.xMP;
		  a[5]=cha.atc;
		  a[6]=cha.def;
		  a[7]=cha.mny;
		  a[8]=cha.exp;
		  a[9]=cha.xexp;
		  a[10]=(double)cha.t;
		  a[11]=(double)cha.e;
		  i=0;
		  while(i<=16)
		  {
			  c[i]=cha.goods[i];
			  b[i]=cha.equ[i];
			  i++;
		  }
		  while(i<=23)
		  {
			  b[i]=cha.equ[i];
			  i++;
		  }
		  
		  fwrite(a,8,12,fr);
		  fwrite(c,sizeof(struct GOODS),17,fr);
		  fwrite(b,sizeof(struct EQUIPMENT),24,fr);
		  fclose(fr);
		  
		  printf("创建成功\n");
		  printf("确定");
		  getchar();
		  printf("\n");
		  t = 0;
	  }
	  else
	  {
		   printf("\n");
		   t = 2;
	  }
	 }      //t=2

	 while(t==3)
	 {
	  fr = fopen(cha.filename,"rb");
      if(fr==NULL)
	  {
	   printf("无角色\n");
	   printf("\n");
	   t = 0;
	  }
	  else
	  {
	   fread(&p,4,1,fr);
	   j = 1;
	   while(j<=p)
	   {
	    printf("%d.",j);
	    fread(cha.name,20,1,fr);
	    puts(cha.name);
		fseek(fr,(size-20),1);
		j++;
	   }
	   printf("请选择");
	   scanf("%d",&d);
	   getchar();
	   if(d<=p && d>=1)
	   {
	    printf("确认删除?\n");
        printf("1.确认 2.取消");
		scanf("%d",&s);
		if(s==1)
		{
         p -= 1;
		 if(p==0)
		 {
		  strcpy(name,cha.name);
		  fclose(fr);
		  unlink(cha.filename);
		  t = 3;
		 }
		 else
		 {
		  FILE* fp;
		  fp = fopen(tfile,"wb");
		  rewind(fr);
		  char ch;
		  ch = fgetc(fr);
		  while(!feof(fr))
		  {
		   fputc(ch,fp);
		   ch = fgetc(fr);
		  }
		  fclose(fp);
		  fclose(fr);
		  fr = fopen(cha.filename,"wb");
		  fp = fopen(tfile,"rb");
		  fwrite(&p,4,1,fr);
		  fseek(fp,4L,0);
		  int z=1;
		  while(z<=d-1)
		  {
		   fread(cha.name,20,1,fp);
		   fread(cha.prof,20,1,fp);
		   fread(cha.v,20,1,fp);
	       fread(a,8,12,fp);
	       fread(c,sizeof(struct GOODS),17,fp);
	       fread(b,sizeof(struct EQUIPMENT),24,fp);
		   fwrite(cha.name,20,1,fr);
		   fwrite(cha.prof,20,1,fr);
		   fwrite(cha.v,20,1,fr);
		   fwrite(a,8,12,fr);
		   fwrite(c,sizeof(struct GOODS),17,fr);
		   fwrite(b,sizeof(struct EQUIPMENT),24,fr);
		   z++;
		  }
		  fread(name,20,1,fp);
          fseek(fp,4L+(d*size),0);
		  while(z<=p)
		  {
		   fread(cha.name,20,1,fp);
		   fread(cha.prof,20,1,fp);
		   fread(cha.v,20,1,fp);
	       fread(a,8,12,fp);
	       fread(c,sizeof(struct GOODS),17,fp);
	       fread(b,sizeof(struct EQUIPMENT),24,fp);
		   fwrite(cha.name,20,1,fr);
		   fwrite(cha.prof,20,1,fr);
		   fwrite(cha.v,20,1,fr);
		   fwrite(a,8,12,fr);
		   fwrite(c,sizeof(struct GOODS),17,fr);
		   fwrite(b,sizeof(struct EQUIPMENT),24,fr);
		   z++;
		  }
		  fclose(fp);
		  fclose(fr);
		  unlink(tfile);
		 }
		 int h,g;
		 char nam[20];
		 f1 = fopen(namefile,"rb");
		 FILE* fp;
		 fp = fopen(tfile,"wb");
		 fread(&h,4,1,f1);
		 int x;
		 for(x=1;x<=h;x++)
		 {
		  fread(nam,20,1,f1);
		  if(strcmp(name,nam)==0)
		  {
		   g = x;
		   break;
		  }
		 }
         rewind(f1);
		 char ch;
		 ch = fgetc(f1);
		 while(!feof(f1))
		 {
		   fputc(ch,fp);
		   ch = fgetc(f1);
		 }
		 fclose(fp);
		 fclose(f1);
		 f1 = fopen(namefile,"wb");
		 fp = fopen(tfile,"rb");
		 h -= 1;
		 fwrite(&h,4,1,f1);
		 fseek(fp,4L,0);
		 x = 1;
		 while(x<=g-1)
		 {
		  fread(name,20,1,fp);
		  fwrite(name,20,1,f1);
		  x++;
		 }
		 fseek(fp,4L+g*20L,0);
		 while(x<=h)
		 {
		  fread(name,20,1,fp);
		  fwrite(name,20,1,f1);
		  x++;
		 }
		 fclose(fp);
		 fclose(f1);
		 unlink(tfile);
		 printf("\n");
		}    //s=1
		else
		{
		 fclose(fr);
		 t = 3;
		}
	   }    //d
	   else
	   {
	    fclose(fr);
		t = 0;
	   }
	  }
	 }
     
	 if(t==4)
	 {
	  GameOver();
	  t=0;
	  printf("\n");
	 }

	 while(t!=1 && t!=2 && t!=3 && t!=4)
	 {
	  t = 0;
	  break;
	 }
	}
	Printf(cha);
}

int cqmain(char loginname[20])
{
	strcpy(act,loginname);
    struct CHARACTER cha;
	srand(time(NULL));
	while(1)
	{
		Choice(cha);
	}
	return 0;
}