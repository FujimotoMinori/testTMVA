#include "TMVA/Reader.h"
#include <iostream>

void testVBS(){
	// Create the Reader object

	TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );

	// Create a set of variables and declare them to the reader
	// - the variable names MUST corresponds in name and type to those given in the weight file(s) used
	Float_t MTagResJets;
	Float_t DeltaEtaTagResJets, DeltaEtaSignalJets;
	Float_t PtSignalJet2, PtTagResJet2;
	Float_t WidthSignalJet1, WidthSignalJet2;
	Float_t WidthTagResJet1, WidthTagResJet2;
	Float_t NTrackJets;
	Float_t Mlljj;
	Float_t xiVRes;
	reader->AddVariable("MTagResJets",        &MTagResJets);
	reader->AddVariable("DeltaEtaTagResJets", &DeltaEtaTagResJets);
	reader->AddVariable("DeltaEtaSignalJets", &DeltaEtaSignalJets);
	reader->AddVariable("PtSignalJet2",       &PtSignalJet2);
	reader->AddVariable("WidthSignalJet1",    &WidthSignalJet1);
	reader->AddVariable("WidthSignalJet2",    &WidthSignalJet2);
	reader->AddVariable("PtTagResJet2",       &PtTagResJet2);
	reader->AddVariable("WidthTagResJet1",    &WidthTagResJet1);
	reader->AddVariable("WidthTagResJet2",    &WidthTagResJet2);
	reader->AddVariable("NTrackJets",         &NTrackJets);
	reader->AddVariable("Mlljj",              &Mlljj);
	reader->AddVariable("xiVRes",             &xiVRes);

	// Book the MVA methods
	TString dir    = "dataset/weights/";
	TString prefix = "TMVAClassification";

	// Book method(s)
	TString methodName("BDT method");
	TString weightfile = dir + prefix + TString("_BDT.weights.xml");
        std::cout << "weigtfile= " << weightfile << std::endl;
	reader->BookMVA(methodName, weightfile);

        // Book output histograms
	UInt_t nbin = 100;
	TH1F* histBdt = new TH1F("MVA_BDT", "MVA_BDT", nbin, -0.8, 0.8 );
	//TH1F* histBdtBg = new TH1F("MVA_BDTBg", "MVA_BDTBg", nbin, -0.8, 0.8 );
	TH1F* histBdtZjets = new TH1F("MVA_BDTZjets", "MVA_BDTZjets", nbin, -0.8, 0.8 );
	TH1F* histBdtttbar = new TH1F("MVA_BDTttbar", "MVA_BDTttbar", nbin, -0.8, 0.8 );

	// Prepare input tree (this must be replaced by your data source)
	// in this example, there is a toy tree with signal and one with background events
	// we'll later on use only the "signal" events for the test in this example.
	/*
	TFile *input(0);
	TString fname = "./tmva_example.root";
        input = TFile::Open( fname ); // check if file in local directory exists
	if (!input) {
		std::cout << "ERROR: could not open data file" << std::endl;
		exit(1);
	}
	std::cout << "--- TMVAClassificationApp    : Using input file: " << input->GetName() << std::endl;
        */

        TChain* tsignal = new TChain("Nominal");
        TChain* tbackground = new TChain("Nominal");
        TChain* tZjets = new TChain("Nominal");
        TChain* tttbar = new TChain("Nominal");
	tsignal->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/EWVVjj_MGPy8-*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/Zmumu*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/Zee*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/Ztautau*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/ttbar_dilep_PwPy8-*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/stops_PwPy8-*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/stopt_PwPy8-*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/stopWt_dilep_PwPy8-*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/ZqqZll_Sh221-*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/ZqqZvv_Sh221-*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/WqqZll_Sh221-*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/WqqWlv_Sh221-*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/Wenu*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/Wmunu*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/Wtaunu*.root");
	tZjets->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/Zmumu*.root");
	tZjets->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/Zee*.root");
	tZjets->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/Ztautau*.root");
	tttbar->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/ttbar_dilep_PwPy8-*.root");
	// Event loop

	// Prepare the event tree
	// - Here the variable names have to corresponds to your tree
	// - You can use the same variables as above which is slightly faster,
	//   but of course you can use different ones and copy the values inside the event loop
	
	/*
	std::cout << "--- Select signal sample" << std::endl;
	TTree* theTree = (TTree*)input->Get("TreeS");
        */

	//Float_t userVar1, userVar2;
	//tsignal->SetBranchAddress( "var1", &userVar1 );
	//tsignal->SetBranchAddress( "var2", &userVar2 );
	//signal
	Float_t weight;
	tsignal->SetBranchAddress("MTagResJets",        &MTagResJets);
	tsignal->SetBranchAddress("DeltaEtaTagResJets", &DeltaEtaTagResJets);
	tsignal->SetBranchAddress("DeltaEtaSignalJets", &DeltaEtaSignalJets);
	tsignal->SetBranchAddress("PtSignalJet2",       &PtSignalJet2);
	tsignal->SetBranchAddress("WidthSignalJet1",    &WidthSignalJet1);
	tsignal->SetBranchAddress("WidthSignalJet2",    &WidthSignalJet2);
	tsignal->SetBranchAddress("PtTagResJet2",       &PtTagResJet2);
	tsignal->SetBranchAddress("WidthTagResJet1",    &WidthTagResJet1);
	tsignal->SetBranchAddress("WidthTagResJet2",    &WidthTagResJet2);
	tsignal->SetBranchAddress("NTrackJets",         &NTrackJets);
	tsignal->SetBranchAddress("Mlljj",              &Mlljj);
	tsignal->SetBranchAddress("xiVRes",             &xiVRes);
	tsignal->SetBranchAddress("weight",             &weight);
	//background
	tbackground->SetBranchAddress("MTagResJets",        &MTagResJets);
	tbackground->SetBranchAddress("DeltaEtaTagResJets", &DeltaEtaTagResJets);
	tbackground->SetBranchAddress("DeltaEtaSignalJets", &DeltaEtaSignalJets);
	tbackground->SetBranchAddress("PtSignalJet2",       &PtSignalJet2);
	tbackground->SetBranchAddress("WidthSignalJet1",    &WidthSignalJet1);
	tbackground->SetBranchAddress("WidthSignalJet2",    &WidthSignalJet2);
	tbackground->SetBranchAddress("PtTagResJet2",       &PtTagResJet2);
	tbackground->SetBranchAddress("WidthTagResJet1",    &WidthTagResJet1);
	tbackground->SetBranchAddress("WidthTagResJet2",    &WidthTagResJet2);
	tbackground->SetBranchAddress("NTrackJets",         &NTrackJets);
	tbackground->SetBranchAddress("Mlljj",              &Mlljj);
	tbackground->SetBranchAddress("xiVRes",             &xiVRes);
	tbackground->SetBranchAddress("weight",             &weight);
	//Zjets
	tZjets->SetBranchAddress("MTagResJets",        &MTagResJets);
	tZjets->SetBranchAddress("DeltaEtaTagResJets", &DeltaEtaTagResJets);
	tZjets->SetBranchAddress("DeltaEtaSignalJets", &DeltaEtaSignalJets);
	tZjets->SetBranchAddress("PtSignalJet2",       &PtSignalJet2);
	tZjets->SetBranchAddress("WidthSignalJet1",    &WidthSignalJet1);
	tZjets->SetBranchAddress("WidthSignalJet2",    &WidthSignalJet2);
	tZjets->SetBranchAddress("PtTagResJet2",       &PtTagResJet2);
	tZjets->SetBranchAddress("WidthTagResJet1",    &WidthTagResJet1);
	tZjets->SetBranchAddress("WidthTagResJet2",    &WidthTagResJet2);
	tZjets->SetBranchAddress("NTrackJets",         &NTrackJets);
	tZjets->SetBranchAddress("Mlljj",              &Mlljj);
	tZjets->SetBranchAddress("xiVRes",             &xiVRes);
	tZjets->SetBranchAddress("weight",             &weight);
	//ttbar
	tttbar->SetBranchAddress("MTagResJets",        &MTagResJets);
	tttbar->SetBranchAddress("DeltaEtaTagResJets", &DeltaEtaTagResJets);
	tttbar->SetBranchAddress("DeltaEtaSignalJets", &DeltaEtaSignalJets);
	tttbar->SetBranchAddress("PtSignalJet2",       &PtSignalJet2);
	tttbar->SetBranchAddress("WidthSignalJet1",    &WidthSignalJet1);
	tttbar->SetBranchAddress("WidthSignalJet2",    &WidthSignalJet2);
	tttbar->SetBranchAddress("PtTagResJet2",       &PtTagResJet2);
	tttbar->SetBranchAddress("WidthTagResJet1",    &WidthTagResJet1);
	tttbar->SetBranchAddress("WidthTagResJet2",    &WidthTagResJet2);
	tttbar->SetBranchAddress("NTrackJets",         &NTrackJets);
	tttbar->SetBranchAddress("Mlljj",              &Mlljj);
	tttbar->SetBranchAddress("xiVRes",             &xiVRes);
	tttbar->SetBranchAddress("weight",             &weight);
        std::cout << "set branches" << std::endl;

	// Efficiency calculator for cut method
	Int_t    nSelCutsGA = 0;
	Double_t effS       = 0.7;

	std::vector<Float_t> vecVar(4); // vector for EvaluateMVA tests

        //signal
        std::cout << "--- Processing: " << tsignal->GetEntries() << " events" << std::endl;
	for (Long64_t ievt=0; ievt<tsignal->GetEntries();ievt++) {
		if (ievt%1000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;
		tsignal->GetEntry(ievt);
		//var1 = userVar1 + userVar2;
		//var2 = userVar1 - userVar2;
		// Return the MVA outputs and fill into histograms
		histBdt ->Fill(reader->EvaluateMVA("BDT method"),weight);
	}
        /*
        //bg
        std::cout << "--- Processing: " << tbackground->GetEntries() << " events" << std::endl;
	for (Long64_t ievt=0; ievt<tbackground->GetEntries();ievt++) {
		if (ievt%1000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;
		tbackground->GetEntry(ievt);
		// Return the MVA outputs and fill into histograms
		histBdtBg ->Fill(reader->EvaluateMVA("BDT method") );
	}
        */
        //Zjets
        std::cout << "--- Processing: " << tZjets->GetEntries() << " events" << std::endl;
	for (Long64_t ievt=0; ievt<tZjets->GetEntries();ievt++) {
		if (ievt%1000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;
		tZjets->GetEntry(ievt);
		// Return the MVA outputs and fill into histograms
		histBdtZjets ->Fill(reader->EvaluateMVA("BDT method"),weight);
	}
        //ttbar
        std::cout << "--- Processing: " << tttbar->GetEntries() << " events" << std::endl;
	for (Long64_t ievt=0; ievt<tttbar->GetEntries();ievt++) {
		if (ievt%1000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;
		tttbar->GetEntry(ievt);
		// Return the MVA outputs and fill into histograms
		histBdtttbar ->Fill(reader->EvaluateMVA("BDT method"),weight);
	}
     
	// --- Write histograms
	TFile *target = new TFile( "TMVApp.root","RECREATE" ); 
	histBdt ->Write();
	//histBdtBg ->Write();
	histBdtZjets ->Write();
	histBdtttbar ->Write();
	target->Close();

	std::cout << "--- Created root file: \"TMVApp.root\" containing the MVA output histograms" << std::endl;
	delete reader;
	std::cout << "==> TMVAClassificationApplication is done!" << std::endl << std::endl;

}


