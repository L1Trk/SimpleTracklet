#include "L1Trigger/TrackFindingTMTT/interface/TrackletSeed.h"
#include "L1Trigger/TrackFindingTMTT/interface/Stub.h"
#include "L1Trigger/TrackFindingTMTT/interface/Utility.h"
#include "L1Trigger/TrackFindingTMTT/interface/StubCluster.h"
#include "L1Trigger/TrackFindingTMTT/interface/TrackletProjection.h"
#include <L1Trigger/TrackFindingTMTT/interface/Sector.h>


using namespace std;
namespace TMTT{

 //////////////////////////////////////////////////////////////////////////////////////
 TrackletSeed::TrackletSeed(const Stub* outerStub, const Stub* innerStub, unsigned int phiSec, 
   const Settings* settings):
  innerStub_(innerStub),
  outerStub_(outerStub),
  settings_(settings)
 {
  seedTypeReduced_ =  TrackletSeed::whichSeedTypeReduced(outerStub, innerStub);
  
  seedTypeFull_ = TrackletSeed::whichSeedTypeFull(outerStub, innerStub);

  if(!seedTypeReduced_){std::cout << "seedType not valid" << std::endl; assert(0);}
  
   
  this->setSectorParams(phiSec); 
  
  this->seed(outerStub, innerStub, seedTypeReduced_);

  makeTracklet();

 }



 void TrackletSeed::makeTracklet(){

  switch( seedTypeReduced_ ){
   case 1:

    // for( int layer = 0; layer < 4; ++layer ){
    for( int layer = 0; layer < 6; ++layer ){
     barrelProjections_.push_back(this->projectBarrel(layer));
    }

    for( int disk = 0; disk < 5; ++disk ){
     diskProjections_.push_back(this->projectEndcap(disk));
    }

    break;

   case 2:

    for( int layer = 0; layer < 6; ++layer ){
     barrelProjections_.push_back(this->projectBarrel(layer));
    }

    for( int disk = 0; disk < 5; ++disk ){
     diskProjections_.push_back(this->projectEndcap(disk));
    }

    break;

   case 3:

    for( int layer = 0; layer < 6; ++layer ){
     barrelProjections_.push_back(this->projectBarrel(layer));
    }

    for( int disk = 0; disk < 5; ++disk ){
     diskProjections_.push_back(this->projectEndcap(disk));
    }

    break;

   default:

    break;
  }

 }
 //////////////////////////////////////////////////////////////////////////////////////

 void TrackletSeed::phiSec(unsigned int x){phiSec_=x;}
 void TrackletSeed::etaSec(unsigned int x){etaSec_=x;}
 void TrackletSeed::secPhiMax(double x){secPhiMax_=x;}
 void TrackletSeed::secPhiMin(double x){secPhiMin_=x;}
 const unsigned int TrackletSeed::phiSec(){return phiSec_;}
 unsigned int TrackletSeed::seedTypeReduced(){return seedTypeReduced_;}
 unsigned int TrackletSeed::seedTypeFull(){return seedTypeFull_;}
 unsigned int TrackletSeed::etaSec(){return etaSec_;}
 double TrackletSeed::secPhiMax(){return secPhiMax_;}
 double TrackletSeed::secPhiMin(){return secPhiMin_;}

 const Stub* TrackletSeed::innerStub() { return innerStub_; }
 const Stub* TrackletSeed::outerStub() { return outerStub_; }

 double TrackletSeed::phi0(){return phi0_;}
 double TrackletSeed::rInv(){return rInv_;}
 double TrackletSeed::tanLambda(){return tanLambda_;}
 double TrackletSeed::z0(){return z0_;}

 std::vector<TrackletProjection> TrackletSeed::barrelProjections(){return barrelProjections_;}
 std::vector<TrackletProjection> TrackletSeed::diskProjections(){return diskProjections_;}

 //////////////////////////////////////////////////////////////////////////////////////
 void TrackletSeed::setSectorParams(unsigned int phiSec){

  phiSec_ = phiSec;

  Sector sector;//no eta regions in tracklet-tmtt
  sector.init(settings_, phiSec_, 0); //no eta regions in tracklet-tmtt

  secPhiMin_ = sector.phiCentre() - sector.sectorHalfWidth();
  secPhiMax_ = sector.phiCentre() + sector.sectorHalfWidth();
 }

 //////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////

