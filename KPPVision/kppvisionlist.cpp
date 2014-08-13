#include "kppvisionlist.h"
#include "kppvision.h"
using namespace Vision;




void Instantiations::Instantiate()
{
    KPPVisionList<KPPVision> inst1;
    inst1.Load();
    inst1.Save();
    inst1.getList();

    KPPVisionList<Request> inst2;
    inst2.Load();
    inst2.Save();
    inst2.getList();

    KPPVisionList<Inspection> inst3;
    inst3.Load();
    inst3.Save();
    inst3.getList();

    //inst.Loaded(new QObject());
    // other explicit instantiations may follow
}


