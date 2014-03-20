// -*- C++ -*-
//
// Package:    MyAnalyzer
// Class:      MyAnalyzer
// 
/**\class MyAnalyzer MyAnalyzer.cc trial/MyAnalyzer/src/MyAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Christoperh Grud
//         Created:  Mon Mar 17 14:02:45 EDT 2014
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
//you need the TFileService in order to make plots
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
//for reco::Candidate
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
//for the GenParticleCollection and GenParticles
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/Math/interface/deltaR.h"
#include <vector>
#include <iostream>    
#include <cmath> 
#include "TH2D.h"
//
// class declaration
//

class MyAnalyzer : public edm::EDAnalyzer {
   public:
      explicit MyAnalyzer(const edm::ParameterSet&);
      ~MyAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------
};


edm::Service<TFileService> fs;
edm::Handle< reco::GenParticleCollection > particles;
edm::InputTag particles_;

TH2D* bbBarDRVsHiggsPt;

MyAnalyzer::MyAnalyzer(const edm::ParameterSet& iConfig)

{
   particles_ = iConfig.getParameter<edm::InputTag>("particles");

}


MyAnalyzer::~MyAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
MyAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   iEvent.getByLabel(particles_,particles);


   for (reco::GenParticleCollection::const_iterator iParticle = particles->begin(); iParticle != particles->end(); ++iParticle){
   double bbBarDR, bEta, bBarEta, bPhi, bBarPhi;
   if ( (iParticle->pdgId() != 25) || (iParticle->status() != 3) ) continue;
   for (unsigned int i = 0; i < iParticle->numberOfDaughters(); i++){
      int pdgid = iParticle->daughter(i)->pdgId();
      if (pdgid == 5) {
	bEta = iParticle->daughter(i)->eta();
	bPhi = iParticle->daughter(i)->phi();
	
      }
      else if (pdgid == -5) {
	bBarEta = iParticle->daughter(i)->eta();
	bBarPhi = iParticle->daughter(i)->phi();
	
      }
      
}
   
   bbBarDR = reco::deltaR(bEta, bPhi, bBarEta, bBarPhi);
   bbBarDRVsHiggsPt->Fill(iParticle->pt(),bbBarDR);
   
   
   }
}


// ------------ method called once each job just before starting event loop  ------------
void 
MyAnalyzer::beginJob()
{

  bbBarDRVsHiggsPt = fs->make<TH2D>("dR vs. Pt","dR vs. Pt",150,0,1300,150,0,14);

}

// ------------ method called once each job just after ending the event loop  ------------
void 
MyAnalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
MyAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
MyAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
MyAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
MyAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MyAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MyAnalyzer);
