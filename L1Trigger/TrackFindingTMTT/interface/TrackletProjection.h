//////////////////////////////////////////////////////
class TrackletProjection{

TrackletProjection(rProjection, zProjection, phiProjection, rDerivitive, zDerivitive, phiDerivitive) :
rProjection_(rProjection),
zProjection_(zProjection),
phiProjection_(phiProjection),
rDerivitive_(rDerivitive),
zDerivitive_(zDerivitive),
phiDerivitive_(phiDerivitive)
{
};

~Projection(){};

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
double rProjection_, zProjection, phiProjection, rDerivitive, zDerivitive, phiDerivitive;
////////////////////////////////////////////////////////////////////////////////////////////
