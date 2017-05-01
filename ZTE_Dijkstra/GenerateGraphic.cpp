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

����˵��(�Թ���caseΪ��)��
	0 17 (��� �յ�, ���Ϊ��С�Ľڵ�id���յ�Ϊ���Ľڵ�id)

	7 12 (�ؾ��㼯,�ڵ�id���Կո���)

	11 12 (��ֹ�ߣ������ж�����ÿ�б�ʾһ���ߣ��ڵ�id��)
	...(���ܶ���)

	2 4 (�ؾ��ߣ������ж�����ÿ�б�ʾһ���ߣ��ڵ�id��)
	13 14...(���ܶ���)

	0 1 3(ͼ�еı��Լ�Ȩ��,ÿ�б�ʾһ���ߣ��ڵ�id���Լ��ñߵ�Ȩ��)
	...(����)

���˵����

	13 (�ڵ���,û��·����Ϊ0)

	0 2 4 5 6 7 8 14 13 12 16 17 (·��,�Կո���·���Ͻڵ�id)

*/


//���ڵ����
#define MAX_VERTEX_NUM	  10000
//0-1֮��������
#define rand_01			  ((double)rand() / RAND_MAX)

using namespace std;


//ȫ��ͼ
int graphic[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
//�ڵ�Ķ�
int adj[MAX_VERTEX_NUM];

//�������ͼ
int main(int argc, char *argv[])
{
	//if (argc < 2) {
	//	cerr << "Usage Error.\n" << endl;
	//	return -1;
	//}

	//�����ļ�λ��
	const char * file = "..\\ShortPath\\input.txt"; //argv[1]; 
	const double ratio = 0.01; //�����ߵĸ���,Сͼ��Ҫ�ʵ����Ӹ���
	const int	 vert_num = 1000; //���Ķ���
	const int	 weight_max = 10;	//�ߵ����Ȩ��

									//�������
	srand(unsigned(time(0)));

	//��������ͼ
	for (int i = 0; i < vert_num; i++) {
		int edge_num = int(rand_01 * ratio * vert_num); //��������ߵ�����
		for (int j = 0; j < edge_num; j++) {
			int v;
			do {
				v = rand() % vert_num;
			} while (graphic[i][v] || i == v);			  //�ų��ظ��Լ��Լ�ָ���Լ��Ļ�·

			int weight = rand() % weight_max + 1;		  //���Ȩ��		
			graphic[i][v] = weight;
			graphic[v][i] = weight;
			adj[i]++;									  //���ӳ����
			adj[v]++;
		}
	}

	//����ļ�
	ofstream of(file);

	//��� �յ�
	of << 0 << ' ' << vert_num - 1 << "\n\n";

	//ʹ�õĵ㼯
	set<int> used_vert;
	//�ؾ���,�������յ���������㣬��Ϊ�����յ㱾��Ϊ�ؾ���
	used_vert.insert(0);
	used_vert.insert(vert_num - 1);
	//����ָ�������ıؾ���, Ĭ��vert_num / 20�����Ը����������
	for (int i = 0; i < vert_num / 20; i++) {
		int v;
		do {
			v = rand() % vert_num;
		} while (used_vert.find(v) != used_vert.end()); //�ų��Ѿ�ʹ�ù���
		used_vert.insert(v); //���øĵ���ʹ��
		of << v << " ";		 //����ؾ���
	}
	of << "\n\n";

	//ʹ�õı߼�
	set<int> used_edge;

	//��ֹ�ߣ����ڽ�ֹ�ߵ�λ��û�м��޶����磺�ؾ��������һ����Ϊ�ǽ�ֹ��,
	//��Ҫ�Ļ�����pass_vert_must_bigger_one�ļ��㣩
	//����ָ�������Ľ�ֹ��, Ĭ��vert_num / 40�����Ը����������
	//��������ߵĸ���̫С����Ҫ��ߵ��������࣬��������ѭ��
	//�����ͼ��̫�٣���һ����)����û��˼��
	for (int i = 0; i < vert_num / 40; i++) {
		int from, to, edge_id;
		bool pass_vert_must_bigger_one = false; //�ؾ��������һ����Ϊ�ǽ�ֹ�ߵ����ñ�־
		do {
			from = rand() % vert_num;
			to = rand() % vert_num;
			if (from > to) {
				swap(from, to);
			}
			edge_id = from * vert_num + to; //��һ�޶��ıߵ�id
			//�ؾ��������һ����Ϊ�ǽ�ֹ��
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
			|| pass_vert_must_bigger_one); //�ų������ڱߺ���ʹ�õı��Լ��ؾ��������һ����Ϊ�ǽ�ֹ�ߵ����
										   //ע�⣺���ڶ�����ֹ���й����ڵ�������û�н�ֹ�������
		used_edge.insert(edge_id);			   //���øñ���ʹ��
		used_edge.insert(to * vert_num + from);//����ͼΪ˫���
		adj[to]--;		//����ȼ���
		adj[from]--;	//����ȼ���
		of << from << " " << to << "\n"; //�����ֹ��
	}
	of << "\n";

	//�ؾ��ߣ�����Ϊ��ֹ�ߣ�
	//����ָ�������Ľ�ֹ��, Ĭ��vert_num / 40�����Ը����������
	//��������ߵĸ���̫С����Ҫ��ߵ��������࣬��������ѭ��
	//�����ͼ��̫�٣���������)����û��˼��
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
			|| used_edge.find(edge_id) != used_edge.end());//�ų������ڱߺ���ʹ�õı�	
														   //ע�⣺���ڶ����ؾ����й����ڵ�������û�н�ֹ�������
		used_edge.insert(edge_id);			   //���øñ���ʹ��
		used_edge.insert(to * vert_num + from);//����ͼΪ˫���
		of << from << " " << to << "\n";       //����ؾ���
	}
	of << "\n";

	//���ͼ
	for (int i = 0; i < vert_num; i++) {
		for (int j = 0; j < vert_num; j++) {
			if (graphic[i][j]) {
				graphic[j][i] = 0; //��Ϊ������ͼ
				of << i << " " << j << " " << graphic[i][j] << "\n"; //���ͼ�ı�
			}
		}
	}

	return 0;
}