/*********************************

Generate Graphic source file

Author:		 ShooterIT
Datetime:    2017-4-30 16:26:12
Description: some algorithms about generate graphic

*********************************/

#include <iostream>
#include <fstream>
#include <functional>
#include <set>
#include <ctime>

/**********************************

输入说明(以官网case为例)：
	0 17 (起点 终点, 起点为最小的节点id，终点为最大的节点id)

	7 12 (必经点集,节点id，以空格间隔)

	11 12 (禁止边，可能有多条，每行表示一条边，节点id对)
	...(可能多行)

	2 4 (必经边，可能有多条，每行表示一条边，节点id对)
	13 14...(可能多行)

	0 1 3(图中的边以及权重,每行表示一条边，节点id对以及该边的权重)
	...(多行)

输出说明：

	13 (节点数,没有路径则为0)

	0 2 4 5 6 7 8 14 13 12 16 17 (路径,以空格间隔路径上节点id)

*/


//最大节点个数
#define MAX_VERTEX_NUM	  10000
//0-1之间的随机数
#define rand_01			  ((double)rand() / RAND_MAX)

using namespace std;


//全局图
int graphic[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
//节点的度
int adj[MAX_VERTEX_NUM];

//生成随机图
int main(int argc, char *argv[])
{
	//if (argc < 2) {
	//	cerr << "Usage Error.\n" << endl;
	//	return -1;
	//}

	//生成文件位置
	const char * file = "..\\ShortPath\\input.txt"; //argv[1]; 
	const double ratio = 0.01; //产生边的概率,小图需要适当增加概率
	const int	 vert_num = 1000; //最大的顶点
	const int	 weight_max = 10;	//边的最大权重

									//随机种子
	srand(unsigned(time(0)));

	//产生无向图
	for (int i = 0; i < vert_num; i++) {
		int edge_num = int(rand_01 * ratio * vert_num); //随机产生边的数量
		for (int j = 0; j < edge_num; j++) {
			int v;
			do {
				v = rand() % vert_num;
			} while (graphic[i][v] || i == v);			  //排除重复以及自己指向自己的回路

			int weight = rand() % weight_max + 1;		  //随机权重		
			graphic[i][v] = weight;
			graphic[v][i] = weight;
			adj[i]++;									  //增加出入度
			adj[v]++;
		}
	}

	//输出文件
	ofstream of(file);

	//起点 终点
	of << 0 << ' ' << vert_num - 1 << "\n\n";

	//使用的点集
	set<int> used_vert;
	//必经点,除起点和终点以外的两点，因为起点和终点本就为必经点
	used_vert.insert(0);
	used_vert.insert(vert_num - 1);
	//生成指定数量的必经点, 默认vert_num / 20，可以根据需求更改
	for (int i = 0; i < vert_num / 20; i++) {
		int v;
		do {
			v = rand() % vert_num;
		} while (used_vert.find(v) != used_vert.end()); //排除已经使用过的
		used_vert.insert(v); //设置改点已使用
		of << v << " ";		 //输出必经点
	}
	of << "\n\n";

	//使用的边集
	set<int> used_edge;

	//禁止边，对于禁止边的位置没有加限定（如：必经点必须有一条边为非禁止边,
	//需要的话开启pass_vert_must_bigger_one的计算）
	//生成指定数量的禁止边, 默认vert_num / 40，可以根据需求更改
	//如果产生边的概率太小，而要求边的数量过多，会陷入死循环
	//如果大图，太少（如一条：)）就没意思了
	for (int i = 0; i < vert_num / 40; i++) {
		int from, to, edge_id;
		bool pass_vert_must_bigger_one = false; //必经点必须有一条边为非禁止边的启用标志
		do {
			from = rand() % vert_num;
			to = rand() % vert_num;
			if (from > to) {
				swap(from, to);
			}
			edge_id = from * vert_num + to; //独一无二的边的id
			//必经点必须有一条边为非禁止边
			/*if (graphic[from][to]) {
				if (used_vert.find(from) != used_vert.end()) {
					if (adj[from] <= 1) {
						pass_vert_must_bigger_one = true;
					}
				}
				if (used_vert.find(to) != used_vert.end()) {
					if (adj[to] <= 1) {
						pass_vert_must_bigger_one = true;
					}
				}
			}*/
		} while (!graphic[from][to]
			|| used_edge.find(edge_id) != used_edge.end()
			|| pass_vert_must_bigger_one); //排除不存在边和已使用的边以及必经点必须有一条边为非禁止边的情况
										   //注意：存在多条禁止边有公共节点的情况（没有禁止此情况）
		used_edge.insert(edge_id);			   //设置该边已使用
		used_edge.insert(to * vert_num + from);//无向图为双向边
		adj[to]--;		//出入度减少
		adj[from]--;	//出入度减少
		of << from << " " << to << "\n"; //输出禁止边
	}
	of << "\n";

	//必经边（不能为禁止边）
	//生成指定数量的禁止边, 默认vert_num / 40，可以根据需求更改
	//如果产生边的概率太小，而要求边的数量过多，会陷入死循环
	//如果大图，太少（如两条：)）就没意思了
	for (int i = 0; i < vert_num / 40; i++) {
		int from, to, edge_id;
		do {
			from = rand() % vert_num;
			to = rand() % vert_num;
			if (from > to) {
				swap(from, to);
			}
			edge_id = from * vert_num + to;
		} while (!graphic[from][to]
			|| used_edge.find(edge_id) != used_edge.end());//排除不存在边和已使用的边	
														   //注意：存在多条必经边有公共节点的情况（没有禁止此情况）
		used_edge.insert(edge_id);			   //设置该边已使用
		used_edge.insert(to * vert_num + from);//无向图为双向边
		of << from << " " << to << "\n";       //输出必经边
	}
	of << "\n";

	//输出图
	for (int i = 0; i < vert_num; i++) {
		for (int j = 0; j < vert_num; j++) {
			if (graphic[i][j]) {
				graphic[j][i] = 0; //因为是无向图
				of << i << " " << j << " " << graphic[i][j] << "\n"; //输出图的边
			}
		}
	}

	return 0;
}