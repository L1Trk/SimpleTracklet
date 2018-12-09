#include "L1Trigger/TrackFindingTMTT/interface/TrackletSeed.h"
#include "L1Trigger/TrackFindingTMTT/interface/Stub.h"
#include "L1Trigger/TrackFindingTMTT/interface/Utility.h"
#include "L1Trigger/TrackFindingTMTT/interface/StubCluster.h"


using namespace std;
namespace TMTT{

//////////////////////////////////////////////////////////////////////////////////////
 TrackletSeed::TrackletSeed(Stub* outerStub, Stub* innerStub, unsigned int phiSec, 
   const Settings* settings):
  settings_(settings)
 {

  unsigned int seedType =  TrackletSeed::whichSeedType(outerStub, innerStub);

  if(!seedType){std::cout << "seedType not valid" << std::endl; assert(0);}

  this->setSectorParams(phiSec);
  
  this->seed(outerStub, innerStub, seedType);
  
  makeTracklet();

 }



 void TrackletSeed::makeTracklet(){

  vector<projection> barrelProjections;
  vector<projection> endcapProjections;

  switch( this->seedType() ){
   case 1:
      
    for( int layer = 0; layer < 4; ++layer ){
    barrelProjections.push_back(this->projectBarrel(layer));
    }

    for( int disk = 0; disk < 5; ++disk ){
    endcapProjections.push_back(this->projectEndcap(disk));
    }
  
    break;

   case 2:
    
    for( int layer = 0; layer < 4; ++layer ){
    barrelProjections.push_back(this->projectBarrel(layer));
    }

    for( int disk = 0; disk < 5; ++disk ){
    endcapProjections.push_back(this->projectEndcap(disk));
    }
    
    break;
   
   case 3:
    
    for( int layer = 0; layer < 4; ++layer ){
    barrelProjections.push_back(this->projectBarrel(layer));
    }

    for( int disk = 0; disk < 5; ++disk ){
    endcapProjections.push_back(this->projectEndcap(disk));
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
 void TrackletSeed::seedType(unsigned int x){seedType_=x;}
 unsigned int TrackletSeed::phiSec(){return phiSec_;}
 unsigned int TrackletSeed::seedType(){return seedType_;}
 unsigned int TrackletSeed::etaSec(){return etaSec_;}
 double TrackletSeed::secPhiMax(){return secPhiMax_;}
 double TrackletSeed::secPhiMin(){return secPhiMin_;}

 
//////////////////////////////////////////////////////////////////////////////////////
 void TrackletSeed::setSectorParams(unsigned int phiSec){

  this->phiSec(phiSec);

  double dphiSec=M_PI/settings_->numPhiSectors()+2*fmax(
    fabs(asin(0.5*settings_->invPtToDphi()*settings_->radLayers().at(0)-asin(0.5*settings_->invPtToDphi()*settings_->chosenRofPhi()))),
    fabs(asin(0.5*settings_->invPtToDphi()*settings_->radLayers().at(5)-asin(0.5*settings_->invPtToDphi()*settings_->chosenRofPhi()))));

  secPhiMin(Utility::wrapRadian(phiSec*2*M_PI/settings_->numPhiSectors() - 0.5*dphiSec));
  secPhiMax(Utility::wrapRadian(secPhiMin() + 2*M_PI/settings_->numPhiSectors() + 2*dphiSec));
 }

//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
 unsigned int TrackletSeed::whichSeedType(Stub* outerStub, Stub* innerStub){ //returns 1 for barrel, 2 for disk, 3 for overlap

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
 void TrackletSeed::seed(Stub* outerStub, Stub* innerStub, unsigned int seedType){

  double deltaPhi = Utility::wrapRadian(outerStub->phi() - innerStub->phi());

  double displacement = sqrt(pow(outerStub->r(),2) + pow(innerStub->r(),2) 
    - 2*outerStub->r()*innerStub->r()*cos(deltaPhi));

  double rInv = 2*sin(deltaPhi)/displacement;

  if(seedType==2 && innerStub->r() > innerStub->r()){
  
   rInv = -rInv;

  }

  double phi0 = innerStub->phi() - this->secPhiMin() + (secPhiMax() - secPhiMin())/6.0
   + asin(0.5*innerStub->r()*settings_->invPtToDphi());

  double tanLambda = (innerStub->z() - outerStub->z())*settings_->invPtToDphi() /
   2*(asin(0.5*settings_->invPtToDphi()*innerStub->r()) - 
     asin(0.5*settings_->invPtToDphi()*outerStub->r()));

  double z0 = innerStub->z() - tanLambda*(2*(asin(0.5*settings_->invPtToDphi()*innerStub->r())));

  rInv_=rInv;
  z0_=z0;
  phi0_=phi0;
  tanLambda_=tanLambda;

    }

//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
  TrackletProjection TrackletSeed::projectBarrel(unsigned int rProjection){
  
  double phiProjection = phi0_ - asin ( 0.5 * rProjection * rInv_);
  
  double zProjection = z0_ + 2 * tanLambda_ * asin( 0.5 * rProjection * rInv_);

  double phiDerivitive = - 0.5 * rInv_ / sqrt( 1 - pow( 0.5 * rProjection * rInv_ , 2 ) );

  double zDerivitive = tanLambda_ / sqrt( 1 - pow ( 0.5* rProjection * rInv_ , 2 ) );
    
  }

////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
TrackletProjection projectEndcap(unsigned int numDisk){

double zProjection = this->endcapProj.at( numDisk );

if( tanLambda_ < 0 ){
zProjection = -zProjection;
}

double tmp = rInv * ( zProjection - z0_ ) / 2.0 * tanLambda_;

double rProjection = 2.0 * sin( tmp ) / rInv_;

double phiProjection = phi0_ - tmp;

double phiDerivitive = - 0.5 * rInv_ / tanLambda_;

double rDerivitive = cos( tmp ) / tanLambda_;

projection Projection(rProjection, zProjection, phiProjection, rDerivitive, 0, phiDerivitive);

return projection;
}
/////////////////////////////////////////////////////////////
