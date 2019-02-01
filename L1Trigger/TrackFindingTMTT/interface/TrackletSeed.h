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

   TrackletSeed(const Stub* outerStub, const Stub* innerStub, unsigned int phiSec, const TMTT::Settings* settings);
   ~TrackletSeed(){};
   void makeTracklet();
   void setSectorParams(unsigned int);
   unsigned int whichSeedTypeReduced(const Stub* outerStub, const Stub* innerStub); 
   unsigned int whichSeedTypeFull(const Stub* outerStub, const Stub* innerStub); 
   void storeSeedType(Stub* outerStub, Stub* innerStub); 
   void seed(const Stub* outerStub, const Stub* innerStub, unsigned int seedType);
   void phiSec(unsigned int x);
   void etaSec(unsigned int x);
   void secPhiMax(double x);
   void secPhiMin(double x);
   TrackletProjection projectBarrel(unsigned int rProjection);
   TrackletProjection projectEndcap(unsigned int rProjection);

   const unsigned int phiSec();
   unsigned int seedTypeReduced();
   unsigned int seedTypeFull();
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

   std::vector<TrackletProjection> barrelProjections();
   std::vector<TrackletProjection> diskProjections();
 
  private:

   Stub* innerStub_;
   Stub* outerStub_;
   unsigned int phiSec_, etaSec_, seedTypeFull_, seedTypeReduced_;
   double rInv_, phi0_, z0_, tanLambda_; //Track params
   double secPhiMin_, secPhiMax_;
   const Settings* settings_;
   std::vector <TrackletProjection> barrelProjections_; 
   std::vector <TrackletProjection> diskProjections_; 
 };

}
#endif
