{
	TMVA::Tools::Instance();

	//auto inputFile = TFile::Open("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0318/fetch/data-MVATree/EWVVjj_MGPy8-1.root");
	//auto inputFileBG = TFile::Open("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0318/fetch/data-MVATree/ZeeB_Sh221-1.root");
	//std::cout << "--- TMVAClassification   : Using input file: " << inputFile->GetName() << std::endl;
	auto outputFile = TFile::Open("TMVAOutputCVtestVBS_leading2jet.root", "RECREATE");

	//Create a ROOT output file where TMVA store ntuples, histograms, etc.
		TMVA::Factory factory("TMVAClassification", outputFile,
				"!V:ROC:!Correlations:!Silent:Color:!DrawProgressBar:AnalysisType=Classification" );

	TMVA::DataLoader loader("dataset_leading2jet");

	// Define the input variables that chall be used for the MVA training
	// 16 variables for resolved regime
	loader.AddVariable("MTagResJets");
	loader.AddVariable("DeltaEtaTagResJets");
	loader.AddVariable("DeltaEtaSignalJets");
	loader.AddVariable("PtSignalJet2");
	loader.AddVariable("WidthSignalJet1");
	loader.AddVariable("WidthSignalJet2");
	loader.AddVariable("PtTagResJet2");
	loader.AddVariable("WidthTagResJet1");
	loader.AddVariable("WidthTagResJet2");
	loader.AddVariable("Mlljj");
	loader.AddVariable("xiVRes");
	loader.AddVariable("NTrackJets", 'I');
	loader.AddVariable("NumTrkPt500SigJet1", 'I');
	//loader.AddVariable("NumTrkPt500SigJet2", 'I');
	loader.AddVariable("NumTrkPt500TagResJet1", 'I');
	loader.AddVariable("NumTrkPt500TagResJet2", 'I');
        // additional variables for resolved regime
	//loader.AddVariable("MVHadRes");
	//loader.AddVariable("PtVHadRes");
	//loader.AddVariable("AzvRes");

	// --- Register the training and test trees
	//TTree *tsignal, *tbackground;
        TChain* tsignal = new TChain("Nominal");
        TChain* tbackground = new TChain("Nominal");
	tsignal->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_l2jets_forMVATreeSRVBS4/fetch/data-MVATree/EWVVjj_MGPy8-*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_l2jets_forMVATreeSRVBS4/fetch/data-MVATree/Zmumu*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_l2jets_forMVATreeSRVBS4/fetch/data-MVATree/Zee*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_l2jets_forMVATreeSRVBS4/fetch/data-MVATree/Ztautau*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_l2jets_forMVATreeSRVBS4/fetch/data-MVATree/ttbar_dilep_PwPy8-*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_l2jets_forMVATreeSRVBS4/fetch/data-MVATree/stops_PwPy8-*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_l2jets_forMVATreeSRVBS4/fetch/data-MVATree/stopt_PwPy8-*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_l2jets_forMVATreeSRVBS4/fetch/data-MVATree/stopWt_dilep_PwPy8-*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_l2jets_forMVATreeSRVBS4/fetch/data-MVATree/ZqqZll_Sh221-*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_l2jets_forMVATreeSRVBS4/fetch/data-MVATree/ZqqZvv_Sh221-*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_l2jets_forMVATreeSRVBS4/fetch/data-MVATree/WqqZll_Sh221-*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_l2jets_forMVATreeSRVBS4/fetch/data-MVATree/WqqWlv_Sh221-*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_l2jets_forMVATreeSRVBS4/fetch/data-MVATree/Wenu*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_l2jets_forMVATreeSRVBS4/fetch/data-MVATree/Wmunu*.root");
	tbackground->Add("/eos/user/m/mfujimot/CONDOR_output/output_testCondor_llqqPF_mc16aEMPflow_0408_l2jets_forMVATreeSRVBS4/fetch/data-MVATree/Wtaunu*.root");
        
	//inputFile->GetObject("Nominal", tsignal);
	//inputFileBG->GetObject("Nominal", tbackground);

	TCut mycuts, mycutb;
   
	// Add an arbitrary number of signal or background trees
	loader.AddSignalTree    (tsignal,     1.0);   //signal weight  = 1
	loader.AddBackgroundTree(tbackground, 1.0);   //background weight = 1
        // Setting individual event weights (variables must exist in the original TTree)
        loader.SetSignalWeightExpression("weight");
        loader.SetBackgroundWeightExpression("weight");
	loader.PrepareTrainingAndTestTree(mycuts, mycutb,
			"nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );  //nTrain = 0 means to split total sample in half

	//Boosted Decision Trees
	factory.BookMethod(&loader,TMVA::Types::kBDT, "BDT",
			"!V:NTrees=400:MinNodeSize=15%:MaxDepth=4:Shrinkage=0.1:nCuts=20:BoostType=Grad:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20:IgnoreNegWeightsInTraining" );
	//factory.BookMethod(&loader,TMVA::Types::kBDT, "BDT",
	//		"!V:NTrees=400:MinNodeSize=15%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20:IgnoreNegWeightsInTraining" );

	//Multi-Layer Perceptron (Neural Network)
	//factory.BookMethod(&loader, TMVA::Types::kMLP, "MLP",
        //			"!H:!V:NeuronType=tanh:VarTransform=N:NCycles=100:HiddenLayers=N+5:TestRate=5:!UseRegulator" );

	// --- Train MVAs using the set of training events
	factory.TrainAllMethods();
	// --- Evaluate all MVAs using the set of training events
	factory.TestAllMethods();
	// --- Evaluate and compare performance of all configured MVAs
	factory.EvaluateAllMethods();

	std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
	std::cout << "==> TMVAClassification is done!" << std::endl;

}

