#include<ctime>
#include<iostream>
#include<vector>
#include "blockchain.h"

using namespace std;


// contructor with params
block::block (int idx, transactionData d, size_t prevHarsh)
{
    index=idx;
    data=d;
    previousHarsh=prevHarsh;
    blockHarsh=generateHarsh();

}
//private function:generate harsh
size_t block::generateHarsh()
{
    hash<string> harsh1;
    hash<size_t> harsh2;
    hash<size_t> harsh3;

    string toHarsh=to_string(data.amount)+data.receiverKey+data.senderKey+to_string(data.timestamp);
    return finalHash(harsh1(toHarsh)+harsh2(previousHarsh));

}
//public funtions
size_t block::getHarsh()
{
    return blockHarsh;
}
size_t block::getpreviousHarsh()
{
    return previousHarsh;
}
bool block::isHarshValid()
{

return generateHarsh()==blockHarsh;
}


//Blockchain contructor
blockchain::blockchain()
{
    block genesis=creategenesisblock();
    chain.push_back(genesis);

}
//public chain getter
std::vector<block> blockchain::getChain()
{
    return chain;
}

block blockchain::creategenesisblock()
{
    //get current time
    std::time_t current;
    //initial transaction data
    transactionData d(0,"Genesis","Genesis",time(&current));
    //creating string of transaction data
    std::string toHashS=std::to_string(d.amount)+d.senderKey+d.receiverKey+std::to_string(d.timestamp);
    //harshing
    std::hash<std::string> tDataHash;//hashes transaction string
    std::hash<std::string> prevHash;//re-hashes previous hash(for combination)
    //combine hashes
    size_t hash=tDataHash(toHashS)^(prevHarsh(std::string(0))<<1);

    block genesis(0,d,harsh);
    return genesis;
}
// only for demo
block *blockchain::getlatestblock()
{
    return &chain.back();
 
}
void blockchain::addBlock(transactionData d)
{
    int index= (int)chain.size();
    std::size_t lastHash=(int)chain.size()>0?getlatestblock()->getHarsh():0;
    block newBlock(index,d,lastHash);
    chain.push_back(newBlock);
}
bool blockchain::isChainValid()
{
    vector<block>::iterator it;
    int chainlen =(int)chain.size();
    for(it=chain.begin();it!=chain.end();++it)
    {
        block currentblock=*it;
        if(!currentblock.isHarshValid())
        {
            //invalid
            return false;
        }
        if(chainlen>1)
        {
            block previousblock=*(it-1);
            if(currentblock.getpreviousHarsh()!=previousblock.getHarsh())
            {
                //inalid
                return false;
            }
        }
    }
    return true;
}
void blockchain::printChain()
{
    std::vector<block>::iterator it;
    for(it=chain.begin();it!=chain.end();++it)
    {
        block currentblock=*it;
        printf("\n\nBlock=======================");
        printf("\nIndex:%d",currentblock.getIndex());
        printf("\nAmount:%f",currentblock.data.amount);
        printf("\nSenderKey: %s", currentblock.data.senderKey.c_str());
    }
}
