#ifndef DATASTRUCTURE_HH
#define DATASTRUCTURE_HH
#include <vector>
#include <iostream>
#include "G4AutoLock.hh"
#include "G4Threading.hh"
#include "G4ThreadLocalSingleton.hh"

// TODO: 加载重离子注入的三维位置分布root文件。测试能否通过载入root库直接执行，如果不行则考虑使用Geant4的histo载入方式。
// TODO: 调用rapidjson库，将部分参数写入到json文件中，并读取。实现模板化。测试多线程是否可正常运行。
//结构体构造函数不占用内存

//struct intInfo{
//    intInfo(){
//        EventID=-1;
//        TrackID=-1;
//        xid=-1;
//        yid=-1;
//    }
//    int EventID;
//    int TrackID;
//    int xid;
//    int yid;
//} ;
const int maxhit=15;
typedef std::pair<std::string,int> intPair;
typedef std::pair<std::string,double> doublePair;
static std::vector<intPair> intInfo={
    {"EventID",-1},
    {"TrackID",-1},
    {"xid",-1},
    {"yid",-1}
};
static std::vector<doublePair> doubleInfo={
    {"Edep",0},
    {"Posx",0},
    {"Posy",0},
    {"Posz",0}
};
typedef std::pair<std::string,std::vector<intPair>> intPar;
typedef std::pair<std::string,std::vector<doublePair>> doublePar;

typedef std::vector<intPar> idet;
typedef std::vector<doublePar> ddet;
static idet intPars={
    {"d0",intInfo},
    {"d1",intInfo},
    {"d2",intInfo}
};
static ddet doublePars={
    {"d0",doubleInfo},
    {"d1",doubleInfo},
    {"d2",doubleInfo}
};
//多线程运行时，需要指定G4ThreadLocal关键字，且必须为静态类型。
G4ThreadLocal static std::vector<idet> ihit;
G4ThreadLocal static std::vector<ddet> dhit;
static void init(){
    for (int i = 0; i < maxhit; ++i) {
        ihit.push_back(intPars);
        dhit.push_back(doublePars);
    }
}
static void clear(){
    ihit.clear();
    dhit.clear();
}


//int getIntInfo(intInfo obj,int index){
//    //return *(int*)((char*)&obj+sizeof(int)*index);
//}
//double getDoubleInfo(doubleInfo obj,int index){
//    return *(double*)((char*)&obj+sizeof(double)*index);
//}
//info getDetInfo(hit obj,int index){
//    return *(info*)((char*)&obj+sizeof(info)*index);
//}

//int getIntInfoCount(){
//    return sizeof(intInfo)/sizeof(int);
//}

//double getDoubleInfoCount(){
//    return sizeof(doubleInfo)/sizeof(double);
//}

//static std::vector<std::string> detName={"d0","d1","d2"};
//static std::vector<std::string> intInfoName ={"EventID","TrackID","xid","yid"};
//static std::vector<std::string> doubleInfoName={"Edep","Posx","Posy","Posz"};
//static hit hitevent;
//static std::vector<hit> hits;// max 256
//void init(){
//    for(int i=0;i<sizeof(hit)/sizeof(info);i++){

//        for(int j=0;j<getIntInfoCount();j++){
//            std::cout<<detName[i]<<intInfoName[j]<<std::endl;
//            std::cout<<getIntInfo(getDetInfo(hitevent,i).intInform,j)<<std::endl;

//        }
//        for(int j=0;j<getDoubleInfoCount();j++){
//            std::cout<<detName[i]<<intInfoName[j]<<std::endl;
//            std::cout<<getDoubleInfo(getDetInfo(hitevent,i).doubleInform,j)<<std::endl;
//        }
//    }
//}





#endif // DATASTRUCTURE_HH

