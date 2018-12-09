#include "L1Trigger/TrackFindingTMTT/interface/TrackletSeed.h"


namespace TMTT{


 TrackletMatched::TrackletMatched(TrackletSeed* tracklet) :
tracklet_(tracklet)
 {

 }



void TrackletMatched::MatchStub( Stub* stub, TrackletWindows* windows){

 unsigned int layer = stub->layer();//layer must go from 0-5

double deltaR = stub->r() - tracklet_->barrelProjections().at(layer).rProjection();

double deltaPhi = stub->phi() - tracklet_->barrelProjections().at(layer).phiProjection() - deltaR*tracklet_->barrelProjections.at(layer).phiDerivitive();

double deltaZ = stub->z() - tracklet_->barrelProjections().at(layer).zProjection - deltaR*tracklet->barrelProjections().at(layer).zDerivitive();

double layerRadii = settings->layerRadii.at(layer); 

bool match = ( deltaPhi < windows->phiMatchingWindowsBarrel[layer][tracklet_->seedType()] / layerRadii && 
  deltaZ < windows->zMatchingWindowsBarrel[layer][tracklet_->seedType()] / layerRadii );

if(match){
stubList.push_back(stub);
}



double phiMatchingWindowsBarrel[6][8] = //first index (row) is layer number, second index (column) is tracklet seed type
 //zero elements are unused
{ 
 { 0,    0.07, 0.08, 0.07, 0.05, 0,    0.05, 0.10 },//layer 1 phi windows
 { 0,    0.06, 0.08, 0.05, 0,    0,    0,    0    },//layer 2 phi windows
 { 0.10, 0,    0.08, 0,    0,    0,    0,    0    },//layer 3 phi windows
 { 0.19, 0,    0.05, 0,    0,    0,    0,    0.19 },//layer 4 phi windows
 { 0.4,  0.08, 0,    0,    0,    0,    0,    0.4  },//layer 5 phi windows
 { 0.5,  0.19 ,0,    0,    0,    0,    0,    0    } //layer 6 phi windows
};

double zMatchingWindowsBarrel[6][8] = //first index (row) is layer number, second index (column) is tracklet seed type
 //zero elements are unused
{ 
 { 0,    0,    0,    0,    0,    0,    0,    0    },//layer 1 z windows
 { 0,    0,    0,    0,    0,    0,    0,    0    },//layer 2 z windows
 { 0,    0,    0,    0,    0,    0,    0,    0    },//layer 3 z windows
 { 0,    0,    0,    0,    0,    0,    0,    0    },//layer 4 z windows
 { 0,    0,    0,    0,    0,    0,    0,    0    },//layer 5 z windows
 { 0,    0,    0,    0,    0,    0,    0,    0    } //layer 6 z windows
};

}



};
