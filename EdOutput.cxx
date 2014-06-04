#include "EdOutput.h"

EdOutput::EdOutput(EdInput *inp, const char *fileout){
    char defaultname[255] = "output.root";

    if( fileout ){
	strcpy(fOutName, fileout);
    } else {
	strcpy(fOutName, defaultname);
    }
    printf("output file set as %s\n", fOutName);

    fTree = new TTree("T", "HG Monte Carlo");
    fNevt    = ((double) inp->GetNevt());
    n_part = inp->GetNpart();

    InitTree();

    return;
}

EdOutput::~EdOutput(){
    delete fTree;

    return;
}

void EdOutput::InitTree(){
    fTree->Branch("n_part", &n_part, "n_part/I");
    fTree->Branch("theta", theta, "theta[n_part]/D");
  
    fTree->Branch("phi", phi, "phi[n_part]/D");
    fTree->Branch("x", &x, "x/D");
    fTree->Branch("Ef", Ef, "Ef[n_part]/D");
 
    fTree->Branch("Q2", &Q2, "Q2/D");
    fTree->Branch("nu", &nu, "nu/D");

    fTree->Branch("W", &W, "W/D");
    fTree->Branch("y", &y, "y/D");

  
    fTree->Branch("Z_ion", &Z_ion, "Z_ion/I");
    fTree->Branch("N_ion", &N_ion, "N_ion/I");
    
    fTree->Branch("particle_id", particle_id, "particle_id[n_part]/I");
    fTree->Branch("charge", charge, "charge[n_part]/I");

    fTree->Branch("pf", pf, "pf[n_part]/D");
    fTree->Branch("px", px, "px[n_part]/D");
    fTree->Branch("py", py, "py[n_part]/D");
    fTree->Branch("pz", pz, "pz[n_part]/D");

    fTree->Branch("vx", &vx, "vx[n_part]/D");
    fTree->Branch("vy", &vy, "vy[n_part]/D");
    fTree->Branch("vz", &vz, "vz[n_part]/D");

    fTree->Branch("weight", &weight, "weight/D");


    return;
}

void EdOutput::SetTheta( double *val, int tot){
  for (int i =0; i<tot; i++) {
    theta[i] = val[i];
  }
  n_part = tot;
}
void EdOutput::SetPhi(double *val, int tot){
  for (int i =0; i<tot; i++) {
    phi[i] = val[i];
  }
}
void EdOutput::SetEf(double *val, int tot){
  for (int i =0; i<tot; i++) {
    Ef[i] = val[i];
  }

}
void EdOutput::Setpf(double *val, int tot){
  for (int i =0; i<tot; i++) {
    pf[i] = val[i];
  }

}
void EdOutput::Setpx(double *val, int tot){
  for (int i =0; i<tot; i++) {
    px[i] = val[i];
  }

}
void EdOutput::Setpy(double *val, int tot){
  for (int i =0; i<tot; i++) {
    py[i] = val[i];
  }

}
void EdOutput::Setpz(double *val, int tot){
  for (int i =0; i<tot; i++) {
    pz[i] = val[i];
  }

}
void EdOutput::Setparticle_id(int *val, int tot){
  for (int i =0; i<tot; i++) {
    particle_id[i] = val[i];
  }

}
void EdOutput::Setcharge(int *val, int tot){
  for (int i =0; i<tot; i++) {
    charge[i] = val[i];
  }

}
void EdOutput::Setvx(double *val, int tot){
  for (int i =0; i<tot; i++) {
    vx[i] = val[i];
  }

}
void EdOutput::Setvy(double *val, int tot){
  for (int i =0; i<tot; i++) {
    vy[i] = val[i];
  }

}
void EdOutput::Setvz(double *val, int tot){
  for (int i =0; i<tot; i++) {
    vz[i] = val[i];
  }

}
void EdOutput::Setweight(double *val, int tot){
  for (int i =0; i<tot; i++) {
    weight[i] = val[i];
  }

}
void EdOutput::Settowrite(int *val, int tot){
  for (int i =0; i<tot; i++) {
    towrite[i] = val[i];
  }

}

void EdOutput::Write(){
    fTree->Fill();

    return;
}

void EdOutput::Close(){
    fOutfile = new TFile(fOutName, "RECREATE");
    fTree->Write();
    fOutfile->Close();
    delete fOutfile;

    return;
}

void  EdOutput::MakeFileLUND(){


  

  TString file(fOutName);
  file.ReplaceAll("root","lund"); 
  char outstring[200];

  
  Int_t nentries = (Int_t)fTree->GetEntries();
  int tot_part = 0;
  for (int j=0; j<n_part; j++) {
    tot_part = tot_part +towrite[j];
  }

  double vxcm,vycm,vzcm;

  ofstream OUT (file.Data());
  for (int i=0; i<nentries ; i++) {
    fTree->GetEntry(i);
    if(i % 1000000 == 0 ){
      printf("Analyzed %09d events of total %09d \n",i,nentries);
    }
    sprintf(outstring,"%i %i %i 0 0 %1.4e %1.4e %1.4e %1.4e %1.4e",tot_part,(Z_ion+N_ion),Z_ion,x,y,W,Q2,nu);
    OUT << outstring << endl;
    //    OUT << tot_part << " " << (Z_ion + N_ion)  << " " << Z_ion  << " " << "0"  << " " << "0" << " "  << x << " " << y  << " \t " << W  << " \t " << Q2  << " \t " << nu << endl;
    for (int j=0; j<n_part; j++) {
      if (towrite[j] == 1) {
	vxcm = vx[j]*100.0;
	vycm = vy[j]*100.0;
	vzcm = vz[j]*100.0;
	sprintf(outstring,"  1 %i 1 %i 0 0 %1.4e %1.4e %1.4e %1.4e 0 %1.4e %1.4e %1.4e",charge[j],particle_id[j],px[j],py[j],pz[j],Ef[j],vxcm,vycm,vzcm); 
	OUT << outstring << endl;
	//	OUT << " \t " << "1" << " \t " << charge[j] << " \t " << "1" << " \t " << particle_id[j] << " \t " << "0" << " \t " << "0" << " \t " << px[j] << " \t " << py[j] << " \t " << pz[j] << " \t " << Ef[j] << " \t " << "0" << " \t " << vxcm  << " \t " << vycm << " \t " << vzcm << endl;
      }
    }
  }

  OUT.close();

}


