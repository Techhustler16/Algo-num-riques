#include <stdio.h>
#include <math.h>

/*
   Définition de la fonction f(x) = x^3 - x - 2
   On cherche à résoudre f(x) = 0
 */
 
double fonction_equation(double x) {
    return x*x*x - x - 2;
}

/* 
   Définition de la fonction de substitution g(x)
   Réécriture : x = cbrt(x + 2)
   => g(x) = racine cubique de (x+2)
*/
double fonction_substitution(double x) {
    return cbrt(x + 2); // cbrt = racine cubique
}

/* -----------------------------------------------------------
   Définition de la dérivée de g(x)
   g(x) = (x+2)^(1/3)
   g'(x) = 1 / (3 * (x+2)^(2/3))
------------------------------------------------------------ */
double derivee_fonction_substitution(double x) {
    return 1.0 / (3.0 * pow(x + 2, 2.0/3.0));
}

/* -----------------------------------------------------------
   Méthode du point fixe (substitution)
------------------------------------------------------------ */
void methode_point_fixe(double valeur_initiale, double tolerance, int nombre_iterations_max) {
    double valeur_actuelle = valeur_initiale;
    double valeur_suivante;
    int compteur_iterations = 0;

    /* Boucle d’itération */
    do {
        valeur_suivante = fonction_substitution(valeur_actuelle);
        compteur_iterations++;

        printf("Iteration %d : x = %.5f, f(x) = %.5f\n",
               compteur_iterations, valeur_suivante, fonction_equation(valeur_suivante));

        /* Critère d’arrêt */
        if (fabs(valeur_suivante - valeur_actuelle) < tolerance ||
            fabs(fonction_equation(valeur_suivante)) < tolerance) {
            printf(" Solution approche : %.5f obtenue en %d iterations\n",
                   valeur_suivante, compteur_iterations);
            return;
        }

        valeur_actuelle = valeur_suivante;

    } while (compteur_iterations < nombre_iterations_max);

    printf("❌ Pas de convergence après %d iterations.\n", nombre_iterations_max);
}

/* -----------------------------------------------------------
   Fonction principale main()
   - Demande les paramètres à l’utilisateur
   - Vérifie l’intervalle jusqu’à ce qu’il soit correct
------------------------------------------------------------ */
int main() {
    double valeur_initiale, borne_inferieure, borne_superieure, tolerance;
    int nombre_iterations_max;

    printf("=== Resolution par la methode du point fixe ===\n");
    printf("Equation : f(x) = x^3 - x - 2\n");
    printf("Substitution : g(x) = racine cubique de (x+2)\n\n");

    /* Saisie de la valeur initiale */
    printf("Entrer la valeur initiale x0 : ");
    scanf("%lf", &valeur_initiale);

    /* Boucle pour demander un intervalle valide */
    int intervalle_valide = 0;
    do {
        printf("Entrer la borne inferieure de votre intervalle : ");
        scanf("%lf", &borne_inferieure);

        printf("Entrer la borne superieure de votre intervalle : ");
        scanf("%lf", &borne_superieure);

        /* Vérification de l’invariance */
        if (fonction_substitution(borne_inferieure) < borne_inferieure ||
            fonction_substitution(borne_superieure) > borne_superieure) {
            printf("⚠️ Intervalle invalide : g(x) ne reste pas dans [a,b]. Ressaisissez.\n");
            continue;
        }

        /* Vérification de la condition de convergence */
        double derivee_test = derivee_fonction_substitution(valeur_initiale);
        if (fabs(derivee_test) >= 1) {
            printf("⚠️ Intervalle invalide : condition |g'(x)| < 1 non respectée. Ressaisissez.\n");
            continue;
        }

        /* Si les deux conditions sont respectées */
        intervalle_valide = 1;

    } while (!intervalle_valide);

    /* Saisie des autres paramètres */
    printf("Entrer la tolerance (ex: 1e-6) : ");
    scanf("%lf", &tolerance);

    printf("Entrer le nombre maximum iterations : ");
    scanf("%d", &nombre_iterations_max);

    /* Appel de la méthode du point fixe */
    methode_point_fixe(valeur_initiale, tolerance, nombre_iterations_max);

    return 0;
}
