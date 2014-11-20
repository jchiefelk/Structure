//This Little Piece of Code Calculates the Radial Distribution Function and Number of Waters//
//Within a Spherical Shell Relative to the Center of Mass of a specified Molecule in Gromacs//

#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#define pi  3.14159
#define CUB(x) ((x)*(x)*(x))
#define SQR(x) ((x)*(x))



/*Calculates Radial Distribution from Gromacs Data*/
/* Input data from file */
int main(int argc, char *argv[]) {
	   
    
	if (argc != 10){
        printf("%s","Usage: %s InputSolData(.txt) Bin_Width(Angstroms) MaxRadius(Angstroms) Nsol Simlength(ps) Timestep(ps) rho RDF_Out Num_Out\n");
        exit(1);
    }
	
	else {
    
        //File Input//
        //Store Distance Data in an Array called Dist//
        int i,j,Length,Line_Num,MaxRadius,nT,NoW,ir,ID;
        float Bin_Width,rho,Dist,Radius,Nfact,Number,Time,t;
		char inFile[80],buf[180];
        rho = atof(argv[7])/1000; /*Convert to angstroms, Bulk Density*/
        Bin_Width=atof(argv[2]);
        MaxRadius = atoi(argv[3]);
        NoW = atof(argv[4]);
        nT = atof(argv[5])/atof(argv[6]);
        Length = MaxRadius/Bin_Width; /*Total Numer of Distance Samples in Analysis*/
		FILE *fp;
		sprintf(inFile,"%s",argv[1]);
		fp = fopen(inFile,"r");
		Line_Num = nT * NoW;
		double GoR[Length];
		for(i=0;i<Length;i++){
			GoR[i]=0.0;
		}
		printf("Good artists copy\n");	

		//Get 2 Header Lines//
		fgets(buf,180,fp);
		fgets(buf,180,fp);
		for(i=0;i<nT;++i){

			for(j=0;j<NoW;j++){
				fgets(buf,180,fp);
				sscanf(buf,"%f %i %f\n",&t,&ID,&Dist);
				ir = (Dist*10)/Bin_Width;
				if (ir < Length){
					GoR[ir] += 1.0;
				}
				
			}
		}
		
		
		
        fclose(fp);
		printf("Great artists steal\n");	
		//Calculate Radial Distribution Function//
		FILE *RDF;
        FILE *Num;
        char RDF_out[80],Num_out[80];
        sprintf(RDF_out,"%s",argv[8]);
        sprintf(Num_out,"%s",argv[9]);
        RDF = fopen(RDF_out, "w");
        Num =fopen(Num_out,"w");
		Nfact = 4*pi*rho*nT*CUB(Bin_Width);
		printf("Please stolen code make me a meal\n");
		Number = 0.0;
		for (i = 0; i < Length; i++){
			Radius=i*Bin_Width;
			GoR[i] /= (Nfact*(i*(i+1)+1.0/3.0));
			Number += 4.0*pi*rho*Radius*Radius*Bin_Width*GoR[i]; /*Integral of RDF*/
			printf("%f %f %f\n",Radius,Number,GoR[i]); 
            fprintf(Num,"%f %f\n",Radius,Number);
            fprintf(RDF,"%f %f\n",Radius,GoR[i]);
		}
        fclose(RDF);
        fclose(Num);

    }

}
