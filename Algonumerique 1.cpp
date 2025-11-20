#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

// Définition de la fonction f(x) = x³ - 4x + 1
double f(double x) {
    return pow(x, 3) - 4 * x + 1;
}

// Dérivée de f(x) pour Newton-Raphson : f'(x) = 3x² - 4
double df(double x) {
    return 3 * pow(x, 2) - 4;
}

// Fonction de substitution g(x) = (x^3 + 1)/4
double g(double x) {
    return (pow(x, 3) + 1) / 4;
}

// Méthode de Newton-Raphson
void newton_raphson(double x0, double epsilon, int max_iter) {
    printf("\nMethode de Newton-Raphson\n");
    int iter = 0;
    double x = x0;
    double fx = f(x);
    while (fabs(fx) > epsilon && iter < max_iter) {
        double dfx = df(x);
        if (dfx == 0) {
            printf("Derivée nulle. Methode echouee.\n");
            return;
        }
        x = x - fx / dfx;
        fx = f(x);
        iter++;
    }
    if (fabs(fx) <= epsilon) {
        printf("Racine approchee : %.5f\n", x);
        printf("Iterations : %d\n", iter);
        printf("Erreur absolue finale : %.8f\n", fabs(fx));
    } else {
        printf("La methode n'a pas converge.\n");
    }
}

// Méthode de la dichotomie (bisection)
void dichotomie(double a, double b, double epsilon, int max_iter) {
    printf("\nMethode de la dichotomie\n");
    if (f(a) * f(b) >= 0) {
        printf("f(a) et f(b) doivent etre de signes opposes.Intervalle invalide pour la dichotomie\n");
        return;
    }
    int iter = 0;
    double c;
    while ((b - a) / 2 > epsilon && iter < max_iter) {
        c = (a + b) / 2;
        if (f(c) == 0.0) break;
        if (f(a) * f(c) < 0) b = c;
        else a = c;
        iter++;
    }
    c = (a + b) / 2;
    printf("Racine approchee : %.6f\n", c);
    printf("Iterations : %d\n", iter);
    printf("Erreur absolue finale : %.6f\n", fabs(f(c)));
}

// Méthode du point fixe (substitution)
void point_fixe(double x0, double epsilon, int max_iter) {
    printf("\nMethode du point fixe\n");

    int iter = 0;
    double x = x0;
    double x_next = g(x);

    while (fabs(x_next - x) > epsilon && iter < max_iter) {
        x = x_next;
        x_next = g(x);
        iter++;
    }

    if (fabs(x_next - x) <= epsilon) {
        printf("Racine approchee : %.6f\n", x_next);
        printf("Iterations : %d\n", iter);
        printf("Erreur absolue finale : %.6f\n", fabs(f(x_next)));
    } else {
    printf("Erreur : la méthode du point fixe n'a pas converger. Verifiez la fonction g(x) ou l'approximation initiale.\n");

    }
}

// Méthode de la sécante
void secante(double x0, double x1, double epsilon, int max_iter) {
    printf("\nMethode de la secante\n\n");
    int iter = 0;
    double f0 = f(x0), f1 = f(x1);
    double x2;
    while (fabs(f1) > epsilon && iter < max_iter) {
        if (f1 - f0 == 0) {
            printf("Division par zero. Methode echouee.\n");
            return;
        }
        x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
        x0 = x1;
        f0 = f1;
        x1 = x2;
        f1 = f(x1);
        iter++;
    }
    if (fabs(f1) <= epsilon) {
        printf("Racine approchee : %.6f\n", x1);
        printf("Iterations : %d\n", iter);
        printf("Erreur absolue finale : %.6f\n", fabs(f1));
    } else {
        printf("La méthode n'a pas converge.\n");
    }
}
// Menu principal
int main() {
    setlocale(LC_ALL, " "); // Activer l'affichage des caractères accentués
    int choix, max_iter;
    double a, b, x0, x1, epsilon;

    printf("Resolution de f(x) = x^3 - 4x + 1 = 0\n");
    printf("Choisissez la methode :\n");
    printf("1. Newton-Raphson\n");
    printf("2. Dichotomie\n");
    printf("3. Point fixe\n");
    printf("4. Secante\n");
    printf("5. Toutes les methodes\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    printf("Tolerance (epsilon) : ");
    scanf("%lf", &epsilon);
    printf("Nombre maximal d'iterations : ");
    scanf("%d", &max_iter);

    switch (choix) {
        case 1:
            printf("Approximation initiale x0 : ");
            scanf("%lf", &x0);
            newton_raphson(x0, epsilon, max_iter);
            break;
        case 2:
            printf("Intervalle [a, b] :\n");
            printf("a = ");
            scanf("%lf", &a);
            printf("b = ");
            scanf("%lf", &b);
            dichotomie(a, b, epsilon, max_iter);
            break;
        case 3:
            printf("Entrer une valeur initiale x0 : ");
            scanf("%lf", &x0);
            point_fixe(x0, epsilon, max_iter);
            break;
        case 4:
            printf("Veuillez entrer les valeurs initiales x0 et x1 :\n");
            printf("x0 = ");
            scanf("%lf", &x0);
            printf("x1 = ");
            scanf("%lf", &x1);
            secante(x0, x1, epsilon, max_iter);
            break;
        case 5:
            printf("\n--- Parametres communs pour toutes les methodes ---\n");
            printf("x0 = ");
            scanf("%lf", &x0);
            printf("x1 = ");
            scanf("%lf", &x1);
            printf("a = ");
            scanf("%lf", &a);
            printf("b = ");
            scanf("%lf", &b);

            printf("\n>>> Execution de toutes les methodes <<<\n");
            newton_raphson(x0, epsilon, max_iter);
            dichotomie(a, b, epsilon, max_iter);
            point_fixe(x0, epsilon, max_iter);
            secante(x0, x1, epsilon, max_iter);
            break;
        default:
            printf("Choix invalide.\n");
    }

    return 0;
}

