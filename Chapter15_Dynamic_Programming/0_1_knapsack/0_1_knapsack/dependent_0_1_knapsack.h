/*
购物单
参与人数：524时间限制：1秒空间限制：32768K
本题知识点： 字符串
 算法知识视频讲解
题目描述
 
王强今天很开心，公司发给N元的年终奖。王强决定把年终奖用于购物，他把想买的物品分为两类：主件与附件，附件是从属于某个主件的，下表就是一些主件与附件的例子：
主件  附件
电脑  打印机，扫描仪
书柜  图书
书桌  台灯，文具
工作椅 无
如果要买归类为附件的物品，必须先买该附件所属的主件。每个主件可以有 0 个、 1 个或 2 个附件。附件不再有从属于自己的附件。王强想买的东西很多，为了不超出预算，他把每件物品规定了一个重要度，分为 5 等：用整数 1 ~ 5 表示，第 5 等最重要。他还从因特网上查到了每件物品的价格（都是 10 元的整数倍）。他希望在不超过 N 元（可以等于 N 元）的前提下，使每件物品的价格与重要度的乘积的总和最大。
    设第 j 件物品的价格为 v[j] ，重要度为 w[j] ，共选中了 k 件物品，编号依次为 j 1 ， j 2 ，……， j k ，则所求的总和为：
v[j 1 ]*w[j 1 ]+v[j 2 ]*w[j 2 ]+ … +v[j k ]*w[j k ] 。（其中 * 为乘号）
    请你帮助王强设计一个满足要求的购物单。
 
输入描述:
输入的第 1 行，为两个正整数，用一个空格隔开：N m
（其中 N （ <32000 ）表示总钱数， m （ <60 ）为希望购买物品的个数。）
 
从第 2 行到第 m+1 行，第 j 行给出了编号为 j-1 的物品的基本数据，每行有 3 个非负整数 v p q
 
（其中 v 表示该物品的价格（ v<10000 ）， p 表示该物品的重要度（ 1 ~ 5 ）， q 表示该物品是主件还是附件。如果 q=0 ，表示该物品为主件，如果 q>0 ，表示该物品为附件， q 是所属主件的编号）
 
 
输出描述:
 输出文件只有一个正整数，为不超过总钱数的物品的价格与重要度乘积的总和的最大值（ <200000 ）。
 
输入例子:
1000 5
800 2 0
400 5 1
300 5 1
400 3 0
500 2 0
 
输出例子:
2200
*/

//此种算法步骤只适合固定最大附件数量的情况
#include <iostream>
#include <vector>

using namespace std;

#define max(x,y) (x)>(y)?(x):(y)

void Dependent_0_1_knapsack(){
    int N,m;
    cin>>N>>m;
    N = N/10;
    
    vector<vector<int> > price;
    vector<vector<int> > weight;
    for(int i = 0;i <= m;i++){
        vector<int> temp;
        for(int j = 0;j< 3;j++)
        	temp.push_back(0);
        price.push_back(temp);
        weight.push_back(temp);
    }
    //将主件和附件按照主件分组
    int j = 1;
    while(j<=m){
        int v,p,q;
        cin>>v>>p>>q;
        if(q == 0){
            price[j][0] = v;
            weight[j][0] = p;
        }
        else if(weight[q][1] == 0){
            price[q][1] = v;
            weight[q][1] = p;
        }
        else{
            price[q][2] = v;
            weight[q][2] = p;
        }
		j++;
    }
    vector<vector<int> > m_price;
    for(int i = 0;i <= m;i++){
        vector<int> temp;
        for(int j = 0;j <= N;j++){
            temp.push_back(0);
        }
        m_price.push_back(temp);
    }
    //动态规划，加入主件，然后计算加入不同数量的附件
    for(int i = 1;i <= m;i++){
        for(int j = 1;j <= N;j++){
            m_price[i][j]=m_price[i-1][j];
            if(price[i][0]/10<=j){
               int t = max(m_price[i-1][j],m_price[i-1][j-(price[i][0])/10]+
                            (price[i][0]*weight[i][0]));
			   if(t>m_price[i][j])
				   m_price[i][j] = t;
            }
            if((price[i][0]+price[i][1])/10<=j){
                m_price[i][j] = max(m_price[i][j],m_price[i-1][j-(price[i][0]+price[i][1])/10]
                                   +price[i][0]*weight[i][0]+price[i][1]*weight[i][1]);
            }
            if((price[i][0]+price[i][2])/10<=j){
				m_price[i][j] = max(m_price[i][j],m_price[i-1][j-(price[i][0]+price[i][2])/10]
                                   +price[i][0]*weight[i][0]+price[i][2]*weight[i][2]);
            }
            if((price[i][0]+price[i][1]+price[i][2])/10<=j)
                m_price[i][j] = max(m_price[i][j],m_price[i-1][j-(price[i][0]+price[i][1]+
                    price[i][2])/10]+price[i][0]*weight[i][0]+price[i][1]*weight[i][1]+price[i][2]*weight[i][2]);
        }
    }
	cout<<m_price[m][N];
}
int main(){
    while(true){
       Dependent_0_1_knapsack();
    }
    return 0;
}
