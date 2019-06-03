#ifndef DATASTRUCTURE_HH
#define DATASTRUCTURE_HH

#define maxhit 1
#include "TROOT.h"
#include "TObject.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>
#include "G4ios.hh"

using namespace  std;
using namespace rapidjson;
static double energy;
static double depth;
static void loadconf(){
    ifstream ifs("./conf.json");
    IStreamWrapper isw(ifs);

    Document d;
    d.ParseStream(isw);
    energy=d["particle"]["proton"]["energy"].GetDouble();
    depth=d["particle"]["proton"]["z"].GetDouble();
    ifs.close();
}
//class det{

//public:
//    int eventID[maxhit];
//    int trackID[maxhit];
//    int xid[maxhit];
//    int yid[maxhit];
//    double eDep[maxhit];
//    double posX[maxhit];
//    double posY[maxhit];
//    double posZ[maxhit];
//   ClassDef(det,2);
//};
#endif // DATASTRUCTURE_HH
