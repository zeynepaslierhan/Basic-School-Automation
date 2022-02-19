#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// prototypes
void kayitEkle(FILE *ogrenciPtr);
void ogrenciDersKaydi(FILE *ogrenciPtr);
void puanGir(FILE *ogrenciPtr);
int secenekGir();
void indexDosyasiOlustur(FILE *readPtr);
void indeksDosyasiniGoster(FILE *ogrenciPtr);
void indeksDosyasiniSil();
void indexDosyasiGuncelle(FILE *ogrenciPtr);
void veriDosyasiniGoster(FILE *ogrenciPtr);
int kayitBul(FILE *ogrenciPtr);
int ogrenciSayisi(FILE *ogrenciPtr);
void kayitGuncelle(FILE *ogrenciPtr);
int ogrenciNumaraSorgulama(FILE *ogrenciPtr);
void kayitSil(FILE *ogrenciPtr);

// Defined student structure
struct Ogrenci
{
    char ad[21]; // student first name
    char soyad[21]; // student last name
    int ogrenciNumarasi; // student number
    int dersKodlari[10]; // student lesson code
    int puan[10]; // student grades
};
// Defined lesson structure
struct Ders
{
    char dersAdi[20]; // Lesson name
    int dersKodu; //lesson code
};
int main()
{  
	int kontrol=1;
	FILE *ogrenciPtr; // ogrenci.bin file pointer
	

	while(kontrol==1)
	{	
		ogrenciPtr=fopen("ogrenci.bin","rb+"); //File opens in add and read mode; exits if file cannot be opened
  		if(ogrenciPtr==NULL)
		{
			printf("ogrenci.bin Dosyasi Acilamadi...\n");
    		exit(0); //Exiting the program
       	}
		
		switch(secenekGir()) //get user's choice
	    {
			//create student registration
		   	case 1:
		       	kayitEkle(ogrenciPtr);
		        printf("\n");
		        break;
		        
		    //enroll the registered student in the course
			case 2:
				ogrenciDersKaydi(ogrenciPtr);
				printf("\n");
		        break;
		        
			//Enter the score of the course in which the registered student is registered.
			case 3:
	        	puanGir(ogrenciPtr);
				printf("\n");
		       	break;
		        
			//create index file from data file
			case 4:
		      	indexDosyasiOlustur(ogrenciPtr);
		       	printf("\n");
		       	break;
		        
			//delete index file
			case 5:
				indeksDosyasiniSil();
				printf("\n");
				break;
			
			//show data file
			case 6:
				veriDosyasiniGoster(ogrenciPtr);	
				printf("\n");
				break;
			
			//Find records with binary search
			case 7:
				kayitBul(ogrenciPtr);
				printf("\n");
				break;
				
			//show index file
			case 8:
				indeksDosyasiniGoster(ogrenciPtr);
				printf("\n");
				break;
				
			// update record
			case 9:
				kayitGuncelle(ogrenciPtr);
				printf("\n");
				break;
				
			//delete record
			case 10:
				kayitSil(ogrenciPtr);
				printf("\n");
				break;
				
			//close the program	
			case 11:
		        printf("\nOgrenci Veri Tabani Sisteminden Cikmaktasiniz...\n");
		        kontrol=0;
		        break;
		        
			//display message if user does not select valid choice
			default:
		        printf("\nBoyle Bir Islem Seceneginiz Bulunmamaktadir. Yeniden Secim Yapiniz.\n\n");
		        break;  	
		}
	}
	
	
	fclose(ogrenciPtr);// close opened file
    return 0; //It is used to show that the operations (function) are completed successfully.
}
// enable user to input menu choice
int secenekGir()
{
	
	// display available options
	printf("\nHangisini istersiniz?\n"
		"1 - Ogrenci Ekle\n"
		"2 - Kayitli ogrenciyi derse ekleyin\n"
		"3 - Kayitli ogrencinin kayit oldugu dersin puanini ekle\n"
		"4 - Index dosyasi olustur\n"
		"5 - Index dosyasini siliniz\n"
		"6 - Veri dosyasini goster\n"
		"7 - Ogrenci kaydi bul\n"
		"8 - Index dosyasini göster\n"
		"9 - Kayitli ogrencinin kayit oldugu dersin puanini guncelle\n"
		"10 - Kayitli ogrencinin kaydini sil\n"
		"11 - programi kapa?\n");
			
	int menuSecenek; // variable to store user's choice
	scanf("%d", &menuSecenek); // receive choice from user
	fflush(stdin); //The buffer is emptying.
	return menuSecenek;
}
//create student registration
void kayitEkle(FILE *ogrenciPtr) 
{
	//create structure for student to be added and student to be used to obtain information
	struct Ogrenci girilenOgrenci, tempOgrenci; 
    
	int karakterSayisi, ogrenciNo; //variable for character count and student number
    int dosyaUzunlugu; // variable for file length
    int indis;// variable for course code element

    fseek(ogrenciPtr,0,SEEK_END); //ogrenciPtr points to the end of the file
    dosyaUzunlugu=ftell(ogrenciPtr); //The size of the file is calculated with the help of the "ftell()" function

    if(dosyaUzunlugu==0) //If the file is empty, set the student number to 1
        ogrenciNo=1;
    else
    {
        rewind(ogrenciPtr); //ogrenciPtr points to the beginning of the file
        while( !feof(ogrenciPtr) ) //keep looping until you reach the end of the file
        {
            fread( &tempOgrenci,sizeof(struct Ogrenci),1,ogrenciPtr ); //Information about the student is read from the file
            ogrenciNo=tempOgrenci.ogrenciNumarasi; //The student number of the last student registered in the system is determined
        }
        ogrenciNo++; //A student number is created for the next student to be added to the system
    }

        do //Getting the name of the student
        {
            printf("Ogrenci Adini Giriniz:");
            gets(girilenOgrenci.ad);
            fflush(stdin);  //The buffer is emptying.
            
			karakterSayisi=strlen(girilenOgrenci.ad); //Finding the number of characters in the name
			if(karakterSayisi>20)//Notify about character limit
            {
                printf("\nOgrenci Adi 20 Karakterden Fazla Olamaz!\n");
                printf("Lutfen Ogrenci Adini Tekrar Giriniz.\n\n");
            }
        }
        while(karakterSayisi>20); //continue the loop as long as the number of characters is greater than 20

        do//Getting the surname of the student
        {
            printf("Ogrenci Soyadini Giriniz:");
            gets(girilenOgrenci.soyad);
            fflush(stdin);  //The buffer is emptying.
            
			karakterSayisi=strlen(girilenOgrenci.soyad); //Finding the number of characters in the surname.
            if(karakterSayisi>20)//Notify about character limit
            {
                printf("\nOgrenci Soyadi 20 Karakterden Fazla Olamaz!\n");
                printf("Lutfen Ogrenci Soyadini Tekrar Giriniz.\n\n");
            }
        }
        while(karakterSayisi>20); //continue the loop as long as the number of characters is greater than 20

        rewind(ogrenciPtr);
        girilenOgrenci.ogrenciNumarasi=ogrenciNo; //Give the added student the student number

        for(indis=0;indis<10;indis++)
        {
            girilenOgrenci.dersKodlari[indis]=0; //Assign 0 to the code of 10 courses that the added student can take
            girilenOgrenci.puan[indis]=0; //Assign 0 to the grades of 10 courses that the added student can take
        }	
	
	//Determining the order in which the student will be in the file according to the student number
    fseek( ogrenciPtr,(ogrenciNo-1)*sizeof(struct Ogrenci),SEEK_SET ); 
    //Print added student information to file
	fwrite( &girilenOgrenci,sizeof(struct Ogrenci),1,ogrenciPtr );
	
	printf("#%d ogrenci numarasiyla %s %s isimli ogrenci sisteme kaydolmustur.\n",girilenOgrenci.ogrenciNumarasi,girilenOgrenci.ad,girilenOgrenci.soyad);
	fclose(ogrenciPtr); // close opened file
	indexDosyasiGuncelle(ogrenciPtr); // update index file
}
//find the number of students
int ogrenciSayisi(FILE *ogrenciPtr)
{	
	int kayitliOgrenciSayisi=0;
	struct Ogrenci okunanOgrenci3;
    
    rewind(ogrenciPtr);
    while(!feof(ogrenciPtr))
    {	
    	if(fread(&okunanOgrenci3,sizeof(struct Ogrenci),1,ogrenciPtr)==1)
			kayitliOgrenciSayisi++;
	}
	
	return kayitliOgrenciSayisi;
}
//enroll the registered student in the course
void ogrenciDersKaydi(FILE *ogrenciPtr) 
{	
	//dersler.bin file pointer
    FILE *derslerPtr;
    
	struct Ogrenci okunanOgrenci5;// create a structure for the student 
	struct Ders okunanDers;// structure for controlling courses
    
	int girilenOgrenciNo,girilenDersKodu; // variable for student number and lesson code
    int ogrenciDersSayisi=0,kontrol=0,indis,indis1; // variable for number of registered courses, control, element

    //Files open ; exits if file cannot be opened
    derslerPtr=fopen("dersler.bin","rb");// Files open in read mode
    if(derslerPtr==NULL)
    {
        printf("dersler.bin Dosyasi Acilamadi...\n");
        exit(0);// Exiting the program
    }

	indis=kayitBul(ogrenciPtr);
	// Determining the location of the file according to the student number entered
    fseek( ogrenciPtr,indis*sizeof(struct Ogrenci),SEEK_SET ); 
    fread( &okunanOgrenci5,sizeof(struct Ogrenci),1,ogrenciPtr ); // reading student information
    
	for(indis1=0;indis1<10;indis1++)
    {
        if(okunanOgrenci5.dersKodlari[indis1]!=0)
            ogrenciDersSayisi++; //Determining the number of courses the student is enrolled in
    }

    if(ogrenciDersSayisi==10)
        printf("\nOgrenciye Tanimli 10 Ders Bulunmaktadir. Ogrenciye Baska Ders Tanimlayamassiniz!\n");
    
	else //If there are less lessons than the lesson limit
    {
        rewind(ogrenciPtr);
        do
        {
            printf("Ogrenciye Tanimlamak Istediginiz Dersin Kodunu Giriniz:(1001-1020)\n  ");
            scanf("%d",&girilenDersKodu);
            fflush(stdin); //The buffer is emptying
            
            // Determining the location of the file according to the lesson code entered
			fseek( derslerPtr,(girilenDersKodu-1-1000)*sizeof(struct Ders),SEEK_SET );
            fread( &okunanDers,sizeof(struct Ders),1,derslerPtr );// reading lesson information
            
			if(girilenDersKodu!=okunanDers.dersKodu)// If the entered course code is not in the system
                printf("\n%d Ders Kodlu Ders Sistemde Kayitli Degildir!\nLutfen Yeni Bir Ders Kodu Giriniz.\n\n",girilenDersKodu);
            rewind(derslerPtr);// file pointer returns to the beginning of the file
        }
        while(girilenDersKodu!=okunanDers.dersKodu); // Continue the loop until the entered course code is a course code registered in the system
	
		// Determining the location of the file according to the student number entered
        fseek( ogrenciPtr,indis*sizeof(struct Ogrenci),SEEK_SET );      
        fread( &okunanOgrenci5,sizeof(struct Ogrenci),1,ogrenciPtr );// reading student information

        for(indis1=0;indis1<10;indis1++)
        {
            if(okunanOgrenci5.dersKodlari[indis1]==0) // If the course code is not defined in the relevant index, it enters the if structure
            {
                okunanOgrenci5.dersKodlari[indis1]=okunanDers.dersKodu; // The code of the course that the user wants to enroll the student in is transferred to the courseCodes array
                kontrol=1;
                break;
            }
            else
            {	//If the course code entered by the user is the code of the course the student is enrolled in, the if structure is entered.
                if(okunanOgrenci5.dersKodlari[indis1]==okunanDers.dersKodu) 
                {
                    kontrol=0;
                    break;
                }
            }
        }
		
		//Thanks to the control variable, it is learned whether the student is enrolled in the course or not
        if(kontrol==1)
        {
            rewind(ogrenciPtr);
            fseek( ogrenciPtr,indis*sizeof(struct Ogrenci),SEEK_SET );
            fwrite( &okunanOgrenci5,sizeof(struct Ogrenci),1,ogrenciPtr ); //Student information is written to the file together with the course record.
            
			printf("\n%d Numarali Ogrencinin %d Kodlu %s Dersine Kaydi Yapilmistir!\n",okunanOgrenci5.ogrenciNumarasi,okunanDers.dersKodu,okunanDers.dersAdi);
        }
        else
            printf("\n%d Numarali Ogrencinin %d Kodlu %s Dersine Kaydi Bulunmaktadir!\n",okunanOgrenci5.ogrenciNumarasi,okunanDers.dersKodu,okunanDers.dersAdi);
    }

    fclose(ogrenciPtr); //close opened file
    fclose(derslerPtr);
    indexDosyasiGuncelle(ogrenciPtr); // update index file
}
//Enter the score of the course in which the registered student is registered.
void puanGir(FILE *ogrenciPtr)
{
    struct Ogrenci okunanOgrenci;// create a structure for the student 
    int girilenOgrenciNo,dersKodu;// variable for student number and lesson code
    int ogrenciDersSayisi=0,kontrol=0,indis,indis1; // variable for number of registered courses, control, course code element
    
    indis1=kayitBul(ogrenciPtr);

    fseek( ogrenciPtr,indis1*sizeof(struct Ogrenci),SEEK_SET );  // detecting the location in the file according to the student number entered
    fread( &okunanOgrenci,sizeof(struct Ogrenci),1,ogrenciPtr ); // get relevant student data.
    
    printf("#%d numarali %s %s isimli ogrencinin sahip oldugu derslerin kodlari:\n"
					,okunanOgrenci.ogrenciNumarasi,okunanOgrenci.ad,okunanOgrenci.soyad);
					
	for(indis=0;indis<10;indis++)//Show student's registered courses
	{
		if(okunanOgrenci.dersKodlari[indis]!=0)
    		printf("-%d-",okunanOgrenci.dersKodlari[indis]);
	}
 	printf("\n");
 	
 	do{
 		//get the desired course code from the user
		printf("Kodu giriniz:\n");
 		scanf("%d",&dersKodu);
 		fflush(stdin);//The buffer is emptying
 		
		 //Checking the student's course registration
	 	for(indis=0;indis<10;indis++)
	 	{
	 		if(okunanOgrenci.dersKodlari[indis]==dersKodu)
	        {
                kontrol=1;	                
				break;
	        }
		}
		
		if(kontrol!=1)
	        printf("\n%d Numarali Ogrencinin %d Kodlu dersine Kaydi Yoktur!\n"
					"Kayitli oldugu ders kodunu giriniz.\n",girilenOgrenciNo,dersKodu);
					
	 }while(kontrol==0);
	 
        
	
	//get grade from user
	printf("%d koduna sahip ders için puan giriniz:",okunanOgrenci.dersKodlari[indis]);
	scanf("%d",&okunanOgrenci.puan[indis]);	
	fflush(stdin);//The buffer is emptying
	
	
	rewind(ogrenciPtr);// ogrenciPtr point to the beginning of the file
    fseek( ogrenciPtr,indis1*sizeof(struct Ogrenci),SEEK_SET );// Detecting the location in the file according to the student number entered
	fwrite( &okunanOgrenci,sizeof(struct Ogrenci),1,ogrenciPtr );// Student information is written to the file together with the course record

	printf("Kayit yapilmistir..\n");
    fclose(ogrenciPtr); // closed opened file
	indexDosyasiGuncelle(ogrenciPtr); // update index file	
}
//create index file from data file
void indexDosyasiOlustur(FILE *readPtr)
{
	FILE *writePtr; //kayit.txt and ogrenci.bin file pointer 
	int indis;
	
	// fopen opens the file; exits if file cannot be opened
	if((writePtr=fopen("kayit.txt","w"))==NULL)
	{
		puts("dosya açilamadi.");
	}

	else
	{
		rewind(readPtr);// sets pointer to beginning of file
		fprintf(writePtr,"%-15s%-22s\n\n"," ","OGRENCI BILGILERI");

		// copy all records from random-access file into text file
		while (!feof(readPtr)) 
		{		
			// create kayit with default information
			struct Ogrenci kayit ={ "","", 0, 0, 0};
			int result =fread(&kayit, sizeof(struct Ogrenci), 1, readPtr);
		
			// write single record to text file
			if (result != 0 && kayit.ogrenciNumarasi != 0)
			{	
				fprintf(writePtr, "%#-19s %-21s%-20s\n"," ","ADI", "SOYADI");
				
				fprintf(writePtr, "%#-10d %-s %-20s %-20s\n"
								,kayit.ogrenciNumarasi,"Numarali",kayit.ad, kayit.soyad);
				
				for(indis=0;indis<10;indis++)
				{
					if(kayit.dersKodlari[indis]!=0)
						fprintf(writePtr, "%-15s%4d     %-15s%3d\n","Ders Kodu:"
										,kayit.dersKodlari[indis],"Ders Puani:", kayit.puan[indis]);
				}
				
				fprintf(writePtr, "\n\n");						
			}
		}
		
		fclose(writePtr); // fclose closes the file
		fclose(readPtr);
		
		printf("Index dosyasina gerekli islemler yapildi.\n");
	}
}
//show index file 
void indeksDosyasiniGoster(FILE *ogrenciPtr)
{
    char karakter; //variable for character
    ogrenciPtr=fopen("kayit.txt","r"); // The file is opened in read mode. The cursor is at the beginning of the file.
    
	do
	{	//reading test file character by character
		karakter=getc(ogrenciPtr);
		if(karakter !=EOF)
		{
			//print test file character by character
			putchar(karakter);
		}	
		
	}while(karakter !=EOF);
	
    fclose(ogrenciPtr); //close opened file
    
    printf("\n Okuma Islemi Tamamlandi \n");
}
// delete text file
void indeksDosyasiniSil()
{
	remove("kayit.txt");// function that deletes files from memory
	printf("Dosya silindi.\n");
}
//update index file
void indexDosyasiGuncelle(FILE *ogrenciPtr)
{
	ogrenciPtr=fopen("ogrenci.bin","rb+"); //File opens in add and read mode; exits if file cannot be opened
  	if(ogrenciPtr==NULL)
	{
		printf("ogrenci.bin Dosyasi Acilamadi...\n");
    	exit(0); //Exiting the program
    }
	if(fopen("kayit.txt","r")!=NULL)//if kayit.txt file exist keep going
		indexDosyasiOlustur(ogrenciPtr);	
}
// list data file
void veriDosyasiniGoster(FILE *ogrenciPtr) 
{
    FILE *derslerPtr;// dersler.bin file pointer
    
	struct Ogrenci okunanOgrenci;// create a structure for the student 
    struct Ders okunanDers;// structure for controlling courses
    
	int girilenOgrenciNo=1,alinanDersSaysi=0;// variable for student number and number of lessons taken
    int indis;// variable for number of registered courses, control, course code element

    derslerPtr=fopen("dersler.bin","rb"); // The file is opened in read mode. The cursor is at the beginning of the file.
    if(derslerPtr==NULL)
    {
        printf("dersler.bin Dosyasi Acilamadi...\n");
        exit(0);//Exit the program
    }


    rewind(ogrenciPtr);// ogrenciPtr point to the beginning of the file
   	if(fread(&okunanOgrenci,sizeof(struct Ogrenci),1,ogrenciPtr )!=1)
   		printf("Veri Dosyasinda kayitli bilgi yoktur.\n");

    while(fread(&okunanOgrenci,sizeof(struct Ogrenci),1,ogrenciPtr )==1) //The loop continues as long as the file does not reach the end.
	{	
		// Student information read from the file is transferred to okunanOgrenci
		printf("\nOgrenci Numarasi  : %d\n",okunanOgrenci.ogrenciNumarasi);
	    printf("Ogrenci Adi       : %s\n",okunanOgrenci.ad);
	    printf("Ogrenci Soyadi    : %s\n\n",okunanOgrenci.soyad);
	    printf("Ogrencinin Aldigi Dersler:\n");
	
		rewind(derslerPtr);
	    while(fread(&okunanDers,sizeof(struct Ders),1,derslerPtr)==1) //The loop continues as long as the file does not reach the end.
	    { 	
			// Course information read from the file is transferred to okunanDers.
	        for(indis=0;indis<10;indis++)
	        {
	            if(okunanOgrenci.dersKodlari[indis]==okunanDers.dersKodu)
	            {	
	            	// The code of the course the student is registered for and the name of the course are printed on the screen.
	                printf("Dersin Kodu: %d\tDersin Adi : %s\t Aldigi Puan: %d\n",okunanDers.dersKodu,okunanDers.dersAdi,okunanOgrenci.puan[indis]); 
	                alinanDersSaysi++;// The number of courses that the student is registered in the system is determined.
	            }
	        }
	    }
	    if(alinanDersSaysi==0)
	        printf("Ogrenci Hicbir Derse Kayitli Degildir!\n");
	    printf(".\n.\n");
	}
	    

    fclose(ogrenciPtr); //close opened files
    fclose(derslerPtr);
}
//Find records with binary search
int kayitBul(FILE *ogrenciPtr)
{
	int girilenOgrenciNo;
	struct Ogrenci arananOgrenci;
   	int mid,low,high;
   	
	do
	{
		printf("Istediginiz Ogrencinin Numarasini Giriniz:");
	    scanf("%d",&girilenOgrenciNo);
	    fflush(stdin);  //The buffer is emptying.
				
		high=ogrenciSayisi(ogrenciPtr)-1;
		low=0;
		rewind(ogrenciPtr);
		
		while (low<=high) 
		{  
			mid = (high + low)/2;
			fseek(ogrenciPtr,mid*sizeof(struct Ogrenci),SEEK_SET);
			fread(&arananOgrenci,sizeof(struct Ogrenci),1,ogrenciPtr);
			if (arananOgrenci.ogrenciNumarasi==girilenOgrenciNo)
			{	
				printf("#%d numarali %s %s isimli ögrenci bilgileri bulunmustur.\n ",arananOgrenci.ogrenciNumarasi,arananOgrenci.ad,arananOgrenci.soyad);
			   	return mid;
			}	
			else if (arananOgrenci.ogrenciNumarasi<girilenOgrenciNo)
			{
				low = mid + 1;	
			}		    
			else if (arananOgrenci.ogrenciNumarasi>girilenOgrenciNo)
			{	
				high = mid - 1;
			}
		}
	
		printf("#%d numarali ogrenci sistemde kayitli degildir.\n ",girilenOgrenciNo);
		printf("kayitli bir ogrenci numarasi giriniz:\n ");
		
	}while(girilenOgrenciNo!=arananOgrenci.ogrenciNumarasi);
}
// update students grades
void kayitGuncelle(FILE *ogrenciPtr)
{	
	puanGir(ogrenciPtr);
}

