import FWCore.ParameterSet.Config as cms

#---------------------------------------------------------------------------------------------------------
# This describes the full Hybrid track reconstruction chains with 2 GeV threshold.
#---------------------------------------------------------------------------------------------------------

#=== Import default values for all parameters & define EDProducer.

from L1Trigger.TrackFindingTMTT.TMTrackProducer_Defaults_cfi import TMTrackProducer_params
from L1Trigger.TrackFindingTMTT.Hybrid_Defaults_cfi import Hybrid_params

TMTrackProducer = cms.EDProducer('TMTrackProducer',
  # Load cfg parameters from TMTrackProducer_Defaults_cfi.py & Hybrid_Defaults_cfi.py
  TMTrackProducer_params,
  Hybrid_params # Not used for pure TMTT
)

#===================================================================================================
# Uncomment the following 2 lines to disable all use of MC truth info & all output histograms.
# THIS SAVES CPU, SO IS GOOD IDEA IF YOU ONLY CARE ABOUT PRODUCING TTTrack COLLECTION!
#===================================================================================================

#TMTrackProducer.EnableMCtruth = cms.bool(False)
#TMTrackProducer.EnableHistos  = cms.bool(False)

#===================================================================================================
#=== Parameters changed from their default values.
#===================================================================================================

#--- Uncomment for Hybrid tracking 
TMTrackProducer.Hybrid = cms.bool( True )

TMTrackProducer.GenCuts.GenMinPt             = cms.double(2.0)
TMTrackProducer.HTArraySpecRphi.HoughMinPt   = cms.double(2.0) # Although HT not used, this also controls window cut in FE electronics.

#--- Configs that differ for Hybrid & TMTT

TMTrackProducer.PhiSectors.NumPhiSectors = cms.uint32( 9 ) # Hybrid uses only 9 phi sectors.
TMTrackProducer.DupTrkRemoval.DupTrkAlgFit = cms.uint32( 0 ) # need new DR algo for hybrid
TMTrackProducer.StubDigitize.EnableDigitize = cms.bool( False ) #need new digitisation ranges for 9 sector hourglass
TMTrackProducer.PhiSectors.ChosenRofPhi =  cms.double( 55. )

#-- Configure track fitter

# Use only 4 parameter helix fit Kalman Filter.
TMTrackProducer.TrackFitSettings.TrackFitters = cms.vstring("KF4ParamsComb")

TMTrackProducer.TrackFitSettings.KalmanMaxNumStubs  = cms.uint32(6)
TMTrackProducer.TrackFitSettings.KalmanHOtilted     = cms.bool(True)
TMTrackProducer.TrackFitSettings.KalmanHOhelixExp   = cms.bool(True)
TMTrackProducer.TrackFitSettings.KalmanHOalpha      = cms.uint32(1)
TMTrackProducer.TrackFitSettings.KalmanHOprojZcorr  = cms.uint32(1)
TMTrackProducer.TrackFitSettings.KalmanHOdodgy      = cms.bool( False )
#TMTrackProducer.TrackFitSettings.KalmanRemove2PScut = cms.bool( True )
#TMTrackProducer.TrackFitSettings.KalmanMaxSkipLayers  = cms.uint32( 4 )
# Set KF debug level to 1 or 2 for debugging
TMTrackProducer.TrackFitSettings.KalmanDebugLevel        = cms.uint32(0)

