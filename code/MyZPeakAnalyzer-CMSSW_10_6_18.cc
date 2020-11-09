#include <map>
#include <string>

#include "TH1.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

class MyZPeakAnalyzer : public edm::EDAnalyzer {

public:
   explicit MyZPeakAnalyzer(const edm::ParameterSet&);
   ~MyZPeakAnalyzer();
  
private:

   virtual void beginJob() ;
   virtual void analyze(const edm::Event&, const edm::EventSetup&);
   virtual void endJob() ;
  
   // simple map to contain all histograms; 
   // histograms are booked in the beginJob() 
   // method
   std::map<std::string,TH1F*> histContainer_; 
   // ----------member data ---------------------------     
   edm::EDGetTokenT<pat::MuonCollection> muonCollToken;
   edm::EDGetTokenT<pat::ElectronCollection> elecCollToken;
 
   // input tags 
   edm::InputTag muonSrc_;
   edm::InputTag elecSrc_;
};


MyZPeakAnalyzer::MyZPeakAnalyzer(const edm::ParameterSet& iConfig):

   histContainer_(),
   muonSrc_(iConfig.getUntrackedParameter<edm::InputTag>("muonSrc")),
   elecSrc_(iConfig.getUntrackedParameter<edm::InputTag>("elecSrc")){

   muonCollToken = consumes<pat::MuonCollection>(muonSrc_);
   elecCollToken = consumes<pat::ElectronCollection>(elecSrc_);

}

MyZPeakAnalyzer::~MyZPeakAnalyzer(){
}

void
MyZPeakAnalyzer::analyze(const edm::Event& iEvent, 
                         const edm::EventSetup& iSetup){

   // get pat muon collection 
   edm::Handle< std::vector<pat::Muon>> muons;
   iEvent.getByToken(muonCollToken, muons);

   // fill pat muon histograms
   for (auto it = muons->cbegin(); it != muons->cend(); ++it) {
      histContainer_["muonPt"] ->Fill(it->pt());
      histContainer_["muonEta"]->Fill(it->eta());
      histContainer_["muonPhi"]->Fill(it->phi());

      if( it->pt()>20 && fabs(it->eta())<2.1 ){
         for (auto it2 = muons->cbegin(); it2 != muons->cend(); ++it2){
            if (it2 > it){
               // check only muon pairs of unequal charge 
               if( it->charge()*it2->charge()<0){
                  histContainer_["mumuMass"]->Fill((it->p4()+it2->p4()).mass());
               }
            }
         }
      }
   }

   // get pat electron collection 
   edm::Handle< std::vector<pat::Electron>> electrons;
   iEvent.getByToken(elecCollToken, electrons);

   // loop over electrons
   for (auto it = electrons->cbegin(); it != electrons->cend(); ++it) {
      histContainer_["elePt"] ->Fill(it->pt());
      histContainer_["eleEta"]->Fill(it->eta());
      histContainer_["elePhi"]->Fill(it->phi());    
   }

   // Multiplicity
   histContainer_["eleMult" ]->Fill(electrons->size());
   histContainer_["muonMult"]->Fill(muons->size() );
}

void 
MyZPeakAnalyzer::beginJob()
{
   // register to the TFileService
   edm::Service<TFileService> fs;


   histContainer_["mumuMass"]=fs->make<TH1F>("mumuMass", "mass",    90,   30., 120.);
  
   // book histograms for Multiplicity:

   histContainer_["eleMult"]=fs->make<TH1F>("eleMult",   "electron multiplicity", 100, 0,  50);
   histContainer_["muonMult"]=fs->make<TH1F>("muonMult",   "muon multiplicity",     100, 0,  50);

   // book histograms for Pt:

   histContainer_["elePt"]=fs->make<TH1F>("elePt",   "electron Pt", 100, 0,  200);
   histContainer_["muonPt"]=fs->make<TH1F>("muonPt",   "muon Pt", 100, 0, 200);

   // book histograms for Eta:
   histContainer_["eleEta"]=fs->make<TH1F>("eleEta",   "electron Eta",100, -5,  5);
   histContainer_["muonEta"]=fs->make<TH1F>("muonEta",   "muon Eta",  100, -5,  5);


   // book histograms for Phi:
   histContainer_["elePhi"]=fs->make<TH1F>("elePhi",   "electron Phi", 100, -3.5, 3.5);
   histContainer_["muonPhi"]=fs->make<TH1F>("muonPhi",   "muon Phi",     100, -3.5, 3.5);
    
}

void 
MyZPeakAnalyzer::endJob() 
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(MyZPeakAnalyzer);

