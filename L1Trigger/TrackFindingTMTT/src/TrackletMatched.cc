#include "L1Trigger/TrackFindingTMTT/interface/TrackletSeed.h"
#include "L1Trigger/TrackFindingTMTT/interface/TrackletMatched.h"
#include "L1Trigger/TrackFindingTMTT/interface/TrackletProjection.h"
#include <L1Trigger/TrackFindingTMTT/interface/Sector.h>


namespace TMTT{

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 TrackletMatched::TrackletMatched(TrackletSeed* tracklet, Settings* settings) :
  tracklet_(tracklet),
  settings_(settings)
 {
  stublist_.push_back( tracklet_->innerStub() );
  stublist_.push_back( tracklet_->outerStub() );
 };

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 void TrackletMatched::MatchLayerStub( const Stub* stub, TrackletWindows* windows){

  unsigned int layer = stub->layerId();//layer must go from 0-5

  layer-=1;

  double stubPhiInSector = stub->phi() - tracklet_->secPhiMin();// + asin(0.5*stub->r()*settings_->invPtToDphi());

  double deltaR = stub->r() - tracklet_->barrelProjections().at(layer).rProjection();
  double deltaPhi = stubPhiInSector - tracklet_->barrelProjections().at(layer).phiProjection() - deltaR*tracklet_->barrelProjections().at(layer).phiDerivitive();
  double deltaZ = stub->z() - tracklet_->barrelProjections().at(layer).zProjection() - deltaR*tracklet_->barrelProjections().at(layer).zDerivitive();

  double layerRadii = settings_->layerRadii().at(layer); 
  //Execute stub matching conditions here, seedType must be extended format 0-7
  bool match = ( std::fabs(deltaPhi) < windows->phiMatchingWindowsBarrel[layer][tracklet_->seedTypeFull()] / layerRadii && 
    std::fabs(deltaZ) < windows->zMatchingWindowsBarrel[layer][tracklet_->seedTypeFull()] );// / layerRadii );

  if(match){stublist_.push_back(stub);}
 }
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 void TrackletMatched::MatchDiskStub( const Stub* stub, TrackletWindows* windows){

  unsigned int disk = stub->layerId();//disk must go from 0-4

  if(disk > 20){//encoded for endcap B between 21 and 25
   disk-=21;
  }else{ //encoded for endcap A between 11 and 15
   disk-=11;
  }

  double stubPhiInSector = stub->phi() - tracklet_->secPhiMin();// + asin(0.5*stub->r()*settings_->invPtToDphi());

  double deltaZ = stub->z() - tracklet_->diskProjections().at(disk).zProjection();

  double deltaPhi = stubPhiInSector - tracklet_->diskProjections().at(disk).phiProjection() - deltaZ * tracklet_->diskProjections().at(disk).phiDerivitive();

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

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 std::vector< const Stub* > TrackletMatched::stublist(){
 return stublist_;}

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 L1track3D TrackletMatched::returntrack3D(){

  unsigned int etaReg = 0; // Bad, as this default value is an actual eta region
 for (unsigned int iEtaReg = 0; iEtaReg < settings_->numEtaRegions(); iEtaReg++) {
  Sector sector;
  sector.init( settings_, tracklet_->phiSec(), iEtaReg );
  if ( sector.inside( stublist_[0] ) ) etaReg = iEtaReg;
 }

  L1track3D track = L1track3D(settings_, stublist_, pair<unsigned int, unsigned int>(0, 0), 
    pair<float,float>(tracklet_->rInv()/settings_->invPtToInvR(), tracklet_->phi0() + tracklet_->secPhiMin()), pair<float, float>(tracklet_->z0(), 
     tracklet_->tanLambda()), tracklet_->phiSec(), etaReg, 0, false);
 return track;
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /*
   L1track3D(const Settings* settings, const vector<const Stub*>& stubs,
                 pair<unsigned int, unsigned int> cellLocationHT, pair<float, float> helixRphi, pair<float, float> helixRz,
                       unsigned int iPhiSec, unsigned int iEtaReg, unsigned int optoLinkID, bool mergedHTcell) :}
*/
}
};
