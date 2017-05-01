# 中兴算法挑战赛---迪杰斯特拉派
#### 说明
- 可以生产简单随机无向图
- 可以设置图的规模，必经点数量，禁止边数量，必经边数量
- 可以根据自己的需求更改代码，生成自己需要格式的case文件
- 测试用例目录下对应了几个不同规模的case以及对应的解(可能并不好)
- 希望对大家有所帮助，但时间和水平有限，难免有bug(⊙o⊙)哦！

#### 测试用例文件格式(以官网case为例):
  	0 17 (起点 终点，起点为最小的节点id，终点为最大的节点id)

	7 12 (必经点集，节点id，以空格间隔)

	11 12 (禁止边，可能有多条，每行表示一条边，节点id对)
	...(可能多行)

	2 4 (必经边，可能有多条，每行表示一条边，节点id对)
	13 14...(可能多行)

	0 1 3(图中的边以及权重,每行表示一条边，节点id对以及该边的权重)
	...(多行)
	
#### 结果文件格式
    13 (节点数，没有路径则为0)

	0 2 4 5 6 7 8 14 13 12 16 17 (路径，以空格间隔路径上节点id)
