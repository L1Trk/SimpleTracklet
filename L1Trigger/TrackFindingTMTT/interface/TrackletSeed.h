#ifndef __TRACKLETSEED_H__
#define __TRACKLETSEED_H__

#include <vector>

using namespace std;

namespace TMTT {
 class Stub;
 class Settings;
 class TrackletProjection;
 class TrackletSeed{

  public:

   TrackletSeed(Stub* outerStub, Stub* innerStub, unsigned int phiSec, const TMTT::Settings* settings);
   ~TrackletSeed(){};
   void makeTracklet();
   void setSectorParams(unsigned int);
   unsigned int whichSeedType(Stub* outerStub, Stub* innerStub); 
   void seed(Stub* outerStub, Stub* innerStub, unsigned int seedType);
   void phiSec(unsigned int x);
   void etaSec(unsigned int x);
   void secPhiMax(double x);
   void secPhiMin(double x);
   void seedType(unsigned int x);
   TrackletProjection projectBarrel(unsigned int rProjection);
   TrackletProjection projectEndcap(unsigned int rProjection);

   unsigned int phiSec();
   unsigned int seedType();
   unsigned int etaSec();
   double secPhiMax();
   double secPhiMin();

   double rInv();
   double phi0();
   double z0();
   double tanLambda();

   void setRInv(double rInv);
   void setPhi0(double phi0);
   void setZ0(double z0);
   void setTanLambda(double tanLambda);

  private:

   Stub* innerStub_;
   Stub* outerStub_;
   unsigned int phiSec_, etaSec_, seedType_;
   double rInv_, phi0_, z0_, tanLambda_; //Track params
   double secPhiMin_, secPhiMax_;
   std::vector <TrackletProjection> projections; 
   const Settings* settings_;
 };

}
#endif
