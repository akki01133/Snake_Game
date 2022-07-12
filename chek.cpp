#include<iostream>
#include<bits/stdc++.h>
#include<conio.h>

using namespace std;

int fx,fy,len;
vector<pair<int,int>> V(len);
int main()
{ system("cls");
   fstream saved;
    int no,a,b;
    saved.open("saved.txt",ios::in);
    saved>>no;
    fx=no;
    saved>>no;
    fy=no;
    saved>>no;
    len=no;
 for(int j=0;j<len;j++)
      {saved>>a;
      saved>>b;
        V.push_back(make_pair(a,b));} 
    saved.close(); 
 cout<<fx<<endl<<fy<<endl<<len;
 for(auto it: V)
 {
   cout<<it.first<<" "<<it.second<<endl;
 }
  return 0;
}