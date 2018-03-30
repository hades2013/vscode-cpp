/********************************************************************************** 
* 
* Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? 
* Find all unique triplets in the array which gives the sum of zero.
* 
* Note:
* 
* Elements in a triplet (a,b,c) must be in non-descending order. (ie, a ≤ b ≤ c)
* The solution set must not contain duplicate triplets.
* 
*     For example, given array S = {-1 0 1 2 -1 -4},
* 
*     A solution set is:
*     (-1, 0, 1)
*     (-1, -1, 2)
* 
*               
**********************************************************************************/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std; 


vector<vector<int>> threeSumA(vector<int> &num){
    vector<vector<int>> result; 
    if(num.size()==0 || num.size()==1 || num.size() == 2) 
        return result;
    sort(num.begin(), num.end());
    int n = num.size();
    for(int i =0; i< n-2; i++){
        //skip the duplication
        if (i>0 && num[i-1]==num[i]) continue;
        int a = num[i];
        int low = i+1;
        int high = n-1;
        while ( low < high ) {
            int b = num[low];
            int c = num[high];
            if (a+b+c == 0) {
                //got the soultion
                vector<int> v;
                v.push_back(a);
                v.push_back(b);
                v.push_back(c);
                result.push_back(v);
                // Continue search for all triplet combinations summing to zero.
                //skip the duplication
                while(low<n-1 && num[low]==num[low+1]) low++; 
                while(high>0 && num[high]==num[high-1]) high--; 
                low++;
                high--;
            } else if (a+b+c > 0) {
                //skip the duplication
                while(high>0 && num[high]==num[high-1]) high--;
                high--;
            } else{
                //skip the duplication
                while(low<n-1 && num[low]==num[low+1]) low++;
                low++;
            } 
        }
    }
    return result; 
}

void printMatrix(vector<vector<int>> &matrix)
{
    for(int i = 0; i < matrix.size(); i++){
        printf("{");
        for(int j =0; j < matrix.size(); j++){
            printf("%3d", matrix[i][j]);
        }
        printf("}\n");
    }
    cout<<endl; 
}

vector<vector<int>> threeSumB(vector<int>& nums) {
    vector<vector<int>> triples;
    sort(nums.begin(), nums.end());
    int i = 0, last = nums.size() - 1;
    while (i < last) {
    int a = nums[i], j = i+1, k = last;
        while (j < k) {
            int b = nums[j], c = nums[k], sum = a+b+c;
            if (sum == 0) triples.push_back({a, b, c});
            if (sum <= 0) while (nums[j] == b && j < k) j++;
            if (sum >= 0) while (nums[k] == c && j < k) k--;        
            }
        while (nums[i] == a && i < last) i++;
    }
    return triples;
}

int main()
{
    //int a[] = {-1, 0, 1, 2, -1, 1, -4};
    int a[] = {-1, 1, 1, 1, -1, -1, 0,0,0};
    vector<int> n(a, a+sizeof(a)/sizeof(int));
    vector< vector<int> > result = threeSumB(n);
    printMatrix(result);    
    return 0; 
}

