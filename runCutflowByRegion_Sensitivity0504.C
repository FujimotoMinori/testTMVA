int runCutflowByRegion_Sensitivity0504(){
std::string savefilename = "original_0504";
std::string inputFileName = "TMVAppcategory.root";

//std::string cutflowDirectoryName = "CutFlow_Dilep/Nominal";
//end of input and stuff to change
TFile *f1 = new TFile(inputFileName.c_str(),"READ"); cout<<"processing file " << inputFileName.c_str() << endl;
//TDirectory *cutflowDirectory = f1->GetDirectory(cutflowDirectoryName.c_str());

std::vector<double> sigma = {0.01,0.03,0.05,0.10,0.15,0.20};
vector<std::string> cutflowCategoryNames, cutflowRegionNames;
vector<TH1F*> cutflows;
TIter keyList(f1->GetListOfKeys()); //originally cutflowDirectory
TKey *key;
//first loop should get all the mc categories to see how many columns the table needs
while ((key = (TKey*)keyList())) {
  TClass *cl = gROOT->GetClass(key->GetClassName());
  if (!cl->InheritsFrom("TH1")) continue;
  std::string keyName = key->GetName();
  std::string cutflowCategoryName = keyName.substr(0, keyName.find("_"));
  if(cutflowCategoryName =="") continue;
  if((cutflowCategoryName != "data")&& (std::find(cutflowCategoryNames.begin(), cutflowCategoryNames.end(), cutflowCategoryName) == cutflowCategoryNames.end()))  cutflowCategoryNames.push_back(cutflowCategoryName);//data doesn't go to list of mcCategories. It is "called" manually so we don't have to save it here
  std::string cutflowRegionName = keyName.substr(keyName.find("_"));
  if((cutflowCategoryName == "data") &&( std::find(cutflowRegionNames.begin(), cutflowRegionNames.end(), cutflowRegionName) == cutflowRegionNames.end())) {
	  cutflowRegionNames.push_back(cutflowRegionName);
  }
}
//second loop should get all the actual histograms
for (std::string cutflowRegionName:cutflowRegionNames){
ofstream savefile;
ofstream savefile_txt;
std::string savefilename_tex =/* "cutflow/" +*/ savefilename + cutflowRegionName + ".tex";
std::string savefilename_txt =/* "cutflow/" +*/ savefilename + cutflowRegionName + ".txt";

//do tex
savefile.open(savefilename_tex.c_str());
savefile_txt.open(savefilename_txt.c_str());
savefile << "\\providecommand{\\xmark}{{\\sffamily \\bfseries X}}\n \\providecommand\\rotatecell[2]{\\rotatebox[origin=c]{#1}{#2}}\n \\scalebox{0.3}{\n \\begin{tabular}{ r || ";
for(std::string counter : cutflowCategoryNames){
  if(counter == "Signal")savefile << " r ";
}
savefile << "r || r r r r ";
for(auto sig: sigma){
	savefile << " r" ;
}
savefile << " |} \n \\ensuremath{\\sqrt{s}=13 TeV}, \\ensuremath{\\mathcal{L}=36 fb^{-1}} "; 
for(std::string mcName : cutflowCategoryNames){
  if(mcName != "data" && mcName == "Signal") savefile << " & " << mcName.c_str();
}
savefile << "& BG & Total MC & Signal/BG & \\ensuremath{S/\\sqrt{B}} & Z";
for(auto sig: sigma){
 savefile << "& ZwUC($\\sigma=$" << sig << ")";
}
savefile << " \\tabularnewline \n \\hline \n";

//print table
TH1F* histToShow;
f1->GetObject(("data"+cutflowRegionName).c_str(), histToShow);
for(int i = 1; i < histToShow->GetNbinsX(); i++){
  savefile << histToShow->GetXaxis()->GetBinLabel(i);
  std::cout << "categoryName=" << histToShow->GetXaxis()->GetBinLabel(i) << std::endl;
  double mcTotal = 0;
  double Signal = 0;
  double BG = 0;
  double Z = 0;
  for(std::string mcName : cutflowCategoryNames){
    TH1F* readCutflow;
    f1->GetObject((mcName+cutflowRegionName).c_str(), readCutflow);
    double binContent = readCutflow -> GetBinContent(i);
    if(mcName == "Signal")savefile << " & " << binContent ;
    mcTotal += binContent;
    if (mcName == "Signal") Signal += binContent;
    else BG += binContent; 
  }
  TH1F* readCutflow;
  f1->GetObject(("data"+cutflowRegionName).c_str(), readCutflow);
  double dataTotal = readCutflow -> GetBinContent(i);
  std::cout << "dataTotal=" << dataTotal << std::endl;
  if((dataTotal==0)||(mcTotal == 0)) {cout << "ERROR: either mc or data has 0 events !!" <<endl; mcTotal = 1;}
  //calcurate sensitivity
  Z =  sqrt(2*(mcTotal*std::log(1+Signal/BG)-Signal));
  savefile << " & " << BG << " & " << mcTotal << " & " << Signal/BG  << " & " << Signal/sqrt(BG) <<  " & " <<  Z;
  if(i!=1) savefile_txt << 0.0 << " " << Z << std::endl;
  for(auto sig: sigma){
	  if( i != 1) savefile_txt << sig ;
	  double sigmaBG = 0; 
	  double SoBwU = 0; 
	  double ZwU = 0;
	  sigmaBG = sig * BG; 
          //ZwU = Signal/sqrt(BG+pow(sigmaBG,2));
          std::cout << "sigma= " << sig << " sigBG= " << sigmaBG << std::endl;
	  //SoBwU =  Signal/sqrt(BG+pow(sigmaBG,2));
	  ZwU =  sqrt(2*(mcTotal*std::log(mcTotal*(BG+pow(sigmaBG,2))/(pow(BG,2)+mcTotal*pow(sigmaBG,2)))-(pow(BG,2)/pow(sigmaBG,2))*std::log(1+(pow(sigmaBG,2)*Signal)/(BG*(BG+pow(sigmaBG,2))))));
	  savefile << "&" << ZwU; 
	  if( i != 1 )savefile_txt << " " << ZwU << std::endl;; 
  }
  savefile << "\\tabularnewline \\hline \n";
}
savefile << "\\end{tabular}\n }";
savefile.close();
savefile_txt.close();
}
return 0;
}
