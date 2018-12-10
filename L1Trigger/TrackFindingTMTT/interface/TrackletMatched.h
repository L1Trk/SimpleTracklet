#ifndef __TRACKLETMATCHED_H__
#define __TRACKLETMATCHED_H__

#include <vector>
#include "L1Trigger/TrackFindingTMTT/interface/Stub.h"
#include "L1Trigger/TrackFindingTMTT/interface/TrackletWindows.h"
#include "L1Trigger/TrackFindingTMTT/interface/TrackletSeed.h"


using namespace std;

namespace TMTT {
 class Stub;
 class TrackletWindows;
 class TrackletSeed;

class TrackletMatched{

 public:
  
  TrackletMatched( TrackletSeed* tracklet, Settings* settings );
  ~TrackletMatched(){};

  void MatchLayerStub( Stub* stub, TrackletWindows* windows );
  void MatchDiskStub(  Stub* stub, TrackletWindows* windows );

 private:
  
  TrackletSeed* tracklet_;
  Settings* settings_;
  std::vector < Stub* > stublist_; 
};

}

#endif
