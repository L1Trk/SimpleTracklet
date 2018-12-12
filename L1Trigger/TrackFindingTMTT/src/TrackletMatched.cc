#include "L1Trigger/TrackFindingTMTT/interface/TrackletSeed.h"
#include "L1Trigger/TrackFindingTMTT/interface/TrackletMatched.h"
#include "L1Trigger/TrackFindingTMTT/interface/TrackletProjection.h"


namespace TMTT{

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 TrackletMatched::TrackletMatched(TrackletSeed* tracklet, Settings* settings) :
  tracklet_(tracklet),
  settings_(settings)
 {
 };

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 void TrackletMatched::MatchLayerStub( Stub* stub, TrackletWindows* windows){

  unsigned int layer = stub->layerId();//layer must go from 0-5

  layer-=1;

  double deltaR = stub->r() - tracklet_->barrelProjections().at(layer).rProjection();

  double deltaPhi = stub->phi() - tracklet_->barrelProjections().at(layer).phiProjection() - deltaR*tracklet_->barrelProjections().at(layer).phiDerivitive();

  double deltaZ = stub->z() - tracklet_->barrelProjections().at(layer).zProjection() - deltaR*tracklet_->barrelProjections().at(layer).zDerivitive();

  double layerRadii = settings_->layerRadii().at(layer); 

  //Execute stub matching conditions here, seedType must be extended format 0-7
  bool match = ( std::fabs(deltaPhi) < windows->phiMatchingWindowsBarrel[layer][tracklet_->seedTypeFull()] / layerRadii && 
    std::fabs(deltaZ) < windows->zMatchingWindowsBarrel[layer][tracklet_->seedTypeFull()] / layerRadii );

  if(match){stublist_.push_back(stub);}
 }
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 void TrackletMatched::MatchDiskStub( Stub* stub, TrackletWindows* windows){

  unsigned int disk = stub->layerId();//disk must go from 0-4

  if(disk > 20){//encoded for endcap B between 21 and 25
   disk-=21;
  }else{ //encoded for endcap A between 11 and 15
   disk-=11;
  }

  double deltaZ = stub->z() - tracklet_->diskProjections().at(disk).zProjection();

  double deltaPhi = stub->phi() - tracklet_->diskProjections().at(disk).phiProjection() - deltaZ * tracklet_->diskProjections().at(disk).phiDerivitive();

  double deltaR = stub->r() - tracklet_->diskProjections().at(disk).rProjection() - deltaZ * tracklet_->diskProjections().at(disk).rDerivitive();

  //alpha corrections go here, not yet added as some confusion re alpha vs alphanew
  //deltaPhi += deltaR * stub->alpha();
  //drphi+=dr*alphanew*4.57/stub->r();
  double deltaRphi = deltaPhi*stub->r();

  bool match;
  //Execute stub matching conditions here, seedType must be extended format 0-7
  if (!stub->psModule()){
   match = std::fabs(deltaRphi) < windows->rphiMatchingWindowsDisk2S[disk][tracklet_->seedTypeFull()] && 
    std::fabs(deltaR) < windows->rMatchingWindowsDisk2S[disk][tracklet_->seedTypeFull()]; 
  }else{
   match = std::fabs(deltaRphi) < windows->rphiMatchingWindowsDiskPS[disk][tracklet_->seedTypeFull()] && 
    std::fabs(deltaR) < windows->rMatchingWindowsDiskPS[disk][tracklet_->seedTypeFull()]; 
  }

  if(match){stublist_.push_back(stub);}
 }
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

};
