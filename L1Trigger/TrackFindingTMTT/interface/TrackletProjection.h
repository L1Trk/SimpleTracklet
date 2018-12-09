//////////////////////////////////////////////////////
#ifndef __TRACKLETPROJECTION_H__
#define __TRACKLETPROJECTION_H__

#include <vector>

namespace TMTT {

 class TrackletProjection{

 public:

  TrackletProjection(double rProjection, double zProjection, double phiProjection, double rDerivitive, double zDerivitive, double phiDerivitive) :
   rProjection_(rProjection),
   zProjection_(zProjection),
   phiProjection_(phiProjection),
   rDerivitive_(rDerivitive),
   zDerivitive_(zDerivitive),
   phiDerivitive_(phiDerivitive)
  {
  };

  ~TrackletProjection(){};

  double rProjection(){return rProjection_;}
  double zProjection(){return zProjection_;}
  double phiProjection(){return phiProjection_;}

  double rDerivitive(){return rDerivitive_;}
  double zDerivitive(){return zDerivitive_;}
  double phiDerivitive(){return phiDerivitive_;}

  void rProjection(double x){ rProjection_ = x; }
  void zProjection(double x){ zProjection_ = x; }
  void phiProjection(double x){ phiProjection_ = x; }

  void rDerivitive(double x){ rDerivitive_ = x; }
  void zDerivitive(double x){ zDerivitive_ = x; }
  void phiDerivitive(double x){ phiDerivitive_ = x; }

  private:
  
  double rProjection_, zProjection_, phiProjection_, rDerivitive_, zDerivitive_, phiDerivitive_;

 };

}
#endif
////////////////////////////////////////////////////////////////////////////////////////////
