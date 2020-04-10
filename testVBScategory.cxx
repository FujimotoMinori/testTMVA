#include "TMVA/Reader.h"
#include <iostream>

class TreeData {
        public:
	Float_t MTagResJets;
	Float_t DeltaEtaTagResJets, DeltaEtaSignalJets;
	Float_t PtSignalJet2, PtTagResJet2;
	Float_t WidthSignalJet1, WidthSignalJet2;
	Float_t WidthTagResJet1, WidthTagResJet2;
	Float_t Mlljj;
	Float_t NTrackJets;
	Float_t xiVRes;
	Float_t weight;
	Float_t NumTrkPt500SigJet1;
	//Float_t NumTrkPt500SigJet2;
	Float_t NumTrkPt500TagResJet1;
	Float_t NumTrkPt500TagResJet2;
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
	t->SetBranchAddress("Mlljj",              &(d.Mlljj));
	t->SetBranchAddress("xiVRes",             &(d.xiVRes));
	t->SetBranchAddress("NTrackJets",         &(d.NTrackJets));
	t->SetBranchAddress("NumTrkPt500SigJet1", &(d.NumTrkPt500SigJet1));
	//t->SetBranchAddress("NumTrkPt500SigJet2", &(d.NumTrkPt500SigJet2));
	t->SetBranchAddress("NumTrkPt500TagResJet1", &(d.NumTrkPt500TagResJet1));
	t->SetBranchAddress("NumTrkPt500TagResJet2", &(d.NumTrkPt500TagResJet2));
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
	reader->AddVariable("Mlljj",              &(data.Mlljj));
	reader->AddVariable("xiVRes",             &(data.xiVRes));
	reader->AddVariable("NTrackJets",         &(data.NTrackJets));
	reader->AddVariable("NumTrkPt500SigJet1", &(data.NumTrkPt500SigJet1));
	//reader->AddVariable("NumTrkPt500SigJet2", &(data.NumTrkPt500SigJet2));
	reader->AddVariable("NumTrkPt500TagResJet1", &(data.NumTrkPt500TagResJet1));
	reader->AddVariable("NumTrkPt500TagResJet2", &(data.NumTrkPt500TagResJet2));

	// Book the MVA methods
	TString dir    = "dataset/weights/";
	TString prefix = "TMVAClassification";

	// Book method(s)
	TString methodName("BDT method");
	TString weightfile = dir + prefix + TString("_BDT.weights.xml");
        std::cout << "weigtfile= " << weightfile << std::endl;
	reader->BookMVA(methodName, weightfile);

	// Prepare input tree (this must be replaced by your data source)
	//TChain* tZZllqqEW6 = new TChain("Nominal");
	//TChain* tWZllqqEW6 = new TChain("Nominal");
	//TChain* tWZlvqqEW6 = new TChain("Nominal");
	TChain* tSignal = new TChain("Nominal");
	TChain* tW = new TChain("Nominal");        
	TChain* tWW = new TChain("Nominal");       
	TChain* tWZ = new TChain("Nominal");       
	TChain* tZ = new TChain("Nominal");        
	TChain* tZZ = new TChain("Nominal");       
	TChain* tstopWtDilep = new TChain("Nominal");
	TChain* tstops = new TChain("Nominal");    
	TChain* tstopt = new TChain("Nominal");    
	TChain* tttbar = new TChain("Nominal");    
	TChain* tData = new TChain("Nominal");     
	
	tSignal->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_forMVATreeSRVBS2/fetch/data-MVATree/EWVVjj_MGPy8-*.root");
        //Wjets
	tW->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_forMVATreeSRVBS2/fetch/data-MVATree/Wenu*.root");
	tW->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_forMVATreeSRVBS2/fetch/data-MVATree/Wmunu*.root");
	tW->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_forMVATreeSRVBS2/fetch/data-MVATree/Wtaunu*.root");
	tWW->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_forMVATreeSRVBS2/fetch/data-MVATree/WqqWlv_Sh221-*.root");
	tWZ->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_forMVATreeSRVBS2/fetch/data-MVATree/WqqZll_Sh221-*.root");
        //Zjets
	tZ->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_forMVATreeSRVBS2/fetch/data-MVATree/Zmumu*.root");
	tZ->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_forMVATreeSRVBS2/fetch/data-MVATree/Zee*.root");
	tZ->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_forMVATreeSRVBS2/fetch/data-MVATree/Ztautau*.root");
	tZZ->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_forMVATreeSRVBS2/fetch/data-MVATree/ZqqZll_Sh221-*.root");
	tstopWtDilep->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_forMVATreeSRVBS2/fetch/data-MVATree/stopWt_dilep_PwPy8-*.root");
	tstops->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_forMVATreeSRVBS2/fetch/data-MVATree/stops_PwPy8-*.root");
	tstopt->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_forMVATreeSRVBS2/fetch/data-MVATree/stopt_PwPy8-*.root");
	tttbar->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_forMVATreeSRVBS2/fetch/data-MVATree/ttbar_dilep_PwPy8-*.root");
	tData->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_forMVATreeSRVBS2/fetch/data-MVATree/data*.root");

