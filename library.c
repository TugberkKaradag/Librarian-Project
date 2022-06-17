#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#define MAX 256
//******* BAŞLANGIÇTA USERNAME:admin PASSWORD:password *******
FILE *dosya;
int sayiz;
char kitapisim[50];
FILE *gecici;
char username[15]; 
char password[15];
int a=0; 
int isAuthenticated; // Bunu giriş yapılıp yapılmadığını kontrol etmek için kullanıyoruz.

void remove_spaces (char* str_trimmed, const char* str_untrimmed) //Dosyadan elde edilen boşluklu stringin boşluklarını silmeye yarayan fonk.
{
  while (*str_untrimmed != '\0')
  {
    if(!isspace(*str_untrimmed))
    {
      *str_trimmed = *str_untrimmed;
      str_trimmed++;
    }
    str_untrimmed++;
  }
  *str_trimmed = '\0';
}

int Search_in_File() { //Dosyada kitap ararken bize verilen stringi dosyayla karşılaştırma fonk.
	fflush(stdin);
	FILE *fp;
	fp = fopen("booklist.txt","r");
	int line_num = 1;
	int find_result = 0;
	char temp[512];
	char buf[512];
	printf("Aramak istediginiz kitap adini girin: ");
	gets(buf);
	
	if((fp = fopen("booklist.txt", "r")) == NULL) 
	{
	return(-1);
	}

	while(fgets(temp, 512, fp) != NULL) 
	{
		if((strstr(temp, buf)) != NULL) 
		{
			printf("Book ID: %d\n", line_num);
			printf("\n%s\n", temp);
			find_result++;
		}
		line_num++;
	}

	if(find_result == 0) 
	{
		printf("\nUzgunum, eslesme bulunamadi.\n");
	}

	char ch = _getch();
	fclose(fp);
}

void ViewBooks()
{
	system("cls"); //One Hundred Years of Solitude by Gabriel Garcia Marquez
	char singLine[150];
	FILE * fpr;
	int Id=0;
	fpr = fopen("booklist.txt", "r");
		while((fgets(singLine,150,fpr)))
		{
			printf("%d: ", Id);
			puts(singLine);
			Id++;
		}
	printf("\n\t\t----Devam etmek icin bir tusa tiklayiniz.----");
	char ch = _getch();
	fclose(fpr);
}

void ChangePassword()
{
	FILE * fp;
	fp = fopen("usernamepassword.txt", "w");
	char useName[15];
	char pssWord[15];
	printf("Yeni kullanici adini girin:\n"); 
    scanf("%s",&useName); 
    printf("Yeni sifreyi girin:\n"); 
    scanf("%s",&pssWord);
    fprintf(fp,"%s",useName);
    fprintf(fp,"\n");
    fprintf(fp,"%s",pssWord);
    fclose(fp);
    isAuthenticated=0;
}

void IssueBook()
{
	time_t rawtime;
  	struct tm * timeinfo;
  	time ( &rawtime );
  	timeinfo = localtime ( &rawtime );
	FILE * fpy;
	fpy = fopen("issuebook.txt","a");
	char Ad[15];
	char soyAd[15];
	char kitapAdi[15];
	printf("Kitabi alanin adi:\n"); 
    scanf("%s",&Ad); 
    printf("Kitabi alanin soyadi:\n");
    scanf("%s",&soyAd);
    printf("Hangi kitabi aldi:");
    scanf("%s",&kitapAdi);
    system("cls");
    printf("Ismarlama kaydi basariyla olusturuldu.\nAd:%s\nSoyad:%s\nKitap Adi:%s\nAlinan Tarih:%s\n\t\tDevam etmek icin bir tusa basiniz...",Ad,soyAd,kitapAdi,asctime (timeinfo));
    fprintf(fpy,"%s",Ad);
    fprintf(fpy,"\t%s",soyAd);
    fprintf(fpy,"\t%s",kitapAdi);
    fprintf(fpy,"\t%s", asctime (timeinfo) );
    fprintf(fpy,"\n");
    char ch = _getch();
    fclose(fpy);
}
void loginPage()			//Program girişinde açılacak login sayfası.
{
	system("cls");
	int i;
	FILE * fptr;
	fptr = fopen("usernamepassword.txt", "r");
	char singleLine[15];
	char usName[15];
	char psWord[15];

		fgets(singleLine,15,fptr);
		remove_spaces(singleLine,singleLine);
		strcpy(usName,singleLine);

		fgets(singleLine,15,fptr);
		remove_spaces(singleLine,singleLine);
		strcpy(psWord,singleLine);

	fclose(fptr);
	
	printf("Kullanici adinizi giriniz:\n"); 
    scanf("%s",&username); 
    printf("Sifreyi giriniz:\n"); 
    scanf("%s",&password);
    if(strcmp(username,usName)==0)
	{ 
        if(strcmp(password,psWord)==0)
		{ 
			isAuthenticated = 1;
		}
		else
		{ 
    		printf("\nYanlis sifre\n"); 
		} 
    }
	else
	{ 
    printf("\nBoyle bir kullanici bulunamadi\n");
	}
}

