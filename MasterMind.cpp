#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

int code1[5],code2[5];
char joueur[15];
int niveau,bp,mp,tentatives,i,j;
int joker=1,position,choix;
int score=0,choixMenu;

  void Color(int couleurDuTexte,int couleurDeFond){ // fonction d'affichage de couleurs
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
   }

  void validation(int code[5]) {
    _Bool distinct;
    printf("\n\n   Veuillez proposer un code de 5 chiffres distincts : ");
    do {
        for (i=0 ; i<5 ; i++) {
            scanf("%1d",&code[i]); }
        distinct=1;
        for (i=0 ; i<4 ; i++) {
            for (j=i+1 ; j<5 ; j++) {
                if (code[i]==code[j])
                    distinct=0; } }
        if(!distinct){
             Color(4,15);
             printf("\n   Les chiffres doivent etre distincts.");
             Color(0,15);
             printf("\n   Reessayez : "); }
    } while(!distinct); // la boucle se repete jusqu'a les chiffres sont distincts
  }

  void choixjoker(){
    if (tentatives>=10 && tentatives<=17 && joker>0) {
         Color(5,15);
         printf("                                            OPTION JOKER");
         Color(0,15);
         printf("\n  Voulez vous utiliser le joker? (1.Oui 2.Non) : ");
         scanf("%d",&choix);
            if (choix==1) {
                printf("  Choisir la position de chiffre (1-5) : ");
                scanf("%d", &position);
                printf("  Le chiffre dans la position %d est: %1d\n",position,code1[position-1]);
                joker-- ;
                tentatives=tentatives+3 ; // Perte de 3 tentetives
            } }
  }

  void placement(){
    int codetemp1[5], codetemp2[5];
    bp=0;
    mp=0;
    // Copier le contenu du code1 et code2 dans les codes temporaires pour eviter le changement de leurs valeurs
    for (i=0 ; i<5 ; i++) {
        codetemp1[i]=code1[i];
        codetemp2[i]=code2[i]; }
   // Verification des mal places et bien places
    for (i = 0; i < 5; i++) {
        if (codetemp1[i]==codetemp2[i]) {
            bp = bp + 1;
            // Marker le chiffre dans les 2 codes temporaires
            codetemp1[i] = -1;
            codetemp2[i] = -1; } }
    for (i=0 ; i<5 ; i++) {
        for (j=0 ; j<5 ; j++) {
            if (codetemp1[i]==codetemp2[j] && codetemp1[i]!=-1 && codetemp2[j]!=-1) {
                mp = mp + 1;
                // Marker le chiffre dans les 2 codes temporaires
                codetemp1[i] = -1;
                codetemp2[j] = -1;
                break; } } }
    Color(2,15);
    printf("\n %d Bien places\n", bp);
    Color(4,15);
    printf(" %d Mal places\n", mp);
  }

  void tentative(){
    tentatives=0;
    do {
    choixjoker();
    Color(0,15);
    printf("\n  Tentative %d: Trouver le code de 5 chiffres : ", tentatives+1);
    for (i=0 ; i<5 ; i++)
    scanf("%1d",&code2[i]);
    placement();
    tentatives++ ;
    } while (tentatives<20 && bp<5);
  }

  void sauvegarderscore() {
    FILE *fichier = fopen("scores.txt", "a");// pour faire la mise a jour
    if (fichier == NULL) {
       printf("Erreur lors de l'ouverture du fichier pour la sauvegarde du score.\n"); }
    else {
       fprintf(fichier," %s %d\n",joueur,score);// ecrire dans le fichier
       fclose(fichier);  }
  }

  void afficherscore() {
    FILE *fichier = fopen("scores.txt", "r");// read
    if (fichier == NULL) {
        printf("Aucun score enregistre pour le moment.\n"); }
    else {
        Color(4,15);
        printf("\n\n  Scores enregistres: \n");
            char c;
        do{
            c=fgetc(fichier);
        Color(0,15);
            printf("%c",c);
        }while(c!=EOF);
        fclose(fichier);  }
  }

  void afficherMeilleurScore() {
    FILE *fichier = fopen("scores.txt", "r");
    if (fichier == NULL) {
        printf("Aucun score enregistré pour le moment.\n"); }
    else {
    char meilleurJoueur[15];
    int meilleurScore = 20; // Initialisé à une valeur très élevée pour trouver le minimum

    while (fscanf(fichier," %s %d", joueur, &score) != EOF) {
        if (score <= meilleurScore) {
            meilleurScore = score;
            strcpy(meilleurJoueur, joueur);
        }
    }

    fclose(fichier);

    Color(4,15);
    printf("\n  Meilleur score : \n");
    Color(0,15);
    printf(" %s %d\n", meilleurJoueur, meilleurScore); }
  }

int main() {
    do{
    Color(5,15);
    system("CLS");

    printf("\n\n\n");
    printf("                                             ______________________________\n");
    printf("                                            |                              |\n");
    printf("                                            |  BIENVENUE SUR MASTERMIND !  |\n");
    printf("                                            |______________________________|\n\n\n\n");


    Color(0,15);
    printf("  Choisir le niveau :");
    Color(5,15);
    printf("\n [1] ");
    Color(0,15);
    printf("DEBUTANT");
    Color(5,15);
    printf("\n [2] ");
    Color(0,15);
    printf("EXPERT\n");
    scanf("%d", &niveau);
    system("CLS");

    if (niveau==1){

        validation(code1);
        system("CLS");

        printf("\n\n   Entrez votre nom: ");
        scanf("%s",joueur);

        system("CLS");
        tentative();
        }
    else if (niveau==2){

        printf("\n\n   Veuillez proposer un code de 5 chiffres : ");
        for (i=0;i<5;i++) {
            scanf("%1d",&code1[i]);}
        system("CLS");

        printf("\n\n   Entrez votre nom : ");
        scanf("%s",joueur);

        system("CLS");
        tentative();
        }

                      system("CLS");

    if (tentatives==20) {
        Color(4,15);
        printf("\n                                            GAME OVER!\n");
        Color(0,15);
        printf("  le code etait: ");
        for (i=0;i<5;i++)
          printf("%1d",code1[i]);
        }
    if (tentatives==17 && joker==0) {
        Color(4,15);
        printf("\n                                            GAME OVER!\n");
        Color(0,15);
        printf("  le code etait: ");
        for (i=0;i<5;i++)
          printf("%1d",code1[i]);
        }
    else if (bp==5){
        Color(2,15);
        printf("\n Felicitation %s!",joueur);
        Color(0,15);
        printf(" vous avez trouver le code");
        }

    score = tentatives; // Maj du score du joueur
    sauvegarderscore();
    afficherscore();
    afficherMeilleurScore();

        Color(5,15);
        printf("\n\n                                                      [1] ");
        Color(0,15);
        printf("Rejouer\n");
        Color(5,15);
        printf("                                                      [2] ");
        Color(0,15);
        printf("Quitter\n");
        scanf("%d", &choixMenu);

        switch (choixMenu) {
            case 1:
                // Redémarrez le jeu
                break;
            case 2:
                exit(0); // Quittez le jeu
                break;
            default:
               printf("\n Choix invalide.\n");
        }

    } while (choixMenu==1);

return 0;
}
