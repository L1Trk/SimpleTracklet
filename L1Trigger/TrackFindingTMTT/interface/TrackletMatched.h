#ifndef __TRACKLETMATCHED_H__
#define __TRACKLETMATCHED_H__

#include <vector>

using namespace std;

namespace TMTT {

class TrackletMatched{

 public:
  
  TrackletMatched( TrackletSeed tracklet );
  ~TrackletMatched(){};

  void TrackletMatch( Stub* stub );

 private:
  
  std::vector <Stub* stub> stublist_; 

};

}

#endif
