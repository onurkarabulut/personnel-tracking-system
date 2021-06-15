// Onur Karabulut

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define boyut sizeof(struct Personel)
struct Personel
{
    char bilgi;
    char personel_ismi [20];
    char departman_ismi[20];
    char baslama_tarihi[20];
    double maas;
    int personel_id;
};


void kayit_ekle(FILE *fl)
{
    fl=fopen("personel.txt","r+");
    system("cls");
    int say;
    fseek(fl,sizeof(say),SEEK_SET);// bu kısımda kisi sayısı bilgimizi textten okuyarak say degiskenine atıyoruz
    fread(&say,sizeof(say),1,fl);
    struct Personel calisan;
    struct Personel kontrol;
    for(int i=1;i<(say+1);i++){//for say degiskeni kadar dönerek listedeki tüm bos verileri kontrol ediyoruz
        fseek(fl,i*boyut,SEEK_SET);//kisi say kadar olusturulan her veriyi okumak için imleci ilerletiyoruz
        fread(&calisan,boyut,1,fl);//
        if(calisan.bilgi=='F'){//bilgi kısmı F olan yani bos olan ilk veriyi bularak yeni bilgileri kullanıcıdan aldıyoruz ve dosyada bulduðumuz ilk bos yere yazdırıyoruz
            printf("\n\tIsim : ");
            scanf("%s",&calisan.personel_ismi);
            printf("\n\tDepartman Ismi : ");
            scanf("%s",&calisan.departman_ismi);
            printf("\n\tTarih : ");
            scanf("%s",&calisan.baslama_tarihi);
            printf("\n\tMaas : ");
            scanf("%lf",&calisan.maas);
            calisan.bilgi='T'; // eklediğimiz verinin bilgi kısmını T yaparak aktif veri haline getiriyoruz
            for(int j=1;j<(say+1);j++){
                fseek(fl,j*boyut,SEEK_SET);//kisi sayısı kadar olusturulan her veriyi okumak için imleci ilerlettik
                fread(&kontrol,boyut,1,fl);
                if(kontrol.bilgi=='T'){
                    if(kontrol.maas==calisan.maas){
                            if(strcmp(kontrol.personel_ismi,calisan.personel_ismi)==0){
                                if(strcmp(kontrol.baslama_tarihi,calisan.baslama_tarihi)==0){
                                    if(strcmp(kontrol.departman_ismi,calisan.departman_ismi)==0){
                                            printf("GIRDIGINIZ KISI MEVCUT LUTFEN YENI KISI EKLEYINIZ");
                                            getch();
                                            kayit_ekle(fl);
                }}}}}}

            fseek(fl,i*boyut,SEEK_SET);
            fwrite(&calisan,boyut,1,fl);
            printf("\nKAYIT TAMAMLANDI..");
            getch();
            fclose(fl);
        }}}


void listele(FILE *fl)
{
    fl=fopen("personel.txt","r");
    int say;
    fseek(fl,sizeof(say),SEEK_SET);
    fread(&say,sizeof(say),1,fl);
    struct Personel calisan;
    system("cls");
    printf("\n%5s%10s%20s%20s%10s\n","ID","ISIM","DEPARTMAN","TARIH","MAAS");
    for(int i=1;i<(say+1);i++){
        fseek(fl,i*boyut,SEEK_SET);
        fread(&calisan,boyut,1,fl);
        if(calisan.bilgi=='T'){
            printf("\n%5d%10s%20s%20s%10.lf TL\n",calisan.personel_id,calisan.personel_ismi,calisan.departman_ismi,calisan.baslama_tarihi,calisan.maas);
        }}
    fclose(fl);
    getch();
}


void menuY(FILE *fl){
    while(1!=2){
        int secim;
        system("cls");
        printf("\n\tYENI KAYIT ICIN - 1\n\tLISTELEME ICIN - 2\n\tARAMA ICIN - 3\n\tGUNCELLEME ICIN - 4\n\tSILME ICIN - 5\n\tKISI SAYISINI ARTTIRMAK ICIN - 6\n\tCIKIS ICIN - 7\n\tLUTFEN SECIMINIZI GIRINIZ :");
        scanf("%d",&secim);
        switch(secim){
            case 1:{kayit_ekle(fl); break;}
            case 2:{listele(fl); break;}
            case 3:{aramenu(fl); break;}
            case 4:{guncelle(fl);break;}
            case 5:{kayitsil(fl);break;}
            case 6:{alangenislet(fl);break;}
            case 7:{exit(1);;break;}
            default:{}
        }}}


