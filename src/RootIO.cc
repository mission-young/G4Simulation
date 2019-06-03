#include "RootIO.hh"
#include <iostream>

static RootIO* instance = 0;
RootIO::RootIO():ipf(0),opf(0),ipt(0),opt(0)
{

}

RootIO *RootIO::GetInstance()
{
    if(instance==0){
        instance=new RootIO();
    }
    return  instance;
}

void *RootIO::SetIpf(const char* ipfname)
{   if(ipf==0) {
        ipf=new TFile(ipfname);
    }else{
        try {
            ipf->Close();
            delete ipf;
        } catch (const char* msg) {
            ipf->Close();
        }
        ipf=new TFile(ipfname);
    }
}

void *RootIO::SetOpf(const char* opfname)
{
    if(opf==0){
        opf=new TFile(opfname,"recreate");
    }else{
        opf->SetName(opfname);
    }
}

void *RootIO::SetIpt(const char* iptname)
{
    if(ipf){
        try {
            ipt=(TTree*)ipf->Get(iptname);
        } catch (const char* msg) {
            std::cout<<"tree named "<<iptname<<" don't find!"<<std::endl;
        }
    }else{
        std::cout<<"root file don't/can't open!"<<std::endl;
    }
}

void *RootIO::SetOpt(const char* optname,const char* markdown)
{
    if(opt==0){
        opt=new TTree(optname,markdown);
    }else{
        opt->SetNameTitle(optname,markdown);
    }
}
