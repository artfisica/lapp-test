//////////////////////////////////////////////////////////////////////////////////////////
// Creates a TChain to be used by the Analysis.C class
#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
// #include "TProof.h"

void main_HyyAnalysis(int proof = 0, int option= 0)
{

  // path to your local directory *or* URL, please change the default one!

  /* Local path example */
  //TString path = "/eos/project/a/atlas-outreach/projects/open-data/OpenDataTuples/renamedLargeRJets/GamGam/";
  
  /* The URL to the ATLAS Open Data website repository */
  // BEFORE ESCAPE : TString path = "https://atlas-opendata.web.cern.ch/atlas-opendata/samples/2020/GamGam/";
  TString path_xcache = ""; // "root://escape-wp2-puppet-xcache-level0-redirector.cern.ch//"; 

  TString path_alpamed = "root://lapp-testse01.in2p3.fr:1094//dpm/in2p3.fr/home/escape/rucio/lapp_dpm/";
  TString path_cc = "root://ccdcalitest10.in2p3.fr:1094//pnfs/in2p3.fr/data/escape/cc_in2p3_dcache/";
  TString path_napoli = "root://t2-dpm-dome.na.infn.it:1094//dpm/na.infn.it/home/escape/infn_na_dpm/";
  TString path_pic = "root://xrootd.pic.es:1094//pnfs/pic.es/data/escape/rucio/pic_dcache/";
  TString path_desy="root://dcache-se-doma.desy.de:1094//escape/wp2_rucio_testbed/desy_dcache/";
  TString path_sara="root://lobster10.grid.surfsara.nl:1094//pnfs/grid.sara.nl/data/escape/disk/rucio/sara_dcache/";
  TString path_scope = "ATLAS_LAPP_JEZEQUEL/";
  printf("Run on lxplus.cern.ch\n");
  // printf("Read from datalake through Xcache %s\n",path_xcache.Data()); 

  //***************************************************************************************************//
  // We run only over data and Higgs MC
  // option==0 will run all one by one
  // Currently 1 option for MC (2) and 1 for data (1) which can be run in parallel
  //***************************************************************************************************//
 
  //  if (proof == 1)  TProof::Open("");

  if (option==1 || option==0){

  //data
  TChain* chain_data = new TChain("mini");
  // BEFORE ESCAPE : chain_data->AddFile(path+"Data/data_A.GamGam.root");
  //chain_data->AddFile(path_xcache+path_alpamed+path_scope+"6f/98/a9/data_A.GamGam.root");
  printf("Read data_A.GamGam.root, data_B.GamGam.root, data_C.GamGam.root, data_D.GamGam.root from ALPAMED-DPM\n ");
  chain_data->AddFile(path_xcache+path_alpamed+path_scope+"f1/3a/data_B.GamGam.root");
  chain_data->AddFile(path_xcache+path_alpamed+path_scope+"45/95/data_C.GamGam.root");
  chain_data->AddFile(path_xcache+path_alpamed+path_scope+"73/e3/data_D.GamGam.root");
  if (proof == 1)  chain_data->SetProof();
  chain_data->Process("HyyAnalysis.C+","data");
  } // option 1

  if (option==2 || option==0){
  // Higgs MC, ggH production
  TChain* chain_ggH125 = new TChain("mini");
  chain_ggH125->AddFile(path_xcache+path_desy+path_scope+"1b/95/mc_343981.ggH125_gamgam.GamGam.root.1");
  printf("Read mc_343981.ggH125_gamgam.GamGam.root.1 from DESY-DCACHE\n");
  if (proof == 1)  chain_ggH125->SetProof();
  chain_ggH125->Process("HyyAnalysis.C+","ggH125_gamgam");

  // VBF Higgs production
  TChain* chain_VBFH125 = new TChain("mini");
  chain_VBFH125->AddFile(path_xcache+path_sara+path_scope+"ff/c7/mc_345041.VBFH125_gamgam.GamGam.root.1");
  printf("Read mc_345041.VBFH125_gamgam.GamGam.root.1 from SARA-DCACHE\n");
  if (proof == 1)  chain_VBFH125->SetProof();
  chain_VBFH125->Process("HyyAnalysis.C+","VBFH125_gamgam");

  // WH production
  TChain* chain_WH125 = new TChain("mini");
  chain_WH125->AddFile(path_xcache+path_pic+path_scope+"13/b8/mc_345318.WpH125J_Wincl_gamgam.GamGam.root.1");
  printf("Read mc_345318.WpH125J_Wincl_gamgam.GamGam.root.1 from PIC-DCACHE\n");
  if (proof == 1)  chain_WH125->SetProof();
  chain_WH125->Process("HyyAnalysis.C+","WH125_gamgam");

  // ZH production
  TChain* chain_ZH125 = new TChain("mini");
  chain_ZH125->AddFile(path_xcache+path_cc+path_scope+"76/fd/mc_345319.ZH125J_Zincl_gamgam.GamGam.root");
  printf("Read mc_345319.ZH125J_Zincl_gamgam.GamGam.root from IN2P3-CC-DCACHE\n");
  if (proof == 1)  chain_ZH125->SetProof();
  chain_ZH125->Process("HyyAnalysis.C+","ZH125_gamgam");

  // ttH production
  TChain* chain_ttH125 = new TChain("mini");
  chain_ttH125->AddFile(path_xcache+path_napoli+path_scope+"6d/aa/mc_341081.ttH125_gamgam.GamGam.root.1");
  printf("Read mc_341081.ttH125_gamgam.GamGam.root.1 from INFN-NA-DPM\n");
  if (proof == 1)  chain_ttH125->SetProof();
  chain_ttH125->Process("HyyAnalysis.C+","ttH125_gamgam");
  }//option 2

}
