#include<ctime>
#include<vector>

using namespace std;

#ifndef blockchain_h
#define blockchain_h
//tr  ansaction data
struct transactionData{
    double amount;
    std::string senderKey;
    std::string receiverKey;
    time_t timestamp;
    transactionData(){};
    transactionData(double amt,std::string sender ,std::string receiver,time_t time)
    {
        amount=amt;
        senderKey=sender;
        receiverKey=receiver;
        timestamp=time;
    }
};
// Block
class block{

private:
int index;
size_t blockHarsh;
size_t previousHarsh;
size_t generateHarsh();
public:
//constructor
block(int idx, transactionData d, size_t prevHarsh);
//get original harsh
size_t getHarsh();
//get previous harsh

size_t getpreviousHarsh();

//transaction data

transaction data;

//validate harsh
bool isHarshValid();
};

// Blockchain class
class blockchain{

private:
block creategenesisblock();
//public chain
std::vector<block> chain;
public:


//constructor
blockchain();
//functions
std::vector<block>getChain();
void addBlock(transactionData d);
bool isChainValid();

//example for demo
block *getlatestblock();
void printChain();

};

#endif