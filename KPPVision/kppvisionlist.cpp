#include "kppvisionlist.h"
#include "kppvision.h"
using namespace Vision;




void Instantiations::Instantiate()
{
    KPPVisionList<KPPVision> inst;
    inst.Load();
    inst.Save();
    //inst.Loaded(new QObject());
    // other explicit instantiations may follow
}