 unsigned int TrackletSeed::whichSeedTypeFull(const Stub* outerStub, const Stub* innerStub){ //returns seed type index 0-7, matches tracklet emu
  /*
     index Seeding
     0     L1L2
     1     L3L4
     2     L5L6
     3     D1D2
     4     D3D4
     5     L1D1
     6     L2D1
     7     L2L3
     */

  if(seedTypeReduced_ == 1){

   switch (innerStub->layerId() ){
    case 1:
     return 0;
    case 2:
     return 7;
    case 3:
     return 1;
    case 5:
     return 2;
    default:
     assert(0);
   }

  }
  
  if(seedTypeReduced_ == 2){

   unsigned int disk = innerStub->layerId() > 20 ? innerStub->layerId() - 20 :  innerStub->layerId() - 10;  

   switch (disk) {
    case 1:
     return 3;
    case 3:
     return 4;
    default:
     assert(0);
   }

  }
  
  if(seedTypeReduced_ == 3){

   switch (innerStub->layerId()){
    case 1:
     return 5;
    case 2:
     return 6;
    default:
     assert(0);
   }

  }
  return 0;
 } 

 //////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////
 unsigned int TrackletSeed::whichSeedTypeReduced(const Stub* outerStub, const Stub* innerStub){ 
  //Simple seed type 1-3, returns 1 for barrel, 2 for disk, 3 for overlap

  if(innerStub->barrel() && outerStub->endcapRing()){
   return 3;}

  else if(innerStub->barrel() && outerStub->barrel()){
   return 1;}

  else if(innerStub->endcapRing() && outerStub->endcapRing()){
   return 2;}

  else return 0;

 }
 //////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////
 void TrackletSeed::seed(const Stub* outerStub, const Stub* innerStub, unsigned int seedType){ //Calculates initial helix parameters of tracklets

  double deltaPhi = Utility::wrapRadian(outerStub->phi() - innerStub->phi());

  double displacement = sqrt(pow(outerStub->r(),2) + pow(innerStub->r(),2) 
    - 2*outerStub->r()*innerStub->r()*cos(deltaPhi));

  double rInv = 2*sin(deltaPhi)/displacement;

  if(seedType==2 && innerStub->r() > innerStub->r()){

   rInv = -rInv;

  }

  double phi0 = innerStub->phi() - this->secPhiMin() //+ (secPhiMax() - secPhiMin())/6.0
   + asin(0.5*innerStub->r()*rInv);

  double tanLambda = ( innerStub->z() - outerStub->z() ) * rInv / ( 2 * ( asin( 0.5*rInv*innerStub->r() ) - asin( 0.5*rInv*outerStub->r() ) ) );

  double z0 = innerStub->z() - tanLambda * ( 2 * ( asin( 0.5 * rInv * innerStub->r() ) ) ) / rInv;

  rInv_=rInv;
  z0_=z0;
  phi0_=phi0;
  tanLambda_=tanLambda;

 }

 //////////////////////////////////////////////////////////////////////////////////////

 //////////////////////////////////////////////////////////////////////////////////////
 TrackletProjection TrackletSeed::projectBarrel(unsigned int layer){ //Projects seed to layer

  double rProjection = settings_->layerRadii().at( layer ); 

  double phiProjection = phi0_ - asin ( 0.5 * rProjection * rInv_);

  double zProjection = z0_ + 2 * tanLambda_ * asin( 0.5 * rProjection * rInv_) / rInv_;

  double phiDerivitive = - 0.5 * rInv_ / sqrt( 1 - pow( 0.5 * rProjection * rInv_ , 2 ) );

  double zDerivitive = tanLambda_ / sqrt( 1 - pow ( 0.5* rProjection * rInv_ , 2 ) );

  TrackletProjection projection(rProjection, zProjection, phiProjection, 0, zDerivitive, phiDerivitive);

  return projection;
 }

 ////////////////////////////////////////////////////////////////


 /////////////////////////////////////////////////////////////////
 TrackletProjection TrackletSeed::projectEndcap(unsigned int numDisk){ //Projects seed to disk

  double zProjection = settings_->diskZ().at( numDisk );

  if( tanLambda_ < 0 ){
   zProjection = -zProjection;
  }

  double tmp = rInv_ * ( zProjection - z0_ ) / 2.0 * tanLambda_;

  double rProjection = 2.0 * sin( tmp ) / rInv_;

  double phiProjection = phi0_ - tmp;

  double phiDerivitive = - 0.5 * rInv_ / tanLambda_;

  double rDerivitive = cos( tmp ) / tanLambda_;

  TrackletProjection projection(rProjection, zProjection, phiProjection, rDerivitive, 0, phiDerivitive);

  return projection;
 }

}
/////////////////////////////////////////////////////////////