void menuK(FILE *fl){
    while(1!=2){
        int secim;
        system("cls");
        printf("\n\tARAMA ISLEMI ICIN - 1\n\tLUTFEN SECIM YAPINIZ");
        scanf("%d",&secim);
        switch(secim){
            case 1:{aramenu(fl);;break;}
            default:{};
        }}}


void kayitsil(FILE *fl)
{
    fl=fopen("personel.txt","r+");
    struct Personel calisan;
    int id;
    char sil;
    system("cls");
    int say;
    int kisikontrol=0;
    fseek(fl,sizeof(say),SEEK_SET);
    fread(&say,sizeof(say),1,fl);
    printf("\n\tSILINECEK KISININ IDSINI GIRINIZ :");
    scanf("%d",&id);
    for(int i=1;i<(say+1);i++){
        fseek(fl,i*boyut,SEEK_SET);
        fread(&calisan,boyut,1,fl);
        if(calisan.bilgi=='T'){
            if(calisan.personel_id==id){
                printf("\n\tSILINECEK KISI BULUNDU");
                printf("\n%5s%10s%20s%20s%10s\n","ID","ISIM","DEPARTMAN","TARIH","MAAS");
                printf("\n%5d%10s%20s%20s%10.lf TL\n",calisan.personel_id,calisan.personel_ismi,calisan.departman_ismi,calisan.baslama_tarihi,calisan.maas);
                printf("\nBU KULLANICI SILMEK ISTIYORMUSUNUZ E veya H");
                sil=getch();
                if(sil=='E' || sil=='e'){
                    calisan.bilgi='F';
                    fseek(fl,i*boyut,SEEK_SET);
                    fwrite(&calisan,boyut,1,fl);
                    printf("\n\tKULLANICI SILINDI..");
                    getch();
                }
                else if(sil=='H' || sil=='h'){
                    printf("\n\tKULLANICI SILINMEDI..");
                    exit(1);
                }
                else{
                    printf("\n\tYANLIS KARAKTER TUSLADINIZ..");
                }}
            else{
            kisikontrol+=1;
            }
        }
        else{
            kisikontrol+=1;
        }}
    if(kisikontrol==say){
        printf("\n\tARANAN KISI BULUNAMADI");
    }
    fclose(fl);
    getch();
}


void aramenu(FILE *fl){
    while(1!=2){
        int secim;
        system("cls");
        printf("\n\tISME GORE ARAMA ISLEMI ICIN -1\n\tDEPARTMANA GORE ARAMA ICIN -2\n\tID'YE GORE ARAMA ICIN -3\n\tMAASA GORE ARAMA ICIN -4\n\tLUTFEN SECIM YAPINIZ");
        scanf("%d",&secim);
        switch(secim){
            case 1:{isimara(fl);break;}
            case 2:{depara(fl);break;}
            case 3:{idara(fl);break;}
            case 4:{maasara(fl);break;}
            default:{};
        }}}


void isimara(FILE *fl){
    fl=fopen("personel.txt","r");
    int say;
    fseek(fl,sizeof(say),SEEK_SET);
    fread(&say,sizeof(say),1,fl);
    struct Personel calisan;
    system("cls");
    char isim[20];
    int kisikontrol=0;
    printf("\n\tARANACAK ISMI GIRINIZ : ");
    scanf("%s",&isim);
    for(int i=1;i<(say+1);i++){
        fseek(fl,i*boyut,SEEK_SET);
        fread(&calisan,boyut,1,fl);
        if(calisan.bilgi=='T'){
            if(strcmp(calisan.personel_ismi,isim)==0){
                printf("\n\tARANAN KISI BULUNDU\n");
                printf("\n%5s%10s%20s%20s%10s\n","ID","ISIM","DEPARTMAN","TARIH","MAAS");
                printf("\n%5d%10s%20s%20s%10.lf TL\n",calisan.personel_id,calisan.personel_ismi,calisan.departman_ismi,calisan.baslama_tarihi,calisan.maas);
            }
            else{
                kisikontrol+=1;
            }}
        else{
            kisikontrol+=1;
        }}
    if(kisikontrol==say){
        printf("\n\tARANAN KISI BULUNAMADI");
    }
    fclose(fl);
    getch();
}


