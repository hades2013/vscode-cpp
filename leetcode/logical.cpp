#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <stdio.h>
#include <algorithm>
#include <cmath>

using namespace std;

void loadDataset(vector<vector<double>> &dataMat,vector<int> &labelMat,const string &filename)
{

    ifstream file(filename);
    string line;
    while(getline(file,line))
    {
        vector<double> data;
        double x1,x2;
        int label;
        sscanf(line.c_str(),"%lf  %lf  %d",&x1,&x2,&label);
        data.push_back(1);
        data.push_back(x1);
        data.push_back(x2);
        dataMat.push_back(data);
        labelMat.push_back(label);
    }
}

double scalarProduct(vector<double> &w,vector<double> &x)
{
    double ret=0;
    for(int i=0;i<w.size();i++)
        ret+=w[i]*x[i];
    return ret;
}

double sigmoid(double z)
{
    return exp(z)/(1+exp(z));
}

vector<vector<double>> matTranspose(vector<vector<double>> &dataMat)
{
    vector<vector<double>> ret(dataMat[0].size(),vector<double>(dataMat.size(),0));
    for(int i=0;i<ret.size();i++)
        for(int j=0;j<ret[0].size();j++)
            ret[i][j]=dataMat[j][i];
    return ret;
}

void  gradAscent(vector<double> &weight,
                vector<vector<double>> &dataMat,vector<int> &labelMat)
{
    int maxCycles=500;
    double alpha=0.001;
    vector<vector<double>> dataMatT=matTranspose(dataMat);
    while(maxCycles>0)
    {
        vector<double> h;
        vector<double> error;
        for(auto &data:dataMat)
            h.push_back(sigmoid(scalarProduct(data,weight)));
        for(int i=0;i<labelMat.size();i++)
            error.push_back(labelMat[i]-h[i]);
        for(int i=0;i<weight.size();i++)
            weight[i]+=alpha*scalarProduct(dataMatT[i],error);
        maxCycles--;
    }

}

int main()
{
    vector<vector<double>> dataMat;
    vector<int> labelMat;
    string filename("testSet.txt");
    loadDataset(dataMat,labelMat,filename);
    vector<double> weight(dataMat[0].size(),1);
    gradAscent(weight,dataMat,labelMat);
    for(auto v:weight)
        cout<<v<<endl;  
}