//delete an existing record
void kayitSil(FILE *ogrenciPtr)
{	
	FILE *ogrenciPtr_temp;
	int indis;
	struct Ogrenci okunanOgrenci, silinenOgrenci;
    
	ogrenciPtr_temp=fopen("tmp.bin", "wb");
	if (ogrenciPtr_temp==NULL) 
	{
		printf("tmp.bin Dosyasi Acilamadi...\n");
        exit(0);  //Exiting the program
	}
	
	indis=kayitBul(ogrenciPtr);
	fseek(ogrenciPtr,indis*sizeof(struct Ogrenci),SEEK_SET);
	fread(&silinenOgrenci,sizeof(struct Ogrenci),1,ogrenciPtr);
	
	rewind(ogrenciPtr);
	while(fread(&okunanOgrenci,sizeof(struct Ogrenci),1,ogrenciPtr)!=NULL)
	{
		if (silinenOgrenci.ogrenciNumarasi==okunanOgrenci.ogrenciNumarasi) 
		{
			printf("#%d numarali %s %s ögrencinin kaydi silindi.\n\n"
					,okunanOgrenci.ogrenciNumarasi,okunanOgrenci.ad,okunanOgrenci.soyad);
		} 
		else 
		{
			fwrite(&okunanOgrenci,sizeof(struct Ogrenci), 1,ogrenciPtr_temp);
		}
	}

	fclose(ogrenciPtr);
	fclose(ogrenciPtr_temp);

	remove("ogrenci.bin");
	rename("tmp.bin","ogrenci.bin");
	indexDosyasiGuncelle(ogrenciPtr_temp);
}
