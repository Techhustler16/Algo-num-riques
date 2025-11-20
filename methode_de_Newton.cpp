#include <stdio.h>
#include <math.h>

/* -----------------------------------------------------------
   Définition de la fonction f(x) = x^3 - x - 2
   On cherche à résoudre f(x) = 0
   (Tu peux modifier cette fonction selon ton problème)
------------------------------------------------------------ */
double fonction_equation(double x) {
    return x*x*x - x - 2;
}

/* Définition de la dérivée f'(x)
   f(x) = x^3 - x - 2
   => f'(x) = 3x^2 - 1
 */
double derivee_fonction_equation(double x) {
    return 3*x*x - 1;
}

/*
   Méthode de Newton-Raphson
   Paramètres :
   - valeur_initiale : point de départ x0
   - tolerance : précision souhaitée
   - nombre_iterations_max : sécurité pour éviter boucle infinie
*/
void methode_newton(double valeur_initiale, double tolerance, int nombre_iterations_max) {
    double valeur_actuelle = valeur_initiale;
    double valeur_suivante;
    int compteur_iterations = 0;

    /* Boucle d’itération */
    do {
        double f_val = fonction_equation(valeur_actuelle);
        double f_der = derivee_fonction_equation(valeur_actuelle);

        /* Vérification : dérivée non nulle */
        if (fabs(f_der) < 1e-12) {
            printf("Erreur : la derivee est trop proche de zero en x = %.5f.\n", valeur_actuelle);
            return;
        }

        /* Formule de Newton-Raphson */
        valeur_suivante = valeur_actuelle - f_val / f_der;
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

    printf(" Pas de convergence apres %d iterations.\n", nombre_iterations_max);
}

/* -----------------------------------------------------------
   Fonction principale main()
   - Demande les paramètres à l’utilisateur
   - Lance la méthode de Newton-Raphson
------------------------------------------------------------ */
int main() {
    double valeur_initiale, tolerance;
    int nombre_iterations_max;

    printf("=== Resolution par la methode de Newton-Raphson ===\n");
    printf("Equation : f(x) = x^3 - x - 2\n");
    printf("Derivee : f'(x) = 3x^2 - 1\n\n");

    /* Saisie des paramètres */
    printf("Entrer la valeur initiale x0 : ");
    scanf("%lf", &valeur_initiale);

    printf("Entrer la tolerance (ex: 1e-6) : ");
    scanf("%lf", &tolerance);

    printf("Entrer le nombre maximum iterations : ");
    scanf("%d", &nombre_iterations_max);

    /* Appel de la méthode de Newton-Raphson */
    methode_newton(valeur_initiale, tolerance, nombre_iterations_max);

    return 0;
}
