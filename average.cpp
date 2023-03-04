#include<iostream>
#include<cstdlib>
using namespace std;

int main(int argc,char *argv[]){

    double sum =0;
    
    for(int i=1;i<argc ;i++){
        sum += atof(argv[i]);
    }

    if(argc==1)cout<<"Please input numbers to find average.";

    else{
        cout<<"---------------------------------\n";
        cout<<"Average of "<<argc-1<<" numbers = "<<sum/(argc-1)<<'\n';
        cout<<"---------------------------------\n";
    }
}