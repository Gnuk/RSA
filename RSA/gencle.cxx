#include <iostream>
#include <gmpxx.h>

#include <cstdlib>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#include <fstream>
#include <sstream>

#include "utils.h"

using namespace std;

/**
* n = N; t = t_block; p = P; q = Q; a = U; b = C;
* 
**/
int main( int argc, char ** argv )
{
  cout << endl << "** GENERE CLE **" << endl;
  
  // args
  int t_block;
  if (argc < 2)
  {
    cout << "Nombre d'arguments incorrect ( [t] ([fichier]) ) " << endl;;
    exit(1);
  } 

  // taille des blocks
  t_block = atoi(argv[1]);

  // ouverture fichier
  string home =  getenv("HOME");
  const char * filename = "";
  if (argc == 3) {
    filename = argv[2];
  } else {
    filename = (home + "/.my_rsa").c_str();
  }

  ofstream fichier(filename, ios::out | ios::trunc);

  // pick 2 nombre premier P et Q
  // -- init time
  struct timeval tv;
  int val = (int) getpid() + 65536*(int) getppid();
  if ( gettimeofday( &tv, NULL ) == 0 )
    val += (int) (tv.tv_sec*1000000 + tv.tv_usec);

  // -- seed the random generator
  gmp_randclass rr(gmp_randinit_mt);
  rr.seed(val);
  // -- Pick random premier
  mpz_class P = Utils::genereNombrePremierRapide(rr, t_block);
  mpz_class Q = Utils::genereNombrePremierRapide(rr, t_block);
  cout << "# Random variables" << endl;
  cout << "# P --> " << P << endl << "# Q -->" << Q << endl;

  // N = P * Q
  mpz_class N = P * Q;
  cout << "# N (P*Q) --> " << N << endl;

  // M = (P-1)*(Q-1)
  mpz_class M = (P-1)*(Q-1);
  cout << "# M (P-1)*(Q-1) --> " << M << endl;

  // C -> Premier avec M
  mpz_class C = Utils::genereNombrePremierAvecM(rr, M, t_block);
  cout << "# C (generer premier avec M) --> " << C << endl;

  // cle public K = (N,C)  
  cout << "##############################################" << endl << endl;
  cout << "# Votre clé publique N C t est : " << endl  << endl  << N << " " << C << " " << t_block << endl << endl;

  //  U tel que C*U + M*V = 1
  //  U est l'inverse C (bézout)
  mpz_class U = Utils::inverseModulaire(C, M);  
  cout << "# Votre clé privée N U t est : "<< endl << endl << N << " " << U << " " << t_block << endl << endl;

  //écriture dans le fichier
  fichier << t_block << " " << N << " " << P << " " << Q << " " << U << " " << C;
  cout << "Données inscrites dans le fichier : " << filename << endl << endl;

  // Fermeture fichier
  fichier.close();
  // CHMOD (que l'utilisateur peut lire et ecrire)
  chmod(filename, S_IRUSR | S_IWUSR);
}