        //set categoryNames for cutflow
	vector<std::string> categoryNames;
	categoryNames.push_back(std::string("ResolvedSRVBS"));         
	categoryNames.push_back(std::string("BDT > -0.35"));       
	categoryNames.push_back(std::string("BDT > 0"));       

	// --- Prepare the event tree
	vector<std::string> sampleNames;
	//sampleNames.push_back(std::string("ZZllqqEW6"));         //0
	//sampleNames.push_back(std::string("WZllqqEW6"));         //1
	//sampleNames.push_back(std::string("WZlvqqEW6"));         //2
	sampleNames.push_back(std::string("Signal"));            //0
	sampleNames.push_back(std::string("W"));                 //1
	sampleNames.push_back(std::string("WW"));                //2
	sampleNames.push_back(std::string("WZ"));                //3
	sampleNames.push_back(std::string("Z"));                 //4
	sampleNames.push_back(std::string("ZZ"));                //5
	sampleNames.push_back(std::string("stopWtDilep"));       //6
	sampleNames.push_back(std::string("stops"));             //7
	sampleNames.push_back(std::string("stopt"));             //8
	sampleNames.push_back(std::string("ttbar"));             //9
	sampleNames.push_back(std::string("data"));              //10

        //set samplesList
	vector<TChain*> sampleList;
	//sampleList.push_back(tZZllqqEW6);         //0
	//sampleList.push_back(tWZllqqEW6);         //1
	//sampleList.push_back(tWZlvqqEW6);         //2
	sampleList.push_back(tSignal);            //0
	sampleList.push_back(tW);                 //1
	sampleList.push_back(tWW);                //2
	sampleList.push_back(tWZ);                //3
	sampleList.push_back(tZ);                 //4
	sampleList.push_back(tZZ);                //5
	sampleList.push_back(tstopWtDilep);       //6
	sampleList.push_back(tstops);             //7
	sampleList.push_back(tstopt);             //8
	sampleList.push_back(tttbar);             //9
	sampleList.push_back(tData);              //10

	TFile *target = new TFile( "TMVAppcategory.root","RECREATE" ); 
	UInt_t nbin = 100;
        std::string cutflowdir = "CutFlow_Dilep/";
	TH1F* h;
	TH1F* h_1;
	TH1F* hcutflow;
	int i =0;
	for (const auto& x : sampleList) {
		std::cout << "--- numbers: " << i << " --------------------------------- " << std::endl;
		std::cout << "--- sampleName: " << sampleNames[i] << " --------------------------------- " << std::endl;
		std::cout << "--- number of events: " << x->GetEntries() << " events" << std::endl;
		h = new TH1F((sampleNames[i]+categoryNames[0]).c_str(), (sampleNames[i]+categoryNames[0]).c_str(), nbin, -0.8, 0.8 );
		h_1 = new TH1F((sampleNames[i]+categoryNames[1]).c_str(), (sampleNames[i]+categoryNames[1]).c_str(), nbin, -0.8, 0.8 );
		setBranch(x, data);
		// --- Event loop
		double allevents = 0.;
		double passedevents = 0.;
		for (Long64_t ievt=0; ievt<x->GetEntries();ievt++) {
			if (ievt%10000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;
			x->GetEntry(ievt);
			allevents += data.weight;
			h->Fill(reader->EvaluateMVA("BDT method"),data.weight);
			if (reader->EvaluateMVA("BDT method") > -0.40) {
				h_1->Fill(reader->EvaluateMVA("BDT method"),data.weight);
				passedevents += data.weight;
			}
		}
		std::cout << "--- number of all events : " << allevents << " events" << std::endl;
		std::cout << "--- number of events  pased cut : " << passedevents << " events" << std::endl;
		std::cout << "--- finished event loop " << std::endl;

                //for cutflow
		hcutflow = new TH1F((sampleNames[i]+"_cutflow").c_str(),(sampleNames[i]+"_cutflow").c_str(), categoryNames.size(), 0, categoryNames.size());
		hcutflow->GetXaxis()->SetBinLabel(1,categoryNames[0].c_str());
		hcutflow->SetBinContent(1,allevents);
		hcutflow->GetXaxis()->SetBinLabel(2,categoryNames[1].c_str());
		hcutflow->SetBinContent(2,passedevents);
                /*
		int j = 0;
		for (const auto& x : categoryNames){
			j++;
			hcutflow->GetXaxis()->SetBinLabel(j,categoryNames.c_str());
			hcutflow->SetBinContent(j,h->GetEntries());
		}
                */

		// --- Write histograms
		h->Write();
		hcutflow->Write();
		std::cout << "--- wrote histogram " << std::endl;
		i++;
	};


	target->Close();

	std::cout << "--- Created root file: \"TMVAppcategory.root\" containing the MVA output histograms" << std::endl;
	delete reader;
	std::cout << "==> TMVAClassificationApplication is done!" << std::endl << std::endl;

}