void  EdOutput::MakeFileBOS(){


#define h HEAD->head[0]

  TString file(fOutName);
  file.ReplaceAll("root","bos"); 
  
  clasHEAD_t *HEAD;
  clasMCTK_t *MCTK;
  clasMCVX_t *MCVX;
  
  int BosOutputUnitNo = 2; // unit to open for writing (!?!?!?!? FORTRAN)
  int maxFileLength = 2000000;  // Maximum length of the bos file (bos files can be maximum this size)
  int nFileWrite = 0;
  int icode;

  // char out[100];
  char mess[1024];

  Int_t nentries = (Int_t)fTree->GetEntries();
  int tot_part = 0;
  for (int j=0; j<n_part; j++) {
     tot_part = tot_part +towrite[j];
  }

  // double vxcm,vycm,vzcm;


  printf("Output Bos file: %s\n",file.Data());
  //  unlink(file.Data());
  char namefile[100];
  sprintf(namefile,"%s",file.Data());
  printf("Output Bos file: %s\n",namefile);
  sprintf(mess," OPEN BOSOUTPUT UNIT=%3d FILE=\"%s\" WRITE STATUS=NEW RECL=32760 SPLITMB=2047 FORM=BINARY", BosOutputUnitNo,file.Data());
  fparm_c(mess);
  //  open_fpack_unit(namefile,"BOSOUTPUT",BosOutputUnitNo);
  // sprintf(out, "OPEN BOSOUTPUT UNIT=%d FILE=\"%s\" WRITE STATUS=NEW RECL=32768", BosOutputUnitNo, file.Data());
  // if (!fparm_c(out)) {
  //   printf("Unable to open file \'%s\': %s\n\n",out,strerror(errno));
  //   exit(1);
  // }
  // //  bosInit( bcs_.iw, NBCS ); // bosio format
  initbos(); // c_bos_io format
  //formatBank('HEAD','I');
  // formatBank('MCTK','(6F,5I)');
  // formatBank('MCVX','(4F,I)');

  bankList(&bcs_, "C=","HEADMCTKMCVX");  // Write HEAD MCTK MCVX banks into the bos file




   for (int i=0; i<nentries ; i++) {
    fTree->GetEntry(i);
    if(i % 1000000 == 0 ){
       printf("Analyzed %09d events of total %09d \n",i,nentries);
     }
    
    //   // Filling the array for bcs_ from the TTree
    HEAD = (clasHEAD_t *) makeBank(&bcs_,"HEAD",0,8,1); // void *makeBank(BOSbank *bcs, char *bankname, int banknum, int ncol, int nrow)
    MCTK = (clasMCTK_t *) makeBank(&bcs_,"MCTK",1,11,(tot_part+1)); // void *makeBank(BOSbank *bcs, char *bankname, int banknum, int ncol, int nrow)  
    MCVX = (clasMCVX_t *) makeBank(&bcs_,"MCVX",2,5,1); // void *makeBank(BOSbank *bcs, char *bankname, int banknum, int ncol, int nrow)
    
    h.version = 0;
    h.nrun = 10; // gsim run
    h.nevent = i+1; // number of event
    h.time = time(NULL); // time in seconds since Jan 1, 1970
    h.type = 2;
    h.roc = 0;
    h.evtclass = 7;
    


   // Writing into bos file
    
    icode = putBOS(&bcs_, BosOutputUnitNo, "C");
    if(!icode){
      fprintf(stdout,"ERROR - Trouble writing out BOS bank. \n");
    }

    dropAllBanks(&bcs_,"C");
    cleanBanks(&bcs_);

  //   if (fileLength("BOSOUTPUT") > maxFileLength) {
  //     /*close file*/
  //     putBOS(&bcs_, BosOutputUnitNo, "0");
  //     sprintf(mess,"CLOSE BOSOUTPUT UNIT=%d", BosOutputUnitNo);
  //     fparm_c(mess);
  //     sprintf(out,"_%d.bos",nFileWrite);
  //     file.ReplaceAll(".bos",out);
  //     nFileWrite++;
  //     /* if -j option was present, issue PutFile command */
  //     fprintf(stderr,"Output file: %s\n",file.Data());
  //     unlink(file.Data());
  //     sprintf(out, "OPEN BOSOUTPUT UNIT=%d FILE=\"%s\" WRITE STATUS=NEW RECL=32768", BosOutputUnitNo, outfile);
  //     if (!fparm_c(out)) {
  // 	printf("Unable to open file \'%s\': %s\n\n",out,strerror(errno));
  // 	exit(1);
  //     }
  //   }
   }
   close_fpack_unit("BOSOUTPUT");

}

