#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <fcntl.h>
#include <io.h>
int main()
{
    setlocale(LC_CTYPE, "");
    _setmode(_fileno(stdout), _O_U16TEXT);
    char odgovor[2];
    int p=1;
    wchar_t prazna = 0x25CB;
    wchar_t puna = 0x25CF;
    wchar_t red = 0x000A;
    wchar_t tabovi[10][100];
    char slova[100];
    int br;
    wprintf(L"Znas li ti da sviras? (Da/Ne)");
    scanf("%s",odgovor);
    if (strcmp(odgovor,"Ne")==0)
    {
        wprintf(L"Sad ce naucis, ovako se svira skala:\nd  e  f# g  a  b  c# D\n");
        br=8;
        for (int i=0;i<7;i++)
        {
            for (int j=0;j<8;j++)
            {
                if (i+j<6)
                tabovi[i][j]=puna;
                else 
                tabovi[i][j]=prazna;
                if (i==6)
                {
                    if (j<7)
                    tabovi[i][j]=' ';
                    else
                    tabovi[i][j]='+';
                }
                if (j==7 && i<6)
                tabovi[i][j]=puna;
            }
        }
    }
    else if (strcmp(odgovor, "Da")==0)
    {
        wprintf(L"Unesi sekvencu nota koristeci mala i velika slova alfabeta od a-g bez razmaka\n mala slova - 1. oktava\n velika slova - 2. oktava\n");   
        scanf("%s",slova);
        br=strlen(slova);
        for (int i=0;i<br;i++) //validacija
        {
            if ((slova[i]<'A' || ((slova[i]>'G') && slova[i]<'a') || (slova[i]>'g')))
            {
                p=0;
            }
        }
        if (p==0)
        {
            wprintf(L"Nepoznati tonovi");
        }
        else
        {
			for (int i=0;i<br;i++) //stampanje niza tonova sa # ako ih ima
			{
				if ((slova[i]=='F') || (slova[i]=='C') || (slova[i]=='c') || (slova[i]=='f'))
				wprintf(L"%c# ",slova[i]);
				else
				wprintf(L"%c  ",slova[i]);
			}			
			wprintf(L"\n");
        	int note[100];
        	for (int i=0;i<br;i++)
            {
				if ((slova[i]>='A') && (slova[i]<='G')) //pretvaranje velikih slova u mala i popunjavanje vrste za preduvavanje
				{
					tabovi[6][i]='+';
					slova[i]=slova[i]+32;
				}
				else
				{
					tabovi[6][i]=' ';
				}
                if (slova[i]=='a')
                note[i]=2;
                else if (slova[i]=='b')
                note[i]=1;
                else if (slova[i]=='c')
                note[i]=0;
                else if (slova[i]=='d')
                note[i]=6;
                else if (slova[i]=='e')
                note[i]=5;
                else if (slova[i]=='f')
                note[i]=4; 
                else if (slova[i]=='g')
                note[i]=3;
            }
           		for (int j=0;j<br;j++) //popunjavanje matrice
                {
                    for (int i=0;i<6;i++)
                    if (i<note[j])
                    tabovi[i][j]=puna;
                    else
                    tabovi[i][j]=prazna;
                }
    	}
    }
    if ((p==1) && ((strcmp(odgovor,"Da")==0) || (strcmp(odgovor,"Ne")==0)))
    {
        for (int i=0;i<7;i++) // stampanje matrice
        	{
        		for (int j=0;j<br;j++)
            	{
                wprintf(L"%lc  ", tabovi[i][j]);
            	}
        	wprintf(L"\n");
        	}
    }
    return 0;
}
