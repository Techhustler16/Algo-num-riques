
#include <stdio.h>
#include <math.h>

/* -----------------------------------------------------------
   Définition de la fonction h(x) = x - 1/x+1
   On cherche à résoudre f(x) = 0
   (Tu peux modifier cette fonction selon ton problème)
------------------------------------------------------------ */
double fonction_equation(double x)  {
    return (x-1)/(x+1);
}

/* -----------------------------------------------------------
   Méthode dichotomique (bisection)
   Paramètres :
   - borne_inferieure : borne gauche de l’intervalle
   - borne_superieure : borne droite de l’intervalle
   - tolerance : précision souhaitée
   - nombre_iterations_max : sécurité pour éviter boucle infinie
------------------------------------------------------------ */
void methode_dichotomique(double borne_inferieure, double borne_superieure,
                          double tolerance, int nombre_iterations_max) {
    double valeur_milieu;
    int compteur_iterations = 0;

    /* Vérification du changement de signe */
    if (fonction_equation(borne_inferieure) * fonction_equation(borne_superieure) >= 0) {
        printf("Intervalle invalide : f(a) et f(b) doivent avoir des signes contraires.\n");
        return;
    }

    /* Boucle d’itération */
    do {
        valeur_milieu = (borne_inferieure + borne_superieure) / 2.0;
        compteur_iterations++;

        printf("Iteration %d : a = %.5f, b = %.5f, m = %.5f, f(m) = %.5f\n",
               compteur_iterations, borne_inferieure, borne_superieure,
               valeur_milieu, fonction_equation(valeur_milieu));

        /* Vérification du critère d’arrêt */
        if (fabs(fonction_equation(valeur_milieu)) < tolerance ||
            fabs(borne_superieure - borne_inferieure) < tolerance) {
            printf("Solution approchee : %.5f obtenue en %d iterations\n",
                   valeur_milieu, compteur_iterations);
            return;
        }

        /* Réduction de l’intervalle */
        if (fonction_equation(borne_inferieure) * fonction_equation(valeur_milieu) < 0) {
            borne_superieure = valeur_milieu;
        } else {
            borne_inferieure = valeur_milieu;
        }

    } while (compteur_iterations < nombre_iterations_max);

    printf("Attention !!!  Pas de convergence apres %d iterations.\n", nombre_iterations_max);
}

/* -----------------------------------------------------------
   Fonction principale main()
   - Demande les paramètres à l’utilisateur
   - Vérifie l’intervalle jusqu’à ce qu’il soit correct
------------------------------------------------------------ */
int main() {
    double borne_inferieure, borne_superieure, tolerance;
    int nombre_iterations_max;

    printf("=== Resolution par la methode dichotomique ===\n");
    printf("Equation : f(x) = x- 1/x+1\n\n");

    /* Boucle pour demander un intervalle valide */
        printf("Entrer la borne inferieure de votre intervalle : ");
        scanf("%lf", &borne_inferieure);

        printf("Entrer la borne superieure de votre intervalle : ");
        scanf("%lf", &borne_superieure);
    

    /* Saisie des autres paramètres */
    printf("Entrer la tolerance (ex: 1e-6) : ");
    scanf("%lf", &tolerance);

    printf("Entrer le nombre maximum iterations : ");
    scanf("%d", &nombre_iterations_max);
    

    /* Appel de la méthode dichotomique */
    methode_dichotomique(borne_inferieure, borne_superieure, tolerance, nombre_iterations_max);
    return 0;
}
