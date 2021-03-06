import FWCore.ParameterSet.Config as cms
import CondTools.Ecal.conddb_init as conddb_init
import CondTools.Ecal.db_credentials as auth

process = cms.Process("ProcessOne")

process.MessageLogger = cms.Service("MessageLogger",
    debugModules = cms.untracked.vstring('*'),
    cout = cms.untracked.PSet(
        threshold = cms.untracked.string('DEBUG')
    ),
    destinations = cms.untracked.vstring('cout')
)

process.source = cms.Source("EmptyIOVSource",
    lastValue = cms.uint64(100000000000),
    timetype = cms.string('runnumber'),
    firstValue = cms.uint64(100000000000),
    interval = cms.uint64(1)
)

process.load("CondCore.CondDB.CondDB_cfi")

process.CondDB.connect = conddb_init.options.destinationDatabase
process.CondDB.DBParameters.authenticationPath = ''

process.PoolDBOutputService = cms.Service("PoolDBOutputService",
    process.CondDB, 
    toPut = cms.VPSet(cms.PSet(
        record = cms.string('EcalTPGSpikeRcd'),
        tag = cms.string(conddb_init.options.destinationTag)
    ))
)

db_service,db_user,db_pwd = auth.get_readOnly_db_credentials()

process.Test1 = cms.EDAnalyzer("ExTestEcalTPGSpikeAnalyzer",
    record = cms.string('EcalTPGSpikeRcd'),
    loggingOn= cms.untracked.bool(True),
    IsDestDbCheckedInQueryLog=cms.untracked.bool(True),
    SinceAppendMode=cms.bool(True),
    Source=cms.PSet(
     firstRun = cms.string('200000'),
     lastRun = cms.string('100000000'),
     OnlineDBSID = cms.string(db_service),
     OnlineDBUser = cms.string(db_user),
     OnlineDBPassword = cms.string( db_pwd ),
     LocationSource = cms.string('P5'),
     Location = cms.string('P5_Co'),
     GenTag = cms.string('GLOBAL'),
     RunType = cms.string('PHYSICS')
    )                            
)

process.p = cms.Path(process.Test1)
