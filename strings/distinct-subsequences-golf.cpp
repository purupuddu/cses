#include<iostream>
long m=1e9+7,t=1,k,l[1];main(){for(char c;std::cin>>c;)k=l[c],l[c]=t,t=(t+t-k)%m;std::cout<<(t+m-1)%m<<'\n';}