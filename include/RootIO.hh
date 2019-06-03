#ifndef ROOTIO_HH
#define ROOTIO_HH

#include "TROOT.h"
#include "TFile.h"
#include "TSystem.h"
#include "TTree.h"
#include "TRandom3.h"
#include "TH3F.h"

class RootIO
{
public:
    RootIO();
    static RootIO* GetInstance();
    TFile* GetIpf() {return ipf;}
    TFile* GetOpf() {return opf;}
    TTree* GetIpt() {return ipt;}
    TTree* GetOpt() {return opt;}
    void* SetIpf(const char* ipfname="ipf.root");
    void* SetOpf(const char* opfname="opf.root");
    void* SetIpt(const char* iptname="ipt");
    void* SetOpt(const char* optname="opt",const char* markdown="G4 simulation");
private:
    TFile *ipf;
    TFile *opf;
    TTree *ipt;
    TTree *opt;


};

#endif // ROOTIO_HH
