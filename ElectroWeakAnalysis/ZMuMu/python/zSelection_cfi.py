import FWCore.ParameterSet.Config as cms

zSelectionLoose = cms.PSet(
    cut = cms.string("charge = 0 & daughter(0).pt > 15 & daughter(1).pt > 15 & abs(daughter(0).eta)<2.1 & abs(daughter(1).eta)<2.1 & mass > 0"),
    isoCut = cms.double(1000.),
    ptThreshold = cms.untracked.double("1.5"),
    etEcalThreshold = cms.untracked.double("0.2"),
    etHcalThreshold = cms.untracked.double("0.5"),
    deltaRVetoTrk = cms.untracked.double("0.015"),
    deltaRTrk = cms.untracked.double("0.3"),
    deltaREcal = cms.untracked.double("0.25"),
    deltaRHcal = cms.untracked.double("0.25"),
    alpha = cms.untracked.double("0."),
    beta = cms.untracked.double("-0.75"),
    relativeIsolation = cms.bool(False)

# For standard isolation (I_Tkr<3GeV) choose this configuration:
#   isoCut = cms.double(3.),
#   ptThreshold = cms.untracked.double("1.5"),
#   etEcalThreshold = cms.untracked.double("0.2"),
#   etHcalThreshold = cms.untracked.double("0.5"),
#   deltaRVetoTrk = cms.untracked.double("0.015"),
#   deltaRTrk = cms.untracked.double("0.3"),
#   deltaREcal = cms.untracked.double("0.25"),
#   deltaRHcal = cms.untracked.double("0.25"),
#   alpha = cms.untracked.double("0."),
#   beta = cms.untracked.double("-0.75"),
#   relativeIsolation = cms.bool(False)
 )


zSelection = cms.PSet(
    cut = cms.string("charge = 0 & daughter(0).pt > 20. & daughter(1).pt > 10. & abs(daughter(0).eta)<2.1 & abs(daughter(1).eta)<2.1 & mass > 0"),
    isoCut = cms.double(3.),
    ptThreshold = cms.untracked.double("1.5"),
    etEcalThreshold = cms.untracked.double("0.2"),
    etHcalThreshold = cms.untracked.double("0.5"),
    deltaRVetoTrk = cms.untracked.double("0.015"),
    deltaRTrk = cms.untracked.double("0.3"),
    deltaREcal = cms.untracked.double("0.25"),
    deltaRHcal = cms.untracked.double("0.25"),
    alpha = cms.untracked.double("0."),
    beta = cms.untracked.double("-0.75"),
    relativeIsolation = cms.bool(False)
 )

### region A: |eta|<2.1, region B: 2.1< |eta| <2.4

zSelectionABLoose = cms.PSet(
    cut = cms.string("charge = 0 & daughter(0).pt > 15 & daughter(1).pt > 15 & ( (abs(daughter(0).eta)<2.1 & 2.1< abs(daughter(1).eta)<2.4 ) || (abs(daughter(1).eta)<2.1 & 2.1< abs(daughter(0).eta)<2.4 ) )  & mass > 0"),
    isoCut = cms.double(1000.),
    ptThreshold = cms.untracked.double("1.5"),
    etEcalThreshold = cms.untracked.double("0.2"),
    etHcalThreshold = cms.untracked.double("0.5"),
    deltaRVetoTrk = cms.untracked.double("0.015"),
    deltaRTrk = cms.untracked.double("0.3"),
    deltaREcal = cms.untracked.double("0.25"),
    deltaRHcal = cms.untracked.double("0.25"),
    alpha = cms.untracked.double("0."),
    beta = cms.untracked.double("-0.75"),
    relativeIsolation = cms.bool(False)
 )


zSelectionAB = cms.PSet(
    cut = cms.string("charge = 0 & daughter(0).pt > 20. & daughter(1).pt > 20. & ( (abs(daughter(0).eta)<2.1 & 2.1< abs(daughter(1).eta)<2.4 ) || (abs(daughter(1).eta)<2.1 & 2.1< abs(daughter(0).eta)<2.4 ) )  & mass > 0"),
    isoCut = cms.double(1000.),
    ptThreshold = cms.untracked.double("1.5"),
    etEcalThreshold = cms.untracked.double("0.2"),
    etHcalThreshold = cms.untracked.double("0.5"),
    deltaRVetoTrk = cms.untracked.double("0.015"),
    deltaRTrk = cms.untracked.double("0.3"),
    deltaREcal = cms.untracked.double("0.25"),
    deltaRHcal = cms.untracked.double("0.25"),
    alpha = cms.untracked.double("0."),
    beta = cms.untracked.double("-0.75"),
    relativeIsolation = cms.bool(False)
 )


zSelectionBBLoose = cms.PSet(
    cut = cms.string("charge = 0 & daughter(0).pt > 15 & daughter(1).pt > 15 & ( 2.1< abs(daughter(0).eta)<2.4 & 2.1< abs(daughter(1).eta)<2.4 )  & mass > 0"),
    isoCut = cms.double(1000.),
    ptThreshold = cms.untracked.double("1.5"),
    etEcalThreshold = cms.untracked.double("0.2"),
    etHcalThreshold = cms.untracked.double("0.5"),
    deltaRVetoTrk = cms.untracked.double("0.015"),
    deltaRTrk = cms.untracked.double("0.3"),
    deltaREcal = cms.untracked.double("0.25"),
    deltaRHcal = cms.untracked.double("0.25"),
    alpha = cms.untracked.double("0."),
    beta = cms.untracked.double("-0.75"),
    relativeIsolation = cms.bool(False)
 )


zSelectionBB = cms.PSet(
    cut = cms.string("charge = 0 & daughter(0).pt > 20 & daughter(1).pt > 20 & ( 2.1< abs(daughter(0).eta)<2.4 & 2.1< abs(daughter(1).eta)<2.4 )  & mass > 0"),
    isoCut = cms.double(1000.),
    ptThreshold = cms.untracked.double("1.5"),
    etEcalThreshold = cms.untracked.double("0.2"),
    etHcalThreshold = cms.untracked.double("0.5"),
    deltaRVetoTrk = cms.untracked.double("0.015"),
    deltaRTrk = cms.untracked.double("0.3"),
    deltaREcal = cms.untracked.double("0.25"),
    deltaRHcal = cms.untracked.double("0.25"),
    alpha = cms.untracked.double("0."),
    beta = cms.untracked.double("-0.75"),
    relativeIsolation = cms.bool(False)
 )




goodZTight = cms.EDFilter(
    "ZToMuMuIsolatedIDSelector",
    zSelection,
    src = cms.InputTag("goodZ"),
    filter = cms.bool(True) 
)

