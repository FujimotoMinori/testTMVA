#include "TMVA/Reader.h"
#include <iostream>

class TreeData {
        public:
	Float_t MTagResJets;
	Float_t DeltaEtaTagResJets, DeltaEtaSignalJets;
	Float_t PtSignalJet2, PtTagResJet2;
	Float_t WidthSignalJet1, WidthSignalJet2;
	Float_t WidthTagResJet1, WidthTagResJet2;
	Float_t NTrackJets;
	Float_t Mlljj;
	Float_t xiVRes;
	Float_t weight;
}; 

void setBranch(TChain* t, TreeData& d){
	t->SetBranchAddress("MTagResJets", &(d.MTagResJets) );
	t->SetBranchAddress("DeltaEtaTagResJets", &(d.DeltaEtaTagResJets));
	t->SetBranchAddress("DeltaEtaSignalJets", &(d.DeltaEtaSignalJets));
	t->SetBranchAddress("PtSignalJet2",       &(d.PtSignalJet2));
	t->SetBranchAddress("WidthSignalJet1",    &(d.WidthSignalJet1));
	t->SetBranchAddress("WidthSignalJet2",    &(d.WidthSignalJet2));
	t->SetBranchAddress("PtTagResJet2",       &(d.PtTagResJet2));
	t->SetBranchAddress("WidthTagResJet1",    &(d.WidthTagResJet1));
	t->SetBranchAddress("WidthTagResJet2",    &(d.WidthTagResJet2));
	t->SetBranchAddress("NTrackJets",         &(d.NTrackJets));
	t->SetBranchAddress("Mlljj",              &(d.Mlljj));
	t->SetBranchAddress("xiVRes",             &(d.xiVRes));
	t->SetBranchAddress("weight",             &(d.weight));
        return;
}

void testVBScategory(){
	// Create the Reader object
	TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );

	// Create a set of variables and declare them to the reader
	// - the variable names MUST corresponds in name and type to those given in the weight file(s) used
        TreeData data;
	reader->AddVariable("MTagResJets",        &(data.MTagResJets));
	reader->AddVariable("DeltaEtaTagResJets", &(data.DeltaEtaTagResJets));
	reader->AddVariable("DeltaEtaSignalJets", &(data.DeltaEtaSignalJets));
	reader->AddVariable("PtSignalJet2",       &(data.PtSignalJet2));
	reader->AddVariable("WidthSignalJet1",    &(data.WidthSignalJet1));
	reader->AddVariable("WidthSignalJet2",    &(data.WidthSignalJet2));
	reader->AddVariable("PtTagResJet2",       &(data.PtTagResJet2));
	reader->AddVariable("WidthTagResJet1",    &(data.WidthTagResJet1));
	reader->AddVariable("WidthTagResJet2",    &(data.WidthTagResJet2));
	reader->AddVariable("NTrackJets",         &(data.NTrackJets));
	reader->AddVariable("Mlljj",              &(data.Mlljj));
	reader->AddVariable("xiVRes",             &(data.xiVRes));

	// Book the MVA methods
	TString dir    = "dataset/weights/";
	TString prefix = "TMVAClassification";

	// Book method(s)
	TString methodName("BDT method");
	TString weightfile = dir + prefix + TString("_BDT.weights.xml");
        std::cout << "weigtfile= " << weightfile << std::endl;
	reader->BookMVA(methodName, weightfile);

	// Prepare input tree (this must be replaced by your data source)
        TChain* tdata = new TChain("Nominal");
        TChain* tsignal = new TChain("Nominal");
        TChain* tZjets = new TChain("Nominal");
        TChain* tttbar = new TChain("Nominal");
        TChain* tstop = new TChain("Nominal");
        TChain* tDiboson = new TChain("Nominal");
        TChain* tWjets = new TChain("Nominal");
	tdata->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/data*.root");
	tsignal->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/EWVVjj_MGPy8-*.root");
	tZjets->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/Zmumu*.root");
	tZjets->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/Zee*.root");
	tZjets->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/Ztautau*.root");
	tttbar->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/ttbar_dilep_PwPy8-*.root");
	tstop->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/stops_PwPy8-*.root");
	tstop->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/stopt_PwPy8-*.root");
	tstop->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/stopWt_dilep_PwPy8-*.root");
	tDiboson->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/ZqqZll_Sh221-*.root");
	//tDiboson->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/ZqqZvv_Sh221-*.root");
	tDiboson->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/WqqZll_Sh221-*.root");
	//tDiboson->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/WqqWlv_Sh221-*.root");
	tWjets->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/Wenu*.root");
	tWjets->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/Wmunu*.root");
	tWjets->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0322_forMVATree/fetch/data-MVATree/Wtaunu*.root");

	// --- Prepare the event tree
	vector<TChain*> sampleList;
	sampleList.push_back(tdata);         //0
	sampleList.push_back(tsignal);       //1
	sampleList.push_back(tZjets);        //2
	sampleList.push_back(tttbar);        //3
	sampleList.push_back(tstop);         //4
	sampleList.push_back(tDiboson);      //5
	sampleList.push_back(tWjets);        //6
	TFile *target = new TFile( "TMVAppcategory.root","RECREATE" ); 
	UInt_t nbin = 100;
	TH1F* h[sampleList.size()+1];
	int i =0;
	for (const auto& x : sampleList) {
		std::cout << "--- numbers: " << i << " --------------------------------- " << std::endl;
		std::cout << "--- number of events: " << x->GetEntries() << " events" << std::endl;
		h[i] = new TH1F(Form("MVA_BDT_%d",i), Form("MVA_BDT_%d",i), nbin, -0.8, 0.8 );
		setBranch(x, data);
		std::cout << "--- number of events: " << x->GetEntries() << " events" << std::endl;
		// --- Event loop
		for (Long64_t ievt=0; ievt<x->GetEntries();ievt++) {
			if (ievt%10000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;
			x->GetEntry(ievt);
			h[i]->Fill(reader->EvaluateMVA("BDT method"),data.weight);
		}
		std::cout << "--- finished event loop " << std::endl;
		// --- Write histograms
		h[i]->Write();
		std::cout << "--- wrote histogram " << std::endl;
		i++;
	};

	target->Close();

	std::cout << "--- Created root file: \"TMVAppcategory.root\" containing the MVA output histograms" << std::endl;
	delete reader;
	std::cout << "==> TMVAClassificationApplication is done!" << std::endl << std::endl;

}


