#ifndef DATASTRUCTURE_HH
#define DATASTRUCTURE_HH

#define maxhit 10
class det{

public:
    int eventID[maxhit];
    int trackID[maxhit];
    int xid[maxhit];
    int yid[maxhit];
    double eDep[maxhit];
    double posX[maxhit];
    double posY[maxhit];
    double posZ[maxhit];
   // ClassDef(det,2);
};
#endif // DATASTRUCTURE_HH
