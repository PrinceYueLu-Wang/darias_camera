# include <iostream>

using namespace std;

int main(int argc, char** argv){

   int x[2] ={100,200};

   int *p;

   p = x;

   cout<< ++*p<<endl;
   cout<< *p<<endl;

   return 0;
}