#include<iostream>
#include<ctime>
#include<vector>
#include "blockchain.h"

using namespace std;
int main()
[
    blockchain Lcoin;
    time_t data1Time;
    transactionData data1(1.6,"Fidel","Cynthia",time(&data1Time));
    Lcoin.addBlock(data1);

    Lcoin.printChain();
    return 0;
    
]