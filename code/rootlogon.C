{
   gSystem->Load("libFWCoreFWLite.so");
   FWLiteEnabler::enable();
   gSystem->Load("libDataFormatsFWLite.so");
   gROOT->SetStyle ("Plain");
   gSystem->Load("libRooFit") ;
   using namespace RooFit ;
   cout << "loaded" << endl;
}