void depara(FILE *fl){
    fl=fopen("personel.txt","r");
    int say;
    fseek(fl,sizeof(say),SEEK_SET);
    fread(&say,sizeof(say),1,fl);
    struct Personel calisan;
    system("cls");
    char dep[20];
    int kisikontrol=0;
    printf("\n\tARANACAK DEPARTMAN ISMI GIRINIZ : ");
    scanf("%s",&dep);
    for(int i=1;i<(say+1);i++){
        fseek(fl,i*boyut,SEEK_SET);
        fread(&calisan,boyut,1,fl);
        if(calisan.bilgi=='T'){
            if(strcmp(calisan.departman_ismi,dep)==0){
                printf("\n\tARANAN DEPARTMANDA CALISANLAR BULUNDU\n");
                printf("\n%5s%10s%20s%20s%10s\n","ID","ISIM","DEPARTMAN","TARIH","MAAS");
                printf("\n%5d%10s%20s%20s%10.lf TL\n",calisan.personel_id,calisan.personel_ismi,calisan.departman_ismi,calisan.baslama_tarihi,calisan.maas);
            }
            else{
                kisikontrol+=1;
            }}
        else{
            kisikontrol+=1;
        }}
    if(kisikontrol==say){
        printf("\n\tARANAN DEPARTMAN BULUNAMADI");
    }
    fclose(fl);
    getch();
}


void idara(FILE *fl){
    fl=fopen("personel.txt","r");
    int say;
    fseek(fl,sizeof(say),SEEK_SET);
    fread(&say,sizeof(say),1,fl);
    struct Personel calisan;
    system("cls");
    int id;
    int kisikontrol=0;
    printf("\n\tARANACAK IDYI GIRINIZ : ");
    scanf("%d",&id);
    for(int i=1;i<(say+1);i++){
        fseek(fl,i*boyut,SEEK_SET);
        fread(&calisan,boyut,1,fl);
        if(calisan.bilgi=='T'){
            if(calisan.personel_id==id){
                printf("\n\tARANAN ID'YE SAHIP  CALISAN BULUNDU\n");
                printf("\n%5s%10s%20s%20s%10s\n","ID","ISIM","DEPARTMAN","TARIH","MAAS");
                printf("\n%5d%10s%20s%20s%10.lf TL\n",calisan.personel_id,calisan.personel_ismi,calisan.departman_ismi,calisan.baslama_tarihi,calisan.maas);
            }
            else{
                kisikontrol+=1;
            }}
        else{
            kisikontrol+=1;
        }}
    if(kisikontrol==say){
        printf("\n\tARANAN DEPARTMAN BULUNAMADI");
    }
    fclose(fl);
    getch();
}


void maasara(FILE *fl){
    fl=fopen("personel.txt","r");
    int say;
    fseek(fl,sizeof(say),SEEK_SET);
    fread(&say,sizeof(say),1,fl);
    struct Personel calisan;
    system("cls");
    int maas;
    int kisikontrol=0;
    printf("\n\tARANACAK MAASI GIRINIZ : ");
    scanf("%d",&maas);
    for(int i=1;i<(say+1);i++){
        fseek(fl,i*boyut,SEEK_SET);
        fread(&calisan,boyut,1,fl);
        if(calisan.bilgi=='T'){
            if(calisan.maas==maas){
                printf("\n\tARANAN MAASI ALAN CALISANLAR BULUNDU\n");
                printf("\n%5s%10s%20s%20s%10s\n","ID","ISIM","DEPARTMAN","TARIH","MAAS");
                printf("\n%5d%10s%20s%20s%10.lf TL\n",calisan.personel_id,calisan.personel_ismi,calisan.departman_ismi,calisan.baslama_tarihi,calisan.maas);
            }
            else{
                kisikontrol+=1;
            }}
        else{
            kisikontrol+=1;
        }}
    if(kisikontrol==say){
        printf("\n\tARANAN MAASI ALAN CALISAN BULUNAMADI");
    }
    fclose(fl);
    getch();
}


