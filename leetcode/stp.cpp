#include<iostream>
#include<string>
#include<cstring>
#include <algorithm>
using namespace std;
struct PORT//交换机端口
{
    int port_id;//端口序号
	 // int id;//端口ID（端口优先级+端口编号）默认端口优先级为128，端口ID相等
    int rp;//如果值为1为根端口，否则不是根端口
    int dp;//如果值为1为指定端口，否则不是指定端口
    int bp;//如果值为1为阻塞端口，否则不是阻塞端口
	int switches_id;//所在的交换机的编号
};
struct SWITCHES//交换机
{
	int switches_id ;//交换机的编号
    char mac[30];//mac地址
    int level;//优先级，范围0-65535 默认相等
    struct PORT  ports[20];//交换机包含的端口
	int amount; //包含端口的个数
};
struct BRIDGE //网桥
{
   struct PORT node1;//网桥的一个端口
   struct PORT node2;//网桥的一个端口
};
struct SWITCHES switches[20];//存放交换机的数组
struct BRIDGE bridges[30];//存放网桥的数组
int switches_num,bridges_num;
const int INF=10000000;
const int N=100;
int p[N][N],d[N],path[N];
struct SWITCHES temp;
void input()//数据输入函数
{
	int i,j;
	cout<<"输入交换机的个数：";
	cin>>switches_num;
	for(i=0;i<switches_num;i++)
	{
		cout<<"\n"<<"输入第"<<i+1<<"个交换机的mac地址";
		cin>>switches[i].mac;
		cout<<"\n"<<"输入第"<<i+1<<"个交换机的编号";
		cin>>switches[i].switches_id;
		cout<<"\n"<<"输入第"<<i+1<<"个交换机包含的端口的个数";
		cin>>switches[i].amount;
		for(j=0;j<switches[i].amount;j++)
		{
			cout<<"\n"<<"输入第"<<j+1<<"个端口的序号";
			cin>>switches[i].ports[j].port_id;
			switches[i].ports[j].switches_id=switches[i].switches_id;
		}
	}
	cout<<"\n"<<"输入网桥的个数：";
	cin>>bridges_num;
	for(i=0;i<bridges_num;i++)
	{
		cout<<"\n"<<"输入第"<<i+1<<"个网桥的一个端口序号";
		cin>>bridges[i].node1.port_id;
		cout<<"\n"<<"输入第"<<i+1<<"个网桥的一个端口所在的交换机的序号";
		cin>>bridges[i].node1.switches_id;
		cout<<"\n"<<"输入第"<<i+1<<"个网桥的另一个端口序号";
		cin>>bridges[i].node2.port_id;
		cout<<"\n"<<"输入第"<<i+1<<"个网桥的另一个端口所在的交换机的序号";
		cin>>bridges[i].node2.switches_id;
	}
	cout<<"\n";
}
void network()//构造交换机的连接网络
{
	 int i,j;
	 for(i=0;i<switches_num;i++)
    {
        for(j=0;j<switches_num;j++)
        {
            p[i][j]=(i==j?0:INF);
        }
    }
	for(i=0;i<bridges_num;i++)
	{
		int temp1=bridges[i].node1.switches_id;
		int temp2=bridges[i].node2.switches_id;
		for(j=0;j<switches_num;j++)
		{
			if(temp1==switches[j].switches_id)
			{
				temp1=j;
				break;
			}
		}
		for(j=0;j<switches_num;j++)
		{
			if(temp2==switches[j].switches_id)
			{
				temp2=j;
				break;
			}
		}
		p[temp1][temp2]=1;
		p[temp2][temp1]=1;
	}
}
void dijkstra(int sec,int n)    //sec为出发节点，n表示图中节点总数
{
    int i,j,min,min_num;
    int vis[N]={0,};
    for(i=0;i<n;i++)
    {
        d[i]=p[sec][i];
    }
    vis[sec]=1;d[sec]=0;
    for(i=1;i<n;i++)
    {
        min=INF;
        for(j=0;j<n;j++)
        {
            if(!vis[j]&&d[j]<min)
            {
                min=d[j];
                min_num=j;
            }
        }
        vis[min_num]=1;
        for(j=0;j<n;j++)
        {
            if(d[j]>min+p[min_num][j])
            {
                path[j]=min_num;//path[j]记录d[j]暂时最短路径的最后一个中途节点min_num，表明d[j]最后一段从节点min_num到节点j
                d[j]=min+p[min_num][j];
            }
        }
    }
}
void copy(struct SWITCHES s1)//复制交换机对象函数
{
	int h;
	temp.amount=s1.amount;
	temp.level=s1.level;
	temp.switches_id=s1.switches_id;
	for( h=0;h<s1.amount;h++)
	{	temp.ports[h].bp=s1.ports[h].bp;
		temp.ports[h].dp=s1.ports[h].dp;
		temp.ports[h].rp=s1.ports[h].rp;
		temp.ports[h].port_id=s1.ports[h].port_id;
		temp.ports[h].switches_id=s1.ports[h].switches_id;

	}
}
void rootport ()//寻找根端口函数
{
	int i,j,t,s,h;
	for(i=1;i<switches_num;i++)
	{
		
		if(path[i]==-1)
		{
			copy(switches[0]);
		}
		else
		{
			for(j=1;j<switches_num;j++)
			{
				if(j==path[i])
				{
					copy(switches[j]);
				}
			}
		}
		int minport_id=1000000;
		int sign1=-1,sign2=0;
		for(h=0;h<switches[i].amount;h++)
			{
				for(t=0;t<temp.amount;t++)
				{
					for(s=0;s<bridges_num;s++)
					{
						
						if(switches[i].ports[h].switches_id==bridges[s].node1.switches_id&&temp.ports[t].switches_id==bridges[s].node2.switches_id)
							{
								if(switches[i].ports[h].port_id==bridges[s].node1.port_id&&temp.ports[t].port_id==bridges[s].node2.port_id)
								{
									if(bridges[s].node2.port_id<minport_id)
									{
										minport_id=bridges[s].node2.port_id;
								//		sign=h;
										sign1=s;
										sign2=1;

									}
								}
							}
						if(switches[i].ports[h].switches_id==bridges[s].node2.switches_id&&temp.ports[t].switches_id==bridges[s].node1.switches_id)
							{
								if(switches[i].ports[h].port_id==bridges[s].node2.port_id&&temp.ports[t].port_id==bridges[s].node1.port_id)
							
								{
									if(bridges[s].node1.port_id<minport_id)
									{
										minport_id=bridges[s].node1.port_id;
									//	sign=h;
										sign1=s;
										sign2=2;
									}
								}
							}
					}
				}
			}
			for(s=0;s<bridges_num;s++)
			{
				if(s==sign1&&sign2==1)
					bridges[s].node1.rp=1;
				if(s==sign1&&sign2==2)
					bridges[s].node2.rp=1;
			}
	}
}
void designatedport()//寻找指定端口函数
{
	int i,j,k;
	for(i=0;i<bridges_num;i++)
	{
		if(bridges[i].node1.switches_id==switches[0].switches_id)
			bridges[i].node1.dp=1;
		else if(bridges[i].node2.switches_id==switches[0].switches_id)
			bridges[i].node2.dp=1;
		else if(bridges[i].node1.rp==1&&bridges[i].node2.rp!=1)
		{
			bridges[i].node2.dp=1;
		}
		else if(bridges[i].node2.rp==1&&bridges[i].node1.rp!=1)
		{	
			bridges[i].node1.dp=1;
		}
		else 
		{
			int temp1,temp2;
			for(j=0;j<switches_num;j++)
			if(bridges[i].node1.switches_id==switches[j].switches_id)
				temp1=j;
			for(j=0;j<switches_num;j++)
			if(bridges[i].node2.switches_id==switches[j].switches_id)
				temp2=j;
			int distance1,distance2;
			for(j=1;j<switches_num;j++)
			{
				if(j==temp1)distance1=d[j];
				if(j==temp2)distance2=d[j];
			}
			if(distance1>distance2)
			{
				bridges[i].node2.dp=1;
				bridges[i].node1.bp=1;
			}
			else if(distance1<distance2)
			{
				bridges[i].node1.dp=1;
				bridges[i].node2.bp=1;
			}
			else
			{
				if(temp1<temp2)
				{
					bridges[i].node1.dp=1;
					bridges[i].node2.bp=1;
				}
				else
				{
					bridges[i].node2.dp=1;
					bridges[i].node1.bp=1;
				}
			}
		}
	}
	for(i=0;i<switches_num;i++)
	{
		for(j=0;j<switches[i].amount;j++)
		{
			for(k=0;k<bridges_num;k++)
			{
				if(bridges[k].node1.port_id==switches[i].ports[j].port_id&&bridges[k].node1.switches_id==switches[i].ports[j].switches_id)
				{
					switches[i].ports[j].bp=bridges[k].node1.bp;
					switches[i].ports[j].dp=bridges[k].node1.dp;
					switches[i].ports[j].rp=bridges[k].node1.rp;
				}
				if(bridges[k].node2.port_id==switches[i].ports[j].port_id&&bridges[k].node2.switches_id==switches[i].ports[j].switches_id)
				{
					switches[i].ports[j].bp=bridges[k].node2.bp;
					switches[i].ports[j].dp=bridges[k].node2.dp;
					switches[i].ports[j].rp=bridges[k].node2.rp;
				}
			}
		}
	}
}
bool  cmp(const SWITCHES &x, const SWITCHES &y)
{
	//return x.b1<y.b1;//从小到大排<，若要从大到小排则>
	if(strcmp(x.mac,y.mac)<0)return true;
	else
		return false;
}
void output()
{
	int i,j;
	for(i=0;i<switches_num;i++)
	{
		for(j=0;j<switches[i].amount;j++)
		{
			if(switches[i].ports[j].rp==1)
			cout<<"编号为"<<switches[i].switches_id<<"的交换机中编号为"<<switches[i].ports[j].port_id<<"的端口为根端口"<<"\n";
			if(switches[i].ports[j].dp==1)
			cout<<"编号为"<<switches[i].switches_id<<"的交换机中编号为"<<switches[i].ports[j].port_id<<"的端口为指定端口"<<"\n";
			if(switches[i].ports[j].bp==1)
			cout<<"编号为"<<switches[i].switches_id<<"的交换机中编号为"<<switches[i].ports[j].port_id<<"的端口为阻塞端口"<<"\n";
		}
	}
}

int main()
{
	memset(path,-1,sizeof(path));//将path数组初始化为-1
    input();                     //数据的输入函数
	sort(switches,switches+switches_num,cmp);//按mac地址对交换机进行排序
	network();//构造交换机的连接关系p[][]
	dijkstra(0,switches_num);//迪杰斯特拉算法
	rootport();//寻找根端口
	designatedport();//寻找指定端口
	output();//输出函数
	return 0;
}



