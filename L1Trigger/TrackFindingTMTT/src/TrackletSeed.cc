#include "L1Trigger/TrackFindingTMTT/interface/TrackletSeed.h"
#include "L1Trigger/TrackFindingTMTT/interface/Stub.h"
#include "L1Trigger/TrackFindingTMTT/interface/Utility.h"
#include "L1Trigger/TrackFindingTMTT/interface/StubCluster.h"


using namespace std;
namespace TMTT{

 TrackletSeed::TrackletSeed(Stub* outerStub, Stub* innerStub, unsigned int phiSec, 
   const Settings* settings):
  settings_(settings)
 {

  unsigned int seedType =  TrackletSeed::whichSeedType(outerStub, innerStub);

  if(!seedType){std::cout << "seedType not valid" << std::endl; assert(0);}

  this->setSectorParams(phiSec);

 }


 void TrackletSeed::phiSec(unsigned int x){phiSec_=x;}
 void TrackletSeed::etaSec(unsigned int x){etaSec_=x;}
 void TrackletSeed::secPhiMax(double x){secPhiMax_=x;}
 void TrackletSeed::secPhiMin(double x){secPhiMin_=x;}
 unsigned int TrackletSeed::phiSec(){return phiSec_;}
 unsigned int TrackletSeed::etaSec(){return etaSec_;}
 double TrackletSeed::secPhiMax(){return secPhiMax_;}
 double TrackletSeed::secPhiMin(){return secPhiMin_;}
 void TrackletSeed::setSectorParams(unsigned int phiSec){

  this->phiSec(phiSec);

  double dphiSec=M_PI/settings_->numPhiSectors()+2*fmax(
    fabs(asin(0.5*settings_->invPtToDphi()*settings_->radLayers().at(0)-asin(0.5*settings_->invPtToDphi()*settings_->chosenRofPhi()))),
     fabs(asin(0.5*settings_->invPtToDphi()*settings_->radLayers().at(5)-asin(0.5*settings_->invPtToDphi()*settings_->chosenRofPhi()))));

     secPhiMin(Utility::wrapRadian(phiSec*2*M_PI/settings_->numPhiSectors() - 0.5*dphiSec));
     secPhiMax(Utility::wrapRadian(secPhiMin() + 2*M_PI/settings_->numPhiSectors() + 2*dphiSec));
      }

      unsigned int TrackletSeed::whichSeedType(Stub* outerStub, Stub* innerStub){ //returns 1 for barrel, 2 for disk, 3 for overlap

      if(innerStub->barrel() && outerStub->endcapRing()){
      return 3;}

      else if(innerStub->barrel() && outerStub->barrel()){
      return 1;}

      else if(innerStub->endcapRing() && outerStub->endcapRing()){
      return 2;}
      else return 0;

      }

      void TrackletSeed::barrelSeed(Stub* outerStub, Stub* innerStub){

      double deltaPhi = Utility::wrapRadian(outerStub->phi() - innerStub->phi());

      double displacement = sqrt(pow(outerStub->r(),2) + pow(innerStub->r(),2) 
        - 2*outerStub->r()*innerStub->r()*cos(deltaPhi));

      double rInv = 2*sin(deltaPhi)/displacement;
      
      double phi0 = innerStub->phi() - this->secPhiMin() + (secPhiMax() - secPhiMin())/6.0
          + asin(0.5*innerStub->r()*settings_->invPtToDphi());



      }


}