void guncelle(FILE *fl){
    fl=fopen("personel.txt","r+");
    int say;
    fseek(fl,sizeof(say),SEEK_SET);
    fread(&say,sizeof(say),1,fl);
    struct Personel calisan;
    system("cls");
    int id;
    int kisikontrol;
    char gun;
    printf("\n\tGUNCELLEMEK ISTEDIGINIZ KISININ ID'SINI GIRINIZ :");
    scanf("%d",&id);
    for(int i=1;i<(say+1);i++){
        fseek(fl,i*boyut,SEEK_SET);
        fread(&calisan,boyut,1,fl);
        if(calisan.bilgi=='T'){ z
                if(calisan.personel_id==id){
                printf("\n\tGUNCELLEMEK ISTEDIGINIZ KULLANICININ BILGILERI");
                printf("\n%5s%10s%20s%20s%10s\n","ID","ISIM","DEPARTMAN","TARIH","MAAS");
                printf("\n%5d%10s%20s%20s%10.lf TL\n",calisan.personel_id,calisan.personel_ismi,calisan.departman_ismi,calisan.baslama_tarihi,calisan.maas);
                printf("\n\tBU KULLANICI SILMEK ISTIYORMUSUNUZ E veya H");
                gun=getch();
                if(gun=='E' || gun=='e'){
                    printf("\n\tYENI KULLANICI BILGILERINI GIRINIZ");
                    printf("\n\tIsim : ");
                    scanf("%s",&calisan.personel_ismi);
                    printf("\n\tDepartman Ismi : ");
                    scanf("%s",&calisan.departman_ismi);
                    printf("\n\tTarih : ");
                    scanf("%s",&calisan.baslama_tarihi);
                    printf("\n\tMaas : ");
                    scanf("%d",&calisan.maas);
                    fseek(fl,i*boyut,SEEK_SET);
                    fwrite(&calisan,boyut,1,fl);
                    printf("\n\tKULLANICI GUNCELLENDI..");
                    getch();
                }
                else if(gun=='H' || gun=='h'){
                    printf("\n\tKULLANICI GUNCELLENEMDI..");
                    exit(1);
                }
                else{
                    printf("\n\tYANLIS KARAKTER TUSLADINIZ..");
                }
                getch();
            }
            else{
                kisikontrol+=1;
            }}
        else{
            kisikontrol+=1;
        }}
    if(kisikontrol==say){
        printf("\n\tARANAN DEPARTMAN BULUNAMADI");
    }
    fclose(fl);
    getch();
}


void alangenislet(FILE *fl){
    fl=fopen("personel.txt","r+");
    struct Personel calisan={'F',"","","",0.0,0};//
    int say;
    fseek(fl,sizeof(say),SEEK_SET);
    fread(&say,sizeof(say),1,fl);
    int yenisay;
    system("cls");
    printf("\n\tYUKSELTMEK ISTEDIGINIZ YENI KISI SAYISINI GIRINIZ : ");
    scanf("%d",&yenisay);
    if(yenisay<say){
        printf("\n\tGIRDIGINIZ SAYI MEVCUT SAYIDAN KUCUK OLAMAZ");
        getch();
        exit(1);
    }
    fseek(fl,sizeof(say),SEEK_SET);
    fwrite(&yenisay,sizeof(yenisay),1,fl);
    for(int i=(say+1);i<(yenisay+1);i++){
        fseek(fl,i*boyut,SEEK_SET);
        calisan.personel_id=i;
        fwrite(&calisan,boyut,1,fl);
    }
    fclose(fl);
}


void main (void)
{
    FILE *fl;
    int say;
    struct Personel calisan={'F',"","","",0.0,0};
    if((fl=fopen("personel.txt","r+"))==NULL){
        fl=fopen("personel.txt","w+");
        fclose(fl);
        printf("\n\tPERSONEL SAYISINI GIRINIZ : ");
        scanf("%d",&say);
        fl=fopen("personel.txt","r+");
        fseek(fl,sizeof(say),SEEK_SET);
        fwrite(&say,sizeof(say),1,fl);
        for(int i=1;i<(say+1);i++){
            printf("%d",i);
            calisan.personel_id=i;
            fseek(fl,i*boyut,SEEK_SET);
            fwrite(&calisan,boyut,1,fl);
            }
        fclose(fl);
    }
    while(1!=2){//kullanıcı ve yönetici icin 2 arayüz var
        int sec;
        system("cls");
        printf("\n\tYONETICI ICIN -1\n\tKULLANICI ICIN -2\n\tLUTFEN SECIM YAPINIZ :");
        scanf("%d",&sec);
        switch(sec){
            case 1:{menuY(fl);break;}
            case 2:{menuK(fl);break;}
            default:{}
        }}}