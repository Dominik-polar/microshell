#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

char *get_current_dir_name(void);
int chdir(const char *);   

int main()
{
	char *login=getlogin();           /*pobieram z funkcji getlogin, login obecnego uzytkownika*/
	int b;
	int y;		
    char home[256];
	int a;
	int tilde;
	int exit=0;          
	char commend[256];
	char *args[256]; 
	printf("Witaj w moim microshellu! \nJezeli potrzebujesz pomocy napisz help\n");
	do
		{
		b=0;                 
		a=0;
		for(b=0;b<256;b++)                /*ustawia wszystkie args na null*/
		{
         		args[b]=NULL;
		}
	printf("[\x1B[36m");       /*ustawianie kolorow loginu oraz sciezki*/
	printf("%s",login);       /*funkcja zwaracajaca login*/
	printf("\x1B[0m:");
	printf("\x1B[31m");
	printf("%s", get_current_dir_name());    /*funkcja zwracajaca obecna sciezke*/
	printf("\x1B[0m]\n$");

	scanf(" %255[^\r\n]", commend);        /*skanowanie wartosci jakie poda uzytkownik do 255 znakow*/
	args[a]= strtok(commend, " ");    /*funkcja ktora dzieli string podany przez uzytkownika po spacjach na args*/
	while(args[a]!=NULL) 
	{
	  	a++; 
      		args[a]= strtok(NULL, " ");
	}

	int i=strcmp(args[0],"help");          /*porownywanie wpisanego slowa z commendmi*/
	int k=strcmp(args[0],"exit");          
	int j=strcmp(args[0],"cd");   
	if((i==0)&&(args[1]==NULL))            /*sprawdzenie czy uzytkownik wpisal help*/
	{
		printf("Komendy ktore mozesz wykonac:\ncd  - bez sciezki, ~, .., path\nexit\noraz komendy za pomoca fork+exec\nWykonal Dominik Polarczyk\n");
	}
	else if((k==0)&&(args[1]==NULL))       /*sprawdzenie czy uzytkownik chce wyjsc z microshella*/
	{
		printf("Nastapilo wylaczenie Microshella\n");
		exit=1;                             /*zmienna porownywana w while zmieniona*/
	}
	else if((j==0)&&(args[2]==NULL))        /*sprawdzenie czy uzytkownik wpisal cd z dobrymi parametrami czyli cd /path*/
	{
        	if(args[1]==NULL)              /*jezeli wpisano cd bez argumentow to przenosi do katalogu domowego*/
        	{
                	for(y=0; y<256; y++)
                	{
                		home[y]='\0';
                	}
                	strcpy(home,"/home/");
			strcat(home,login);
			chdir(home);
		}
        	else                               
			{
                        tilde=strcmp(args[1],"~");  /*jezeli wpisane cd ~ to przenosi do katalogu domowego*/
	                if(tilde==0)
	        	{
                	for(y=0; y<256; y++)
                	{
                	home[y]='\0';
                	}
                	strcpy(home,"/home/");
			strcat(home,login);
			chdir(home);	
			}	
		else                
		{
            /*funkcja zmieniajaca katalog roboczy na wypisany w argumencie */
			if(chdir(args[1])==-1) 
			{
                		char *path=get_current_dir_name();          /*jezeli path zostala podana bez / to sprawdza czy dodajac do argumentu reszte obecnej sciezki dalej poda blad*/
                		strcat(path,args[1]);
                		if(chdir(path)==-1)
                		{
				printf("Podales bledna sciezke\n");
        	        	}
        		}
		}
}
}
else if((j!=0)||(args[1]!=NULL))         /*jezeli wpisana commend nie jest help,cd oraz exit wykonuje fork+execlp*/
{
pid_t pid=fork();
int status;
if(pid==0)
{
if(execlp(args[0],args[0],args[1],args[2],args[3],args[4],args[5],args[6],args[7],args[8],args[9],args[10],args[11],args[12],args[13],args[14],args[15],args[16],args[17],args[18],args[19],args[20],NULL)==-1) printf("Nierozpoznana commend\n");      /*jezeli execlp nie moze sie wykonac (podano zla komende ktora exec nie moze znalezc w bin) to wychodzi z procesu-dziecka*/
return 1;
}
waitpid(pid, &status, 0);            /*czeka na wykonanie procesu dziecka*/
}  
}
while(exit==0);
return 0;
}





