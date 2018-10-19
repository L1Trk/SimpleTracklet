#ifndef __TRACKLETSEED_H__
#define __TRACKLETSEED_H__

using namespace std;

namespace TMTT {
 class Stub;
 class Settings;
 class TrackletSeed{

  public:

   TrackletSeed(Stub* outerStub, Stub* innerStub, unsigned int phiSec, const TMTT::Settings* settings);
   ~TrackletSeed(){};
   
   void setSectorParams(unsigned int);
   unsigned int whichSeedType(Stub* outerStub, Stub* innerStub); 
   void barrelSeed(Stub* outerStub, Stub* innerStub);
   void phiSec(unsigned int x);
   void etaSec(unsigned int x);
   void secPhiMax(double x);
   void secPhiMin(double x);

   unsigned int phiSec();
   unsigned int etaSec();
   double secPhiMax();
   double secPhiMin();

  private:

   unsigned int seedType_;

   Stub* innerStub_;
   Stub* outerStub_;
   unsigned int phiSec_;
   unsigned int etaSec_;
   double rInv_, phi0_, z0_, tanLambda_; //Track params
   double secPhiMin_, secPhiMax_;
   const Settings* settings_;
 };
}
#endif
