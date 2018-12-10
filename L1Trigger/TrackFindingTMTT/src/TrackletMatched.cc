#include "L1Trigger/TrackFindingTMTT/interface/TrackletSeed.h"
#include "L1Trigger/TrackFindingTMTT/interface/TrackletMatched.h"
#include "L1Trigger/TrackFindingTMTT/interface/TrackletProjection.h"


namespace TMTT{


 TrackletMatched::TrackletMatched(TrackletSeed* tracklet, Settings* settings) :
  tracklet_(tracklet),
  settings_(settings)
 {

 };



 void TrackletMatched::MatchLayerStub( Stub* stub, TrackletWindows* windows){

  unsigned int layer = stub->layerId();//layer must go from 0-5

  layer-=1;

  double deltaR = stub->r() - tracklet_->barrelProjections().at(layer).rProjection();

  double deltaPhi = stub->phi() - tracklet_->barrelProjections().at(layer).phiProjection() - deltaR*tracklet_->barrelProjections().at(layer).phiDerivitive();

  double deltaZ = stub->z() - tracklet_->barrelProjections().at(layer).zProjection() - deltaR*tracklet_->barrelProjections().at(layer).zDerivitive();

  double layerRadii = settings_->layerRadii().at(layer); 

  bool match = ( deltaPhi < windows->phiMatchingWindowsBarrel[layer][tracklet_->seedType()] / layerRadii && 
    deltaZ < windows->zMatchingWindowsBarrel[layer][tracklet_->seedType()] / layerRadii );

  if(match){stublist_.push_back(stub);}
 }

 void TrackletMatched::MatchDiskStub( Stub* stub, TrackletWindows* windows){

  unsigned int disk = stub->layerId();//layer must go from 0-5

  if(disk > 20){//encoded for endcap B
   disk-=21;
  }else{
   disk-=11;
  }

  double deltaZ = stub->z() - tracklet_->diskProjections().at(disk).zProjection();

  double deltaPhi = stub->phi() - tracklet_->diskProjections().at(disk).phiProjection() - deltaZ * tracklet_->diskProjections().at(disk).phiDerivitive();

  double deltaR = stub->r() - tracklet_->diskProjections().at(disk).rProjection() - deltaZ * tracklet_->diskProjections().at(layer).rDerivitive();

  deltaPhi += deltaR * stub->alpha();
 
  
  double layerR = settings_->layerRadii().at(disk); 

  bool match = ( deltaPhi < windows->phiMatchingWindowsBarrel[layer][tracklet_->seedType()] / layerRadii && 
    deltaZ < windows->zMatchingWindowsBarrel[layer][tracklet_->seedType()] / layerRadii );

  if(match){stublist_.push_back(stub);}
 }


};
