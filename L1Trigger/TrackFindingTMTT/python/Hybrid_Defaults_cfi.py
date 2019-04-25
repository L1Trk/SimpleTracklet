import FWCore.ParameterSet.Config as cms

#---------------------------------------------------------------------------------------------------------
# Additional config params needed for Hybrid beyond those in TMTrackProducer_Defaults_cfi.py
#---------------------------------------------------------------------------------------------------------

Hybrid_params = cms.PSet(

  TrackletSettings = cms.PSet(
    LayerRadii = cms.vdouble( 25.1493, 37.468, 52.5977, 68.7737, 86.0591, 110.844 ),
    DiskZ = cms.vdouble( 131.18, 155.0, 185.34, 221.619, 265.0 )
    )

)

#--- Also note boolearn "Hybrid" in TMTrackProducer_Defaults_cfi.py, used to switch between TMTT & Hybrid