void bookadd(){
	system("cls");
	FILE*fptr;
	fptr=fopen("booklist.txt","a");
	char bookname[MAX];
	printf("Eklemek istediginiz kitabi giriniz: \n");
	scanf("%s", bookname);
	fprintf(fptr,"%s\n",bookname);
	fclose(fptr);
}
void deletebook()
{
int lno, ctr = 0;
    char ch;
    FILE *fptr1, *fptr2;
	char fname[MAX];
    char str[MAX], temp[] = "temp.txt";
	ViewBooks();
	printf("\n\n ID ile kitap silme(ILK SATIRDAKI KITAP ID=0,IKINCI SATIR ID=1...) :\n");
	printf("-----------------------------------------\n"); 		
    fptr1 = fopen("booklist.txt", "r");
        if (!fptr1) 
		{
            printf(" Dosya bulunamadi!!\n");
            return;
        }
        fptr2 = fopen(temp, "w"); // open the temporary file in write mode 
        if (!fptr2) 
		{
            printf("Okunacak temp dosyasi acilamadi.!!\n");
            fclose(fptr1);
            return;
        }
        printf(" Silmek istediginiz kitabin ID'sini giriniz : ");
        scanf("%d", &lno);
		lno++;
        // Silinen satir haric dosyadaki tum icerigi baska dosyaya kopyalama
        fflush(stdin);
		while (!feof(fptr1)) 
        {
            strcpy(str, "\0");
            fgets(str, MAX, fptr1);
            if (!feof(fptr1)) 
            {
                ctr++;
                //Verilen satir sayisini atlama
                if (ctr != lno) 
                {
                    fprintf(fptr2, "%s", str);
                }
            }
        }
        fclose(fptr1);
        fclose(fptr2);
        remove("booklist.txt");  		// orijinal dosyanin silinmesi
        rename(temp, "booklist.txt"); 	// gecici acilan dosyanin yine kendi dosyamizin adina donusmesi.
//Bu dosyayi okutup,yeni halini gostermek
   fptr1=fopen("booklist.txt","r"); 
            ch=fgetc(fptr1); 
          printf(" Dosyanin yeni icerigi : \n"); 
          while(ch!=EOF) 
            { 
                printf("%c",ch); 
                 ch=fgetc(fptr1); 
            }
        char cz = _getch();
		fclose(fptr1);      
    }

void GirisSayfasi() //Bu ana menümüz
{
	
	char* welcome= "\t\t\t\t\t************ HOSGELDIN KUTUPHANECI ************\n\n\t\t>>Lutfen bir secenegi sec:\n\n\t\t1.Kitap Listesini Goster\n\n\t\t2.Kitap Ara\n\n\t\t3.Kitap Ekle\n\n\t\t4.Kitap Sil\n\n\t\t5.Ismarlanacak Kitap Kaydi\n\n\t\t6.Oturum Kapat\n\n\t\t7.Sifreyi Degistir\n\n\t\t8.Uygulamayi Kapat\n\n\t\tSeciminizi giriniz(1-8) :";
	printf("%s", welcome);
	
}


int main(int argc, char *argv[]) 
{
	while(1)
	{
	
	while(isAuthenticated == 0)
		{
	loginPage();
		}
		system("cls");
		int input;    
		GirisSayfasi();
		scanf("%d", &input);
		switch(input)
		{
		case 1:
			ViewBooks();
			break;
		case 2:
			Search_in_File();
			break;
		case 3:
			bookadd();
			break;
		case 4:
			deletebook();
			break;	
		case 5:
			system("cls");
			IssueBook();
			break;
		case 6:
			isAuthenticated=0;
			break;
		case 7:
			ChangePassword();
			break;
		case 8:
			exit(0);
			break;
		default:
			printf("Lutfen 1-7 arasindan secim yapiniz.");
		}
	}
	return 0;
}
