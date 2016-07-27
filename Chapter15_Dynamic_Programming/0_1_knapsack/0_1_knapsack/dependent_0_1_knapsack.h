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