#include "mbed.h"

#define fech 40000 // Fréquence d'échantillonnage souhaitée
#define TAILLE_BUFFER_SIG (fech/20) // Pour acquisition de 2000 echantillons

extern void Sauve_USB(float *,int ) ;
extern Serial pc ;

/* Entrées sorties */
AnalogIn entree(PF_10); // A5 connecteur Arduino

/* Timer et Ticker */
Ticker read_sample_ticker ;

/* Variables globales */
float moy = 0 ;
float sig_in[TAILLE_BUFFER_SIG] ;

void read_sample() {
    static int i = 0 ;
    sig_in[i] = 3.3f*entree.read(); // Conversion en volts
    i++;
    if (i >= TAILLE_BUFFER_SIG) i = 0;
}

float val_moyenne() {
    int j ;
    float somme ;
    read_sample_ticker.detach(); 
    somme = 0 ;
    ????????????? // Calcul de la somme des échantillons du bloc
    read_sample_ticker.attach_us(&read_sample,1000000/fech); 
    return(???????????) ; // Retour de la valeur moyenne
}

int main()
{
    pc.printf("\033[2J"); // Sequence escape pour effacer la console
    pc.printf("\033[0;0H"); // Curseur en 0 ; 0
    pc.printf("Mesure de valeur moyenne d'un signal analogique sur la broche PF_10(A5)\n");
    pc.printf("Relier le signal externe sur PF_10(A5)\n");
    pc.printf("fech = %d Hz nombre d'echantillon acquis = %d\n",fech,TAILLE_BUFFER_SIG);
    read_sample_ticker.attach_us(&read_sample,1000000/fech); 
    while (1) {
        moy = val_moyenne() ;
        pc.printf("Valeur moyenne du signal sur PF_10(A5) = %10.3f volts\n",moy) ;
        pc.printf("\033[1A"); // Sequence escape qui remonte le curseur de 1 ligne sur la console
        wait(0.2) ; // pause affichage
    }
}
