import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'root://xrootd.unl.edu//store/mc/Summer12_DR53X/RadionToHHTo4B_M-1500_TuneZ2star_8TeV-nm-madgraph/AODSIM/PU_S10_START53_V7C-v1/10000/145F4514-979E-E211-90A1-00266CFFA048.root',
	'root://xrootd.unl.edu//store/mc/Summer12_DR53X/RadionToHHTo4B_M-1500_TuneZ2star_8TeV-nm-madgraph/AODSIM/PU_S10_START53_V7C-v1/10000/80CC2A81-849E-E211-9EE9-00266CFFA2B8.root',
	'root://xrootd.unl.edu//store/mc/Summer12_DR53X/RadionToHHTo4B_M-1500_TuneZ2star_8TeV-nm-madgraph/AODSIM/PU_S10_START53_V7C-v1/10000/B6DEC909-C49E-E211-AAF7-00266CFFA048.root',
	'root://xrootd.unl.edu//store/mc/Summer12_DR53X/RadionToHHTo4B_M-1500_TuneZ2star_8TeV-nm-madgraph/AODSIM/PU_S10_START53_V7C-v1/10000/D0A664D6-899E-E211-9F50-00266CFFA754.root'
    )
)

process.TFileService = cms.Service("TFileService",
      fileName = cms.string("thatplot.root")
)

process.analyze = cms.EDAnalyzer('MyAnalyzer',
		particles = cms.InputTag("genParticles")
)


process.p = cms.Path(process.analyze)
