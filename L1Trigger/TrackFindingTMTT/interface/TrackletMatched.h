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

  void MatchLayerStub( const Stub* stub, TrackletWindows* windows );
  void MatchDiskStub(  const Stub* stub, TrackletWindows* windows );

  std::vector < const Stub* > stublist();

 private:
  
  TrackletSeed* tracklet_;
  Settings* settings_;
  std::vector < const Stub* > stublist_; 
};

}

#endif
